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
