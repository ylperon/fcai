#pragma once

#include <cstdio>

#include <vector>

#include "test_util.h"
#include "fca_context.h"

extern TestFunctionGroup TestContextAll;

TestFunctionVector GetAllContextTestFunctions();

TEST_RESULT TestContext(const std::string& indent, size_t& ok, size_t& fail);

TEST_RESULT TestContextDefaultConstructor();
TEST_RESULT TestContextTwoSizeConstructor();
TEST_RESULT TestContextBoolTableConstructor();
TEST_RESULT TestContextBitSetTableConstructor();
TEST_RESULT TestContextCopyConstructor();
TEST_RESULT TestContextOperatorAssign();
TEST_RESULT TestContextSetAndGet();
TEST_RESULT TestContextObjAndAttrSize();
TEST_RESULT TestContextIntentGetter();
TEST_RESULT TestContextExtentGetter();
