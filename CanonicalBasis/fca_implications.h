# pragma once

# ifndef FCA_IMPLICATIONS_H_
# define FCA_IMPLICATIONS_H_

# include "fca_definitions.h"

namespace FCA
{
    class Implication
    {
    protected:
        std::vector<Attribute> m_premise;
        std::vector<Attribute> m_conclusion;
    public:
        Implication() {}
        Implication(const std::vector<Attribute> &iPremise, const std::vector<Attribute> &iConclusion) : m_premise(iPremise), m_conclusion(iConclusion) {}

        std::vector<Attribute> &Premise() { return m_premise; }
        const std::vector<Attribute> &Premise() const {return m_premise; }
        std::vector<Object> &Conclusion() { return m_conclusion; }
        const std::vector<Object> &Conclusion() const { return m_conclusion; }
    };

    struct ImplicationInd
    {
    protected:		
        BitSet m_premise;
        BitSet m_conclusion;
    public:		
        ImplicationInd() {}
        ImplicationInd(const BitSet &iPremise, const BitSet &iConclusion) : m_premise(iPremise), m_conclusion(iConclusion) {}

        BitSet &Premise() { return m_premise; }
        const BitSet &Premise() const { return m_premise; }
        BitSet &Conclusion() { return m_conclusion; }
        const BitSet &Conclusion() const { return m_conclusion; }
    };

    Implication Convert(const ImplicationInd &impl, const std::vector<Attribute> &baseSet);

    std::vector<Implication> Convert(const std::vector<ImplicationInd> &impl, const std::vector<Attribute> &baseSet);

    void Convert(const std::vector<Attribute> &current, const std::vector<Attribute> &attributes, const std::vector<Implication> &implications, 
                 BitSet &cCurrent, std::vector<ImplicationInd> &cImplications);	
};

# endif //FCA_IMPLICATIONS_H_