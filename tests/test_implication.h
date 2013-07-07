# pragma once

#include <cstdio>
#include <vector>

#include "test_util.h"
#include "fca_implication.h"

extern TestFunctionGroup TestImplicationAll;

TestFunctionVector GetAllImplicationTestFunctions();

TEST_RESULT TestImplication(const std::string& indent, size_t& ok, size_t& fail);

TEST_RESULT TestImplicationDefaultConstructor();
TEST_RESULT TestImplicationSizeConstructor();
TEST_RESULT TestImplicationTwoBitSetConstructor();
TEST_RESULT TestImplicationCopyConstructor();
TEST_RESULT TestImplicationPremiseGetter();
TEST_RESULT TestImplicationConclusionGetter();
