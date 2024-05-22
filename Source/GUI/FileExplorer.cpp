/*
  ==============================================================================

    FileExplorer.cpp
    Created: 13 May 2024 6:20:10pm
    Author:  camro

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FileExplorer.h"
#include "UIConfig.h"

//==============================================================================
FileExplorer::FileExplorer(const SampleLibraryDataModel& sample_library)
    :m_sample_library(sample_library), 
    AudioFileDragAndDropTarget(sample_library)
{
      generateXML(); 
      m_sample_library.addListener(*this); 

      addAndMakeVisible(m_file_list); 
      setFileListData(); 
      m_file_list.setSelectedRowChangedCallback([this](int row) { onFileListRowSelected(row); });

      addAndMakeVisible(m_search_bar); 
      m_search_bar.addListener(this); 

      addAndMakeVisible(m_add_file_overlay); 
      m_add_file_overlay.setVisible(false); 
}

FileExplorer::~FileExplorer()
{
    m_sample_library.removeListener(*this); 
}

void FileExplorer::paint (juce::Graphics& g)
{

}

void FileExplorer::resized()
{
    auto bounds = getLocalBounds(); 
    
    m_search_bar.setBounds(bounds.removeFromTop(30)); 
    bounds.removeFromTop(spacing::padding1); 

    m_file_list.setBounds(bounds); 
    m_add_file_overlay.setBounds(bounds); 
}


void FileExplorer::textEditorTextChanged(juce::TextEditor& text_editor)
{
    if (&text_editor == &m_search_bar)
    {
        m_search_bar.isEmpty() ? m_search_is_active = false : m_search_is_active = true; 

        std::unique_ptr<juce::XmlElement> sample_library_filtered_xml = std::make_unique<juce::XmlElement>(*m_sample_library_xml); 
        m_fuzzy_search_filter.filter(sample_library_filtered_xml, m_search_bar.getText()); 
        m_file_list.setDataModel(std::move(sample_library_filtered_xml)); 
    }
}

void FileExplorer::sampleAdded(const SampleInfoDataModel& added_sample)
{
     // Add sample to XML state
     std::unique_ptr<juce::XmlElement> added_sample_xml = added_sample.getState().createXml(); 
     m_sample_library_xml->addChildElement(added_sample_xml.release());

     // Copy XML state to m_file_list
     std::unique_ptr<juce::XmlElement> sample_library_xml = std::make_unique<juce::XmlElement>(*m_sample_library_xml); 
     m_file_list.setDataModel(std::move(sample_library_xml));
}

void FileExplorer::setFileListData()
{
}

void FileExplorer::generateXML()
{
   m_sample_library_xml = m_sample_library.getState().createXml(); 
}

void FileExplorer::fileDragEnter(const juce::StringArray&, int, int)
{
    m_add_file_overlay.setVisible(true);
    juce::ComponentAnimator& animator = juce::Desktop::getInstance().getAnimator(); 
    animator.fadeIn(&m_add_file_overlay, 200); 
    repaint(); 
}

void FileExplorer::fileDragExit(const juce::StringArray&)
{
    m_add_file_overlay.setVisible(false);
    juce::ComponentAnimator& animator = juce::Desktop::getInstance().getAnimator(); 
    animator.fadeOut(&m_add_file_overlay, 200); 
    repaint(); 
}


void FileExplorer::onFileListRowSelected(int selected_file_id)
{
    m_sample_library.setActiveFile(selected_file_id); 
}

