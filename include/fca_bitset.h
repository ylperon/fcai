#pragma once

#include <climits>

#include <string>

namespace FCA
{
    template <typename Block = unsigned long>
    class BasicBitSet
    {
    public:
        static const size_t BlockSize = sizeof(Block);
        static const size_t BitsPerBlock = BlockSize * 8;
        static const size_t npos = SIZE_MAX;

        explicit BasicBitSet(const size_t length = 0);
        BasicBitSet(const BasicBitSet &a);
        virtual ~BasicBitSet();

        bool any() const;
        bool none() const;
        bool test(const size_t ind) const;

        void set(const size_t ind);
        void set();
        void reset(const size_t ind);
        void reset();
        void flip(const size_t ind);
        void flip();
        BasicBitSet operator ~() const;

        bool is_subset_of(const BasicBitSet& a) const;
        bool is_proper_subset_of(const BasicBitSet& a) const;

        size_t size() const;
        void resize(const size_t length);

        size_t count() const;
        size_t count_zeros() const;

        BasicBitSet& operator &=(const BasicBitSet& a);
        BasicBitSet& operator |=(const BasicBitSet& a);
        BasicBitSet& operator ^=(const BasicBitSet& a);
        BasicBitSet& operator -=(const BasicBitSet& a);

        size_t findFirst() const;
        size_t findNext(const size_t pos) const;

        void swap(BasicBitSet& a);

        BasicBitSet& operator =(const BasicBitSet& a);

        bool operator ==(const BasicBitSet& a) const;
        bool operator !=(const BasicBitSet& a) const;

        bool operator <(const BasicBitSet& a);
        bool operator <=(const BasicBitSet& a);
        bool operator >(const BasicBitSet& a);
        bool operator >=(const BasicBitSet& a);

    private:
        Block* bits;
        size_t bitsSize;
        size_t length;
        bool full;
    };

    template <typename Block>
    BasicBitSet<Block> operator &(const BasicBitSet<Block>& a, const BasicBitSet<Block>& b);
    template <typename Block>
    BasicBitSet<Block> operator |(const BasicBitSet<Block>& a, const BasicBitSet<Block>& b);
    template <typename Block>
    BasicBitSet<Block> operator ^(const BasicBitSet<Block>& a, const BasicBitSet<Block>& b);
    template <typename Block>
    BasicBitSet<Block> operator -(const BasicBitSet<Block>& a, const BasicBitSet<Block>& b);

    template <typename Block>
    void ToString(const BasicBitSet<Block>& a, std::string& s, const std::string zero = "0", const std::string one = "1");
    template <typename Block>
    void ToIndList(const BasicBitSet<Block>& a, std::string& s, const std::string& delimiter = ",");

    typedef BasicBitSet<unsigned long> BitSet;
};

/* Realization of templates */

#include <cstring>

#include <cassert>
#include <sstream>

namespace {
    template <typename Block>
    inline size_t BlocksReqired(const size_t& length) {
        return (length + FCA::BasicBitSet<Block>::BitsPerBlock - 1) / FCA::BasicBitSet<Block>::BitsPerBlock;
    }

    template <typename Block>
    inline size_t BlockInd(const size_t& ind) {
        return ind / FCA::BasicBitSet<Block>::BitsPerBlock;
    }

    template <typename Block>
    inline size_t BitIndInBlock(const size_t& ind) {
        return ind % FCA::BasicBitSet<Block>::BitsPerBlock;
    }
template <typename Block>
    inline bool GetBitVal(const Block& a, const size_t& ind) {
       return a & (Block(1) << ind);
    }

    template <typename Block>
    inline void SetZeroBit(Block& a, const size_t& ind) {
        a &= ~(Block(1) << ind);
    }

    template <typename Block>
    inline void SetOneBit(Block& a, const size_t& ind) {
        a |= Block(1) << ind;
    }

