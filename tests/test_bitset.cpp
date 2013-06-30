#include "test_bitset.h"

#include <cstdio>

#include <vector>

std::vector<TestFunction> GetAllBitSetTestFunctions() {
    std::vector<TestFunction> res;
    res.push_back(TestFunction("TestBitSetConctruct", &TestBitSetConctruct));
    res.push_back(TestFunction("TestBitSetSetAndTest", &TestBitSetSetAndTest));
    res.push_back(TestFunction("TestBitSetCopyConstruct", &TestBitSetCopyConstruct));
    return res;
}

TEST_RESULT TestBitSetConctruct() {
    const size_t len = 100;
    FCA::BitSet bs(len);
    if (bs.size() != len) {
        return TEST_RESULT_FAIL;
    }
    for (size_t i = 0; i < len; ++i) {
        if (bs.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetSetAndTest() {
    const size_t len = 100;
    FCA::BitSet bs(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs.set(i);
        }
    }
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0 && !bs.test(i)) {
            return TEST_RESULT_FAIL;
        }
        if (i % 3 != 0 && bs.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetCopyConstruct() {
    const size_t len = 100;
    FCA::BitSet bsOriginal(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bsOriginal.set(i);
        }
    }
    const FCA::BitSet bsCopy(bsOriginal);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0 && !bsCopy.test(i)) {
            return TEST_RESULT_FAIL;
        }
        if (i % 3 != 0 && bsCopy.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}
