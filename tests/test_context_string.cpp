#include "test_context_string.h"

#include <cstdio>

#include <vector>

TestFunctionGroup TestContextStringAll("TestContextString", &TestContextString);

TestFunctionVector GetAllContextStringTestFunctions() {
    TestFunctionVector res;
    res.push_back(TestFunction("TestContextStringDefaultConstructor", &TestContextStringDefaultConstructor));
    res.push_back(TestFunction("TestContextStringContextConstructor", &TestContextStringContextConstructor));
    res.push_back(TestFunction("TestContextStringTwoSizeConstructor", &TestContextStringTwoSizeConstructor));
    res.push_back(TestFunction("TestContextStringNamesConstructor", &TestContextStringNamesConstructor));
    res.push_back(TestFunction("TestContextStringBoolTableConstructor", &TestContextStringBoolTableConstructor));
    res.push_back(TestFunction("TestContextStringBitSetTableConstructor", &TestContextStringBitSetTableConstructor));
    return res;
}

TEST_RESULT TestContextString(const std::string& indent, size_t& ok, size_t& fail) {
    fprintf(stdout, "%s%s:\n", indent.c_str(), TestContextStringAll.name.c_str());
    ok = 0;
    fail = 0;
    TestFunctionVector allTests = GetAllContextStringTestFunctions();
    RunTestsFromGroup(allTests, indent + "\t", ok, fail);

    fprintf(stdout, "%sTotal subtest OK: %lu\n", indent.c_str(), ok);
    fprintf(stdout, "%sTotal subtest FAIL: %lu\n", indent.c_str(), fail);
    const double p = (0 == ok + fail ? 100 : static_cast<double>(ok * 100) / static_cast<double>(ok + fail));
    fprintf(stdout, "%sSuccessfull subtests: %.2lf %%\n", indent.c_str(), p);
    fprintf(stdout, "%s%s:", indent.c_str(), TestContextStringAll.name.c_str());
    TEST_RESULT res = (0 == fail ? TEST_RESULT_OK : TEST_RESULT_FAIL);
    PrintOkFailAndLineFeed(res, stdout);
    return res;
}

TEST_RESULT TestContextStringDefaultConstructor() {
    FCA::ContextString c;
    if (c.ObjSize() != 0 || c.AttrSize() != 0) {
        return TEST_RESULT_FAIL;
    }

    if (c.GetObjNames().size() != 0 || c.GetAttrNames().size()) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestContextStringContextConstructor() {
    const size_t objSize = 100;
    const size_t attrSize = 200;
    const FCA::Context c(objSize, attrSize);
    const FCA::ContextString cs(c);

    const std::vector<std::string>& objName = cs.GetObjNames();
    if (objName.size() != objSize) {
        return TEST_RESULT_FAIL;
    }
    for (size_t i = 0; i < objSize; ++i) {
        if (!objName[i].empty()) {
            return TEST_RESULT_FAIL;
        }
    }

    const std::vector<std::string>& attrName = cs.GetAttrNames();
    if (attrName.size() != attrSize) {
        return TEST_RESULT_FAIL;
    }
    for (size_t i = 0; i < attrSize; ++i) {
        if (!attrName[i].empty()) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestContextStringTwoSizeConstructor() {
    const size_t objSize = 100;
    const size_t attrSize = 200;
    const FCA::ContextString c(objSize, attrSize);

    if (c.ObjSize() != objSize || c.AttrSize() != attrSize) {
        return TEST_RESULT_FAIL;
    }

    const std::vector<std::string>& objName = c.GetObjNames();
    if (objName.size() != objSize) {
        return TEST_RESULT_FAIL;
    }
    for (size_t i = 0; i < objSize; ++i) {
        if (!objName[i].empty()) {
            return TEST_RESULT_FAIL;
        }
    }

    const std::vector<std::string>& attrName = c.GetAttrNames();
    if (attrName.size() != attrSize) {
        return TEST_RESULT_FAIL;
    }
    for (size_t i = 0; i < attrSize; ++i) {
        if (!attrName[i].empty()) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestContextStringNamesConstructor() {
    const size_t objSize = 100;
    std::vector<std::string> objName(objSize);
    objName[0] = "o";
    for (size_t i = 1; i < objSize; ++i) {
        objName[i] = objName[i - 1] + "o";
    }

    const size_t attrSize = 200;
    std::vector<std::string> attrName(attrSize);
    attrName[0] = "a";
    for (size_t i = 1; i < attrSize; ++i) {
        attrName[i] = attrName[i - 1] + "a";
    }

    FCA::ContextString c(objName, attrName);
    if (c.ObjSize() != objSize || c.AttrSize() != attrSize) {
        return TEST_RESULT_FAIL;
    }
    if (c.GetObjNames() != objName || c.GetAttrNames() != attrName) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestContextStringBoolTableConstructor() {
    const size_t objSize = 100;
    const size_t attrSize = 200;
    std::vector<std::vector<bool> > table(objSize);
    for (size_t i = 0; i < objSize; ++i) {
        table[i].resize(attrSize);
        for (size_t j = 0; j < attrSize; ++j) {
            if (i % 3 == 0 && j % 5 == 0) {
                table[i][j] = true;
            }
        }
    }
    FCA::ContextString c(table);

    if (c.ObjSize() != objSize || c.AttrSize() != attrSize) {
        return TEST_RESULT_FAIL;
    }
    const std::vector<std::string>& objName = c.GetObjNames();
    const std::vector<std::string>& attrName = c.GetAttrNames();
    if (objName.size() != objSize || attrName.size() != attrSize) {
        return TEST_RESULT_FAIL;
    }
    for (size_t i = 0; i < objSize; ++i) {
        if (!objName[i].empty()) {
            return TEST_RESULT_FAIL;
        }
    }
    for (size_t i = 0; i < attrSize; ++i) {
        if (!attrName[i].empty()) {
            return TEST_RESULT_FAIL;
        }
    }
    for (size_t i = 0; i < objSize; ++i) {
        for (size_t j = 0; j < attrSize; ++j) {
            if (c.Get(i, j) != table[i][j]) {
                return TEST_RESULT_FAIL;
            }
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestContextStringBitSetTableConstructor() {
    const size_t objSize = 100;
    const size_t attrSize = 200;
    FCA::BitSetVector table(objSize);
    for (size_t i = 0; i < objSize; ++i) {
        table[i].resize(attrSize);
        for (size_t j = 0; j < attrSize; ++j) {
            if (i % 3 == 0 && j % 5 == 0) {
                table[i].set(j);
            }
        }
    }
    FCA::ContextString c(table);

    if (c.ObjSize() != objSize || c.AttrSize() != attrSize) {
        return TEST_RESULT_FAIL;
    }
    const std::vector<std::string>& objName = c.GetObjNames();
    const std::vector<std::string>& attrName = c.GetAttrNames();
    if (objName.size() != objSize || attrName.size() != attrSize) {
        return TEST_RESULT_FAIL;
    }
    for (size_t i = 0; i < objSize; ++i) {
        if (!objName[i].empty()) {
            return TEST_RESULT_FAIL;
        }
    }
    for (size_t i = 0; i < attrSize; ++i) {
        if (!attrName[i].empty()) {
            return TEST_RESULT_FAIL;
        }
    }
    for (size_t i = 0; i < objSize; ++i) {
        for (size_t j = 0; j < attrSize; ++j) {
            if (c.Get(i, j) != table[i].test(j)) {
                return TEST_RESULT_FAIL;
            }
        }
    }
    return TEST_RESULT_OK;
}
