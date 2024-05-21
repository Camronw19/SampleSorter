/*
  ==============================================================================

    FileUtils.cpp
    Created: 12 May 2024 11:07:39am
    Author:  camro

  ==============================================================================
*/

#include "FileUtils.h"
#include "UIConfig.h"
#include "SampleInfo.h"

AudioFileDragAndDropTarget::AudioFileDragAndDropTarget(const SampleLibraryDataModel& sample_library)
    :m_sample_library(sample_library)
{

}

bool AudioFileDragAndDropTarget::isInterestedInFileDrag(const juce::StringArray& files)
{
    for (auto& file : files)
        if (file.contains(".wav") || file.contains(".mp3") || file.contains(".aif"))
            return true;

    // If no valid files are found, show an error message
    juce::AlertWindow::showMessageBoxAsync(
        juce::AlertWindow::WarningIcon,
        "Invalid File Format",
        "WAV, MP3, and AIF files only.",
        "OK"
    );

    return false;
}

void AudioFileDragAndDropTarget::filesDropped(const juce::StringArray& files, int x , int y)
{
    for (auto filePath : files)
    {
        if (isInterestedInFileDrag(filePath))
        {
            const juce::File file(filePath); 

            SampleInfoDataModel sample_info;
            sample_info.setName(file.getFileNameWithoutExtension());
            sample_info.setFilePath(file.getFullPathName()); 
            sample_info.setFileExtension(file.getFileExtension()); 

            m_sample_library.AddSample(sample_info); 
        }
    }

    fileDragExit(files); 
}

void AudioFileDragAndDropTarget::fileDragEnter(const juce::StringArray& files, int x, int y)
{

}

void AudioFileDragAndDropTarget::fileDragExit(const juce::StringArray& files)
{

}

//==============================================================================

AddFileOverlay::AddFileOverlay()
{
    this->setAlpha(0.0f); 
}

AddFileOverlay::~AddFileOverlay()
{

}

void AddFileOverlay::paint(juce::Graphics& g)
{
    g.setColour(getLookAndFeel().findColour(AppColors::PrimaryFocused));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), rounding::rounding1);

    g.setColour(getLookAndFeel().findColour(AppColors::OnBackground));
    g.drawText("DROP FILES", getLocalBounds(), juce::Justification::centred, true); 
}

void AddFileOverlay::resized()
{

}

//==============================================================================
AudioFileChooser::AudioFileChooser(const SampleLibraryDataModel& sample_library)
    :m_sample_library(sample_library), 
     m_file_choooser("FileChooser", juce::File(), m_audio_file_patterns)
{
    m_file_chooser_flags = juce::FileBrowserComponent::canSelectFiles |
                      juce::FileBrowserComponent::canSelectDirectories |
                      juce::FileBrowserComponent::canSelectMultipleItems |
                      juce::FileBrowserComponent::openMode; 
}

void AudioFileChooser::browseMultipleFiles()
{
    m_file_choooser.launchAsync(m_file_chooser_flags, [this](const juce::FileChooser& chooser)
        {
            auto results = chooser.getResults(); 

            for (const auto& file : results)
            {
                if (file.isDirectory())
                    addFilesFromDirectory(file);
                else
                    addFile(file); 
            }
        });
}

void AudioFileChooser::addFile(const juce::File& file)
{
      SampleInfoDataModel sample_info;
      sample_info.setName(file.getFileNameWithoutExtension());
      sample_info.setFilePath(file.getFullPathName()); 
      sample_info.setFileExtension(file.getFileExtension()); 

      m_sample_library.AddSample(sample_info); 
}

void AudioFileChooser::addFilesFromDirectory(const juce::File& file)
{
    int what_to_look_for = juce::File::findFiles;     
    bool search_recursively = false; 

    juce::Array<juce::File> files = file.findChildFiles(what_to_look_for, search_recursively, m_audio_file_patterns); 

    for (const auto& file : files)
        addFile(file); 
}

