/*
  ==============================================================================

    FileDisplayComponents.h
    Created: 13 May 2024 5:32:35pm
    Author:  camro

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SampleInfo.h"
#include "SampleLibrary.h"
#include "ValueTreeObjectList.h"

class FileListItem  : public juce::Component
{
public:
    FileListItem(juce::ValueTree);
    ~FileListItem() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    juce::ValueTree getState(); 

private:
    SampleInfoDataModel m_sample_info; 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FileListItem)
};

class FileList : public juce::Component,
    public ValueTreeObjectList<FileListItem>
{
public:
    FileList(juce::ValueTree);
    ~FileList() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    SampleLibraryDataModel m_sample_library; 

    // ValueTreeObjectList methods
    bool isSuitableType(const juce::ValueTree&) const override;
    FileListItem* createNewObject(const juce::ValueTree&) override;
    void deleteObject(FileListItem*) override;
    void newObjectAdded(FileListItem*) override;
    void objectRemoved(FileListItem*) override;
    void objectOrderChanged() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FileList)
};