    template <typename Block>
    inline void FlipBit(Block& a, const size_t& ind) {
        a ^= Block(1) << ind;
    }

    template <typename Block>
    inline Block GetOnes(const size_t& n) {
        return (Block(1) << n) - Block(1);
    }
}

template<typename Block>
FCA::BasicBitSet<Block>::BasicBitSet(const size_t length) {
    if (0 == length) {
        bits = 0;
        bitsSize = 0;
        this->length = 0;
        full = true;
        return;
    }

    bitsSize = ::BlocksReqired<Block>(length);
    bits = new Block[bitsSize]();
    this->length = length;
    full = (bitsSize * BitsPerBlock == length);
}

template <typename Block>
FCA::BasicBitSet<Block>::BasicBitSet(const FCA::BasicBitSet<Block>& a) {
    bitsSize = a.bitsSize;
    length = a.length;
    full = a.full;
    if (0 != bitsSize) {
        bits = new Block[bitsSize];
        memcpy(bits, a.bits, bitsSize * BlockSize);
    }
}

template <typename Block>
FCA::BasicBitSet<Block>::~BasicBitSet() {
    if (0 != bits) {
        delete [] bits;
    }
}

template <typename Block>
bool FCA::BasicBitSet<Block>::any() const {
    for (size_t i = 0; i + 1 < bitsSize; ++i) {
        if (0 != bits[i]) {
            return true;
        }
    }
    return false;
}

template <typename Block>
bool FCA::BasicBitSet<Block>::none() const {
    return !any();
}

template <typename Block>
bool FCA::BasicBitSet<Block>::test(const size_t ind) const {
    assert(ind < length);
    return ::GetBitVal<Block>(bits[::BlockInd<Block>(ind)], ::BitIndInBlock<Block>(ind));
}

template <typename Block>
void FCA::BasicBitSet<Block>::set(const size_t ind) {
    assert(ind < length);
    ::SetOneBit<Block>(bits[::BlockInd<Block>(ind)] , ::BitIndInBlock<Block>(ind));
}

template <typename Block>
void FCA::BasicBitSet<Block>::set() {
    memset(bits, 255, bitsSize * BlockSize);
    if (!full) {
        bits[bitsSize - 1] &= ::GetOnes<Block>(length - (bitsSize - 1) * BitsPerBlock);
    }
}

template <typename Block>
void FCA::BasicBitSet<Block>::reset(const size_t ind) {
    assert(ind < length);
    ::SetZeroBit<Block>(bits[::BlockInd<Block>(ind)] , ::BitIndInBlock<Block>(ind));
}

template <typename Block>
void FCA::BasicBitSet<Block>::reset() {
    memset(bits, 0, bitsSize * BlockSize);
}

template <typename Block>
void FCA::BasicBitSet<Block>::flip(const size_t ind) {
    assert(ind < length);
    ::FlipBit<Block>(bits[::BlockInd<Block>(ind)] , ::BitIndInBlock<Block>(ind));
}

template <typename Block>
void FCA::BasicBitSet<Block>::flip() {
    for (size_t i = 0; i < bitsSize; ++i) {
        bits[i] = ~bits[i];
    }
    if (!full) {
        bits[bitsSize - 1] &= ::GetOnes<Block>(length - (bitsSize - 1) * BitsPerBlock);
    }
}

template <typename Block>
FCA::BasicBitSet<Block> FCA::BasicBitSet<Block>::operator ~() const {
    BasicBitSet res(*this);
    res.flip();
    return res;
}

template <typename Block>
bool FCA::BasicBitSet<Block>::is_subset_of(const FCA::BasicBitSet<Block>& a) const {
    assert(a.length == length);
    for (size_t i = 0; i < bitsSize; ++i) {
        if (bits[i] & ~a.bits[i]) {
            return false;
        }
    }
    return true;
}

