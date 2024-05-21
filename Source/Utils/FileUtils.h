/*
  ==============================================================================

    FileUtils.h
    Created: 12 May 2024 11:07:39am
    Author:  camro

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SampleLibrary.h"

class AudioFileDragAndDropTarget : public juce::FileDragAndDropTarget
{
public: 
    explicit AudioFileDragAndDropTarget(const SampleLibraryDataModel&);

private:
    bool isInterestedInFileDrag(const juce::StringArray&);
    void filesDropped(const juce::StringArray&, int, int);
    virtual void fileDragEnter(const juce::StringArray&, int, int);
    virtual void fileDragExit(const juce::StringArray&); 

    SampleLibraryDataModel m_sample_library; 
};


class AddFileOverlay : public juce::Component,
                       public juce::ComponentAnimator
{
public:
    AddFileOverlay();
    ~AddFileOverlay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private: 

};

class AudioFileChooser
{
public: 
    explicit AudioFileChooser(const SampleLibraryDataModel&); 

protected: 
    void browseMultipleFiles();

private: 
    void addFile(const juce::File&); 
    void addFilesFromDirectory(const juce::File&); 

    const juce::String m_audio_file_patterns = "*.wav;*.mp3;*.aiff;*.flac;*.ogg;*.m4a;*.aac";
    int m_file_chooser_flags;

    juce::FileChooser m_file_choooser; 
    SampleLibraryDataModel m_sample_library; 
};
