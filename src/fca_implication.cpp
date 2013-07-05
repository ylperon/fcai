# include "fca_implication.h"

#include <cassert>

FCA::Implication::Implication() {}

FCA::Implication::Implication(const Implication& impl)
    : premise(impl.premise),
      conclusion(impl.conclusion) {}

FCA::Implication::Implication(const size_t& baseSize)
    : premise(sizeBase),
      conclusion(sizeBase) {}

FCA::Implication::Implication(const FCA::BitSet& premise,
                              const FCA::BitSet& conclusion)
    : premise(premise),
      conclusion(conclusion) {}

FCA::Implication::Implication(const FCA::BitSet& bs)
    : premise(bs),
      conclusion(bs) {}

const FCA::BitSet& FCA::Implication::Premise() const {
    return premise;
}

FCA::BitSet& FCA::Implication::Premise() {
    return premise;
}

size_t FCA::Implication::PremiseSize() const {
    return premise.count();
}

const FCA::BitSet& FCA::Implication::Conclusion() const {
    return conclusion;
}

FCA::BitSet& FCA::Implication::Conclusion() {
    return conclusion;
}

size_t FCA::Implication::SizeConclusion() const {
    return conclusion.count();
}

void FCA::Implication::Complete() {
    assert(premise.size() == conclustion.size());
    conclusion |= premise;
}
