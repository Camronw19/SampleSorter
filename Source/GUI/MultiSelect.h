/*
  ==============================================================================

    MultiSelect.h
    Created: 23 May 2024 12:57:30pm
    Author:  Camron Walsh

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "GenericComponents.h"

class MultiSelect : public juce::Component
{
public: 
    explicit MultiSelect(); 
    ~MultiSelect(); 

    void paint(juce::Graphics&) override; 
    void resized() override; 

    // ==================== Popup Menu ====================//
    void addItem(const juce::String&, int); 
    void addSeparator(); 
    void addSectionHeading(const juce::String&); 
    void setItemEnabled(int, bool);
    void addIcon(const int, std::unique_ptr<juce::Drawable>); 

    juce::PopupMenu::Item* getItemForId(int) const noexcept; 
    juce::PopupMenu::Item* getItemForIndex(const int index) const noexcept;
    int getNumItems() const noexcept;
    juce::String getItemText(const int) const;
    int getItemId(const int) const noexcept;
    int indexOfItemId(const int) const noexcept;
    bool isItemEnabled(int) const noexcept; 

    void clear(const juce::NotificationType); 

    //=======================================================
    void setSelectedItemIndex(const int, const juce::NotificationType); 
    void setButtonText(const juce::String); 
    void setButtonIcon(std::unique_ptr<juce::DrawablePath>&&);
    void addSelectedId(const int, const juce::NotificationType);
    void removeSelectedId(const int, const juce::NotificationType); 
    bool selectIfEnabled(const int);

    bool IsSelected(int); 

    void hidePopup(); 
    void showPopup(); 

    void print(); 

private: 
    void showPopupIfNotActive();

    bool m_popup_active; 
    std::vector<juce::Value> m_selected_ids;    

    IconTextButton m_button;
    juce::PopupMenu m_popup; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiSelect)

};

