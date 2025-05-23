/*
  ==============================================================================

    FilePlayer.cpp
    Created: 23 May 2025 4:31:46pm
    Author:  jerem

  ==============================================================================
*/

#include "FilePlayer.h"

FilePlayer::FilePlayer(juce::AudioProcessorValueTreeState& apvts)
	: apvts(apvts)
{
	formatManager.registerBasicFormats();
	transportSource.addChangeListener(this);
}

FilePlayer::~FilePlayer()
{
	transportSource.removeChangeListener(this);
	transportSource.releaseResources();
}

void FilePlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void FilePlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	if (readerSource.get() == nullptr)
	{
		bufferToFill.clearActiveBufferRegion();
		return;
	}

	transportSource.getNextAudioBlock(bufferToFill);
}

void FilePlayer::releaseResources()
{
	transportSource.releaseResources();
}

void FilePlayer::start()
{
	transportSource.start();
}

void FilePlayer::stop()
{
	transportSource.stop();
}

bool FilePlayer::isPlaying()
{
	return transportSource.isPlaying();
}

void FilePlayer::loadFile(const juce::File& file)
{
	if (file != juce::File{})
	{
		auto* reader = formatManager.createReaderFor(file);

		if (reader != nullptr)
		{
			auto newSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
			transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
			readerSource.reset(newSource.release());
		}
	}
}

void FilePlayer::setTransportPosition(double pos)
{
	transportSource.setPosition(pos);
}

void FilePlayer::changeListenerCallback(juce::ChangeBroadcaster* source)
{
	auto* stateParam = dynamic_cast<juce::AudioParameterChoice*>(apvts.getParameter("TransportState"));
	auto currentState = stateParam != nullptr ? stateParam->getIndex() : -1;

	if (source == &transportSource)
	{
		if (transportSource.isPlaying()) {
			onTransportStateChanged(Playing);
		}
		else if ((currentState == Stopping) || (currentState == Playing)) {
			onTransportStateChanged(Stopped);
		}
		else if (currentState == Pausing) {
			onTransportStateChanged(Paused);
		}
	}
}