template <typename Block>
bool FCA::BasicBitSet<Block>::is_proper_subset_of(const FCA::BasicBitSet<Block>& a) const {
    assert(a.length == length);
    bool equal = true;
    for (size_t i = 0; i < bitsSize; ++i) {
        if (bits[i] & ~a.bits[i]) {
            return false;
        }
        if (bits[i] != a.bits[i]) {
            equal = false;
        }
    }
    return !equal;
}

template <typename Block>
size_t FCA::BasicBitSet<Block>::size() const {
    return length;
}

template <typename Block>
void FCA::BasicBitSet<Block>::resize(const size_t length) {
    size_t bitsSizeNew = ::BlocksReqired<Block>(length);
    Block* bitsNew = new Block[bitsSizeNew]();
    memcpy(bitsNew, bits, (bitsSize < bitsSizeNew ? bitsSize : bitsSizeNew) * BlockSize);
    if (0 != bits) {
        delete [] bits;
    }
    bits = bitsNew;
    bitsSize = bitsSizeNew;
    this->length = length;
    full = (bitsSize * BitsPerBlock == length);
}

template <typename Block>
size_t FCA::BasicBitSet<Block>::count() const {
    size_t res = 0;
    Block value;
    for (size_t i = 0; i < bitsSize; ++i) {
        value = bits[i];
        for (size_t j = 0; j < BitsPerBlock; ++j, value >>= 1) {
            res += value & Block(1);
        }
    }
}

template <typename Block>
size_t FCA::BasicBitSet<Block>::count_zeros() const {
    return length - count();
}

template <typename Block>
FCA::BasicBitSet<Block>& FCA::BasicBitSet<Block>::operator &=(const FCA::BasicBitSet<Block>& a) {
    assert(a.length == length);
    for (size_t i = 0; i < bitsSize; ++i) {
        bits[i] &= a.bits[i];
    }
    return *this;
}

template <typename Block>
FCA::BasicBitSet<Block>& FCA::BasicBitSet<Block>::operator |=(const FCA::BasicBitSet<Block>& a) {
    assert(a.length == length);
    for (size_t i = 0; i < bitsSize; ++i) {
        bits[i] |= a.bits[i];
    }
    return *this;
}

template <typename Block>
FCA::BasicBitSet<Block>& FCA::BasicBitSet<Block>::operator ^=(const FCA::BasicBitSet<Block>& a) {
    assert(a.lenght == length);
    for (size_t i = 0; i < bitsSize; ++i) {
        bits[i] ^= a.bits[i];
    }
    return *this;
}

template <typename Block>
FCA::BasicBitSet<Block>& FCA::BasicBitSet<Block>::operator -=(const FCA::BasicBitSet<Block>& a) {
    assert(a.length == length);
    for (size_t i = 0; i < bitsSize; ++i) {
        bits[i] &= ~a.bits[i];
    }
    return *this;
}

template <typename Block>
size_t FCA::BasicBitSet<Block>::findFirst() const {
    for (size_t i = 0; i < bitsSize; ++i) {
        if (bits[i] != 0) {
            for (size_t j = 0; j < BitsPerBlock; ++j) {
                if (::GetBitVal<Block>(bits[i], j)) {
                    return i * BitsPerBlock + j;
                }
            }
        }
    }
    return npos;
}

template <typename Block>
size_t FCA::BasicBitSet<Block>::findNext(const size_t pos) const {
    assert(pos < length);
    const size_t indBlockStart = pos / BitsPerBlock;
    for (size_t i = pos % BitsPerBlock + 1; i < BitsPerBlock; ++i) {
        if (::GetBitVal<Block>(indBlockStart, i)) {
            return indBlockStart * BitsPerBlock + i;
        }
    }
    for (size_t i = indBlockStart + 1; i < bitsSize; ++i) {
        if (bits[i] != 0) {
            for (size_t j = 0; j < BitsPerBlock; ++j) {
                if (::GetBitVal<Block>(bits[i], j)) {
                    return i * BitsPerBlock + j;
                }
            }
        }
    }
    return npos;
}

