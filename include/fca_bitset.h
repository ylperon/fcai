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
        static const size_t npos = std::numeric_limits<size_t>::max();

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
        void resize(const size_t new_size);

        size_t count() const;
        size_t count_zeros() const

        BasicBitSet& operator &=(const BasicBitSet& a);
        BasicBitSet& operator |=(const BasicBitSet& a);
        BasicBitSet& operator ^=(const BasicBitSet& a);
        BasicBitSet& operator -=(const BasicBitSet& a);

        size_t findFirst() const;
        size_t findNext(const size_t pos) const;

        void swap(BasicBitSet& a);

        BasicBitSet& operator =(const BasicBitSet& a);

        friend bool operator ==(const BasicBitSet& a, const BasicBitSet& b);
        friend bool operator !=(const BasicBitSet& a, const BasicBitSet& b);
        friend bool operator <(const BasicBitSet& a, const BasicBitSet& b);
        friend bool operator <=(const BasicBitSet& a, const BasicBitSet& b);
        friend bool operator >(const BasicBitSet& a, const BasicBitSet& b);
        friend bool operator >=(const BasicBitSet& a, const BasicBitSet& b);

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

#include <ctsring>

#include <cassert>

namespace {
    template <typename Block>
    inline size_t BlocksReqired(const size_t& length) {
        return (length + BasicBitSet<Block>::BitsPerBlock - 1) / BasicBitSet<Block>::BitsPerBlock;
    }

    tempalte <typename Block>
    inline size_t BlockInd(const size_t& ind) {
        return ind / BasicBitSet<Block>::BitsPerBlock;
    }

    template <typename Block>
    inline size_t BitIndInBlock(const size_t& ind) {
        return ind % BasicBitSet<Block>::BitsPerBlock;
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
BasicBitSet<Block>::BasicBitSet(const size_t length) {
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
BasicBitSet<Block>::BasicBitSet(const BasicBitSet<Block>& a) {
    bitsSize = a.bitsSize;
    length = a.length;
    full = a.full;
    if (0 != aSize) {
        bits = new Block[bitsSize];
        memcpy(bits, a.bits, bitsSize * BlockSize);
    }
}

template <typename Block>
BasicBitSet<Block>::~BasicBitSet() {
    if (0 != bits) {
        delete [] bits;
    }
}

template <typename Block>
bool BasicBitSet<Block>::any() const {
    for (size_t i = 0; i + 1 < bitsSize; ++i) {
        if (0 != bits[i]) {
            return true;
        }
    }
    return false;
}

template <typename Block>
bool BasicBitSet<Block>::none() const {
    return !any();
}

template <typename Block>
bool BasicBitSet<Block>::test(const size_t ind) const {
    assert(ind < lenght);
    return ::GetBitVal<Block>(bits[::BlockInd<Block>(ind)], ::BitIndInBlock<Block>(ind));
}

template <typename Block>
void BasicBitSet<Block>::set(const size_t ind) {
    assert(ind < length);
    ::SetOneBit<Block>(bits[::BlockInd<Block>(ind)] , ::BitIndInBlock<Block>(ind));
}

template <typename Block>
void BasicBitSet<Block>::set() {
    memset(bits, 255, bitsSize * BlockSize);
    if (!full) {
        bits[bitsSize - 1] |= ::GetOnes<Block>(length - (bitsSize - 1) * BitsPerBlock);
    }
}

template <typename Block>
void BasicBitSet<Block>::reset(const size_t ind) {
    assert(ind < lenght)
    ::SetZeroBit<Block>(bits[::BlockInd<Block>(ind)] , ::BitIndInBlock<Block>(ind));
}

template <typename Block>
void BasicBitSet<Block>::reset() {
    memset(bits, 0, bitsSize * BlockSize);
}

template <typename Block>
void BasicBitSet<Block>::flip(const size_t ind) {
    assert(ind < length);
    ::FlipBit<Block>(bits[::BlockInd<Block>(ind)] , ::BitIndInBlock<Block>(ind));
}

template <typename Block>
void BasicBitSet<Block>::flip() {
    for (size_t i = 0; i < bitsSize; ++i) {
        bits[i] = ~bits[i];
    }
    if (!full) {
        bits[bitsSize - 1] |= ::GetOnes<Block>(length - (bitsSize - 1) * BitsPerBlock);
    }
}

template <typename Block>
BasicBitSet<Block> BasicBitSet<Block>::operator ~() const {
    BasicBitSet res(*this);
    res.flip();
    return res;
}

template <typename Block>
bool BasicBitSet<Block>::is_subset_of(const BasicBitSet<Block>& a) const {
    assert(a.length == length);
    for (size_t i = 0; i < bitsSize; ++i) {
        if (bits[i] & ~a.bits[i]) {
            return false;
        }
    }
    return true;
}

template <typename Block>
bool BasicbitSet<Block>::is_proper_subset_of(const BasicBitSet<Block>& a) const {
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

