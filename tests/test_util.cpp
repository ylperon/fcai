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
