# pragma once

# ifndef FCA_CONCEPT_H_
# define FCA_CONCEPT_H_

# include "fca_definitions.h"

namespace FCA
{
    class Concept
    {
    protected:
        std::vector<Object> m_extent;
        std::vector<Attribute> m_intent;
    public:
        Concept() {}
        Concept(const std::vector<Object> &iExtent, const std::vector<Attribute> &iIntent) : m_extent(iExtent), m_intent(iIntent) {}

        std::vector<Object> &Extent() { return m_extent; }
        const std::vector<Object> &eExtent() const { return m_extent; }
        std::vector<Attribute> &Intent() { return m_intent; }
        const std::vector<Attribute> &Intent() const { return m_intent; }
    };

    class ConceptInd
    {
    protected:
        BitSet m_extent;
        BitSet m_intent;
    public:
        ConceptInd() {}
        ConceptInd(const BitSet &iExtent, const BitSet &iIntent) : m_extent(iExtent), m_intent(iIntent) {}

        BitSet &Extent() { return m_extent; }
        const BitSet &Extent() const { return m_extent; }
        BitSet &Intent() { return m_intent; }
        const BitSet &Intent() const { return m_intent; }
    };
};

# endif //FCA_CONCEPT_H_