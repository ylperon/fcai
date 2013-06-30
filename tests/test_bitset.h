#pragma once

#include <cstdio>
#include <vector>

#include "test_util.h"
#include "fca_bitset.h"

std::vector<TestFunction> GetAllBitSetTestFunctions();

TEST_RESULT TestBitSetConctruct();
TEST_RESULT TestBitSetCopyConstruct();
TEST_RESULT TestBitSetSetAndTest();
