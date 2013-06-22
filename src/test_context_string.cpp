# include "test_context_string.h"

# include "fca_context_string.h"

# include <cstdio>

TEST_RESULT TestReadContextString()
{
    fprintf(stdout, "TEST: TestReadContextString\n");

    static const char filename[] = "../contexts/vote.cxt";

    FILE* input = fopen(filename, "r");
    if (0 == input)
    {
        fprintf(stdout, "\tERROR: can not open \"%s\"\n", filename);
        return TEST_RESULT_FAILED;
    }

    try
    {
        FCA::ContextString cxt;
        FCA::Read(input, cxt);
    }
    catch (std::exception &e)
    {
        fprintf(stdout, "\tERROR: %s\n", e.what());
        return TEST_RESULT_FAILED;
    }

    if (0 != fclose(input))
    {
        fprintf(stdout, "\tERROR: fclose() failed\n");
        return TEST_RESULT_FAILED;
    }

    return TEST_RESULT_OK;
}