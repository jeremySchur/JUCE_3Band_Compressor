/*
  ==============================================================================

    Compressor.h
    Created: 24 May 2025 12:36:44pm
    Author:  jerem

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class CompressorBand
{
public:
    CompressorBand();
    ~CompressorBand();

    void prepare(const juce::dsp::ProcessSpec& spec);
    void updateCompressorSettings();
    void process(juce::AudioBuffer<float>& buffer);

    juce::AudioParameterFloat* attack{ nullptr };
    juce::AudioParameterFloat* release{ nullptr };
    juce::AudioParameterFloat* threshold{ nullptr };
    juce::AudioParameterChoice* ratio{ nullptr };
    juce::AudioParameterBool* bypassed{ nullptr };
    juce::AudioParameterBool* mute{ nullptr };
    juce::AudioParameterBool* solo{ nullptr };

private:
    juce::dsp::Compressor<float> compressor;
};