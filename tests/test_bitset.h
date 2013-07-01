#pragma once

#include <cstdio>
#include <vector>

#include "test_util.h"
#include "fca_bitset.h"

extern TestFunctionGroup TestBitSetAll;

std::vector<TestFunction> GetAllBitSetTestFunctions();

TEST_RESULT TestBitSet(const std::string& indent, size_t& ok, size_t& fail);

TEST_RESULT TestBitSetConctruct();
TEST_RESULT TestBitSetCopyConstruct();
TEST_RESULT TestBitSetSetAndTest();
