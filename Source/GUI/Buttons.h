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

class AddButton : public juce::Button
{
public: 
    AddButton(); 
    ~AddButton() override; 

    void paintButton (juce::Graphics&, bool, bool) override;
    void resized() override;

    void setText(const juce::String); 

private:
    juce::String m_text; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AddButton)
};

class AddComboBox : public juce::ComboBox
{
public: 
    AddComboBox(); 
    ~AddComboBox() override;

private: 
    class AddComboBoxLookAndFeel : public DarkLookAndFeel
    {
    public:
        void drawComboBox(juce::Graphics&, int, int, bool,
            int, int, int, int, ComboBox&) override; 

        void drawPopupMenuBackground(juce::Graphics&, int, int) override; 

        void drawPopupMenuBackgroundWithOptions(juce::Graphics&, int, int, const juce::PopupMenu::Options&) override; 
        
        void drawPopupMenuItem (juce::Graphics&, const juce::Rectangle<int>& area,
                            bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu,
                            const juce::String& text, const juce::String& shortcutKeyText,
                            const juce::Drawable* icon, const juce::Colour* textColour) override;

        juce::PopupMenu::Options getOptionsForComboBoxPopupMenu(juce::ComboBox& box, juce::Label& label) override; 
    };

    AddComboBoxLookAndFeel m_add_combo_box_lnf; 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AddComboBox)
};
