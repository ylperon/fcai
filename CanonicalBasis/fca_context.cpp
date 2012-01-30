# include <set>
# include <map>
# include <stdexcept>
# include <algorithm>

# include "fca_context.h"

FCA::Context::Context(const std::vector<FCA::Object> &iObjects, const std::vector<FCA::Attribute> &iAttributes, 
                      const std::vector<std::vector<bool> > &iTable)
{
    if (iTable.size() != iObjects.size())			
        throw std::invalid_argument("number of object and number of rows of table must agree");

    if (!iTable.empty() && iTable.front().size() != iAttributes.size())
        throw std::invalid_argument("number of attributes and number of coloms of table must agree");	

    m_objects = iObjects;
    m_objCnt = m_objects.size();
    m_attributes = iAttributes;	
    m_attrCnt = m_attributes.size();
    m_objectsIntent.resize(m_objCnt);
    m_attributesExtent.resize(m_attrCnt);
    m_table = std::vector<BitSet>(m_objCnt, BitSet(m_attrCnt));

    for (size_t objInd = 0; objInd < m_objCnt; ++objInd)
    {
        m_table[objInd].reset();
        for (size_t attrInd = 0; attrInd < m_attrCnt; ++attrInd)
            if (iTable[objInd][attrInd])
            {
                m_table[objInd].set(attrInd);
                m_objectsIntent[objInd].push_back(attrInd);
            }
    }

    m_tableT = std::vector<BitSet>(m_attrCnt, BitSet(m_objCnt));

    for (size_t attrInd = 0; attrInd < m_attrCnt; ++attrInd)
    {
        m_tableT[attrInd].reset();
        for (size_t objInd = 0; objInd < m_objCnt; ++objInd)
            if (iTable[objInd][attrInd])
            {
                m_tableT[attrInd].set(objInd);
                m_attributesExtent[attrInd].push_back(objInd);
            }
    }
}

FCA::Context::Context(const std::vector<Object> &iObjects, const std::vector<Attribute> &iAttributes, const std::vector<FCA::BitSet> &iTable)
{
    if (iTable.size() != iObjects.size())			
        throw std::invalid_argument("number of object and number of rows of table must agree");

    if (!iTable.empty() && iTable.front().size() != iAttributes.size())
        throw std::invalid_argument("number of attributes and number of coloms of table must agree");	

    m_objects = iObjects;
    m_objCnt = m_objects.size();
    m_attributes = iAttributes;	
    m_attrCnt = m_attributes.size();
    m_objectsIntent.resize(m_objCnt);
    m_attributesExtent.resize(m_attrCnt);
    m_table = std::vector<BitSet>(m_objCnt, BitSet(m_attrCnt));

    for (size_t objInd = 0; objInd < m_objCnt; ++objInd)
    {
        m_table[objInd].reset();
        for (size_t attrInd = 0; attrInd < m_attrCnt; ++attrInd)
            if (iTable[objInd].test(attrInd))
            {
                m_table[objInd].set(attrInd);
                m_objectsIntent[objInd].push_back(attrInd);
            }
    }

    m_tableT = std::vector<BitSet>(m_attrCnt, BitSet(m_objCnt));

    for (size_t attrInd = 0; attrInd < m_attrCnt; ++attrInd)
    {
        m_tableT[attrInd].reset();
        for (size_t objInd = 0; objInd < m_objCnt; ++objInd)
            if (iTable[objInd].test(attrInd))
            {
                m_tableT[attrInd].set(objInd);
                m_attributesExtent[attrInd].push_back(objInd);
            }
    }
}

size_t FCA::Context::getObjectIndex(const FCA::Object &obj) const
{
    std::vector<std::string>::const_iterator it = std::find(m_objects.begin(), m_objects.end(), obj);

    if (it == m_objects.end())
    {
        throw std::invalid_argument("there is no such object");
    }

    return it - m_objects.begin();
}

size_t FCA::Context::getAttributeIndex(const FCA::Attribute &attr) const
{
    std::vector<std::string>::const_iterator it = std::find(m_attributes.begin(), m_attributes.end(), attr);

    if (it == m_attributes.end())
    {
        throw std::invalid_argument("there is no such attribute");
    }

    return it - m_attributes.begin();
}

std::vector<FCA::Attribute> FCA::Context::getObjIntentByIndex(const size_t ind) const
{
    CheckObjectInd(ind);

    std::vector<Attribute> res;		

    for (size_t i = 0; i < m_objectsIntent[ind].size(); ++i)
        res.push_back(m_attributes[m_objectsIntent[ind][i]]);

    return res;
}

std::vector<size_t> FCA::Context::getObjIntentIndByIndex(const size_t ind) const
{
    CheckObjectInd(ind);

    return m_objectsIntent[ind];
}

FCA::BitSet FCA::Context::getObjIntentAsBitSetByIndex(const size_t ind) const
{
    CheckObjectInd(ind);

    return m_table[ind];
}

std::vector<FCA::Object> FCA::Context::getAttrExtentByIndex(const size_t ind) const
{	
    CheckAttributeInd(ind);

    std::vector<Object> res;

    for (size_t i = 0; i < m_attributesExtent[ind].size(); ++i)
        res.push_back(m_objects[m_attributesExtent[ind][i]]);

    return res;
}

