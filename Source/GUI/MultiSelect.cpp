/*
  ==============================================================================

    MultiSelect.cpp (Adapted from juce::ComboBox) 
    Created: 23 May 2024 12:57:30pm
    Author:  Camron Walsh

  ==============================================================================
*/

#include "MultiSelect.h"
#include "algorithm"
#include "UIConfig.h"

MultiSelect::MultiSelect()
    : m_popup_active(false)
{
    addAndMakeVisible(m_button); 
    auto rect = std::make_unique<juce::DrawableRectangle>();
    rect->setRectangle(juce::Rectangle<float>(50, 50, 100, 100));
    rect->setFill(juce::Colours::lightblue);
    m_button.setIcon(std::move(rect)); 
    m_button.onClick = [this]() { showPopupIfNotActive(); };
}

MultiSelect::~MultiSelect()
{
}

void MultiSelect::paint(juce::Graphics&)
{

}

void MultiSelect::resized()
{
    auto bounds = getLocalBounds(); 
    m_button.setBounds(bounds); 
}

// ==================== Popup Menu ====================//

void MultiSelect::addItem(const juce::String& item_text, int item_id)
{
    // you can't add empty strings to the list..
    jassert (item_text.isNotEmpty());

    // IDs must be non-zero, as zero is used to indicate a lack of selection.
    jassert (item_id != 0);

    // you shouldn't use duplicate item IDs!
    jassert (getItemForId (item_id) == nullptr);

    if (item_text.isNotEmpty() && item_id != 0)
        m_popup.addItem (item_id, item_text, true, false);

}

void MultiSelect::addSeparator()
{
    m_popup.addSeparator(); 
}

void MultiSelect::addSectionHeading (const juce::String& heading_name)
{
    // you can't add empty strings to the list..
    jassert (heading_name.isNotEmpty());

    if (heading_name.isNotEmpty())
        m_popup.addSectionHeader (heading_name);
}

void MultiSelect::setItemEnabled (int item_id, bool should_be_enabled)
{
    if (juce::PopupMenu::Item* item = getItemForId (item_id))
        item->isEnabled = should_be_enabled;
}

void MultiSelect::addIcon(const int item_id, std::unique_ptr<juce::Drawable> icon)
{
    juce::PopupMenu::Item* item = getItemForId(item_id); 

    if (item != nullptr)
        item->setImage(std::move(icon)); 
}

juce::PopupMenu::Item* MultiSelect::getItemForId (int item_id) const noexcept 
{
    if (item_id != 0)
    {
        for (juce::PopupMenu::MenuItemIterator iterator (m_popup, true); iterator.next();)
        {
            juce::PopupMenu::Item& item = iterator.getItem();

            if (item.itemID == item_id)
                return &item;
        }
    }

    return nullptr;
}

juce::PopupMenu::Item* MultiSelect::getItemForIndex (const int index) const noexcept
{
    int n = 0;

    for (juce::PopupMenu::MenuItemIterator iterator (m_popup, true); iterator.next();)
    {
        juce::PopupMenu::Item& item = iterator.getItem();

        if (item.itemID != 0)
            if (n++ == index)
                return &item;
    }

    return nullptr;
}

int MultiSelect::getNumItems() const noexcept
{
    int n = 0;

    for (juce::PopupMenu::MenuItemIterator iterator (m_popup, true); iterator.next();)
    {
        juce::PopupMenu::Item& item = iterator.getItem();

        if (item.itemID != 0)
            n++;
    }

    return n;
}

juce::String MultiSelect::getItemText (const int index) const
{
    if (juce::PopupMenu::Item* item = getItemForIndex (index))
        return item->text;

    return {};
}

int MultiSelect::getItemId (const int index) const noexcept
{
    if (juce::PopupMenu::Item* item = getItemForIndex (index))
        return item->itemID;

    return 0;
}

int MultiSelect::indexOfItemId(const int itemId) const noexcept
{
    if (itemId != 0)
    {
        int n = 0;

        for (juce::PopupMenu::MenuItemIterator iterator(m_popup, true); iterator.next();)
        {
            juce::PopupMenu::Item& item = iterator.getItem();

            if (item.itemID == itemId)
                return n;

            else if (item.itemID != 0)
                n++;
        }
    }

    return -1;
}

