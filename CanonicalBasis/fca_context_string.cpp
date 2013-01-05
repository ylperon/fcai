# include "fca_context_string.h"

# include <cstring>
# include <stdexcept>

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

void Read(FILE* input, ContextString& cxt)
{
    static const size_t MAX_NAME_LENGTH = 100000;
    static char buffer[MAX_NAME_LENGTH];

    fgets(buffer, MAX_NAME_LENGTH, input);
    if (0 != strncmp("B", buffer, MAX_NAME_LENGTH))
    {
        throw std::runtime_error("in Read(FILE*, ContextString&) \"B\" expected");
    }

    size_t objSize;
    size_t attrSize;
    if (2 != fscanf(input, "\n%u%u\n", &objSize, &attrSize))
    {
        throw std::runtime_error("in Read(FILE*, ContextString&) two "
                                 "unsigned integers expected");
    }

    /*
    reading object names
    */
    std::vector<std::string> obj(objSize);
    for (size_t i = 0; i < objSize; ++i)
    {
        if (0 == fgets(buffer, MAX_NAME_LENGTH, input))
        {
            throw std::runtime_error("in Read(FILE*, ContextString&) object "
                                     "name expected");
        }

        const size_t length = strlen(buffer);
        buffer[length - 1] = 0;
        obj[i] += buffer;
    }

    /*
    reading attribute names
    */
    std::vector<std::string> attr(attrSize);
    for (size_t i = 0; i < attrSize; ++i)
    {
        if (0 == fgets(buffer, MAX_NAME_LENGTH, input))
        {
            throw std::runtime_error("in Read(FILE*, ContextString&) attribute "
                                     "name expected");
        }

        const size_t length = strlen(buffer);
        buffer[length - 1] = 0;
        attr[i] += buffer;
    }

    /*
    reading table names
    */
    std::vector<BitSet> table(objSize, BitSet(attrSize));
    for (size_t i = 0; i < objSize; ++i)
    {
        if (0 == fgets(buffer, MAX_NAME_LENGTH, input))
        {
            throw std::runtime_error("in Read(FILE*, ContextString&) row "
                                     "of attributes expected");
        }

        if (strlen(buffer) != attrSize + 1)
        {
            throw std::runtime_error("in Read(FILE*, ContextString&) row "
                                     "length is different from number of attributes");
        }

        BitSet& objCur = table[i];
        for (size_t j = 0; j < attrSize; ++j)
        {
            if ('X' == buffer[j])
            {
                objCur.set(j);
            }
            else if ('.' != buffer[j])
            {
                throw std::runtime_error("in Read(FILE*, ContextString&) "
                                         "\'X\' or \'.\' expected");
            }
        }
    }

    cxt = ContextString(table, obj, attr);
}

void Write(FILE* output, const ContextString& cxt)
{
    const size_t objSize = cxt.SizeObj();
    const size_t attrSize = cxt.SizeAttr();
    
    fprintf(output, "B\n\n%u\n%u\n\n", objSize, attrSize);
    for (size_t i = 0; i < objSize; ++i)
    {
        fprintf(output, "%s\n", cxt.GetObjName(i).c_str());
    }
    for (size_t i = 0; i < attrSize; ++i)
    {
        fprintf(output, "%s\n", cxt.GetAttrName(i).c_str());
    }

    for (size_t i = 0; i < objSize; ++i)
    {
        for (size_t j = 0; j < attrSize; ++j)
        {
            if (cxt.Get(i, j))
            {
                fprintf(output, "X");
            }
            else
            {
                fprintf(output, ".");
            }
        }
        fprintf(output, "\n");
    }
}