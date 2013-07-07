#include "test_implication.h"

#include <cstdio>

#include <vector>

TestFunctionGroup TestImplicationAll("TestImplication", &TestImplication);

std::vector<TestFunction> GetAllImplicationTestFunctions() {
    std::vector<TestFunction> res;
    res.push_back(TestFunction("TestImplicationDefaultConstructor", &TestImplicationDefaultConstructor));
    res.push_back(TestFunction("TestImplicationSizeConstructor", &TestImplicationSizeConstructor));
    res.push_back(TestFunction("TestImplicationTwoBitSetConstructor", &TestImplicationTwoBitSetConstructor));
    return res;
}

TEST_RESULT TestImplication(const std::string& indent, size_t& ok, size_t& fail) {
    fprintf(stdout, "%sTestImplication:\n", indent.c_str());
    ok = 0;
    fail = 0;
    TestFunctionVector allTests = GetAllImplicationTestFunctions();
    RunTestsFromGroup(allTests, indent + "\t", ok, fail);

    fprintf(stdout, "%sTotal subtest OK: %lu\n", indent.c_str(), ok);
    fprintf(stdout, "%sTotal subtest FAIL: %lu\n", indent.c_str(), fail);
    const double p = (0 == ok + fail ? 100 : static_cast<double>(ok * 100) / static_cast<double>(ok + fail));
    fprintf(stdout, "%sSuccessfull subtests: %.2lf %%\n", indent.c_str(), p);
    fprintf(stdout, "%sTestImplication:", indent.c_str());
    TEST_RESULT res = (0 == fail ? TEST_RESULT_OK : TEST_RESULT_FAIL);
    PrintOkFailAndLineFeed(res, stdout);
    return res;
}

TEST_RESULT TestImplicationDefaultConstructor() {
    FCA::Implication impl;
    if (impl.Premise().size() != 0 || impl.Conclusion().size() != 0) {
        return TEST_RESULT_FAIL;
    }
    if (impl.Premise().any() || impl.Conclusion().any()) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestImplicationSizeConstructor() {
    const size_t baseSize = 100;
    FCA::Implication impl(baseSize);
    if (impl.Premise().size() != baseSize || impl.Conclusion().size() != baseSize) {
        return TEST_RESULT_FAIL;
    }
    if (impl.Premise().any() || impl.Conclusion().any()) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestImplicationTwoBitSetConstructor() {
    const size_t baseSize = 100;
    FCA::BitSet premise(baseSize);
    for (size_t i = 0; i < baseSize; ++i) {
        if (i % 3 == 0) {
            premise.set(i);
        }
    }
    FCA::BitSet conclusion(baseSize);
    for (size_t i = 0; i < baseSize; ++i) {
        if (i % 5 == 0) {
            conclusion.set(i);
        }
    }
    FCA::Implication impl(premise, conclusion);
    if (impl.Premise() != premise || impl.Conclusion() != conclusion) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}
