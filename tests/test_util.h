#pragma once

#include <cstdio>

enum TEST_RESULT {
    TEST_RESULT_OK,
    TEST_RESULT_FAIL,
};

void IncOkFail(const TEST_RESULT res, size_t& ok, size_t& fail);
void PrintOkFail(const TEST_RESULT res, FILE* out);
void PrintOkFailAndLineFeed(const TEST_RESULT res, FILE* out);
