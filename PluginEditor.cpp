/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
GainPlugAudioProcessorEditor::GainPlugAudioProcessorEditor (GainPlugAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (150, 300);
    setResizable(false, false);
    //audioProcessor.bypass = false;



    gainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "Gain", gain);



    
    gainRange.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    gainRange.setRange(6, 48, 6);
    gainRange.setValue(12);
    gainRange.setTextValueSuffix(" dB");
    gainRange.setDoubleClickReturnValue(true, 12);
    gainRange.addListener(this);

    addAndMakeVisible(gainRange);

    Range = gainRange.getValue();

    gain.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    gain.setRange(-Range, Range, 0.1f);
    gain.setValue(0.0f);
    gain.setTextValueSuffix(" dB");
    gain.setDoubleClickReturnValue(true, 0.0f);
    gain.addListener(this);

    addAndMakeVisible(gain);


    
    bypassButton.addListener(this);
    bypassButton.setClickingTogglesState(true);
    bypassButton.setToggleState(true, juce::sendNotification);
    bypassButton.setButtonText("Bypass Off");
    bypassButton.setColour(bypassButton.buttonOnColourId, juce::Colours::darkseagreen);
    bypassButton.setColour(bypassButton.buttonColourId, juce::Colours::darkred);
    bypassButton.setColour(bypassButton.textColourOnId, juce::Colours::lightgrey);
    bypassButton.setColour(bypassButton.textColourOffId, juce::Colours::black);
    bypassButton.setState(juce::Button::buttonNormal);


    bypassButton.onClick = [this]() {BypassButtonClicked(); };

    addAndMakeVisible(bypassButton);


    advanceButton.setClickingTogglesState(true);
    advanceButton.setToggleState(false, juce::dontSendNotification);
    advanceButton.setColour(bypassButton.buttonOnColourId, juce::Colours::azure);
    advanceButton.setColour(bypassButton.buttonColourId, juce::Colours::grey);
    advanceButton.setColour(bypassButton.textColourOnId, juce::Colours::azure);
    advanceButton.setColour(bypassButton.textColourOffId, juce::Colours::grey);

    advanceButton.onClick = [this]() {Advance(); };

    addAndMakeVisible(advanceButton);

}

GainPlugAudioProcessorEditor::~GainPlugAudioProcessorEditor()
{
}

//==============================================================================
void GainPlugAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    g.setFont (24.0f);
    g.drawFittedText("RANGE", 160, 10, 80, 25, juce::Justification::centred, 1, 0.0f);

    gain.setBounds(50, 30, 50, 200);
    gainRange.setBounds(187, 40, 26, 100);

    bypassButton.setBounds(25,250,100,25);
    advanceButton.setBounds(130, 140, 20, 20);

    
}

void GainPlugAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void GainPlugAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{

    if (slider == &gain)
    {
        audioProcessor.coefficient = pow(2, gain.getValue() / 6);
    }

    if (slider == &gainRange)
    {
        Range = gainRange.getValue();
        gain.setRange(-Range, Range, 0.1f);
    }
    

}

void GainPlugAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    
}

void GainPlugAudioProcessorEditor::BypassButtonClicked()
{
    if (audioProcessor.CurrentBypassState == GainPlugAudioProcessor::BypassState::normal)
    {
        audioProcessor.CurrentBypassState = GainPlugAudioProcessor::BypassState::bypass;
        bypassButton.setButtonText("Bypass On");
    }
    else
    {
        audioProcessor.CurrentBypassState = GainPlugAudioProcessor::BypassState::normal;
        bypassButton.setButtonText("Bypass Off");
    }
}

void GainPlugAudioProcessorEditor::Advance()
{
    if (advance == AdvanceState::on)
    {
        advance = AdvanceState::off;
        setSize(150, 300);
    }
    else
    {
        advance = AdvanceState::on;
        setSize(250, 300);
    }
}