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
     m_file_list(sample_library),
     AudioFileDragAndDropTarget(sample_library), 
     m_prev_search_length(0)
{
    m_sample_library.addListener(*this); 

    m_sample_library_xml = std::move(m_sample_library.getState().createXml()); 

    addAndMakeVisible(m_file_list); 
    m_file_list.setSelectedRowChangedCallback([this](int row) { onFileListRowSelected(row); });

    addAndMakeVisible(m_search_bar); 
    m_search_bar.addListener(this); 

    addAndMakeVisible(m_filter_select);
    m_filter_select.setButtonText("Select Filters");
    m_filter_select.addItem("Favorite", 1); 
    m_filter_select.addSeparator();
    m_filter_select.addItem("Kicks", 2); 
    m_filter_select.addItem("Snares", 3); 
    m_filter_select.addItem("Hats", 4); 
    m_filter_select.addItem("Percs", 5); 


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

    auto search_filter_bounds = bounds.removeFromTop(30); 
    
    m_search_bar.setBounds(search_filter_bounds.removeFromLeft(bounds.getWidth() / 3)); 
    search_filter_bounds.removeFromLeft(spacing::padding1); 
    m_filter_select.setBounds(search_filter_bounds.removeFromLeft(bounds.getWidth() / 3));

    bounds.removeFromTop(spacing::padding1); 

    m_file_list.setBounds(bounds); 
    m_add_file_overlay.setBounds(bounds); 
}

void FileExplorer::textEditorTextChanged(juce::TextEditor& text_editor)
{
    if (&text_editor == &m_search_bar)
    {
        juce::String search_text = m_search_bar.getText();
        
        // Use previous filtered XML if user is adding to search, otherwise regenerate 
        if (search_text.length() < m_prev_search_length || m_prev_search_length == 0)
            m_sample_library_xml_filtered = std::make_shared<juce::XmlElement>(*m_sample_library_xml); 

        m_prev_search_length = search_text.length();

        m_fuzzy_search_filter.filter(m_sample_library_xml_filtered, search_text); 
        m_file_list.setDataModel(m_sample_library_xml_filtered); 
    }
}

void FileExplorer::sampleAdded(const SampleInfoDataModel& added_sample)
{
     // Add sample to XML state
     std::unique_ptr<juce::XmlElement> added_sample_xml = added_sample.getState().createXml(); 
     m_sample_library_xml->addChildElement(added_sample_xml.release());

     m_file_list.setDataModel(m_sample_library_xml);
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

