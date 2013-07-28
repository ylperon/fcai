#pragma once

#include <cstdio>

#include <vector>

#include "test_util.h"
#include "fca_context.h"

extern TestFunctionGroup TestContextAll;

TestFunctionVector GetAllContextTestFunctions();

TEST_RESULT TestContext(const std::string& indent, size_t& ok, size_t& fail);

TEST_RESULT TestContextDefaultConstructor();
