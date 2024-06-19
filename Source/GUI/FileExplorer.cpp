/*
  ==============================================================================

    FileExplorer.cpp
    Created: 13 May 2024 6:20:10pm
    Author: Camron Walsh 

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FileExplorer.h"
#include "UIConfig.h"
#include "Icons.h"

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

    initMultiSelect();

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
        FuzzySearchFilter* filter = m_filters.get<FuzzySearchFilter>(); 
        juce::String search_text = m_search_bar.getText();

        if (search_text.length() == 0) // Remove filter if search is empty
        {
            m_filters.remove<FuzzySearchFilter>();
        }
        else if (filter != nullptr) // Modify search filter query if the filter exists
        {
            filter->setQuery(search_text);
        }
        else // Initalize new search filter if it doesn't exist
        {
            m_filters.add(std::make_unique<FuzzySearchFilter>(search_text)); 
        }

        applyFilters(); 
    }
}

void FileExplorer::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &m_filter_select)
    {
        if (m_filter_select.IsSelected(m_filter_ids.find("Favorite")->second))
            m_filters.add(std::make_unique<FavoriteFilter>());
        else if (m_filters.exists<FavoriteFilter>())
            m_filters.remove<FavoriteFilter>(); 
    }

    applyFilters(); 
}

void FileExplorer::applyFilters()
{
    // Reset filtered data set
    m_sample_library_xml = m_sample_library.getState().createXml();

    for (const auto& filter : m_filters)
    {
        std::vector<juce::XmlElement*> elementsToRemove;

        // Collect elements that do not match the filter
        for (auto* item = m_sample_library_xml->getFirstChildElement(); item != nullptr; item = item->getNextElement())
        {
            if (filter->filter(*item))
                elementsToRemove.push_back(item);
        }

        // Remove collected elements
        for (auto* item : elementsToRemove)
            m_sample_library_xml->removeChildElement(item, true);
    }

    m_file_list.setDataModel(m_sample_library_xml);
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

void FileExplorer::initMultiSelect()
{
    m_filter_ids = {
        {"Favorite", 1},
        {"Kicks", 2},
        {"Snares", 3},
        {"Hats", 4},
        {"Percs", 5}
    };

    m_filter_select.addChangeListener(this); 
    m_filter_select.setButtonText("Select Filters");

    for (const auto& item : m_filter_ids)
    {
        m_filter_select.addItem(item.first, item.second);
        if (item.first == "Favorite")
            m_filter_select.addSeparator(); 
    }

    m_filter_select.setButtonIcon(createFilterIcon()); 
    addAndMakeVisible(m_filter_select);
}

