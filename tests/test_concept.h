#pragma once

#include <cstdio>

#include <vector>

#include "test_util.h"
#include "fca_concept.h"

extern TestFunctionGroup TestConceptAll;

TestFunctionVector GetAllConceptTestFunctions();

TEST_RESULT TestConcept(const std::string& indent, size_t& ok, size_t& fail);

TEST_RESULT TestConceptDefaultConstructor();
TEST_RESULT TestConctptSizeConstructor();
TEST_RESULT TestConceptTwoBitSetConstructor();
TEST_RESULT TestConceptCopyConstructor();
TEST_RESULT TestConceptExtentGetter();
TEST_RESULT TestConceptIntentGetter();
TEST_RESULT TestConceptExtentSize();
TEST_RESULT TestConceptIntentSize();
