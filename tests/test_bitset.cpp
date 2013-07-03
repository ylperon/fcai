#include "test_bitset.h"

#include <cstdio>

#include <vector>

TestFunctionGroup TestBitSetAll("TestBitSet", &TestBitSet);

std::vector<TestFunction> GetAllBitSetTestFunctions() {
    std::vector<TestFunction> res;
    res.push_back(TestFunction("TestBitSetConctruct", &TestBitSetConctruct));
    res.push_back(TestFunction("TestBitSetSetAndTest", &TestBitSetSetAndTest));
    res.push_back(TestFunction("TestBitSetCopyConstruct", &TestBitSetCopyConstruct));
    res.push_back(TestFunction("TestBitSetAnyAndNone", &TestBitSetAnyAndNone));
    res.push_back(TestFunction("TestBitSetSetAllAndTestAll", &TestBitSetSetAllAndTestAll));
    res.push_back(TestFunction("TestBitSetFlipAll", &TestBitSetFlipAll));
    res.push_back(TestFunction("TestBitSetFlip", &TestBitSetFlip));
    res.push_back(TestFunction("TestBitSetIsSubsetOf", &TestBitSetIsSubsetOf));
    res.push_back(TestFunction("TestBitSetIsProperSubsetOf", &TestBitSetIsProperSubsetOf));
    res.push_back(TestFunction("TestBitSetSize", &TestBitSetSize));
    res.push_back(TestFunction("TestBitSetResize", &TestBitSetResize));
    res.push_back(TestFunction("TestBitSetOperatorTilda", &TestBitSetOperatorTilda));
    res.push_back(TestFunction("TestBitSetCount", &TestBitSetCount));
    res.push_back(TestFunction("TestBitSetCountZeros", &TestBitSetCount));
    res.push_back(TestFunction("TestBitSetOperatorAnd", &TestBitSetOperatorAnd));
    res.push_back(TestFunction("TestBitSetOperatorOr", &TestBitSetOperatorOr));
    res.push_back(TestFunction("TestBitSetOperatorXor", &TestBitSetOperatorXor));
    res.push_back(TestFunction("TestBitSetOperatorMinus", &TestBitSetOperatorMinus));
    res.push_back(TestFunction("TestBitSetFindFirst", &TestBitSetFindFirst));
    res.push_back(TestFunction("TestBitSetFindNext", &TestBitSetFindNext));
    res.push_back(TestFunction("TestBitSetSwap", &TestBitSetSwap));
    res.push_back(TestFunction("TestBitSetAssignmentOperator", &TestBitSetAssignmentOperator));
    res.push_back(TestFunction("TestBitSetOperatorEqual", &TestBitSetOperatorEqual));
    res.push_back(TestFunction("TestBitSetOperatorNotEqual", &TestBitSetOperatorNotEqual));
    res.push_back(TestFunction("TestBitSetOperatorLess", &TestBitSetOperatorLess));
    res.push_back(TestFunction("TestBitSetOperatorLessEqual", &TestBitSetOperatorLessEqual));
    res.push_back(TestFunction("TestBitSetOperatorGreater", &TestBitSetOperatorGreater));
    res.push_back(TestFunction("TestBitSetOperatorGreaterEqual", &TestBitSetOperatorGreaterEqual));
    return res;
}

