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
#include "FileUtils.h"

class SampleLibraryView : public juce::Component, 
                          public SampleLibraryDataModel::Listener
{
public:
    virtual ~SampleLibraryView(); 
    SampleLibraryView(const SampleLibraryDataModel&); 

    void paint(juce::Graphics&) override; 
    void resized() override; 

protected: 
    SampleLibraryDataModel m_sample_library;

private: 
    virtual void SampleAdded(const SampleInfoDataModel&) = 0; 

};

class FileListTable : public SampleLibraryView,
                      public juce::TableListBoxModel, 
                      public AudioFileDragAndDropTarget
{
public:
    FileListTable(const SampleLibraryDataModel&);
    ~FileListTable() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    // m_table component methods
    int getNumRows() override;
    int getColumnAutoSizeWidth(int) override; 
    void paintCell(juce::Graphics&, int, int, int, int, bool) override;
    void paintRowBackground(juce::Graphics&, int, int, int, bool) override;
    void sortOrderChanged(int, bool) override; 
    void loadData(); 
    void initTable();
    void initHeaders();
    juce::String getAttributeNameForColumnId(const int) const;

    // File dnd methods
    void fileDragEnter(const juce::StringArray&, int, int) override;
    void fileDragExit(const juce::StringArray&) override; 

    // Data model methods
    void SampleAdded(const SampleInfoDataModel&) override; 

    // Data models
    std::unique_ptr<juce::XmlElement> m_data_list;
    int m_num_rows;

    // Components
    juce::TableListBox m_table;
    AddFileOverlay m_add_file_overlay; 
    juce::Font m_font; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FileListTable)
};


