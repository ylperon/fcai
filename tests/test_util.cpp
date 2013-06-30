#include "test_util.h"

void IncOkFail(const TEST_RESULT res, size_t& ok, size_t& fail) {
    if (TEST_RESULT_OK == res) {
        ++ok;
    }
    else if (TEST_RESULT_FAIL == res) {
        ++fail;
    }
    else {
        //unknown!!!
    }
}

void PrintOkFail(const TEST_RESULT res, FILE* out) {
    if (TEST_RESULT_OK == res) {
        fprintf(out, "OK");
    }
    else if (TEST_RESULT_FAIL == res) {
        fprintf(out, "FAIL");
    }
    else {
        //unknown!!!
    }
}

void PrintOkFailAndLineFeed(const TEST_RESULT res, FILE* out) {
    PrintOkFail(res, out);
    fprintf(out, "\n");
}

void RunTestsFromGroup(const std::vector<TestFunction>& testFunctions,
                       const std::string& indent,
                       size_t& ok,
                       size_t& fail) {
    ok = 0;
    fail = 0;
    for (size_t i = 0; i < testFunctions.size(); ++i) {
        fprintf(stdout, "%s%s:", indent.c_str(), testFunctions[i].name.c_str());
        TEST_RESULT res = testFunctions[i].fun();
        IncOkFail(res, ok, fail);
        PrintOkFailAndLineFeed(res, stdout);
    }
}
