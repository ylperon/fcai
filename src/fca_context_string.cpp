# include "fca_context_string.h"

# include <cstring>
# include <cassert>
# include <exception>

FCA::ContextString::ContextString()
    : Context() {
}

FCA::ContextString::ContextString(const FCA::Context& cxt)
    : Context(cxt),
    objName(cxt.objSize),
    attrName(cxt.attrSize) {
}

FCA::ContextString::ContextString(const size_t& objSize, const size_t& attrSize)
    : Context(objSize, attrSize),
    objName(objSize),
    attrName(attrSize) {
}

FCA::ContextString::ContextString(const size_t& objSize,
                                  const size_t& attrSize,
                                  const std::vector<std::string>& objName,
                                  const std::vector<std::string>& attrName)
    : Context(objSize, attrSize),
    objName(objName),
    attrName(attrName) {
        assert(objSize == objName.size());
        assert(attrSize == attrName.size());
}

FCA::ContextString::ContextString(const std::vector<std::vector<bool> >& table)
    : Context(table) {
        objName.resize(objName);
        attrName.resize(attrName);
}

FCA::ContextString::ContextString(const std::vector<std::vector<bool> >& table,
                                  const std::vector<std::string>& objName,
                                  const std::vector<std::string>& attrName)
    : Context(table),
    objName(objName),
    attrName(attrName) {
        assert(objName.size() == objSize);
        assert(attrName.size() == attrSize);
}

FCA::ContextString::ContextString(const FCA::BitSetVector& table)
    : Context(table) {
        objName.resize(objSize);
        attrName.resize(attrSize);
}

FCA::ContextString::ContextString(const BitSetVector& table,
                                  const std::vector<std::string>& objName,
                                  const std::vector<std::string>& attrName)
    : Context(table),
    objName(objName),
    attrName(attrName) {
        assert(objName.size() == objSize);
        assert(attrName.size() == attrSize);
}

FCA::ContextString& FCA::ContextString::operator =(const ContextString& cxt) {
    if (&cxt == this) {
        return *this;
    }

    Context::operator=(cxt);
    mObjName = cxt.mObjName;
    mAttrName = cxt.mAttrName;
    return *this;
}

void FCA::ContextString::SetObjName(const size_t& objInd, const std::string& name) {
    assert(objInd < objSize);
    mObjName[objInd] = name;
}

const std::string& FCA::ContextString::GetObjName(const size_t& objInd) const {
    assert(objInd < objSize);
    return mObjName[objInd];
}

void FCA::ContextString::SetAttrName(const size_t& attrInd, const std::string& name) {
    assert(attrInd < attrSize);
    mAttrName[attrInd] = name;
}

const std::string& FCA::ContextString::GetAttrName(const size_t& attrInd) const {
    assert(attrInd < attrSize);
    return mAttrName[attrInd];
}

void FCA::Read(FILE* input, FCA::ContextString& cxt) {
    static const size_t MAX_NAME_LENGTH = 100000;
    static char buffer[MAX_NAME_LENGTH];

    fgets(buffer, MAX_NAME_LENGTH, input);
    if (0 != strncmp("B\n", buffer, MAX_NAME_LENGTH)) {
        throw std::runtime_error("\"B\" expected");
    }

    size_t objSize;
    size_t attrSize;
    if (2 != fscanf(input, "\n%u%u\n", &objSize, &attrSize)) {
        throw std::runtime_error("two unsigned integers expected");
    }

    //reading object names
    std::vector<std::string> obj(objSize);
    for (size_t i = 0; i < objSize; ++i) {
        if (0 == fgets(buffer, MAX_NAME_LENGTH, input)) {
            throw std::runtime_error("object name expected");
        }

        const size_t length = strlen(buffer);
        buffer[length - 1] = 0;
        obj[i] += buffer;
    }

    //reading attribute names
    std::vector<std::string> attr(attrSize);
    for (size_t i = 0; i < attrSize; ++i) {
        if (0 == fgets(buffer, MAX_NAME_LENGTH, input)) {
            throw std::runtime_error("attribute name expected");
        }

        const size_t length = strlen(buffer);
        buffer[length - 1] = 0;
        attr[i] += buffer;
    }

    //reading table names
    std::vector<FCA::BitSet> table(objSize, FCA::BitSet(attrSize));
    for (size_t i = 0; i < objSize; ++i) {
        if (0 == fgets(buffer, MAX_NAME_LENGTH, input)) {
            throw std::runtime_error("row of attributes expected");
        }

        if (strlen(buffer) != attrSize + 1) {
            throw std::runtime_error("row length is different from number of attributes");
        }

        BitSet& objCur = table[i];
        for (size_t j = 0; j < attrSize; ++j) {
            if ('X' == buffer[j]) {
                objCur.set(j);
            } else if ('.' != buffer[j]) {
                throw std::runtime_error("\'X\' or \'.\' expected");
            }
        }
    }
    cxt = ContextString(table, obj, attr);
}

void FCA::Write(FILE* output, const FCA::ContextString& cxt) {
    const size_t& objSize = cxt.SizeObj();
    const size_t& attrSize = cxt.SizeAttr();

    fprintf(output, "B\n\n%u\n%u\n\n", objSize, attrSize);
    for (size_t i = 0; i < objSize; ++i) {
        fprintf(output, "%s\n", cxt.GetObjName(i).c_str());
    }
    for (size_t i = 0; i < attrSize; ++i) {
        fprintf(output, "%s\n", cxt.GetAttrName(i).c_str());
    }

    for (size_t i = 0; i < objSize; ++i) {
        for (size_t j = 0; j < attrSize; ++j) {
            if (cxt.Get(i, j)) {
                fprintf(output, "X");
            } else {
                fprintf(output, ".");
            }
        }
        fprintf(output, "\n");
    }
}
