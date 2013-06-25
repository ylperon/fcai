#include <cstdio>

#include "test_bitset.h"

TEST_RESULT TestBitSet() {
    fprintf(stdout, "\tTestBitSet:\n");
    size_t ok = 0;
    size_t fail = 0;
    TEST_RESULT res;
    fprintf(stdout, "\t\tTestBitSetConstruct:\n");
    res = TestBitSetConctruct();
    IncOkFail(res, ok, fail);
    PrintOkFail(res, stdout);
    fprintf(stdout, "\t\tTestBitSetSetAndTest:\n");
    res = TestBitSetSetAndTest();
    IncOkFail(res, ok, fail);
    PrintOkFail(res, stdout);

    if (0 == fail) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

int main() {
    fprintf(stdout, "\t\tRunning all tests:\n");
    TestBitSet();
    return 0;
}
