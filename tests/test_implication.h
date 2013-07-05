# pragma once

#include <cstdio>
#include <vector>

#include "test_util.h"
#include "fca_implication.h"

extern TestFunctionGroup TestImplicationAll;

TestFunctionVector GetAllImplicationTestFunctions();

TEST_RESULT TestImplication(const std::string& indent, size_t& ok, size_t& fail);