bool MultiSelect::isItemEnabled (int item_id) const noexcept
{
    if (juce::PopupMenu::Item* item = getItemForId (item_id))
        return item->isEnabled;

    return false;
}


void MultiSelect::clear (const juce::NotificationType notification)
{
    m_popup.clear();
}

//==============================================================================
void MultiSelect::setButtonText(const juce::String text)
{
    m_button.setText(text); 
}

void MultiSelect::setSelectedItemIndex(const int index, const juce::NotificationType notification)
{
    addSelectedId(getItemId(index), notification); 
}

void MultiSelect::addSelectedId (const int new_item_id, const juce::NotificationType notification)
{
    m_selected_ids.push_back(juce::Value(new_item_id)); 
    repaint();

    //sendChange (notification);
}

void MultiSelect::removeSelectedId(const int item_id, const juce::NotificationType notification)
{
    for (const auto& selected_id : m_selected_ids)
    {
        if (selected_id == item_id)
        {
            auto new_end = std::remove(m_selected_ids.begin(), m_selected_ids.end(), selected_id); 
            m_selected_ids.erase(new_end, m_selected_ids.end());

            repaint(); 
            return; 
        }
    }
}

bool MultiSelect::selectIfEnabled (const int index)
{
    if (auto* item = getItemForIndex (index))
    {
        if (item->isEnabled)
        {
            setSelectedItemIndex(index, juce::dontSendNotification);
            return true;
        }
    }

    return false;
}

bool MultiSelect::IsSelected(int id)
{
     auto it = std::find(m_selected_ids.begin(), m_selected_ids.end(), id); 

     if (it != m_selected_ids.end())
         return true;
     else
         return false; 
}

static void multiSelectPopupMenuFinishedCallback (int item_id, MultiSelect* multi_select)
{

    if (multi_select != nullptr)
    {
        multi_select->hidePopup();

        if (item_id != 0)
        {
            if (multi_select->IsSelected(item_id))
                multi_select->removeSelectedId(item_id, juce::dontSendNotification);
            else
                multi_select->addSelectedId(item_id, juce::dontSendNotification);
        }
    }
}

void MultiSelect::showPopup()
{
    if (! m_popup_active)
        m_popup_active = true;

    if (m_popup.getNumItems() > 0)
    {
 
        for (juce::PopupMenu::MenuItemIterator iterator (m_popup, true); iterator.next();)
        {
            auto& item = iterator.getItem();

            if (item.itemID != 0)
                item.isTicked = IsSelected(item.itemID);
        }
    }
    else
    {
        m_popup.addItem (1, "No Choices message", false, false);
    }

    auto& lf = getLookAndFeel();
    m_popup.setLookAndFeel (&lf);

    juce::PopupMenu::Options options =  juce::PopupMenu::Options().withTargetComponent (&m_button)
                               .withMinimumWidth (m_button.getWidth())
                               .withMaximumNumColumns (1)
                               .withTargetScreenArea(m_button.getScreenBounds().translated(0, spacing::padding2));

                               //.withStandardItemHeight (label.getHeight())

    m_popup.showMenuAsync (options, juce::ModalCallbackFunction::forComponent (multiSelectPopupMenuFinishedCallback, this));

}

void MultiSelect::hidePopup()
{
    if (m_popup_active)
    {
        m_popup_active = false;
        juce::PopupMenu::dismissAllActiveMenus();
        repaint();
    }
}



void MultiSelect::showPopupIfNotActive()
{
    if (! m_popup_active)
    {
        m_popup_active = true;

        // as this method was triggered by a mouse event, the same mouse event may have
        // exited the modal state of other popups currently on the screen. By calling
        // showPopup asynchronously, we are giving the other popups a chance to properly
        // close themselves

        juce::MessageManager::callAsync ([safePointer = SafePointer<MultiSelect> { this }]() mutable { if (safePointer != nullptr) safePointer->showPopup(); });
        repaint();
    }
}

void MultiSelect::print()
{
    for (const auto& id : m_selected_ids)
    {
        juce::String val(id.getValue().toString());
        DBG(val); 
    }
}
