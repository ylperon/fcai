#include "test_concept.h"

#include <cstdio>

#include <vector>

TestFunctionGroup TestConceptAll("TestConcept", &TestConcept);

TestFunctionVector GetAllConceptTestFunctions() {
    TestFunctionVector res;
    res.push_back(TestFunction("TestConceptDefaultConstructor", &TestConceptDefaultConstructor));
    res.push_back(TestFunction("TestConctptSizeConstructor", &TestConctptSizeConstructor));
    res.push_back(TestFunction("TestConceptTwoBitSetConstructor", &TestConceptTwoBitSetConstructor));
    res.push_back(TestFunction("TestConceptCopyConstructor", &TestConceptCopyConstructor));
    res.push_back(TestFunction("TestConceptExtentGetter", &TestConceptExtentGetter));
    res.push_back(TestFunction("TestConceptIntentGetter", &TestConceptIntentGetter));
    res.push_back(TestFunction("TestConceptExtentSize", &TestConceptExtentSize));
    res.push_back(TestFunction("TestConceptIntentSize", &TestConceptIntentSize));
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

TEST_RESULT TestConctptSizeConstructor() {
    const size_t objSize = 100;
    const size_t attrSize = 200;
    FCA::Concept c(objSize, attrSize);
    if (c.Extent().size() != objSize || c.Intent().size() != attrSize) {
        return TEST_RESULT_FAIL;
    }
    if (c.Extent().any() || c.Intent().any()) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestConceptTwoBitSetConstructor() {
    const size_t objSize = 100;
    FCA::BitSet extent(objSize);
    for (size_t i = 0; i < objSize; ++i) {
        if (i % 3 == 0) {
            extent.set(i);
        }
    }
    const size_t attrSize = 200;
    FCA::BitSet intent(attrSize);
    for (size_t i = 0; i < attrSize; ++i) {
        if (i % 5 == 0) {
            intent.set(i);
        }
    }
    FCA::Concept c(extent, intent);
    if (c.Extent() != extent || c.Intent() != intent) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestConceptCopyConstructor() {
    const size_t objSize = 100;
    FCA::BitSet extent(objSize);
    for (size_t i = 0; i < objSize; ++i) {
        if (i % 3 == 0) {
            extent.set(i);
        }
    }
    const size_t attrSize = 200;
    FCA::BitSet intent(attrSize);
    for (size_t i = 0; i < attrSize; ++i) {
        if (i % 5 == 0) {
            intent.set(i);
        }
    }
    FCA::Concept c1(extent, intent);
    FCA::Concept c2(c1);
    if (c2.Extent() != extent || c2.Intent() != intent) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestConceptExtentGetter() {
    const size_t objSize = 100;
    FCA::BitSet extent(objSize);
    for (size_t i = 0; i < objSize; ++i) {
        if (i % 3 == 0) {
            extent.set(i);
        }
    }
    const size_t attrSize = 200;
    FCA::BitSet intent(attrSize);
    for (size_t i = 0; i < attrSize; ++i) {
        if (i % 5 == 0) {
            intent.set(i);
        }
    }
    FCA::Concept c(extent, intent);
    if (c.Extent() != extent) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestConceptIntentGetter() {
    const size_t objSize = 100;
    FCA::BitSet extent(objSize);
    for (size_t i = 0; i < objSize; ++i) {
        if (i % 3 == 0) {
            extent.set(i);
        }
    }
    const size_t attrSize = 200;
    FCA::BitSet intent(attrSize);
    for (size_t i = 0; i < attrSize; ++i) {
        if (i % 5 == 0) {
            intent.set(i);
        }
    }
    FCA::Concept c(extent, intent);
    if (c.Intent() != intent) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestConceptExtentSize() {
    const size_t objSize = 100;
    FCA::BitSet extent(objSize);
    size_t extentSize = 0;
    for (size_t i = 0; i < objSize; ++i) {
        if (i % 3 == 0) {
            extent.set(i);
            ++extentSize;
        }
    }
    const size_t attrSize = 200;
    FCA::BitSet intent(attrSize);
    for (size_t i = 0; i < attrSize; ++i) {
        if (i % 5 == 0) {
            intent.set(i);
        }
    }
    FCA::Concept c(extent, intent);
    if (c.ExtentSize() != extentSize) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestConceptIntentSize() {
    const size_t objSize = 100;
    FCA::BitSet extent(objSize);
    for (size_t i = 0; i < objSize; ++i) {
        if (i % 3 == 0) {
            extent.set(i);
        }
    }
    const size_t attrSize = 200;
    FCA::BitSet intent(attrSize);
    size_t intentSize = 0;
    for (size_t i = 0; i < attrSize; ++i) {
        if (i % 5 == 0) {
            intent.set(i);
            ++intentSize;
        }
    }
    FCA::Concept c(extent, intent);
    if (c.IntentSize() != intentSize) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}
