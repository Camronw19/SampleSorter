/*
  ==============================================================================

    DataFilters.h
    Created: 21 May 2024 3:34:17pm
    Author:  camro

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <vector>
#include <memory>

class Filter
{
public: 
    virtual ~Filter() = default; 
    virtual const bool filter(const juce::XmlElement&) = 0; 
};

class FuzzySearchFilter : public Filter
{
public: 
    FuzzySearchFilter(const juce::String); 

    const bool filter(const juce::XmlElement&) override; 
    void setQuery(const juce::String);

private: 
    juce::String m_query; 
};

class FavoriteFilter : public Filter
{
public: 
    const bool filter(const juce::XmlElement&) override; 
};

//===============================================================================

class FilterArray
{
public: 
    void add(std::unique_ptr<Filter>); 

    template<typename Derived>
    void remove(); 

    template<typename Derived>
    bool exists(); 

    template<typename Derived>
    Derived* get(); 

    using iterator = std::vector<std::unique_ptr<Filter>>::iterator;
    using const_iterator = std::vector<std::unique_ptr<Filter>>::const_iterator;

    iterator begin() { return m_filters.begin(); }
    iterator end() { return m_filters.end(); }
    const_iterator begin() const { return m_filters.begin(); }
    const_iterator end() const { return m_filters.end(); }

private: 
    std::vector<std::unique_ptr<Filter>> m_filters; 
};

template<typename Derived>
void FilterArray::remove()
{
    m_filters.erase(
        std::remove_if(m_filters.begin(), m_filters.end(),
            [](const std::unique_ptr<Filter>& basePtr)
            {
                return dynamic_cast<Derived*>(basePtr.get()) != nullptr;
            }),
        m_filters.end());
}

template<typename Derived>
bool FilterArray::exists()
{
    for (const auto& filter : m_filters)
    {
        if (dynamic_cast<Derived*>(filter.get()) != nullptr)
            return true; 
    }

    return false; 
}

template<typename Derived>
Derived* FilterArray::get()
{
    for (auto& filter : m_filters)
    {
        if (auto derivedPtr = dynamic_cast<Derived*>(filter.get()))
            return derivedPtr;
    }
    return nullptr;
}

