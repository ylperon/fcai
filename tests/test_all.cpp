#include <cstdio>

#include "test_bitset.h"

TEST_RESULT TestBitSet() {
    fprintf(stdout, "\tTestBitSet:\n");
    size_t ok = 0;
    size_t fail = 0;
    std::vector<TestFunction> allTests = GetAllBitSetTestFunctions();
    RunTestsFromGroup(allTests, "\t\t", ok, fail);

    fprintf(stdout, "\tTestBitSet: ");
    TEST_RESULT res = (0 == fail ? TEST_RESULT_OK : TEST_RESULT_FAIL);
    PrintOkFailAndLineFeed(res, stdout);
    return res;
}

int main() {
    fprintf(stdout, "Running all tests:\n");
    TestBitSet();
    return 0;
}
