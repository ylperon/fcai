#pragma once

# include "fca_context_interface.h"

# include <vector>

namespace FCA {
    class Context : public ContextInterface {
    public:
        Context();
        Context(const Context& cxt);
        Context(const size_t& objSize, const size_t& attrSize);
        explicit Context(const std::vector<std::vector<bool> >& table);
        explicit Context(const BitSetVector& table);

        Context &operator =(const Context& cxt);

        void Set(const size_t& objInd, const size_t& attrInd, const bool val = true);
        bool Get(const size_t& objInd, const size_t& attrInd) const;

        size_t ObjSize() const { return objSize; }
        size_t AttrSize() const { return attrSize; }

        const BitSet& Intent(const size_t& objInd) const;
        const BitSet& Extent(const size_t& attrInd) const;

        BitSet DrvtAttr(const BitSet& current) const;
        BitSet ClosureAttr(const BitSet& current) const;

        BitSet DrvtObj(const BitSet& current) const;
        BitSet ClosureObj(const BitSet& current) const;

        virtual ~Context() throw() { ;; }

    protected:
        size_t objSize;
        size_t attrSize;
        BitSetVector table;
        BitSetVector tableTr;
    };
};
