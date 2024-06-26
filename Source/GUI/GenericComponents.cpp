/*
  ==============================================================================

    GenericComponents.cpp
    Created: 23 May 2024 8:55:40am
    Author: Camron Walsh 

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GenericComponents.h"
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

    int width = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2;
    int height = juce::jmax(2, width / 10);

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

IconTextButton::IconTextButton()
    : juce::Button("IconTextButton")
{

}

IconTextButton::~IconTextButton()
{

}

void IconTextButton::paintButton(juce::Graphics& g, bool is_mouse_over, bool is_button_down)
{
    juce::Rectangle<int> bounds = getLocalBounds(); 
    juce::Colour icon_text_colour; 

    if (is_mouse_over)
    {
        g.setColour(getLookAndFeel().findColour(AppColors::Surface6dp));
        icon_text_colour = getLookAndFeel().findColour(AppColors::Primary); 
    }
    else
    {
        g.setColour(getLookAndFeel().findColour(AppColors::Surface1dp)); 
        icon_text_colour = getLookAndFeel().findColour(AppColors::OnBackground); 
    }

    g.fillRoundedRectangle(bounds.toFloat(), rounding::rounding1); 

    // Set the color for the icon and text
    g.setColour(icon_text_colour); 
    m_icon->setFill(icon_text_colour);

    if(!m_icon_bounds.isEmpty() && m_icon != nullptr)
        m_icon->drawWithin(g, m_icon_bounds.toFloat(), juce::RectanglePlacement::centred, 1.0f);

    // Draw the text
    juce::Font font(fonts::base); 
    g.setFont(font);
    g.drawText(m_text, m_text_bounds, juce::Justification::centredLeft);
}

void IconTextButton::resized()
{
    calculateIconBounds(); 
    m_icon->setBounds(m_icon_bounds); 

    calculateTextBounds(); 
}

void IconTextButton::setText(const juce::String text)
{
    m_text = text; 
}

void IconTextButton::setIcon(std::unique_ptr<juce::DrawablePath>&& drawable_path)
{
    m_icon = std::move(drawable_path); 
}

int IconTextButton::getFittedWidth()
{
    int fitted_width = 0; 

    if (!m_icon_bounds.isEmpty() && m_icon != nullptr)
        fitted_width += m_icon_bounds.getWidth(); 

    fitted_width += spacing::padding1 * 2; 

    juce::Font font(fonts::base); 
    fitted_width += font.getStringWidth(m_text);

    return fitted_width; 
}

void IconTextButton::calculateIconBounds()
{
    float padding = spacing::padding1;
    float icon_size = static_cast<float>(getBounds().getHeight()) / 2;

    m_icon_bounds.setBounds(padding, getHeight() / 4, icon_size, icon_size);
}

void IconTextButton::calculateTextBounds()
{
    auto bounds = getLocalBounds(); 

    int start_x = m_icon_bounds.getRight() + spacing::padding1; 
    int text_width = bounds.getWidth() - start_x - spacing::padding1;

    m_text_bounds.setBounds(start_x, 0, text_width, bounds.getHeight());
}

//==============================================================================
CustomComboBox::CustomComboBox()
{
    setLookAndFeel(&m_custom_combo_box_lnf);
}

CustomComboBox::~CustomComboBox()
{
    setLookAndFeel(nullptr); 
}

void CustomComboBox::CustomComboBoxLookAndFeel::drawComboBox (juce::Graphics& g, int width, int height, bool,
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


void CustomComboBox::CustomComboBoxLookAndFeel::drawPopupMenuBackground(juce::Graphics& g, int width, int height)
{
    juce::Rectangle<float> bounds(width, height); 
    g.setColour(findColour(juce::PopupMenu::backgroundColourId)); 
    g.fillRoundedRectangle(bounds, rounding::rounding1); 
}


void CustomComboBox::CustomComboBoxLookAndFeel::drawPopupMenuBackgroundWithOptions(juce::Graphics& g, int width, int height, const juce::PopupMenu::Options&)
{
    drawPopupMenuBackground(g, width, height);
}

juce::PopupMenu::Options  CustomComboBox::CustomComboBoxLookAndFeel::getOptionsForComboBoxPopupMenu (juce::ComboBox& box, juce::Label& label)
{
        return juce::PopupMenu::Options().withTargetComponent (&box)
                               .withItemThatMustBeVisible (box.getSelectedId())
                               .withInitiallySelectedItem (box.getSelectedId())
                               .withMinimumWidth (box.getWidth())
                               .withMaximumNumColumns (1)
                               .withStandardItemHeight (label.getHeight())
                               .withTargetScreenArea(box.getScreenBounds().translated(0, spacing::padding1));
}
