# ifndef FCA_CONTEXT_INTERFACE_H_
# define FCA_CONTEXT_INTERFACE_H_

# include <cstddef>

namespace FCA
{
    class BitSet;

    class ContextInterface
    {
    public:
        virtual void Set(const size_t &objInd, const size_t &attrInd, const bool &val) = 0;
        virtual bool Get(const size_t &objInd, const size_t &attrInd) const = 0;
    
        virtual size_t SizeObj() const = 0;
        virtual size_t SizeAttr() const = 0;
    
        virtual BitSet Intent(const size_t &objInd) const = 0;
        virtual BitSet Extent(const size_t &attrInd) const = 0;
    
        virtual BitSet DrvtAttr(const BitSet &current) const = 0;
        virtual BitSet ClosureAttr(const BitSet &current) const = 0;
    
        virtual BitSet DrvtObj(const BitSet &current) const = 0;
        virtual BitSet ClosureObj(const BitSet &current) const = 0;
    
        virtual ~ContextInterface() throw() { ;; }
    };

}

# endif //FCA_CONTEXT_INTERFACE_H_