TEST_RESULT TestBitSet(const std::string& indent, size_t& ok, size_t& fail) {
    fprintf(stdout, "%sTestBitSet:\n", indent.c_str());
    ok = 0;
    fail = 0;
    TestFunctionVector allTests = GetAllBitSetTestFunctions();
    RunTestsFromGroup(allTests, indent + "\t", ok, fail);

    fprintf(stdout, "%sTotal subtest OK: %lu\n", indent.c_str(), ok);
    fprintf(stdout, "%sTotal subtest FAIL: %lu\n", indent.c_str(), fail);
    const double p = (0 == ok + fail ? 100 : static_cast<double>(ok * 100) / static_cast<double>(ok + fail));
    fprintf(stdout, "%sSuccessfull subtests: %.2lf %%\n", indent.c_str(), p);
    fprintf(stdout, "%sTestBitSet:", indent.c_str());
    TEST_RESULT res = (0 == fail ? TEST_RESULT_OK : TEST_RESULT_FAIL);
    PrintOkFailAndLineFeed(res, stdout);
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

TEST_RESULT TestBitSetAnyAndNone() {
    const size_t len = 100;
    FCA::BitSet bs(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs.set(i);
        }
    }
    if (!bs.any() || bs.none()) {
        return TEST_RESULT_FAIL;
    }
    for (size_t i = 0; i < len; ++i) {
        bs.reset(i);
    }
    if (bs.any() || !bs.none()) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetSetAllAndTestAll() {
    const size_t len = 100;
    FCA::BitSet bs(len);
    bs.set();
    for (size_t i = 0; i < len; ++i) {
        if (!bs.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    bs.reset();
    for (size_t i = 0; i < len; ++i) {
        if (bs.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetFlipAll() {
    const size_t len = 100;
    FCA::BitSet bs(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs.set(i);
        }
    }
    bs.flip();
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0 && bs.test(i)) {
            return TEST_RESULT_FAIL;
        } else if (i % 3 != 0 && !bs.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetFlip() {
    const size_t len = 100;
    FCA::BitSet bs(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs.set(i);
        }
    }
    for (size_t i = 0; i < len; ++i) {
        bs.flip(i);
    }
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0 && bs.test(i)) {
            return TEST_RESULT_FAIL;
        } else if (i % 3 != 0 && !bs.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetIsSubsetOf() {
    const size_t len = 100;
    FCA::BitSet bs1(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs1.set(i);
        }
    }
    FCA::BitSet bs2(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 6 == 0) {
            bs2.set(i);
        }
    }
    FCA::BitSet bs3(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs3.set(i);
        }
    }
    FCA::BitSet bs4(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 5 == 0) {
            bs4.set(i);
        }
    }
    if (!bs1.is_subset_of(bs1)) {
        return TEST_RESULT_FAIL;
    }
    if (!bs2.is_subset_of(bs1)) {
        return TEST_RESULT_FAIL;
    }
    if (!bs3.is_subset_of(bs1)) {
        return TEST_RESULT_FAIL;
    }
    if (bs4.is_subset_of(bs1)) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetIsProperSubsetOf() {
    const size_t len = 100;
    FCA::BitSet bs1(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs1.set(i);
        }
    }
    FCA::BitSet bs2(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 6 == 0) {
            bs2.set(i);
        }
    }
    FCA::BitSet bs3(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs3.set(i);
        }
    }
    FCA::BitSet bs4(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 5 == 0) {
            bs4.set(i);
        }
    }
    if (bs1.is_proper_subset_of(bs1)) {
        return TEST_RESULT_FAIL;
    }
    if (!bs2.is_proper_subset_of(bs1)) {
        return TEST_RESULT_FAIL;
    }
    if (bs3.is_proper_subset_of(bs1)) {
        return TEST_RESULT_FAIL;
    }
    if (bs4.is_proper_subset_of(bs1)) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetSize() {
    const size_t len = 100;
    FCA::BitSet bs(len);
    return (bs.size() == len ? TEST_RESULT_OK : TEST_RESULT_FAIL);
}

