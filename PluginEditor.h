/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <memory>


//==============================================================================
/*
*/
class GainPlugAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                      public juce::Slider::Listener,
                                      public juce::TextButton::Listener
{
public:
    GainPlugAudioProcessorEditor (GainPlugAudioProcessor&);
    ~GainPlugAudioProcessorEditor() override;

    //==============================================================================


    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button*) override;

    float Range;


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GainPlugAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainPlugAudioProcessorEditor)

    juce::Slider gain;

    juce::Slider gainRange;

    juce::TextButton bypassButton{"Bypass Button"};
    juce::TextButton advanceButton{"Advance Button"};

    void BypassButtonClicked();

    void Advance();

    enum class AdvanceState
    {
        on, off
    };

    AdvanceState advance = AdvanceState::off;

public:
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainSliderAttachment;
};