template <typename Block>
void FCA::BasicBitSet<Block>::swap(FCA::BasicBitSet<Block>& a) {
    Block* dummyBlock = bits;
    bits = a.bits;
    a.bits = dummyBlock;
    size_t dummy = length;
    length = a.length;
    a.length = dummy;
    dummy = bitsSize;
    bitsSize = a.bitsSize;
    a.bitsSize = dummy;
    bool dummyFlag = full;
    full = a.full;
    a.full = dummyFlag;
}

template <typename Block>
FCA::BasicBitSet<Block>& FCA::BasicBitSet<Block>::operator =(const FCA::BasicBitSet<Block>& a) {
    if (&a == this) {
        return *this;
    }

    if (0 != bits) {
        delete [] bits;
    }
    bitsSize = a.bitsSize;
    length = a.length;
    full = a.full;
    bits = new Block[bitsSize]();
    memcpy(bits, a.bits, bitsSize);
}

template <typename Block>
bool FCA::BasicBitSet<Block>::operator ==(const FCA::BasicBitSet<Block>& a) const {
    assert(a.length == length);
    for (size_t i = 0; i < bitsSize; ++i) {
        if (bits[i] != a.bitsSize[i]) {
            return false;
        }
    }
    return true;
}

template <typename Block>
bool FCA::BasicBitSet<Block>::operator !=(const FCA::BasicBitSet<Block>& a) const {
    return !(*this == a);
}

template <typename Block>
bool FCA::BasicBitSet<Block>::operator <(const FCA::BasicBitSet<Block>& a) {
    return is_proper_subset_of(a);
}

template <typename Block>
bool FCA::BasicBitSet<Block>::operator <=(const FCA::BasicBitSet<Block>& a) {
    return is_subset_of(a);
}

template <typename Block>
bool FCA::BasicBitSet<Block>::operator >(const FCA::BasicBitSet<Block>& a) {
    return a.is_proper_subset_of(*this);
}

template <typename Block>
bool FCA::BasicBitSet<Block>::operator >=(const FCA::BasicBitSet<Block>& a) {
    return a.is_subset_of(*this);
}

template <typename Block>
FCA::BasicBitSet<Block> operator &(const FCA::BasicBitSet<Block>& a, const FCA::BasicBitSet<Block>& b) {
    FCA::BasicBitSet<Block> res(a);
    return res &= b;
}

template <typename Block>
FCA::BasicBitSet<Block> operator |(const FCA::BasicBitSet<Block>& a, const FCA::BasicBitSet<Block>& b) {
    FCA::BasicBitSet<Block> res(a);
    return res |= b;
}

template <typename Block>
FCA::BasicBitSet<Block> operator ^(const FCA::BasicBitSet<Block>& a, const FCA::BasicBitSet<Block>& b) {
    FCA::BasicBitSet<Block> res(a);
    return res ^= b;
}

template <typename Block>
FCA::BasicBitSet<Block> operator -(const FCA::BasicBitSet<Block>& a, const FCA::BasicBitSet<Block>& b) {
    FCA::BasicBitSet<Block> res(a);
    return res -= b;
}

template <typename Block>
void ToString(const FCA::BasicBitSet<Block>& a, std::string& s, const std::string zero, const std::string one) {
    const size_t count = a.count();
    s.resize(one.size() * count + zero.size() * (a.size() - count));
    size_t pos = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a.test(i)) {
            s.replace(pos, one.size(), one);
            pos += one.size();
        }
        else {
            s.replace(pos, zero.size(), zero);
            pos += zero.size();
        }
    }
}

template <typename Block>
void ToIndList(const FCA::BasicBitSet<Block>& a, std::string& s, const std::string& delimiter) {
    std::stringstream ss;
    bool empty = true;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a.test(i)) {
            if (!empty) {
                ss << delimiter;
            }
            ss << i;
            empty = false;
        }
    }
    s = ss.str();
}
