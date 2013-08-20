#include <cstdio>

#include <string>

#include "test_bitset.h"
#include "test_implication.h"
#include "test_concept.h"
#include "test_context.h"
#include "test_context_string.h"

TestFunctionGroupVector InitAllTests() {
    TestFunctionGroupVector res;
    res.push_back(TestBitSetAll);
    res.push_back(TestImplicationAll);
    res.push_back(TestConceptAll);
    res.push_back(TestContextAll);
    res.push_back(TestContextStringAll);
    return res;
}

int main() {
    fprintf(stdout, "Running all tests:\n");
    size_t okGlobal = 0;
    size_t failGlobal = 0;
    size_t okSub = 0;
    size_t failSub = 0;
    TestFunctionGroupVector allTests = InitAllTests();
    for (size_t i = 0; i < allTests.size(); ++i) {
        const std::string indent = "\t";
        size_t ok = 0;
        size_t fail = 0;
        TEST_RESULT res = allTests[i].fun(indent, ok, fail);
        if (TEST_RESULT_OK == res) {
            ++okGlobal;
        } else {
            ++failGlobal;
        }
        okSub += ok;
        failSub += fail;
    }
    fprintf(stdout, "Total subtest OK: %lu\n", okSub);
    fprintf(stdout, "Total subtest FAIL: %lu\n", failSub);
    const double pSub = (0 == okSub + failSub ? 100 : static_cast<double>(okSub * 100) / static_cast<double>(okSub + failSub));
    fprintf(stdout, "Successfull subtest: %.2lf %%\n", pSub);
    fprintf(stdout, "Total test OK: %lu\n", okGlobal);
    fprintf(stdout, "Total test FAIL: %lu\n", failGlobal);
    const double pGlobal = (0 == okGlobal + failGlobal ? 100 : static_cast<double>(okGlobal * 100) / static_cast<double>(okGlobal + failGlobal));
    fprintf(stdout, "Successfull tests: %.2lf %%\n", pGlobal);
    fprintf(stdout, "Running all tests:");
    TEST_RESULT res = (0 == failGlobal ? TEST_RESULT_OK : TEST_RESULT_FAIL);
    PrintOkFailAndLineFeed(res, stdout);

    return 0;
}
