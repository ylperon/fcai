# pragma once

# ifndef FCA_CONTEXT_H_
# define FCA_CONTEXT_H_

# include <vector>

# include "fca_definitions.h"

namespace FCA
{
    class Context
    {
    protected:
        std::vector<Object> m_objects;
        std::vector<std::vector<size_t> > m_objectsIntent;
        std::vector<Attribute> m_attributes;
        std::vector<std::vector<size_t> > m_attributesExtent;
        std::vector<BitSet> m_table;
        std::vector<BitSet> m_tableT;
        size_t m_objCnt;
        size_t m_attrCnt;

        void CheckAttributeCnt(const size_t attrCnt) const;
        void CheckObjectCnt(const size_t objCnt) const;
        void CheckAttributeInd(const size_t attrInd) const;
        void CheckObjectInd(const size_t objInd) const;

    public:
        Context() {}
        Context(const std::vector<Object> &iObjects, const std::vector<Attribute> &iAttributes, const std::vector<std::vector<bool> > &iTable);	
        Context(const std::vector<Object> &iObjects, const std::vector<Attribute> &iAttributes, const std::vector<BitSet> &iTable);

        const std::vector<Object> &getObjects() const	{ return m_objects; }
        const std::vector<Attribute> &getAttributes() const { return m_attributes; }
        size_t getObjectsCnt() const { return m_objCnt; }
        size_t getAttributesCnt() const { return m_attrCnt; }

        size_t getObjectIndex(const Object &obj) const;
        size_t getAttributeIndex(const Attribute &attr) const;

        std::vector<Attribute> getObjIntentByIndex(const size_t ind) const;	
        std::vector<size_t> getObjIntentIndByIndex(const size_t ind) const;
        BitSet getObjIntentAsBitSetByIndex(const size_t ind) const;
        std::vector<Attribute> getObjIntent(const std::string &obj) const;

        std::vector<Object> getAttrExtentByIndex(const size_t ind) const;	
        std::vector<size_t> getAttrExtentIndByIndex(const size_t ind) const;		
        BitSet getAttrExtentAsBitSetByIndex(const size_t ind) const;
        std::vector<Object> getAttrExtent(const std::string &obj) const;

        bool getValueByIndex(size_t indObj, size_t indAttr) const;
        bool getValue(Object obj, Attribute attr) const;
        
        BitSet drvtAttr(const BitSet &current) const;
        BitSet closeAttr(const BitSet &current) const;
        std::vector<Attribute> closeAttr(const std::vector<Attribute> &current) const;
        
        BitSet drvtObj(const BitSet &current) const;
        BitSet closeObj(const BitSet &current) const;
        std::vector<Attribute> closeObj(const std::vector<Object> &current) const;
    };
};

# endif //FCA_CONTEXT_H_