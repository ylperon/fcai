# include "fca_implication.h"

FCA::Implication::Implication() {}

FCA::Implication::Implication(const Implication& impl) 
    : mPremise(impl.mPremise),
      mConclusion(impl.mConclusion) {}

FCA::Implication::Implication(const size_t& sizeBasePremise, 
                              const size_t& sizeBaseConclusion)
    : mPremise(sizeBasePremise),
      mConclusion(sizeBaseConclusion) {}

FCA::Implication::Implication(const size_t& sizeBase)
    : mPremise(sizeBase),
      mConclusion(sizeBase) {}

FCA::Implication::Implication(const FCA::BitSet& premise, 
                              const FCA::BitSet& conclusion)
    : mPremise(premise),
      mConclusion(conclusion) {}

FCA::Implication::Implication(const FCA::BitSet& bs)
    : mPremise(bs),
      mConclusion(bs) {}

const FCA::BitSet& FCA::Implication::Premise() const
{
    return mPremise;
}

FCA::BitSet& FCA::Implication::Premise()
{
    return mPremise;
}

size_t FCA::Implication::SizePremise() const
{
    return mPremise.count();
}

const FCA::BitSet& FCA::Implication::Conclusion() const
{
    return mConclusion;
}

FCA::BitSet& FCA::Implication::Conclusion()
{
    return mConclusion;
}

size_t FCA::Implication::SizeConclusion() const
{
    return mConclusion.count();
}

void FCA::Implication::Complete()
{
    mConclusion |= mPremise;
}