TEST_RESULT TestBitSetResize() {
    const size_t len1 = 100;
    FCA::BitSet bs1(len1);
    for (size_t i = 0; i < len1; ++i) {
        if (i % 3 == 0) {
            bs1.set(i);
        }
    }
    FCA::BitSet bs2(bs1);
    const size_t len2 = len1 / 3;
    bs2.resize(len2);
    for (size_t i = 0; i < len2; ++i) {
        if (i % 3 == 0 && !bs2.test(i)) {
            return TEST_RESULT_FAIL;
        }
        if (i % 3 != 0 && bs2.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    FCA::BitSet bs3(bs1);
    const size_t len3 = len1 * 3;
    bs3.resize(len3);
    for (size_t i = 0; i < len1; ++i) {
        if (i % 3 == 0 && !bs3.test(i)) {
            return TEST_RESULT_FAIL;
        }
        if (i % 3 != 0 && bs3.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    for (size_t i = len1; i < len3; ++i) {
        if (bs3.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetOperatorTilda() {
    const size_t len = 100;
    FCA::BitSet bs1(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs1.set(i);
        }
    }
    FCA::BitSet bs2(len);
    bs2 = ~bs1;
    if (bs1.size() != bs2.size()) {
        return TEST_RESULT_FAIL;
    }
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0 && bs2.test(i)) {
            return TEST_RESULT_FAIL;
        }
        if (i % 3 != 0 && !bs2.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetCount() {
    const size_t len = 100;
    FCA::BitSet bs(len);
    size_t ones = 0;
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs.set(i);
            ++ones;
        }
    }
    return (bs.count() == ones ? TEST_RESULT_OK : TEST_RESULT_FAIL);
}

TEST_RESULT TestBitSetCountZeros() {
    const size_t len = 100;
    FCA::BitSet bs(len);
    size_t zeros = len;
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs.set(i);
            --zeros;
        }
    }
    return (bs.count_zeros() == zeros ? TEST_RESULT_OK : TEST_RESULT_FAIL);
}

TEST_RESULT TestBitSetOperatorAnd() {
    const size_t len = 100;
    FCA::BitSet bs1(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs1.set(i);
        }
    }
    FCA::BitSet bs2(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 6 == 0) {
            bs2.set(i);
        }
    }
    bs1 &= bs2;
    for (size_t i = 0; i < len; ++i) {
        if (i % 6 == 0 && !bs1.test(i)) {
            return TEST_RESULT_FAIL;
        }
        if (i % 6 != 0 && bs1.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetOperatorOr() {
    const size_t len = 100;
    FCA::BitSet bs1(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs1.set(i);
        }
    }
    FCA::BitSet bs2(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 6 == 0) {
            bs2.set(i);
        }
    }
    bs1 |= bs2;
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0 && !bs1.test(i)) {
            return TEST_RESULT_FAIL;
        }
        if (i % 3 != 0 && bs1.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetOperatorXor() {
    const size_t len = 100;
    FCA::BitSet bs1(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs1.set(i);
        }
    }
    FCA::BitSet bs2(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 6 == 0) {
            bs2.set(i);
        }
    }
    bs1 ^= bs2;
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0 && i % 6 == 0 && bs1.test(i)) {
            return TEST_RESULT_FAIL;
        }
        if (i % 3 == 0 && i % 6 != 0 && !bs1.test(i)) {
            return TEST_RESULT_FAIL;
        }
        if (i % 3 != 0 && i % 6 == 0 && !bs1.test(i)) {
            return TEST_RESULT_FAIL;
        }
        if (i % 3 != 0 && i % 6 != 0 && bs1.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetOperatorMinus() {
    const size_t len = 100;
    FCA::BitSet bs1(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs1.set(i);
        }
    }
    FCA::BitSet bs2(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 6 == 0) {
            bs2.set(i);
        }
    }
    bs1 -= bs2;
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0 && i % 6 == 0 && bs1.test(i)) {
            return TEST_RESULT_FAIL;
        }
        if (i % 3 == 0 && i % 6 != 0 && !bs1.test(i)) {
            return TEST_RESULT_FAIL;
        }
        if (i % 3 != 0 && i % 6 == 0 && bs1.test(i)) {
            return TEST_RESULT_FAIL;
        }
        if (i % 3 != 0 && i % 6 != 0 && bs1.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetFindFirst() {
    const size_t len = 100;
    FCA::BitSet bs(len);
    const size_t ind1 = 50;
    const size_t ind2 = 88;
    bs.set(ind1);
    bs.set(ind2);
    if (bs.findFirst() != ind1) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetFindNext() {
    const size_t len = 100;
    FCA::BitSet bs(len);
    const size_t ind1 = 33;
    const size_t ind2 = 66;
    const size_t ind3 = 80;
    bs.set(ind1);
    bs.set(ind2);
    bs.set(ind3);
    const size_t indFirst = bs.findFirst();
    if (bs.findNext(indFirst) != ind2) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetSwap() {
    const size_t len1 = 100;
    FCA::BitSet bs1(len1);
    for (size_t i = 0; i < len1; ++i) {
        if (i % 3 == 0) {
            bs1.set(i);
        }
    }
    const size_t len2 = 300;
    FCA::BitSet bs2(len2);
    for (size_t i = 0; i < len2; ++i) {
        if (i % 5 == 0) {
            bs2.set(i);
        }
    }
    bs1.swap(bs2);
    if (bs1.size() != len2) {
        return TEST_RESULT_FAIL;
    }
    for (size_t i = 0; i < len2; ++i) {
        if (i % 5 == 0 && !bs1.test(i)) {
            return TEST_RESULT_FAIL;
        }
        if (i % 5 != 0 && bs1.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    if (bs2.size() != len1) {
        return TEST_RESULT_FAIL;
    }
    for (size_t i = 0; i < len1; ++i) {
        if (i % 3 == 0 && !bs2.test(i)) {
            return TEST_RESULT_FAIL;
        }
        if (i % 3 != 0 && bs2.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetAssignmentOperator() {
    const size_t len1 = 100;
    FCA::BitSet bs1(len1);
    for (size_t i = 0; i < len1; ++i) {
        if (i % 3 == 0) {
            bs1.set(i);
        }
    }
    const size_t len2 = 10;
    FCA::BitSet bs2(len2);
    bs2 = bs1;
    if (bs2.size() != len1) {
        return TEST_RESULT_FAIL;
    }
    for (size_t i = 0; i < len1; ++i) {
        if (i % 3 == 0 && !bs1.test(i)) {
            return TEST_RESULT_FAIL;
        }
        if (i % 3 != 0 && bs1.test(i)) {
            return TEST_RESULT_FAIL;
        }
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetOperatorEqual() {
    const size_t len = 100;
    FCA::BitSet bs1(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs1.set(i);
        }
    }
    FCA::BitSet bs2(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs2.set(i);
        }
    }
    FCA::BitSet bs3(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 5 == 0) {
            bs3.set(i);
        }
    }
    if (!(bs1 == bs2)) {
        return TEST_RESULT_FAIL;
    }
    if (bs1 == bs3) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetOperatorNotEqual() {
    const size_t len = 100;
    FCA::BitSet bs1(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs1.set(i);
        }
    }
    FCA::BitSet bs2(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs2.set(i);
        }
    }
    FCA::BitSet bs3(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 5 == 0) {
            bs3.set(i);
        }
    }
    if (bs1 != bs2) {
        return TEST_RESULT_FAIL;
    }
    if (!(bs1 != bs3)) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetOperatorLess() {
    const size_t len = 100;
    FCA::BitSet bs1(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs1.set(i);
        }
    }
    FCA::BitSet bs2(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 6 == 0) {
            bs2.set(i);
        }
    }
    FCA::BitSet bs3(len);
    for (size_t i = 0; i < len; ++i) {
        bs3.set(i);
    }
    FCA::BitSet bs4(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 5 == 0) {
            bs4.set(i);
        }
    }
    if (bs1 < bs2) {
        return TEST_RESULT_FAIL;
    }
    if (!(bs1 < bs3)) {
        return TEST_RESULT_FAIL;
    }
    if (bs1 < bs4) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetOperatorLessEqual() {
    const size_t len = 100;
    FCA::BitSet bs1(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs1.set(i);
        }
    }
    FCA::BitSet bs2(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 6 == 0) {
            bs2.set(i);
        }
    }
    FCA::BitSet bs3(len);
    for (size_t i = 0; i < len; ++i) {
        bs3.set(i);
    }
    FCA::BitSet bs4(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 5 == 0) {
            bs4.set(i);
        }
    }
    FCA::BitSet bs5(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs5.set(i);
        }
    }
    if (bs1 <= bs2) {
        return TEST_RESULT_FAIL;
    }
    if (!(bs1 <= bs3)) {
        return TEST_RESULT_FAIL;
    }
    if (bs1 <= bs4) {
        return TEST_RESULT_FAIL;
    }
    if (!(bs1 <= bs5)) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetOperatorGreater() {
    const size_t len = 100;
    FCA::BitSet bs1(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs1.set(i);
        }
    }
    FCA::BitSet bs2(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 6 == 0) {
            bs2.set(i);
        }
    }
    FCA::BitSet bs3(len);
    for (size_t i = 0; i < len; ++i) {
        bs3.set(i);
    }
    FCA::BitSet bs4(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 5 == 0) {
            bs4.set(i);
        }
    }
    if (!(bs1 > bs2)) {
        return TEST_RESULT_FAIL;
    }
    if (bs1 > bs3) {
        return TEST_RESULT_FAIL;
    }
    if (bs1 > bs4) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}

TEST_RESULT TestBitSetOperatorGreaterEqual() {
    const size_t len = 100;
    FCA::BitSet bs1(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs1.set(i);
        }
    }
    FCA::BitSet bs2(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 6 == 0) {
            bs2.set(i);
        }
    }
    FCA::BitSet bs3(len);
    for (size_t i = 0; i < len; ++i) {
        bs3.set(i);
    }
    FCA::BitSet bs4(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 5 == 0) {
            bs4.set(i);
        }
    }
    FCA::BitSet bs5(len);
    for (size_t i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            bs5.set(i);
        }
    }
    if (!(bs1 >= bs2)) {
        return TEST_RESULT_FAIL;
    }
    if (bs1 >= bs3) {
        return TEST_RESULT_FAIL;
    }
    if (bs1 >= bs4) {
        return TEST_RESULT_FAIL;
    }
    if (!(bs1 >= bs5)) {
        return TEST_RESULT_FAIL;
    }
    return TEST_RESULT_OK;
}
