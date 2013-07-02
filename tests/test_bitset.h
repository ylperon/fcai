#pragma once

#include <cstdio>
#include <vector>

#include "test_util.h"
#include "fca_bitset.h"

extern TestFunctionGroup TestBitSetAll;

TestFunctionVector GetAllBitSetTestFunctions();

TEST_RESULT TestBitSet(const std::string& indent, size_t& ok, size_t& fail);

TEST_RESULT TestBitSetConctruct();
TEST_RESULT TestBitSetCopyConstruct();
TEST_RESULT TestBitSetSetAndTest();
TEST_RESULT TestBitSetAnyAndNone();
TEST_RESULT TestBitSetSetAllAndTestAll();
TEST_RESULT TestBitSetFlipAll();
TEST_RESULT TestBitSetFlip();
TEST_RESULT TestBitSetIsSubsetOf();
TEST_RESULT TestBitSetIsProperSubsetOf();
