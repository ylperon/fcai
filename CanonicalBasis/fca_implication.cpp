# include "fca_implication.h"

FCA::Implication::Implication() {}

FCA::Implication::Implication(const Implication& impl) 
    : mPremise(impl.mPremise),
      mConclusion(impl.mConclusion) {}

FCA::Implication::Implication(const size_t& sizePremise, 
                              const size_t& sizeConclusion)
    : mPremise(sizePremise),
      mConclusion(sizeConclusion) {}

FCA::Implication::Implication(const size_t& size)
    : mPremise(size),
      mConclusion(size) {}

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