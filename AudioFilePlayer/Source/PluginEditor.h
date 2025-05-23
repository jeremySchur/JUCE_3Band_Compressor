/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "TransportState.h"

//==============================================================================
/**
*/
class AudioFilePlayerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    AudioFilePlayerAudioProcessorEditor (AudioFilePlayerAudioProcessor&);
    ~AudioFilePlayerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioFilePlayerAudioProcessor& audioProcessor;

    juce::TextButton openButton;
    juce::TextButton playButton;
    juce::TextButton stopButton;

    std::unique_ptr<juce::FileChooser> chooser;

    juce::AudioParameterChoice* stateParam{ nullptr };

    void openButtonClicked();
    void playButtonClicked();
    void stopButtonClicked();
    void changeState(int newState);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioFilePlayerAudioProcessorEditor)
};
