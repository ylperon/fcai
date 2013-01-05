# include "fca_bitset.h"

# include <sstream>

# ifdef BOOST_BITSET_ON

FCA::BitSet::BitSet(const size_t newSize) : mBS(newSize) {}

FCA::BitSet::BitSet(const FCA::BitSet& a) : mBS(a.mBS) {}

bool FCA::BitSet::none() const
{ 
    return mBS.none(); 
}

bool FCA::BitSet::test(const size_t ind) const 
{ 
    return mBS.test(ind);
}

void FCA::BitSet::set(const size_t ind) 
{
    mBS.set(ind);
}

void FCA::BitSet::set() 
{ 
    mBS.set();
}

void FCA::BitSet::reset(const size_t ind)
{ 
    mBS.reset(ind);
}

void FCA::BitSet::reset() 
{
    mBS.reset();
}

void FCA::BitSet::flip() 
{ 
    mBS.flip(); 
}

bool FCA::BitSet::is_subset_of(const FCA::BitSet& a) const 
{ 
    return mBS.is_subset_of(a.mBS); 
}

bool FCA::BitSet::is_proper_subset_of(const FCA::BitSet& a) const
{ 
    return mBS.is_proper_subset_of(a.mBS); 
}

size_t FCA::BitSet::size() const 
{ 
    return mBS.size();
}

void FCA::BitSet::resize(const size_t new_size)
{
    return mBS.resize(new_size);
}

size_t FCA::BitSet::count() const 
{ 
    return mBS.count(); 
}

FCA::BitSet& FCA::BitSet::operator |=(const FCA::BitSet& a) 
{ 
    mBS |= a.mBS; 
    return *this;
}

FCA::BitSet& FCA::BitSet::operator -=(const FCA::BitSet& a) 
{ 
    mBS -= a.mBS; 
    return *this;
}

FCA::BitSet& FCA::BitSet::operator &=(const FCA::BitSet& a) 
{
    mBS &= a.mBS;
    return *this; 
}

size_t FCA::BitSet::findFirst() const
{
    return mBS.find_first();
}

size_t FCA::BitSet::findNext(const size_t pos) const
{
    return mBS.find_next(pos);
}

bool FCA::operator ==(const FCA::BitSet& a, const FCA::BitSet& b)
{
    return a.mBS == b.mBS; 
}

bool FCA::operator !=(const FCA::BitSet& a, const FCA::BitSet& b)
{
    return a.mBS != b.mBS; 
}

bool FCA::operator <(const FCA::BitSet& a, const FCA::BitSet& b)
{
    return a.mBS < b.mBS;
}

bool FCA::operator <=(const FCA::BitSet& a, const FCA::BitSet& b)
{
    return a.mBS <= b.mBS;
}

bool FCA::operator >(const FCA::BitSet& a, const FCA::BitSet& b)
{
    return a.mBS > b.mBS;
}

bool FCA::operator >=(const FCA::BitSet& a, const FCA::BitSet& b)
{
    return a.mBS >= b.mBS;
}

FCA::BitSet FCA::operator &(const FCA::BitSet& a, const FCA::BitSet& b)
{
    return BitSet(a) &= b;
}

FCA::BitSet FCA::operator |(const FCA::BitSet& a, const FCA::BitSet& b)
{
    return BitSet(a) |= b;
}

FCA::BitSet FCA::operator ^(const FCA::BitSet& a, const FCA::BitSet& b)
{
    return BitSet(a) ^= b;
}

FCA::BitSet FCA::operator -(const FCA::BitSet& a, const FCA::BitSet& b)
{
    return BitSet(a) -= b;
}

void FCA::ToString(const FCA::BitSet& a, std::string& s)
{
    s.reserve(a.size());
    for (size_t i = 0; i < a.size(); ++i)
    {
        if (a.test(i))
            s += "1";
        else
            s += "0";
    }
}

void FCA::ToIndList(const FCA::BitSet& a, std::string& s, const std::string& delimiter)
{
    std::stringstream ss;
    const size_t first = a.findFirst();
    if (FCA::BitSet::npos != first)
    {
        ss << first;
    }

    for (size_t i = a.findNext(first); i != FCA::BitSet::npos; i = a.findNext(i))
    {
        ss << delimiter << i;
    }

    s = ss.str();
}

# endif //BOOST_BITSET_ON

# ifdef MAGIC_BITSET_ON

FCA::BitSet::BitSet(const size_t new_size) : mBS(new_size) {}

FCA::BitSet::BitSet(const FCA::BitSet& a) : mBS(a.mBS) {}

bool FCA::BitSet::none() const
{ 
    return mBS.none(); 
}

bool FCA::BitSet::test(const size_t ind) const 
{ 
    return mBS.test(ind);
}

void FCA::BitSet::set(const size_t ind) 
{
    mBS.set(ind);
}

void FCA::BitSet::set() 
{ 
    mBS.set();
}

void FCA::BitSet::reset(const size_t ind)
{ 
    mBS.set(ind, false);
}

void FCA::BitSet::reset() 
{
    mBS.reset();
}

void FCA::BitSet::flip() 
{ 
    mBS.flip(); 
}

bool FCA::BitSet::is_subset_of(const FCA::BitSet& a) const 
{ 
    for (size_t i = 0; i < mBS.size(); ++i)
    {
        if (!a.mBS.test(i)& & mBS.test(i))
        {
            return false;
        }
    }

    return true;
}

bool FCA::BitSet::is_proper_subset_of(const FCA::BitSet& a) const
{ 
    return is_subset_of(a)& & mBS != a.mBS;
}

size_t FCA::BitSet::size() const 
{ 
    return mBS.size();
}

void FCA::BitSet::resize(const size_t new_size)
{
    return mBS.resize(new_size);
}

size_t FCA::BitSet::count() const 
{ 
    return mBS.count(); 
}

FCA::BitSet& FCA::BitSet::operator |=(const FCA::BitSet& a) 
{ 
    mBS |= a.mBS; 
    return *this;
}

FCA::BitSet& FCA::BitSet::operator -=(const FCA::BitSet& a) 
{ 
    mBS -= a.mBS; 
    return *this;
}

FCA::BitSet& FCA::BitSet::operator& =(const FCA::BitSet& a) 
{
    mBS& = a.mBS;
    return *this; 
}

bool FCA::BitSet::operator ==(const FCA::BitSet& a) 
{
    return mBS == a.mBS; 
}

bool FCA::BitSet::operator !=(const FCA::BitSet& a) 
{
    return mBS != a.mBS; 
}

FCA::BitSet FCA::operator -(const FCA::BitSet& a, const FCA::BitSet& b)
{
    BitSet tmp(a);
    return tmp -= b;
}

FCA::BitSet FCA::operator& (const FCA::BitSet& a, const FCA::BitSet& b)
{
    BitSet tmp(a);
    return tmp& = b;
}

# endif //MAGIC_BITSET_ON