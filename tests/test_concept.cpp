#include "test_concept.h"

#include <cstdio>

#include <vector>

TestFunctionGroup TestConceptAll("TestConcept", &TestConcept);

TestFunctionVector GetAllConceptTestFunctions() {
    TestFunctionVector res;
    res.push_back(TestFunction("TestConceptDefaultConstructor", &TestConceptDefaultConstructor));
    return res;
}

TEST_RESULT TestConcept(const std::string& indent, size_t& ok, size_t& fail) {
    fprintf(stdout, "%s%s:\n", indent.c_str(), TestConceptAll.name.c_str());
    ok = 0;
    fail = 0;
    TestFunctionVector allTests = GetAllConceptTestFunctions();
    RunTestsFromGroup(allTests, indent + "\t", ok, fail);

    fprintf(stdout, "%sTotal subtest OK: %lu\n", indent.c_str(), ok);
    fprintf(stdout, "%sTotal subtest FAIL: %lu\n", indent.c_str(), fail);
    const double p = (0 == ok + fail ? 100 : static_cast<double>(ok * 100) / static_cast<double>(ok + fail));
    fprintf(stdout, "%sSuccessfull subtests: %.2lf %%\n", indent.c_str(), p);
    fprintf(stdout, "%s%s:", indent.c_str(), TestConceptAll.name.c_str());
    TEST_RESULT res = (0 == fail ? TEST_RESULT_OK : TEST_RESULT_FAIL);
    PrintOkFailAndLineFeed(res, stdout);
    return res;
}

TEST_RESULT TestConceptDefaultConstructor() {
    FCA::Concept c;
    if (c.Extent().size() != 0 || c.Intent().size() != 0) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}
