/*
  ==============================================================================

    FilePlayer.h
    Created: 23 May 2025 4:31:59pm
    Author:  jerem

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "TransportState.h"

class FilePlayer : public juce::AudioSource,
				   public juce::ChangeListener
{
public:
	FilePlayer(juce::AudioProcessorValueTreeState& apvts);
	~FilePlayer() override;

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
	void releaseResources();

	void start();
	void stop();
	bool isPlaying();
	void loadFile(const juce::File& file);
	void setTransportPosition(double pos);

	void changeListenerCallback(juce::ChangeBroadcaster* source) override;

	std::function<void(int)> onTransportStateChanged;

private:
	juce::AudioProcessorValueTreeState& apvts;

	std::unique_ptr<juce::FileChooser> chooser;
	juce::AudioFormatManager formatManager;
	std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
	juce::AudioTransportSource transportSource;
};
