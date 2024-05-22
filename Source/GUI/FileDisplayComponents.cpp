/*
  ==============================================================================

    FileDisplayComponents.cpp
    Created: 13 May 2024 5:32:35pm
    Author:  Camron

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FileDisplayComponents.h"
#include "UIConfig.h"
#include "DataSorting.h"

FileListTable::FileListTable()
    : m_table("FileListTable", this), 
      m_num_rows(0), 
      m_font(fonts::base) 
{
    initTable(); 
    initTableHeaders(); 
}

FileListTable::~FileListTable()
{
}

void FileListTable::paint(juce::Graphics& g)
{
    g.setColour(getLookAndFeel().findColour(AppColors::Surface1dp));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), rounding::rounding1);
}

void FileListTable::resized()
{
    juce::Rectangle<int> bounds = getLocalBounds(); 
    m_table.setBounds(bounds.reduced(0, spacing::padding1));
}

void FileListTable::setDataModel(std::shared_ptr<juce::XmlElement> sample_library)
{
    m_sample_library_xml = sample_library; 
    dataChanged(); 
}

void FileListTable::initTable()
{
    addAndMakeVisible(m_table);

    m_table.getHeader().setSortColumnId(1, true); 
    m_table.setMultipleSelectionEnabled(false); 
}

void FileListTable::initTableHeaders()
{
    m_table.getHeader().addColumn("ID", 1, 90, 50, 400, juce::TableHeaderComponent::defaultFlags);
    m_table.getHeader().addColumn("Name", 2, 90, 50, 400, juce::TableHeaderComponent::defaultFlags);
    m_table.getHeader().addColumn("Type", 3, 90, 50, 400, juce::TableHeaderComponent::defaultFlags); 
}

int FileListTable::getNumRows()
{ 
    return m_num_rows; 
}

juce::String FileListTable::getAttributeNameForColumnId(const int column_id) const
{
    if (column_id == 1)
        return ModelIdentifiers::id.toString();
    else if (column_id == 2)
        return ModelIdentifiers::name.toString();
    else if (column_id == 3)
        return ModelIdentifiers::file_extension.toString(); 

    return {};
}

void FileListTable::paintRowBackground(juce::Graphics& g, int row_number, 
    int width, int height, bool row_is_selected)
{
    if (row_is_selected)
        g.fillAll(getLookAndFeel().findColour(AppColors::PrimaryFocused));
}

void FileListTable::paintCell(juce::Graphics& g, int row_number, 
    int column_id, int width, int height, bool row_is_selected)
{
    if (m_sample_library_xml != nullptr)
    {
        g.setColour(row_is_selected ? getLookAndFeel().findColour(AppColors::Primary) : getLookAndFeel().findColour(AppColors::OnBackground));
        g.setFont(m_font);

        if (auto* row_element = m_sample_library_xml->getChildElement(row_number))
        {
            auto& text = row_element->getStringAttribute(getAttributeNameForColumnId(column_id));
            g.drawText(text, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
        }
    }
}


void FileListTable::sortOrderChanged(int new_sort_col_id, bool forwards)
{
    if (new_sort_col_id != 0)
    {
        CompareNaturalStringSorter sorter(getAttributeNameForColumnId(new_sort_col_id), "id", forwards);
        m_sample_library_xml->sortChildElements(sorter); 
        m_table.updateContent(); 
    }
}


void FileListTable::selectedRowsChanged(int row)
{
    juce::XmlElement* selected_xml_element = m_sample_library_xml->getChildElement(row); 

    if (selected_xml_element != nullptr)
    {
        int selected_file_id = selected_xml_element->getIntAttribute("id");
        activeFileCallback(selected_file_id); 
    }
}

void FileListTable::dataChanged()
{
    m_num_rows = m_sample_library_xml->getNumChildElements();
    m_table.updateContent();
    m_table.autoSizeAllColumns();
    m_table.repaint(); 
}

int FileListTable::getColumnAutoSizeWidth(int columnId)
{
    int widest = 32;

    if (m_sample_library_xml != nullptr)
    {
        for (auto i = getNumRows(); --i >= 0;)
        {
            if (auto* row_element = m_sample_library_xml->getChildElement(i))
            {
                auto& text = row_element->getStringAttribute(getAttributeNameForColumnId(columnId));
                widest = juce::jmax(widest, m_font.getStringWidth(text));
            }
        }

    }

    return widest + spacing::padding2;
}

void FileListTable::setSelectedRowChangedCallback(std::function<void(int)> callback)
{
    activeFileCallback = callback; 
}
