# ifdef _DEBUG	
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
# endif

# include <cstdio>

# include "test_context_string.h"

void PrintOk()
{
    fprintf(stdout, "\tOK\n");
}

void PrintFailed()
{
    fprintf(stdout, "\tFAILED\n");
}

void RunAllTests()
{
    if (TEST_RESULT_OK == TestReadContextString())
    {
        PrintOk();
    }
    else
    {
        PrintFailed();
    }
}

int main()
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif    

    RunAllTests();

    return 0;
}