/*
  ==============================================================================

    FileDisplayComponents.cpp
    Created: 13 May 2024 5:32:35pm
    Author:  camro

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FileDisplayComponents.h"
#include "UIConfig.h"

//==============================================================================
FileListItem::FileListItem(juce::ValueTree sample_info)
    :m_sample_info(sample_info)
{
    
}

FileListItem::~FileListItem()
{
}

void FileListItem::paint (juce::Graphics& g)
{

}

void FileListItem::resized()
{

}

juce::ValueTree FileListItem::getState()
{
    return m_sample_info.getState(); 
}

//==============================================================================

FileListTable::FileListTable(const SampleLibraryDataModel& sample_library)
    :m_sample_library(sample_library),
     AudioFileDragAndDropTarget(sample_library),
     m_table("FileListTable", this), 
     m_num_rows(0), 
     m_font(14.0f) 
{
    m_sample_library.addListener(*this); 

    addAndMakeVisible(m_add_file_overlay); 

    initTable(); 
    initHeaders(); 
    loadData(); 
}

FileListTable::~FileListTable()
{
    m_sample_library.removeListener(*this); 
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
    m_add_file_overlay.setBounds(bounds); 
}

void FileListTable::initTable()
{
    addAndMakeVisible(m_table);

    m_table.getHeader().setSortColumnId(1, true); 
    m_table.setMultipleSelectionEnabled(false); 
}

void FileListTable::initHeaders()
{
    m_table.getHeader().addColumn("ID", 1, 90, 50, 400, juce::TableHeaderComponent::defaultFlags);
    m_table.getHeader().addColumn("Name", 2, 90, 50, 400, juce::TableHeaderComponent::defaultFlags);
    m_table.getHeader().addColumn("Type", 3, 90, 50, 400, juce::TableHeaderComponent::defaultFlags); 
}

void FileListTable::loadData()
{
    m_data_list = m_sample_library.getState().createXml(); 
    m_num_rows = m_data_list->getNumChildElements();
}

int FileListTable::getNumRows()
{ 
    return m_num_rows; 
}

juce::String FileListTable::getAttributeNameForColumnId(const int column_id) const
{
    if (column_id == 1)
        return "id";
    else if (column_id == 2)
        return "name";
    else if (column_id == 3)
        return "file_extension"; 

    return {};
}

void FileListTable::paintRowBackground(juce::Graphics& g, int row_number, 
    int width, int height, bool row_is_selected)
{
    juce::Colour alternate_colour = getLookAndFeel().findColour(AppColors::Surface1dp);

    if (row_is_selected)
    {
        g.fillAll(getLookAndFeel().findColour(AppColors::PrimaryFocused));
        g.setColour(getLookAndFeel().findColour(AppColors::Primary));  
    }

}

void FileListTable::paintCell(juce::Graphics& g, int row_number, 
    int column_id, int width, int height, bool row_is_selected)
{
    g.setColour(row_is_selected ? getLookAndFeel().findColour(AppColors::Primary) : getLookAndFeel().findColour(AppColors::OnBackground));
    g.setFont(m_font);

    if (auto* rowElement = m_data_list->getChildElement(row_number))
    {
        auto& text = rowElement->getStringAttribute(getAttributeNameForColumnId(column_id));

        g.drawText(text, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    }
}

void FileListTable::SampleAdded(const SampleInfoDataModel& addedSample)
{
    loadData(); 
    m_table.updateContent();
    m_table.autoSizeAllColumns();
    m_table.repaint(); 
}

int FileListTable::getColumnAutoSizeWidth(int columnId)
{
    int widest = 32;

    for (auto i = getNumRows(); --i >= 0;)
    {
        if (auto* rowElement = m_data_list->getChildElement(i))
        {
            auto& text = rowElement->getStringAttribute(getAttributeNameForColumnId(columnId));

            widest = juce::jmax(widest, m_font.getStringWidth(text));
        }
    }

    return widest + spacing::padding2;
}

void FileListTable::fileDragEnter(const juce::StringArray&, int, int)
{
    juce::ComponentAnimator& animator = juce::Desktop::getInstance().getAnimator(); 
    animator.fadeIn(&m_add_file_overlay, 200); 
    repaint(); 
}

void FileListTable::fileDragExit(const juce::StringArray&)
{
    juce::ComponentAnimator& animator = juce::Desktop::getInstance().getAnimator(); 
    animator.fadeOut(&m_add_file_overlay, 200); 

    repaint(); 
}
