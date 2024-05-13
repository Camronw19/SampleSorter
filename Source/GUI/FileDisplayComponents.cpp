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

    for (auto& object : objects)
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
