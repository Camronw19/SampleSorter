/*
  ==============================================================================

    Buttons.h
    Created: 23 May 2024 8:55:40am
    Author:  camro

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "UIConfig.h"
#include <vector>

//==============================================================================
/*
*/
class PlusButton : public juce::Button
{
public:
    PlusButton();
    ~PlusButton() override;

    void paintButton (juce::Graphics&, bool, bool) override;
    void resized() override;


private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlusButton)
};

class IconTextButton : public juce::Button
{
public: 
    IconTextButton(); 
    ~IconTextButton() override; 

    void paintButton (juce::Graphics&, bool, bool) override;
    void resized() override;

    int getFittedWidth(); 

    void setText(const juce::String); 
    void setIcon(std::unique_ptr<juce::Drawable>); 

private:
    void calculateIconBounds(); 
    
    juce::Rectangle<int> m_icon_bounds; 
    std::unique_ptr<juce::Drawable> m_icon; 
    juce::String m_text; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IconTextButton)
};


class CustomComboBox : public juce::ComboBox
{
public: 
    CustomComboBox(); 
    ~CustomComboBox() override;

private: 
    class CustomComboBoxLookAndFeel : public DarkLookAndFeel
    {
    public:
        void drawComboBox(juce::Graphics&, int, int, bool,
            int, int, int, int, ComboBox&) override; 
        void drawPopupMenuBackground(juce::Graphics&, int, int) override; 
        void drawPopupMenuBackgroundWithOptions(juce::Graphics&, int, int, const juce::PopupMenu::Options&) override; 
        juce::PopupMenu::Options getOptionsForComboBoxPopupMenu(juce::ComboBox& box, juce::Label& label) override; 
    };

    CustomComboBoxLookAndFeel m_custom_combo_box_lnf; 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomComboBox)
};
