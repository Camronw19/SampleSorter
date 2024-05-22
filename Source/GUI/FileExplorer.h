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

//==============================================================================
/*
*/
class FileExplorer  : public juce::Component,
                      public juce::TextEditor::Listener, 
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
    void generateXML(); 
    void setFileListData();    
    void onFileListRowSelected(int); 
    
    // File dnd methods
    void fileDragEnter(const juce::StringArray&, int, int) override;
    void fileDragExit(const juce::StringArray&) override; 

    SampleLibraryDataModel m_sample_library; 
    std::unique_ptr<juce::XmlElement> m_sample_library_xml; 

    FileListTable m_file_list;
    SearchBar m_search_bar; 

    AddFileOverlay m_add_file_overlay; 

    FuzzySearchFilter m_fuzzy_search_filter; 
    bool m_search_is_active; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FileExplorer)
};
