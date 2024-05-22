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

class FileListTable : public juce::Component, 
                      public juce::TableListBoxModel
{
public:

    FileListTable();
    ~FileListTable() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void setDataModel(std::unique_ptr<juce::XmlElement>); 
    void setSelectedRowChangedCallback(std::function<void(int)>); 

private:
    void dataChanged(); 

    // m_table component methods
    int getNumRows() override;
    int getColumnAutoSizeWidth(int) override; 
    void paintCell(juce::Graphics&, int, int, int, int, bool) override;
    void paintRowBackground(juce::Graphics&, int, int, int, bool) override;
    void sortOrderChanged(int, bool) override; 
    void selectedRowsChanged(int) override;
    void initTable();
    void initTableHeaders();
    juce::String getAttributeNameForColumnId(const int) const;


    std::unique_ptr<juce::XmlElement> m_sample_library_xml;
    int m_num_rows;

    // Components
    juce::TableListBox m_table;
    juce::Font m_font; 

    std::function<void(int)> activeFileCallback; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FileListTable)
};


