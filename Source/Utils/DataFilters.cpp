/*
  ==============================================================================

    DataFilters.cpp
    Created: 21 May 2024 3:34:17pm
    Author:  camro

  ==============================================================================
*/

#include "DataFilters.h"
#include  "SampleInfo.h"

const bool FuzzySearchFilter::filter(const juce::XmlElement& element)
{
    juce::String name = element.getStringAttribute(ModelIdentifiers::name); 

    if (name.isNotEmpty())
    {
        if (!name.containsIgnoreCase(m_query))
        {
            return true; 
        }
    }

    return false; 
}

void FuzzySearchFilter::setQuery(const juce::String query)
{
    m_query = query; 
}


const bool FavoriteFilter::filter(const juce::XmlElement& element)
{
    bool is_favorite = element.getBoolAttribute(ModelIdentifiers::is_favorite); 
    
    if (!is_favorite)
        return true;
    else
        return false; 
}

//===============================================================================

void FilterArray::add(std::unique_ptr<Filter> filter)
{
    m_filters.push_back(std::move(filter)); 
}

