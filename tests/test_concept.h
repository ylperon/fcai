#pragma once

#include <cstdio>

#include <vector>

#include "test_util.h"
#include "fca_concept.h"

extern TestFunctionGroup TestConceptAll;

TestFunctionVector GetAllConceptTestFunctions();

TEST_RESULT TestConcept(const std::string& indent, size_t& ok, size_t& fail);

TEST_RESULT TestConceptDefaultConstructor();
