/*
  ==============================================================================

    Buttons.cpp
    Created: 23 May 2024 8:55:40am
    Author:  camro

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Buttons.h"
#include "UIConfig.h"

//==============================================================================
PlusButton::PlusButton()
    : juce::Button("PlusButton")
{

}

PlusButton::~PlusButton()
{
}

void PlusButton::paintButton (juce::Graphics& g, bool is_mouse_over, bool is_button_down)
{
    juce::Rectangle<int> bounds = getLocalBounds(); 

    if (is_mouse_over)
        g.setColour(getLookAndFeel().findColour(AppColors::Surface6dp)); 
    else
        g.setColour(getLookAndFeel().findColour(AppColors::Surface1dp));

    g.fillRoundedRectangle(bounds.toFloat(), rounding::rounding1); 
    
    // Draw add icon
    int center_x = bounds.getCentreX();
    int center_y = bounds.getCentreY();

    const int width = 20; 
    const int height = 2; 

    g.setColour(getLookAndFeel().findColour(AppColors::Secondary)); 

    // Draw the horizontal line
    g.fillRect(center_x - width / 2, center_y - height/ 2, width, height);

    // Draw the vertical line
    g.fillRect(center_x - height / 2, center_y - width / 2, height, width);

}

void PlusButton::resized()
{
}

//==============================================================================

AddButton::AddButton()
    : juce::Button("AddButton")
{

}

AddButton::~AddButton()
{

}

void AddButton::paintButton(juce::Graphics& g, bool is_mouse_over, bool is_button_down)
{
    juce::Rectangle<int> bounds = getLocalBounds(); 

    if (is_mouse_over)
    {
        g.setColour(getLookAndFeel().findColour(AppColors::Surface6dp)); 
        g.fillRoundedRectangle(bounds.toFloat(), rounding::rounding1); 
    }


    // Set the color for the plus sign and text
    g.setColour(getLookAndFeel().findColour(AppColors::OnBackground));

    // Calculate the bounds for the plus sign and text
    int padding = spacing::padding1;
    int plus_size = bounds.getHeight() / 2;
    int plus_thickness= 2;

    // Draw the plus sign
    juce::Path plusPath;
    plusPath.startNewSubPath(padding, bounds.getCentreY());
    plusPath.lineTo(padding + plus_size, bounds.getCentreY());
    plusPath.startNewSubPath(padding + plus_size / 2, bounds.getCentreY() - plus_size / 2);
    plusPath.lineTo(padding + plus_size / 2, bounds.getCentreY() + plus_size / 2);

    g.strokePath(plusPath, juce::PathStrokeType(plus_thickness));

    // Draw the text
    juce::Font font(fonts::base); 
    g.setFont(font);

    // Calculate the area available for text
    int textStartX = padding + plus_size + padding;
    int textWidth = bounds.getWidth() - textStartX - padding;

    if (g.getCurrentFont().getStringWidth(m_text) <= textWidth)
        g.drawText(m_text, textStartX, 0, textWidth, bounds.getHeight(), juce::Justification::centredLeft);

    }

void AddButton::resized()
{

}

void AddButton::setText(const juce::String text)
{
    m_text = text; 
}


//==============================================================================

AddComboBox::AddComboBox()
{
    setLookAndFeel(&m_add_combo_box_lnf);
}

AddComboBox::~AddComboBox()
{
    setLookAndFeel(nullptr); 
}

void AddComboBox::AddComboBoxLookAndFeel::drawComboBox (juce::Graphics& g, int width, int height, bool,
                                   int, int, int, int, ComboBox& box)
{
    auto cornerSize = box.findParentComponentOfClass<juce::ChoicePropertyComponent>() != nullptr ? 0.0f : 3.0f;
    juce::Rectangle<int> boxBounds (0, 0, width, height);

    g.setColour (box.findColour (ComboBox::backgroundColourId));
    g.fillRoundedRectangle (boxBounds.toFloat(), cornerSize);

    g.setColour (box.findColour (ComboBox::outlineColourId));
    g.drawRoundedRectangle (boxBounds.toFloat().reduced (0.5f, 0.5f), cornerSize, 1.0f);

    juce::Rectangle<int> arrowZone (width - 30, 0, 20, height);
    juce::Path path;
    path.startNewSubPath ((float) arrowZone.getX() + 3.0f, (float) arrowZone.getCentreY() - 2.0f);
    path.lineTo ((float) arrowZone.getCentreX(), (float) arrowZone.getCentreY() + 3.0f);
    path.lineTo ((float) arrowZone.getRight() - 3.0f, (float) arrowZone.getCentreY() - 2.0f);

    g.setColour (box.findColour (ComboBox::arrowColourId).withAlpha ((box.isEnabled() ? 0.9f : 0.2f)));
    g.strokePath (path, juce::PathStrokeType (2.0f));
}


void AddComboBox::AddComboBoxLookAndFeel::drawPopupMenuBackground(juce::Graphics& g, int width, int height)
{
    juce::Rectangle<float> bounds(width, height); 
    g.setColour(findColour(juce::PopupMenu::backgroundColourId)); 
    g.fillRoundedRectangle(bounds, rounding::rounding1); 
}


void AddComboBox::AddComboBoxLookAndFeel::drawPopupMenuBackgroundWithOptions(juce::Graphics& g, int width, int height, const juce::PopupMenu::Options&)
{
    drawPopupMenuBackground(g, width, height);
}

void AddComboBox::AddComboBoxLookAndFeel::drawPopupMenuItem (juce::Graphics& g, const juce::Rectangle<int>& area,
                                        const bool isSeparator, const bool isActive,
                                        const bool isHighlighted, const bool isTicked,
                                        const bool hasSubMenu, const juce::String& text,
                                        const juce::String& shortcutKeyText,
                                        const juce::Drawable* icon, const juce::Colour* const textColourToUse)
{
    if (isSeparator)
    {
        auto r = area.reduced (5, 0);
        r.removeFromTop (r.getHeight() / 2 - 1);

        g.setColour (juce::Colour (0x33000000));
        g.fillRect (r.removeFromTop (1));

        g.setColour (juce::Colour (0x66ffffff));
        g.fillRect (r.removeFromTop (1));
    }
    else
    {
        auto textColour = findColour (juce::PopupMenu::textColourId);

        if (textColourToUse != nullptr)
            textColour = *textColourToUse;

        auto r = area.reduced (1);

        if (isHighlighted)
        {
            g.setColour (findColour (juce::PopupMenu::highlightedBackgroundColourId));
            g.fillRect (r);

            g.setColour (findColour (juce::PopupMenu::highlightedTextColourId));
        }
        else
        {
            g.setColour (textColour);
        }

        if (! isActive)
            g.setOpacity (0.3f);

        juce::Font font (getPopupMenuFont());

        auto maxFontHeight = (float) area.getHeight() / 1.3f;

        if (font.getHeight() > maxFontHeight)
            font.setHeight (maxFontHeight);

        g.setFont (font);

        auto iconArea = r.removeFromLeft ((r.getHeight() * 5) / 4).reduced (3).toFloat();

        if (icon != nullptr)
        {
            icon->drawWithin (g, iconArea, juce::RectanglePlacement::centred | juce::RectanglePlacement::onlyReduceInSize, 1.0f);
        }
        else if (isTicked)
        {
            auto tick = getTickShape (1.0f);
            g.fillPath (tick, tick.getTransformToScaleToFit (iconArea, true));
        }

        if (hasSubMenu)
        {
            auto arrowH = 0.6f * getPopupMenuFont().getAscent();

            auto x = (float) r.removeFromRight ((int) arrowH).getX();
            auto halfH = (float) r.getCentreY();

            juce::Path p;
            p.addTriangle (x, halfH - arrowH * 0.5f,
                           x, halfH + arrowH * 0.5f,
                           x + arrowH * 0.6f, halfH);

            g.fillPath (p);
        }

        r.removeFromRight (3);
        g.drawFittedText (text, r, juce::Justification::centredLeft, 1);

        if (shortcutKeyText.isNotEmpty())
        {
            juce::Font f2 (font);
            f2.setHeight (f2.getHeight() * 0.75f);
            f2.setHorizontalScale (0.95f);
            g.setFont (f2);

            g.drawText (shortcutKeyText, r, juce::Justification::centredRight, true);
        }
    }
}

juce::PopupMenu::Options  AddComboBox::AddComboBoxLookAndFeel::getOptionsForComboBoxPopupMenu (juce::ComboBox& box, juce::Label& label)
{
        return juce::PopupMenu::Options().withTargetComponent (&box)
                               .withItemThatMustBeVisible (box.getSelectedId())
                               .withInitiallySelectedItem (box.getSelectedId())
                               .withMinimumWidth (box.getWidth())
                               .withMaximumNumColumns (1)
                               .withStandardItemHeight (label.getHeight())
                               .withTargetScreenArea(box.getScreenBounds().translated(0, spacing::padding1));
}

