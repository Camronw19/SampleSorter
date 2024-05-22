/*
  ==============================================================================

    DataFilters.cpp
    Created: 21 May 2024 3:34:17pm
    Author:  camro

  ==============================================================================
*/

#include "DataFilters.h"
#include  "SampleInfo.h"

void FuzzySearchFilter::filter(std::shared_ptr<juce::XmlElement>& tree_to_filter, juce::String query)
{
    std::vector<juce::XmlElement*> elementsToRemove;

    for (auto* child_element : tree_to_filter->getChildIterator())
    {
        juce::String name = child_element->getStringAttribute(ModelIdentifiers::name);
        if (!name.containsIgnoreCase(query))
        {
            elementsToRemove.push_back(child_element);
        }
    }

    for (auto* element : elementsToRemove)
    {
        tree_to_filter->removeChildElement(element, true);
    }

}
