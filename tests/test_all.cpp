#include <cstdio>

#include "test_bitset.h"

TEST_RESULT TestBitSet() {
    fprintf(stdout, "\tTestBitSet:\n");
    size_t ok = 0;
    size_t fail = 0;
    TEST_RESULT res;
    fprintf(stdout, "\t\tTestBitSetConstruct: ");
    res = TestBitSetConctruct();
    IncOkFail(res, ok, fail);
    PrintOkFailAndLineFeed(res, stdout);
    fprintf(stdout, "\t\tTestBitSetSetAndTest: ");
    res = TestBitSetSetAndTest();
    IncOkFail(res, ok, fail);
    PrintOkFailAndLineFeed(res, stdout);

    if (0 == fail) {
        res = TEST_RESULT_FAIL;
    }
    res = TEST_RESULT_OK;
    fprintf(stdout, "\tTestBitSet: ");
    PrintOkFailAndLineFeed(res, stdout);
    return res;
}

int main() {
    fprintf(stdout, "Running all tests:\n");
    TestBitSet();
    return 0;
}
