/*
  ==============================================================================

    ValueTreeObjectList.h
    Created: 13 May 2024 5:20:30pm
    Author:  camro

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
template <typename T>
concept HasGetStateMethod = requires(T t)
{
    { t.getState() } -> std::same_as<juce::ValueTree>;
};

template<typename ObjectType, typename CriticalSectionType = juce::DummyCriticalSection>
requires HasGetStateMethod<ObjectType>
class ValueTreeObjectList : public juce::ValueTree::Listener
{
public:
    ValueTreeObjectList(const juce::ValueTree& parentTree)
        : parent(parentTree)
    {
        parent.addListener(this);
    }

    virtual ~ValueTreeObjectList()
    {
        jassert(m_objects.size() == 0); // must call freeObjects() in the subclass destructor!
    }

    // call in the sub-class when being created
    void rebuildObjects()
    {
        jassert(m_objects.size() == 0); // must only call this method once at construction

        for (const auto& v : parent)
            if (isSuitableType(v))
                if (ObjectType* newObject = createNewObject(v))
                    m_objects.add(newObject);
    }

    // call in the sub-class when being destroyed
    void freeObjects()
    {
        parent.removeListener(this);
        deleteAllObjects();
    }

    //==============================================================================
    virtual bool isSuitableType(const juce::ValueTree&) const = 0;
    virtual ObjectType* createNewObject(const juce::ValueTree&) = 0;
    virtual void deleteObject(ObjectType*) = 0;

    virtual void newObjectAdded(ObjectType*) = 0;
    virtual void objectRemoved(ObjectType*) = 0;
    virtual void objectOrderChanged() = 0;

    //==============================================================================
    void valueTreeChildAdded(juce::ValueTree&, juce::ValueTree& tree) override
    {
        if (isChildTree(tree))
        {
            const int index = parent.indexOf(tree);
            (void)index;
            jassert(index >= 0);

            if (ObjectType* newObject = createNewObject(tree))
            {
                {
                    const ScopedLockType sl(m_array_lock);

                    if (index == parent.getNumChildren() - 1)
                        m_objects.add(newObject);
                    else
                        m_objects.addSorted(*this, newObject);
                }

                newObjectAdded(newObject);
            }
            else
                jassertfalse;
        }
    }

    void valueTreeChildRemoved(juce::ValueTree& exParent, juce::ValueTree& tree, int) override
    {
        if (parent == exParent && isSuitableType(tree))
        {
            const int oldIndex = indexOf(tree);

            if (oldIndex >= 0)
            {
                ObjectType* o;

                {
                    const ScopedLockType sl(m_array_lock);
                    o = m_objects.removeAndReturn(oldIndex);
                }

                objectRemoved(o);
                deleteObject(o);
            }
        }
    }

    void valueTreeChildOrderChanged(juce::ValueTree& tree, int, int) override
    {
        if (tree == parent)
        {
            {
                const ScopedLockType sl(m_array_lock);
                sortArray();
            }

            objectOrderChanged();
        }
    }

    void valueTreePropertyChanged(juce::ValueTree&, const juce::Identifier&) override {}
    void valueTreeParentChanged(juce::ValueTree&) override {}

    void valueTreeRedirected(juce::ValueTree&) override { jassertfalse; } // may need to add handling if this is hit

    juce::Array<ObjectType*> m_objects;
    CriticalSectionType m_array_lock;
    typedef typename CriticalSectionType::ScopedLockType ScopedLockType;

protected:
    juce::ValueTree parent;

    void deleteAllObjects()
    {
        const ScopedLockType sl(m_array_lock);

        while (m_objects.size() > 0)
            deleteObject(m_objects.removeAndReturn(m_objects.size() - 1));
    }

    bool isChildTree(juce::ValueTree& v) const
    {
        return isSuitableType(v) && v.getParent() == parent;
    }

    int indexOf(const juce::ValueTree& v) const noexcept
    {
        for (int i = 0; i < m_objects.size(); ++i)
            if (m_objects.getUnchecked(i)->getState() == v)
                return i;

        return -1;
    }

    void sortArray()
    {
        m_objects.sort(*this);
    }

public:
    int compareElements(ObjectType* first, ObjectType* second) const
    {
        int index1 = parent.indexOf(first->getState());
        int index2 = parent.indexOf(second->getState());
        return index1 - index2;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ValueTreeObjectList)
};
