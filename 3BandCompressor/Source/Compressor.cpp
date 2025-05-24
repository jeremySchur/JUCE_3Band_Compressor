/*
  ==============================================================================

    Compressor.cpp
    Created: 24 May 2025 12:36:37pm
    Author:  jerem

  ==============================================================================
*/

#include "Compressor.h"

CompressorBand::CompressorBand()
{
}

CompressorBand::~CompressorBand()
{
}


void CompressorBand::prepare(const juce::dsp::ProcessSpec& spec)
{
    compressor.prepare(spec);
}

void CompressorBand::updateCompressorSettings()
{
    compressor.setAttack(attack->get());
    compressor.setRelease(release->get());
    compressor.setThreshold(threshold->get());
    compressor.setRatio(ratio->getCurrentChoiceName().getFloatValue());
}

void CompressorBand::process(juce::AudioBuffer<float>& buffer)
{
    auto block = juce::dsp::AudioBlock<float>(buffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(block);

    context.isBypassed = bypassed->get();

    compressor.process(context);
}