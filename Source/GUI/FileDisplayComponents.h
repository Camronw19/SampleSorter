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
#include "UIConfig.h"

class FileListTable : public juce::Component, 
                      public juce::TableListBoxModel
{
public:

    FileListTable(const SampleLibraryDataModel&);
    ~FileListTable() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void setDataModel(std::shared_ptr<juce::XmlElement>); 
    void setSelectedRowChangedCallback(std::function<void(int)>); 

    int getSelection(const int) const; 
    void setSelection(const int row_number, const int new_selection); 

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
    juce::Component* refreshComponentForCell(int, int, bool, juce::Component*) override; 

    SampleLibraryDataModel m_sample_library; 
    std::shared_ptr<juce::XmlElement> m_sample_library_xml;
    int m_num_rows;

    // Components
    juce::TableListBox m_table;
    juce::Font m_font; 

    std::function<void(int)> activeFileCallback; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FileListTable)
};

class StarToggle : public juce::Component
{
public:  
    StarToggle(FileListTable&); 
    ~StarToggle(); 

    void resized() override; 

    void setRowAndColumn(int, int);

private: 
    class StarToggleLookAndFeel : public DarkLookAndFeel
    {
    public:
        void drawToggleButton(juce::Graphics& g, juce::ToggleButton& button,
            bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    };


    FileListTable& m_owner;
    juce::ToggleButton m_toggle_button; 

    int m_row; 
    int m_column_id; 

    StarToggleLookAndFeel m_star_toggle_lnf; 
};
