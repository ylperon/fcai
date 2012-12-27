# include "fca_context_string.h"

using namespace FCA;

ContextString::ContextString()
    : Context() {}

ContextString::ContextString(const Context& cxt)
    : Context(cxt),
    mObjName(cxt.SizeObj()),
    mAttrName(cxt.SizeAttr()) {}

ContextString::ContextString(const size_t& objSize, const size_t& attrSize)
    : Context(objSize, attrSize),
    mObjName(objSize),
    mAttrName(attrSize) {}

ContextString::ContextString(const size_t& objSize,
                             const size_t& attrSize,
                             const std::vector<std::string>& objName,
                             const std::vector<std::string>& attrName)
                             : Context(objSize, attrSize),
                             mObjName(objName),
                             mAttrName(attrName)
{
    CheckSetSizeAndThrowError(mObjName.size(), mObjSize, "objects count does not match in "
                              "ContextString::ContextString(const size_t&, const size_t&, "
                              "const std::vector<std::string>&, const std::vector<std::string>&)");
    CheckSetSizeAndThrowError(mAttrName.size(), mAttrSize, "attributes count does not match in "
                              "ContextString::ContextString(const size_t&, const size_t&, "
                              "const std::vector<std::string>&, const std::vector<std::string>&)");
}

ContextString::ContextString(const std::vector<std::vector<bool> >& table)
    : Context(table),
    mObjName(mObjSize),
    mAttrName(mAttrSize) {}

ContextString::ContextString(const std::vector<std::vector<bool> >& table,
                             const std::vector<std::string>& objName,
                             const std::vector<std::string>& attrName)
                             : Context(table),
                             mObjName(objName),
                             mAttrName(attrName)
{
   CheckSetSizeAndThrowError(mObjName.size(), mObjSize, "objects count does not match in "
                             "ContextString::ContextString(const std::vector<std::vector<bool> >&, "
                             "const std::vector<std::string>&, "
                             "const std::vector<std::string>&)");
   CheckSetSizeAndThrowError(mAttrName.size(), mAttrSize, "attributes count does not match in "
                             "ContextString::ContextString(const std::vector<std::vector<bool> >&, "
                             "const std::vector<std::string>&, "
                             "const std::vector<std::string>&)");
}

ContextString::ContextString(const std::vector<FCA::BitSet>& table)
    : Context(table),
    mObjName(mObjSize),
    mAttrName(mAttrSize) {}

ContextString::ContextString(const std::vector<FCA::BitSet>& table,
                             const std::vector<std::string>& objName,
                             const std::vector<std::string>& attrName)
                             : Context(table),
                             mObjName(objName),
                             mAttrName(attrName)
{
   CheckSetSizeAndThrowError(mObjName.size(), mObjSize, "objects count does not match in "
                             "ContextString::ContextString(const std::vector<FCA::BitSet>&, "
                             "const std::vector<std::string>&, "
                             "const std::vector<std::string>&)");
   CheckSetSizeAndThrowError(mAttrName.size(), mAttrSize, "attributes count does not match in "
                             "ContextString::ContextString(const std::vector<FCA::BitSet>&, "
                             "const std::vector<std::string>&, "
                             "const std::vector<std::string>&)");
}

ContextString& ContextString::operator =(const ContextString& cxt)
{
    if (&cxt == this)
    {
        return *this;
    }

    Context::operator=(cxt);
    mObjName = cxt.mObjName;
    mAttrName = cxt.mAttrName;

    return *this;
}

void ContextString::SetObjName(const size_t& objInd, const std::string& name)
{
    CheckRangeAndThrowError(objInd, mObjSize, "object index out of range in "
                            "ContextString::SetObjName(const size_t&, const std::string&)");
    mObjName[objInd] = name;
}

const std::string& ContextString::GetObjName(const size_t& objInd) const
{
    CheckRangeAndThrowError(objInd, mObjSize, "object index out of range in "
                            "ContextString::GetObjName(const size_t&)");
    return mObjName[objInd];
}

void ContextString::SetAttrName(const size_t& attrInd, const std::string& name)
{
    CheckRangeAndThrowError(attrInd, mAttrSize, "attribute index out of range in "
                            "ContextString::SetAttrName(const size_t&, const std::string&)");
    mAttrName[attrInd] = name;
}

const std::string& ContextString::GetAttrName(const size_t& attrInd) const
{
    CheckRangeAndThrowError(attrInd, mAttrSize, "attribute index out of range in "
                            "ContextString::GetAttrName(const size_t&)");
    return mAttrName[attrInd];
}