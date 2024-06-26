/*
  ==============================================================================

    FileDisplayComponents.cpp
    Created: 13 May 2024 5:32:35pm
    Author:  Camron

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FileDisplayComponents.h"
#include "UIConfig.h"
#include "DataSorting.h"

FileListTable::FileListTable(const SampleLibraryDataModel& sample_library)
    : m_sample_library(sample_library),
      m_table("FileListTable", this), 
      m_num_rows(0), 
      m_font(fonts::base) 
{
    initTable(); 
    initTableHeaders(); 
}

FileListTable::~FileListTable()
{
    m_table.setModel(nullptr); 
}

void FileListTable::paint(juce::Graphics& g)
{
    g.setColour(getLookAndFeel().findColour(AppColors::Surface1dp));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), rounding::rounding1);
}

void FileListTable::resized()
{
    juce::Rectangle<int> bounds = getLocalBounds(); 
    m_table.setBounds(bounds.reduced(0, spacing::padding1));
}

void FileListTable::setDataModel(std::shared_ptr<juce::XmlElement> sample_library)
{
    m_sample_library_xml = sample_library; 
    dataChanged(); 
}

void FileListTable::initTable()
{
    addAndMakeVisible(m_table);

    m_table.getHeader().setSortColumnId(1, true); 
    m_table.setMultipleSelectionEnabled(false); 
}

void FileListTable::initTableHeaders()
{
    m_table.getHeader().addColumn("ID", 1, 90, 50, 400, juce::TableHeaderComponent::defaultFlags);
    m_table.getHeader().addColumn("Name", 2, 90, 50, 400, juce::TableHeaderComponent::defaultFlags);
    m_table.getHeader().addColumn("Type", 3, 90, 50, 400, juce::TableHeaderComponent::defaultFlags); 
    m_table.getHeader().addColumn("Favorite", 4, 90, 50, 400, juce::TableHeaderComponent::defaultFlags); 
}

int FileListTable::getNumRows()
{ 
    return m_num_rows; 
}

juce::String FileListTable::getAttributeNameForColumnId(const int column_id) const
{
    if (column_id == 1)
        return ModelIdentifiers::id.toString();
    else if (column_id == 2)
        return ModelIdentifiers::name.toString();
    else if (column_id == 3)
        return ModelIdentifiers::file_extension.toString();
    else if (column_id == 4)
        return ModelIdentifiers::is_favorite.toString(); 

    return {};
}

void FileListTable::paintRowBackground(juce::Graphics& g, int row_number, 
    int width, int height, bool row_is_selected)
{
    if (row_is_selected)
        g.fillAll(getLookAndFeel().findColour(AppColors::PrimaryFocused));
}

void FileListTable::paintCell(juce::Graphics& g, int row_number, 
    int column_id, int width, int height, bool row_is_selected)
{
    if (m_sample_library_xml != nullptr)
    {
        g.setColour(row_is_selected ? getLookAndFeel().findColour(AppColors::Primary) : getLookAndFeel().findColour(AppColors::OnBackground));
        g.setFont(m_font);

        if (auto* row_element = m_sample_library_xml->getChildElement(row_number))
        {
            auto& text = row_element->getStringAttribute(getAttributeNameForColumnId(column_id));
            g.drawText(text, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
        }
    }
}

void FileListTable::sortOrderChanged(int new_sort_col_id, bool forwards)
{
    if (new_sort_col_id != 0)
    {
        CompareNaturalStringSorter sorter(getAttributeNameForColumnId(new_sort_col_id), "id", forwards);
        m_sample_library_xml->sortChildElements(sorter); 
        m_table.updateContent(); 
    }
}


void FileListTable::selectedRowsChanged(int row)
{
    juce::XmlElement* selected_xml_element = m_sample_library_xml->getChildElement(row); 

    if (selected_xml_element != nullptr)
    {
        int selected_file_id = selected_xml_element->getIntAttribute("id");
        activeFileCallback(selected_file_id); 
    }
}

void FileListTable::dataChanged()
{
    m_num_rows = m_sample_library_xml->getNumChildElements();
    m_table.updateContent();
    m_table.autoSizeAllColumns();
    m_table.repaint(); 
}

int FileListTable::getColumnAutoSizeWidth(int columnId)
{
    int widest = 32;

    if (m_sample_library_xml != nullptr)
    {
        for (auto i = getNumRows(); --i >= 0;)
        {
            if (auto* row_element = m_sample_library_xml->getChildElement(i))
            {
                auto& text = row_element->getStringAttribute(getAttributeNameForColumnId(columnId));
                widest = juce::jmax(widest, m_font.getStringWidth(text));
            }
        }

    }

    return widest + spacing::padding2;
}

juce::Component* FileListTable::refreshComponentForCell(int row_num, int column_id, 
    bool is_row_selected, juce::Component* component_to_update)
{
    if (column_id == 4)
    {
        auto* favorite_select = static_cast<StarToggle*>(component_to_update);

        if (favorite_select == nullptr)
            favorite_select = new StarToggle(*this);

        favorite_select->setRowAndColumn(row_num, column_id); 
        return favorite_select; 
    }

    jassert(component_to_update == nullptr);
    return nullptr; 
}

void FileListTable::setSelectedRowChangedCallback(std::function<void(int)> callback)
{
    activeFileCallback = callback; 
}

int FileListTable::getSelection(const int row_number) const
{
    return m_sample_library_xml->getChildElement(row_number)->getIntAttribute(ModelIdentifiers::is_favorite); 
}

void FileListTable::setSelection(const int row_number, const int selection)
{
    juce::XmlElement* selected_child = m_sample_library_xml->getChildElement(row_number); 
    selected_child->setAttribute(ModelIdentifiers::is_favorite, selection); 
    
    
    int selected_child_id = selected_child->getIntAttribute(ModelIdentifiers::id, 0); 
    if (selected_child_id != 0)
    {
        SampleInfoDataModel sample_info = m_sample_library.getState().getChildWithProperty(ModelIdentifiers::id, selected_child_id); 
        sample_info.setIsFavorite(selection); 
    }
}

//==============================================================================

StarToggle::StarToggle(FileListTable& owner)
    : m_owner(owner), 
      m_row(0), 
      m_column_id(0)
{
    addAndMakeVisible(m_toggle_button);

    setLookAndFeel(&m_star_toggle_lnf); 

    m_toggle_button.onClick = [this] { m_owner.setSelection(m_row, (int)m_toggle_button.getToggleState()); }; 
}

StarToggle::~StarToggle()
{
    setLookAndFeel(nullptr); 
}

void StarToggle::resized()
{
    m_toggle_button.setBoundsInset(juce::BorderSize<int>(2));
}

void StarToggle::setRowAndColumn(int row, int col_id)
{
    m_row = row; 
    m_column_id = col_id; 
    m_toggle_button.setToggleState((bool)m_owner.getSelection(row), juce::dontSendNotification); 
}

void StarToggle::StarToggleLookAndFeel::drawToggleButton(juce::Graphics& g, juce::ToggleButton& button,
            bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)       
{
	auto is_selected = button.getToggleState();
		
	auto bounds = button.getLocalBounds();

	auto min_side_length = juce::jmin(bounds.getWidth(), bounds.getHeight()); 
	float outer_radius = min_side_length / 2.5f;
	float inner_radius = outer_radius / 2.65f;
	juce::Point<float> center(min_side_length, bounds.getHeight() / 2);

	juce::Path star;
	star.addStar(center, 5, inner_radius, outer_radius);
	if (is_selected)
	{
		g.setColour(findColour(AppColors::Primary));
		g.strokePath(star, juce::PathStrokeType(1.0f));
		g.fillPath(star); 
		
	}
	else
	{
		g.setColour(findColour(AppColors::Surface6dp));
		g.strokePath(star, juce::PathStrokeType(1.0f));
		g.fillPath(star); 
	} 
}

