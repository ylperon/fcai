#pragma once

#include <cstdio>

#include <vector>
#include <string>

enum TEST_RESULT {
    TEST_RESULT_OK,
    TEST_RESULT_FAIL,
};

struct TestFunction {
    TestFunction(const std::string& name = "", TEST_RESULT(* const fun)() = 0) : name(name), fun(fun) {
    }
    std::string name;
    TEST_RESULT (*fun)();
};

typedef std::vector<TestFunction> TestFunctionVector;

struct TestFunctionGroup {
    TestFunctionGroup(const std::string& name = "", TEST_RESULT(* const fun)(const std::string&, size_t&, size_t&) = 0) : name(name), fun(fun) {
    }
    std::string name;
    TEST_RESULT (*fun)(const std::string&, size_t&, size_t&);
};

typedef std::vector<TestFunctionGroup> TestFunctionGroupVector;

void IncOkFail(const TEST_RESULT res, size_t& ok, size_t& fail);
void PrintOkFail(const TEST_RESULT res, FILE* out);
void PrintOkFailAndLineFeed(const TEST_RESULT res, FILE* out);

void RunTestsFromGroup(const TestFunctionVector& testFunctions,
                       const std::string& indent,
                       size_t& ok,
                       size_t& fail);
