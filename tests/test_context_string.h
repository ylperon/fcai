#pragma once

#include <cstdio>

#include <vector>

#include "test_util.h"
#include "fca_context_string.h"

extern TestFunctionGroup TestContextStringAll;

TestFunctionVector GetAllContextStringTestFunctions();

TEST_RESULT TestContextString(const std::string& indent, size_t& ok, size_t& fail);

TEST_RESULT TestContextStringDefaultConstructor();
