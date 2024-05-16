/*
  ==============================================================================

    DataSorting.cpp
    Created: 16 May 2024 12:25:48pm
    Author:  camro

  ==============================================================================
*/

#include "DataSorting.h"

 CompareNaturalStringSorter::CompareNaturalStringSorter(const juce::String& attribute_to_sort_by, const juce::String&
    defualt_attribute_to_sort_by, bool forwards)
    :m_attribute_to_sort(attribute_to_sort_by), 
     m_defualt_attribute_to_sort(defualt_attribute_to_sort_by),
     m_direction(forwards ? 1 : -1)
{
    
}

int CompareNaturalStringSorter::compareElements(juce::XmlElement* first, juce::XmlElement* second)
{
    auto result = first->getStringAttribute(m_attribute_to_sort)
        .compareNatural(second->getStringAttribute(m_attribute_to_sort));

    if (result == 0)
        result = first->getStringAttribute(m_defualt_attribute_to_sort)
        .compareNatural(second->getStringAttribute(m_defualt_attribute_to_sort));

    return m_direction * result;
}


