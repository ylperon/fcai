#include "test_context_string.h"

#include <cstdio>

#include <vector>

TestFunctionGroup TestContextStringAll("TestContextString", &TestContextString);

TestFunctionVector GetAllContextStringTestFunctions() {
    TestFunctionVector res;
    res.push_back(TestFunction("TestContextStringDefaultConstructor", &TestContextStringDefaultConstructor));
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
