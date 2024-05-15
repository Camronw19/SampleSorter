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

class FileListTable : public juce::Component,
                      public juce::TableListBoxModel, 
                      public SampleLibraryDataModel::Listener
{
public:
    FileListTable(juce::ValueTree);
    ~FileListTable() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    // 

private:
    // m_table component methods
    void initTable();
    void initHeaders();
    void loadData(); 
    int getNumRows() override;
    void paintRowBackground(juce::Graphics&, int, int, int, bool) override;
    void paintCell(juce::Graphics&, int, int, int, int, bool) override;
    int getColumnAutoSizeWidth(int) override; 
    juce::String getAttributeNameForColumnId(const int) const;

    void SampleAdded(const SampleInfoDataModel&) override; 

    // Data models
    SampleLibraryDataModel m_sample_library;
    std::unique_ptr<juce::XmlElement> m_data_list;
    int m_num_rows;

    juce::TableListBox m_table;
    juce::Font m_font; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FileListTable)
};


