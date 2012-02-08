# include "fca_bitset.h"

# ifdef BOOST_BITSET_ON

FCA::BitSet::BitSet(const size_t new_size) : m_bs(new_size) {}

FCA::BitSet::BitSet(const FCA::BitSet &a) : m_bs(a.m_bs) {}

bool FCA::BitSet::none() const
{ 
    return m_bs.none(); 
}

bool FCA::BitSet::test(const size_t ind) const 
{ 
    return m_bs.test(ind);
}

void FCA::BitSet::set(const size_t ind) 
{
    m_bs.set(ind);
}

void FCA::BitSet::set() 
{ 
    m_bs.set();
}

void FCA::BitSet::reset(const size_t ind)
{ 
    m_bs.reset(ind);
}

void FCA::BitSet::reset() 
{
    m_bs.reset();
}

void FCA::BitSet::flip() 
{ 
    m_bs.flip(); 
}

bool FCA::BitSet::is_subset_of(const FCA::BitSet &a) const 
{ 
    return m_bs.is_subset_of(a.m_bs); 
}

bool FCA::BitSet::is_proper_subset_of(const FCA::BitSet &a) const
{ 
    return m_bs.is_proper_subset_of(a.m_bs); 
}

size_t FCA::BitSet::size() const 
{ 
    return m_bs.size();
}

void FCA::BitSet::resize(const size_t new_size)
{
    return m_bs.resize(new_size);
}

size_t FCA::BitSet::count() const 
{ 
    return m_bs.count(); 
}

FCA::BitSet &FCA::BitSet::operator |=(const FCA::BitSet &a) 
{ 
    m_bs |= a.m_bs; 
    return *this;
}

FCA::BitSet &FCA::BitSet::operator -=(const FCA::BitSet &a) 
{ 
    m_bs -= a.m_bs; 
    return *this;
}

FCA::BitSet &FCA::BitSet::operator &=(const FCA::BitSet &a) 
{
    m_bs &= a.m_bs;
    return *this; 
}

bool FCA::BitSet::operator ==(const FCA::BitSet &a) 
{
    return m_bs == a.m_bs; 
}

bool FCA::BitSet::operator !=(const FCA::BitSet &a) 
{
    return m_bs != a.m_bs; 
}

FCA::BitSet FCA::operator -(const FCA::BitSet &a, const FCA::BitSet &b)
{
    BitSet tmp(a);
    return tmp -= b;
}

FCA::BitSet FCA::operator &(const FCA::BitSet &a, const FCA::BitSet &b)
{
    BitSet tmp(a);
    return tmp &= b;
}

# endif //BOOST_BITSET_ON

# ifdef MAGIC_BITSET_ON

FCA::BitSet::BitSet(const size_t new_size) : m_bs(new_size) {}

FCA::BitSet::BitSet(const FCA::BitSet &a) : m_bs(a.m_bs) {}

bool FCA::BitSet::none() const
{ 
    return m_bs.none(); 
}

bool FCA::BitSet::test(const size_t ind) const 
{ 
    return m_bs.test(ind);
}

void FCA::BitSet::set(const size_t ind) 
{
    m_bs.set(ind);
}

void FCA::BitSet::set() 
{ 
    m_bs.set();
}

void FCA::BitSet::reset(const size_t ind)
{ 
    m_bs.set(ind, false);
}

void FCA::BitSet::reset() 
{
    m_bs.reset();
}

void FCA::BitSet::flip() 
{ 
    m_bs.flip(); 
}

bool FCA::BitSet::is_subset_of(const FCA::BitSet &a) const 
{ 
    for (size_t i = 0; i < m_bs.size(); ++i)
    {
        if (!a.m_bs.test(i) && m_bs.test(i))
        {
            return false;
        }
    }

    return true;
}

bool FCA::BitSet::is_proper_subset_of(const FCA::BitSet &a) const
{ 
    return is_subset_of(a) && m_bs != a.m_bs;
}

size_t FCA::BitSet::size() const 
{ 
    return m_bs.size();
}

void FCA::BitSet::resize(const size_t new_size)
{
    return m_bs.resize(new_size);
}

size_t FCA::BitSet::count() const 
{ 
    return m_bs.count(); 
}

FCA::BitSet &FCA::BitSet::operator |=(const FCA::BitSet &a) 
{ 
    m_bs |= a.m_bs; 
    return *this;
}

FCA::BitSet &FCA::BitSet::operator -=(const FCA::BitSet &a) 
{ 
    m_bs -= a.m_bs; 
    return *this;
}

FCA::BitSet &FCA::BitSet::operator &=(const FCA::BitSet &a) 
{
    m_bs &= a.m_bs;
    return *this; 
}

bool FCA::BitSet::operator ==(const FCA::BitSet &a) 
{
    return m_bs == a.m_bs; 
}

bool FCA::BitSet::operator !=(const FCA::BitSet &a) 
{
    return m_bs != a.m_bs; 
}

FCA::BitSet FCA::operator -(const FCA::BitSet &a, const FCA::BitSet &b)
{
    BitSet tmp(a);
    return tmp -= b;
}

FCA::BitSet FCA::operator &(const FCA::BitSet &a, const FCA::BitSet &b)
{
    BitSet tmp(a);
    return tmp &= b;
}

# endif //MAGIC_BITSET_ON