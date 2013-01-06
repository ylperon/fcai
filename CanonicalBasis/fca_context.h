# ifndef FCA_CONTEXT_H_
# define FCA_CONTEXT_H_

# include <vector>

# include "fca_context_interface.h"
# include "fca_bitset.h"

namespace FCA
{
    class Context : public FCA::ContextInterface
    {
    public:
        Context();
        Context(const Context& cxt);
        Context(const size_t& objSize, const size_t& attrSize);
        explicit Context(const std::vector<std::vector<bool> >& table);
        explicit Context(const std::vector<FCA::BitSet>& table);

        Context &operator =(const Context& cxt);

        virtual void Set(const size_t& objInd, const size_t& attrInd, const bool& val);
        virtual bool Get(const size_t& objInd, const size_t& attrInd) const;

        virtual size_t SizeObj() const { return mObjSize; }
        virtual size_t SizeAttr() const { return mAttrSize; }

        virtual const BitSet& Intent(const size_t& objInd) const;
        virtual const BitSet& Extent(const size_t& attrInd) const;

        virtual BitSet DrvtAttr(const BitSet& current) const;
        virtual BitSet ClosureAttr(const BitSet& current) const;

        virtual BitSet DrvtObj(const BitSet& current) const;
        virtual BitSet ClosureObj(const BitSet& current) const;

        virtual ~Context() throw() { ;; }

    protected:
        inline static void CheckRangeAndThrowError(const size_t& ind, const size_t& limit, const char* message)
        {
            if (ind >= limit)
            {
                throw std::out_of_range(message);
            }
        }        
        inline static void CheckSetSizeAndThrowError(const size_t& size, const size_t& ethalon, const char* message)
        {
            if (size != ethalon)
            {
                throw std::invalid_argument(message);
            }
        }

        size_t mObjSize;
        size_t mAttrSize;
        std::vector<FCA::BitSet> mTable;
        std::vector<FCA::BitSet> mTableTr;
    };
};

# endif //FCA_CONTEXT_H_