std::vector<size_t> FCA::Context::getAttrExtentIndByIndex(const size_t ind) const
{
    CheckAttributeInd(ind);

    return m_attributesExtent[ind];
}

FCA::BitSet FCA::Context::getAttrExtentAsBitSetByIndex(const size_t ind) const
{
    CheckAttributeInd(ind);

    return m_tableT[ind];
}

std::vector<FCA::Attribute> FCA::Context::getObjIntent(const FCA::Object &obj) const
{
    size_t ind = getObjectIndex(obj);

    return getObjIntentByIndex(ind);
}

std::vector<FCA::Object> FCA::Context::getAttrExtent(const FCA::Attribute &attr) const
{
    size_t ind = getAttributeIndex(attr);	

    return getAttrExtentByIndex(ind);
}

bool FCA::Context::getValueByIndex(size_t indObj, size_t indAttr) const
{
    CheckAttributeInd(indAttr);
    CheckObjectInd(indObj);

    return m_table[indObj].test(indAttr);
}

bool FCA::Context::getValue(FCA::Object obj, FCA::Attribute attr) const
{
    size_t indObj = getObjectIndex(obj);
    size_t indAttr = getAttributeIndex(attr);

    return m_table[indObj].test(indAttr);
}

FCA::BitSet FCA::Context::drvtAttr(const FCA::BitSet &current) const
{
    CheckAttributeCnt(current.size());

    BitSet res(m_objCnt);
    res.set();

    for (size_t attrCur = 0; attrCur < m_attrCnt; ++attrCur)
    {
        if (current.test(attrCur))
        {
            res &= m_tableT[attrCur];
        }
    }

    return res;
}

FCA::BitSet FCA::Context::closeAttr(const FCA::BitSet &current) const
{
    CheckAttributeCnt(current.size());

    if (current.none())
        return current;

    BitSet res(m_attrCnt);
    res.set();

    for (size_t i = 0; i < m_objCnt; ++i)	
        if (current.is_subset_of(m_table[i]))
        {
            res &= m_table[i];
        }	

    return res;
}

std::vector<FCA::Attribute> FCA::Context::closeAttr(const std::vector<FCA::Attribute> &current) const
{
    std::map<std::string, size_t> indexer;
    for (size_t i = 0; i < m_attrCnt; ++i)
        indexer[m_attributes[i]] = i;

    BitSet tmp(m_attrCnt);
    tmp.reset();
    for (size_t i = 0; i < current.size(); ++i)
        tmp.set(indexer[current[i]]);

    tmp = closeAttr(tmp);

    std::vector<FCA::Attribute> res;
    for (size_t i = 0; i < m_attrCnt; ++i)
        if (tmp.test(i))
            res.push_back(m_attributes[i]);

    return res;
}

FCA::BitSet FCA::Context::drvtObj(const FCA::BitSet &current) const
{
    CheckObjectCnt(current.size());

    BitSet res(m_attrCnt);
    res.set();

    for (size_t objCur = 0; objCur < m_objCnt; ++objCur)
    {
        if (current.test(objCur))
        {
            res &= m_table[objCur];
        }
    }

    return res;
}

FCA::BitSet FCA::Context::closeObj(const FCA::BitSet &current) const
{
    CheckObjectCnt(current.size());

    if (current.none())
        return current;

    BitSet res(m_objCnt);
    res.set();

    for (size_t i = 0; i < m_attrCnt; ++i)	
        if (current.is_subset_of(m_tableT[i]))
        {
            res &= m_tableT[i];
        }	

    return res;
}

std::vector<FCA::Attribute> FCA::Context::closeObj(const std::vector<FCA::Object> &current) const
{
    std::map<std::string, size_t> indexer;
    for (size_t i = 0; i < m_attrCnt; ++i)
        indexer[m_objects[i]] = i;

    BitSet tmp(m_objCnt);
    tmp.reset();
    for (size_t i = 0; i < current.size(); ++i)
        tmp.set(indexer[current[i]]);

    tmp = closeObj(tmp);

    std::vector<FCA::Object> res;
    for (size_t i = 0; i < m_objCnt; ++i)
        if (tmp.test(i))
            res.push_back(m_objects[i]);

    return res;
}

void FCA::Context::CheckAttributeCnt(const size_t attrCnt) const
{
    if (attrCnt != m_attrCnt)
    {
        throw std::invalid_argument("input number of attributes must agree with number of attribute of context");
    }
}

void FCA::Context::CheckObjectCnt(const size_t objCnt) const
{
    if (objCnt != m_objCnt)
    {
        throw std::invalid_argument("input number of objects must agree with number of attributes of context");
    }
}

void FCA::Context::CheckAttributeInd(const size_t attrInd) const
{
    if (attrInd >= m_attrCnt)
    {
        throw std::out_of_range("index of attribute is too big");
    }
}

void FCA::Context::CheckObjectInd(const size_t objInd) const
{
    if (objInd >= m_objCnt)
    {
        throw std::out_of_range("index of object is too big");
    }
}