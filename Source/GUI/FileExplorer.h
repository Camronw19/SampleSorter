/*
  ==============================================================================

    FileExplorer.h
    Created: 13 May 2024 6:20:10pm
    Author:  camro

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SampleLibrary.h"
#include "FileDisplayComponents.h"
#include "SearchBar.h"
#include "DataFilters.h"
#include "MultiSelect.h"
#include "map"

//==============================================================================
/*
*/
class FileExplorer  : public juce::Component,
                      public juce::TextEditor::Listener, 
                      public juce::ChangeListener,
                      public SampleLibraryDataModel::Listener,
                      public AudioFileDragAndDropTarget
{
public:
    FileExplorer(const SampleLibraryDataModel&);
    ~FileExplorer() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void textEditorTextChanged(juce::TextEditor&) override; 

private:
    void sampleAdded(const SampleInfoDataModel& addedSample) override; 
    void onFileListRowSelected(int); 

    void changeListenerCallback(juce::ChangeBroadcaster*) override;
    void applyFilters(); 
    
    // File dnd methods
    void fileDragEnter(const juce::StringArray&, int, int) override;
    void fileDragExit(const juce::StringArray&) override;  

    // Init Methods
    void initMultiSelect(); 

    SampleLibraryDataModel m_sample_library; 
    std::shared_ptr<juce::XmlElement> m_sample_library_xml; 
    std::shared_ptr<juce::XmlElement> m_sample_library_xml_filtered; 

    FileListTable m_file_list;
    SearchBar m_search_bar; 
    MultiSelect m_filter_select; 
    
    AddFileOverlay m_add_file_overlay; 

    int m_prev_search_length; 
    std::map<juce::String, int> m_filter_ids; 
    FilterArray m_filters; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FileExplorer)
};
