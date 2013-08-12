#include "test_context.h"

#include <cstdio>

#include <vector>

TestFunctionGroup TestContextAll("TestContext", &TestContext);

TestFunctionVector GetAllContextTestFunctions() {
    TestFunctionVector res;
    res.push_back(TestFunction("TestContextDefaultConstructor", &TestContextDefaultConstructor));
    res.push_back(TestFunction("TestContextTwoSizeConstructor", &TestContextTwoSizeConstructor));
    res.push_back(TestFunction("TestContextBoolTableConstructor", &TestContextBoolTableConstructor));
    return res;
}

TEST_RESULT TestContext(const std::string& indent, size_t& ok, size_t& fail) {
    fprintf(stdout, "%s%s:\n", indent.c_str(), TestContextAll.name.c_str());
    ok = 0;
    fail = 0;
    TestFunctionVector allTests = GetAllContextTestFunctions();
    RunTestsFromGroup(allTests, indent + "\t", ok, fail);

    fprintf(stdout, "%sTotal subtest OK: %lu\n", indent.c_str(), ok);
    fprintf(stdout, "%sTotal subtest FAIL: %lu\n", indent.c_str(), fail);
    const double p = (0 == ok + fail ? 100 : static_cast<double>(ok * 100) / static_cast<double>(ok + fail));
    fprintf(stdout, "%sSuccessfull subtests: %.2lf %%\n", indent.c_str(), p);
    fprintf(stdout, "%s%s:", indent.c_str(), TestContextAll.name.c_str());
    TEST_RESULT res = (0 == fail ? TEST_RESULT_OK : TEST_RESULT_FAIL);
    PrintOkFailAndLineFeed(res, stdout);
    return res;
}

TEST_RESULT TestContextDefaultConstructor() {
    FCA::Context c;
    if (c.ObjSize() != 0 || c.AttrSize() != 0) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestContextTwoSizeConstructor() {
    const size_t objSize = 100;
    const size_t attrSize = 200;
    FCA::Context c(objSize, attrSize);

    if (c.ObjSize() != objSize || c.AttrSize() != attrSize) {
        return TEST_RESULT_FAIL;
    }
    for (size_t i = 0; i < objSize; ++i) {
        for (size_t j = 0; j < attrSize; ++j) {
            if (c.Get(i, j)) {
                return TEST_RESULT_FAIL;
            }
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestContextBoolTableConstructor() {
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
    FCA::Context c(table);

    if (c.ObjSize() != objSize || c.AttrSize() != attrSize) {
        return TEST_RESULT_FAIL;
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
