/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioFilePlayerAudioProcessorEditor::AudioFilePlayerAudioProcessorEditor (AudioFilePlayerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    stateParam = dynamic_cast<juce::AudioParameterChoice*>(audioProcessor.apvts.getParameter("TransportState"));
    jassert(stateParam != nullptr);

    audioProcessor.filePlayer.onTransportStateChanged = [this](int newState)
    {
        changeState(newState);
    };

    addAndMakeVisible(&openButton);
    openButton.setButtonText("Open...");
    openButton.onClick = [this] { openButtonClicked(); };

    addAndMakeVisible(&playButton);
    playButton.setButtonText("Play");
    playButton.onClick = [this] { playButtonClicked(); };
    playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    playButton.setEnabled(false);

    addAndMakeVisible(&stopButton);
    stopButton.setButtonText("Stop");
    stopButton.onClick = [this] { stopButtonClicked(); };
    stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    stopButton.setEnabled(false);

    setSize(480, 270);
}

AudioFilePlayerAudioProcessorEditor::~AudioFilePlayerAudioProcessorEditor()
{
}

//==============================================================================
void AudioFilePlayerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void AudioFilePlayerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto bounds = getLocalBounds().reduced(10);
    int buttonWidth = 100;
    int buttonHeight = 30;
    int spacing = 10;

    int totalWidth = buttonWidth * 3 + spacing * 2;
    int startX = (bounds.getWidth() - totalWidth) / 2;
    int startY = (bounds.getHeight() - buttonHeight) / 2;

    playButton.setBounds(startX, startY, buttonWidth, buttonHeight);
    stopButton.setBounds(startX + buttonWidth + spacing, startY, buttonWidth, buttonHeight);
    openButton.setBounds(startX + (buttonWidth + spacing) * 2, startY, buttonWidth, buttonHeight);
}

void AudioFilePlayerAudioProcessorEditor::openButtonClicked()
{
    chooser = std::make_unique<juce::FileChooser>("Select a file to play...",
        juce::File{},
        "*.wav;*.aif;*.aiff");

    auto chooserFlags = juce::FileBrowserComponent::openMode
        | juce::FileBrowserComponent::canSelectFiles;

    chooser->launchAsync(chooserFlags, [this](const juce::FileChooser& fc)
        {
            auto file = fc.getResult();
            audioProcessor.filePlayer.loadFile(file);
            playButton.setEnabled(true);
            changeState(Stopped);
        });
}

void AudioFilePlayerAudioProcessorEditor::playButtonClicked()
{
    auto currentState = stateParam->getIndex();

    if ((currentState == Stopped) || (currentState == Paused)) {
        changeState(Starting);
    }
    else if (currentState == Playing) {
        changeState(Pausing);
    }
}

void AudioFilePlayerAudioProcessorEditor::stopButtonClicked()
{
    auto currentState = stateParam->getIndex();

    if (currentState == Paused) {
        changeState(Stopped);
    }
    else {
        changeState(Stopping);
    }
}

void AudioFilePlayerAudioProcessorEditor::changeState(int newState)
{
    auto currentState = stateParam->getIndex();

    if (currentState != newState) {
        switch (newState) {
        case Stopped:
            playButton.setButtonText("Play");
            stopButton.setButtonText("Stop");
            stopButton.setEnabled(false);
            audioProcessor.filePlayer.setTransportPosition(0.0);
            break;
        case Starting:
            audioProcessor.filePlayer.start();
            break;
        case Playing:
            playButton.setButtonText("Pause");
            stopButton.setButtonText("Stop");
            stopButton.setEnabled(true);
            break;
        case Pausing:
            audioProcessor.filePlayer.stop();
            break;
        case Paused:
            playButton.setButtonText("Resume");
            stopButton.setButtonText("Restart");
            break;
        case Stopping:
            audioProcessor.filePlayer.stop();
            break;
        default:
            return;
        }

        stateParam->beginChangeGesture();
        stateParam->setValueNotifyingHost(stateParam->convertTo0to1(newState));
        stateParam->endChangeGesture();
    }
}