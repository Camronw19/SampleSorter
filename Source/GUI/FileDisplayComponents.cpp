/*
  ==============================================================================

    FileDisplayComponents.cpp
    Created: 13 May 2024 5:32:35pm
    Author:  camro

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FileDisplayComponents.h"

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
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    juce::String name = m_sample_info.getName(); 
    g.drawText (name, getLocalBounds(),
                juce::Justification::centred, true);
}

void FileListItem::resized()
{

}

juce::ValueTree FileListItem::getState()
{
    return m_sample_info.getState(); 
}

//==============================================================================
FileList::FileList(juce::ValueTree sample_library)
    : m_sample_library(sample_library), ValueTreeObjectList<FileListItem>(sample_library)
{
    rebuildObjects(); 
}

FileList::~FileList()
{
    freeObjects(); 
}

void FileList::paint(juce::Graphics&)
{

}

void FileList::resized()
{
    auto bounds = getLocalBounds(); 
    auto component_height = bounds.getHeight() / m_sample_library.getState().getNumChildren(); 

    for (auto& object : m_objects)
    {
        object->setBounds(bounds.removeFromTop(component_height));
    }
}


bool FileList::isSuitableType(const juce::ValueTree& sample_info) const
{
    return sample_info.hasType(ModelIdentifiers::SAMPLE_INFO);
}

FileListItem* FileList::createNewObject(const juce::ValueTree& vt)
{
    FileListItem* file_list_item = new FileListItem(vt); 
    addAndMakeVisible(file_list_item); 
    return file_list_item; 
}

void FileList::deleteObject(FileListItem* file_list_item)
{
    delete file_list_item; 
}

void FileList::newObjectAdded(FileListItem*)
{
    repaint();
}

void FileList::objectRemoved(FileListItem*)
{
    repaint();
}

void FileList::objectOrderChanged()
{
    repaint(); 
}

//==============================================================================

FileListTable::FileListTable(juce::ValueTree vt)
    :m_sample_library(vt),
     m_table("FileListTable", this), 
     m_num_rows(0)
{
    m_sample_library.addListener(*this); 

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
    auto bounds = getBounds();
    g.setColour(juce::Colours::aliceblue); 
    g.drawRect(bounds); 
}

void FileListTable::resized()
{
    auto bounds = getBounds(); 
    m_table.setBounds(bounds); 
}

void FileListTable::initTable()
{
    addAndMakeVisible(m_table);

    m_table.setColour(juce::ListBox::outlineColourId, juce::Colours::grey); 
    m_table.setOutlineThickness(1); 
    m_table.getHeader().setSortColumnId(1, true); 
    m_table.setMultipleSelectionEnabled(true); 
}

void FileListTable::initHeaders()
{
    m_table.getHeader().addColumn("ID", 1, 90, 50, 400, juce::TableHeaderComponent::defaultFlags);
    m_table.getHeader().addColumn("Name", 2, 90, 50, 400, juce::TableHeaderComponent::defaultFlags);
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

    return {};
}

void FileListTable::paintRowBackground(juce::Graphics& g, int row_number, 
    int width, int height, bool row_is_selected)
{
    juce::Colour alternate_colour = getLookAndFeel().findColour(juce::ListBox::backgroundColourId).
        interpolatedWith(getLookAndFeel().
            findColour(juce::ListBox::textColourId), 0.03f); 

    if (row_is_selected)
        g.fillAll(juce::Colours::lightblue);
    else if (row_number % 2)
        g.fillAll(alternate_colour); 

}

void FileListTable::paintCell(juce::Graphics& g, int row_number, 
    int column_id, int width, int height, bool row_is_selected)
{
    g.setColour(row_is_selected ? juce::Colours::darkblue : getLookAndFeel().findColour(juce::ListBox::textColourId));  // [5]
    g.setFont(juce::Font {14.0f});

    if (auto* rowElement = m_data_list->getChildElement(row_number))
    {
        auto text = rowElement->getStringAttribute(getAttributeNameForColumnId(column_id));

        g.drawText(text, 2, 0, width - 4, height, juce::Justification::centredLeft, true);                             // [6]
    }

    g.setColour(getLookAndFeel().findColour(juce::ListBox::backgroundColourId));
    g.fillRect(width - 1, 0, 1, height);
}

void FileListTable::SampleAdded(const SampleInfoDataModel& addedSample)
{
    loadData(); 
}