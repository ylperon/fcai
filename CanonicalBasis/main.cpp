# include <fstream>
# include <vector>
# include <string>
# include <algorithm>
# include <iostream>

# ifdef _DEBUG	
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
# endif

# include "fca_closure_operators.h"
# include "test_functions.h"

using namespace std;

void RunReadAndPrintTest(string inputFileName, string outputFileName)
{
    ifstream input;
    ofstream output(outputFileName.c_str());	
    std::string clName("Closure");	
    std::string lcName("LinClosure");	
    std::string lciName("LinClosureImproved");

    /*input.open(inputFileName.c_str());
    ReadContextAndPrintDGBasisUsingGanter<FCA::Closure>(input, output, clName);
    input.close();
    output << endl;*/

    /*input.open(inputFileName.c_str());
    ReadContextAndPrintDGBasisUsingGanter<FCA::LinClosure>(input, output, lcName);
    input.close();
    output << endl;

    input.open(inputFileName.c_str());
    ReadContextAndPrintDGBasisUsingGanter<FCA::LinClosureImproved>(input, output, lciName);
    input.close();
    output << endl;*/

    /*input.open(inputFileName.c_str());
    ReadContextAndPrintDGBasisUsingGanterOptimized<FCA::Closure>(input, output, clName);
    input.close();
    output << endl;*/

    /*input.open(inputFileName.c_str());
    ReadContextAndPrintDGBasisUsingGanterOptimized<FCA::LinClosure>(input, output, lcName);
    input.close();
    output << endl;*/

    /*input.open(inputFileName.c_str());
    ReadContextAndPrintDGBasisUsingGanterOptimized<FCA::LinClosureImproved>(input, output, lciName);
    input.close();
    output << endl;*/

    /*input.open(inputFileName.c_str());
    ReadContextAndPrintDGBasisUsingProperBasis(input, output);
    input.close();
    output << endl;*/

    /*input.open(inputFileName.c_str());
    ReadContextAndPrintDGBasisUsingObjIncremental(input, output);
    input.close();
    output << endl;*/

    /*input.open(inputFileName.c_str());
    ReadContextAndPrintDGBasisUsingMinGen1(input, output);
    input.close();
    output << endl;*/

    input.open(inputFileName.c_str());
    std::cout << (input.is_open() ? "file open" : "file not open") << std::endl;
    ReadContextAndPrintDGBasisUsingAttrIncremental(input, output);
    input.close();
    output << endl;
    
    output.close();
}

void RunBasisBuilderSpeedTest(string inputFileName, string outputFileName)
{		
    std::string clName("Closure");	
    std::string lcName("LinClosure");	
    std::string lciName("LinClosureImproved");
    string ganterAlgorithm("Ganter");
    string ganterOptimizedAlgorithm("Ganter optimized");
    string attributeIncrementalAlgorithm("Attribute incremental algorithm");

    vector<string> fileNames;
    ifstream input(inputFileName.c_str());	
    fileNames = ReadFileNames(input);
    input.close();

    ofstream output(outputFileName.c_str());

    /*output << "canonical base algorithm: " << ganterAlgorithm << endl
           << "closure function: " << clName << endl;
    SpeedTestUsingGanter<FCA::Closure>(fileNames, output, clName);
    output << endl;
    
    output << "canonical base algorithm: " << ganterAlgorithm << endl
           << "closure function: " << lcName << endl;
    SpeedTestUsingGanter<FCA::LinClosure>(fileNames, output, lcName);
    output << endl;

    output << "canonical base algorithm: " << ganterAlgorithm << endl
           << "closure function: " << lciName << endl;
    SpeedTestUsingGanter<FCA::LinClosureImproved>(fileNames, output, lciName);
    output << endl;*/
    
    output << "canonical base optimized algorithm: " << ganterOptimizedAlgorithm << endl
           << "closure function: " << clName << endl;
    SpeedTestUsingGanterOptimized<FCA::Closure>(fileNames, output, clName);
    output << endl;
    
    output << "canonical base optimized algorithm: " << ganterOptimizedAlgorithm << endl
           << "closure function: " << lcName << endl;
    SpeedTestUsingGanterOptimized<FCA::LinClosure>(fileNames, output, lcName);
    output << endl;
    
    output << "canonical base optimized algorithm: " << ganterOptimizedAlgorithm << endl
           << "closure function: " << lciName << endl;
    SpeedTestUsingGanterOptimized<FCA::LinClosureImproved>(fileNames, output, lciName);
    output << endl;

    /*output << "Impec algorithm and convertion from proper basis to DG basis" << endl;
    SpeedTestUsingProperBasis(fileNames, output);
    output << endl;*/

    /*output << "Object Incremental algorithm:" << endl;
    SpeedTestUsingObjIncremental(fileNames, output);
    output << endl;*/

    /*output << "MinGen1 algorithm:" << endl;
    SpeedTestUsingMinGen1(fileNames, output);
    output << endl;*/

    output << "canonical base optimized algorithm: " << attributeIncrementalAlgorithm << endl;
    SpeedTestUsingAttrIncremental(fileNames, output);
    output << endl;
    
    output.close();
}

void RunCloseFunctionSpeedTest(string inputFileName, string outputFileName, const size_t rep, const bool rev)
{	
    std::string clName("Closure");	
    std::string lcName("LinClosure");	
    std::string lciName("LinClosureImproved");

    vector<string> fileNames;		
    ifstream input(inputFileName.c_str());
    fileNames = ReadFileNames(input);
    input.close();

    ofstream output(outputFileName.c_str());

    output << "rep = " << rep << std::endl;

    output << "closure function: " << clName << endl;
    SpeedTest<FCA::Closure>(fileNames, output, clName, rep, rev);
    output << endl;

    output << "closure function: " << lcName << endl;
    SpeedTest<FCA::LinClosure>(fileNames, output, lcName, rep, rev);
    output << endl;

    output << "closure function: " << lciName << endl;
    SpeedTest<FCA::LinClosureImproved>(fileNames, output, lciName, rep, rev);
    output << endl;
    
    output.close();
}

void RunBasisBuilderIdentityTest(string inputFileName, string outputFileName)
{	
    std::string clName("Closure");	
    std::string lcName("LinClosure");	
    std::string lciName("LinClosureImproved");
    string ganterAlgorithm("Ganter");
    string ganterOptimizedAlgorithm("Ganter optimized");

    vector<string> fileNames;
    ifstream input(inputFileName.c_str());	
    fileNames = ReadFileNames(input);
    input.close();

    ofstream output(outputFileName.c_str());

    //start of using Ganter algorithm

    output << "canonical base algorithm 1: " << ganterAlgorithm << endl
           << "closure function 1: " << clName << endl
           << "canonical base algorithm 2: " << ganterAlgorithm << endl
           << "closure function 2: " << lcName << endl;
    IsBasisComputedByGanterIdentical<FCA::Closure, FCA::LinClosure>(fileNames, output, clName, lcName);
    output << endl;	

    output << "canonical base algorithm 1: " << ganterAlgorithm << endl
           << "closure function 1: " << clName << endl
           << "canonical base algorithm 2: " << ganterAlgorithm << endl
           << "closure function 2: " << lciName << endl;
    IsBasisComputedByGanterIdentical<FCA::Closure, FCA::LinClosureImproved>(fileNames, output, clName, lciName);
    output << endl;

    output << "canonical base algorithm 1: " << ganterAlgorithm << endl
           << "closure function 1: " << lcName << endl
           << "canonical base algorithm 2: " << ganterAlgorithm << endl
           << "closure function 2: " << lciName << endl;
    IsBasisComputedByGanterIdentical<FCA::LinClosure, FCA::LinClosureImproved>(fileNames, output, lcName, lciName);
    output << endl;

    //end of using Ganter algorithm

    //start of using Ganter optimized algorithm

    output << "canonical base algorithm 1: " << ganterOptimizedAlgorithm << endl
           << "closure function 1: " << clName << endl
           << "canonical base algorithm 2: " << ganterOptimizedAlgorithm << endl
           << "closure function 2: " << lcName << endl;
    IsBasisComputedByGanterOptimizedIdentical<FCA::Closure, FCA::LinClosure>(fileNames, output, clName, lcName);
    output << endl;	

    output << "canonical base algorithm 1: " << ganterOptimizedAlgorithm << endl
           << "closure function 1: " << clName << endl
           << "canonical base algorithm 2: " << ganterOptimizedAlgorithm << endl
           << "closure function 2: " << lciName << endl;
    IsBasisComputedByGanterOptimizedIdentical<FCA::Closure, FCA::LinClosure>(fileNames, output, clName, lciName);
    output << endl;

    output << "canonical base algorithm 1: " << ganterOptimizedAlgorithm << endl
           << "closure function 1: " << lcName << endl
           << "canonical base algorithm 2: " << ganterOptimizedAlgorithm << endl
           << "closure function 2: " << lciName << endl;
    IsBasisComputedByGanterOptimizedIdentical<FCA::LinClosure, FCA::LinClosureImproved>(fileNames, output, lcName, lciName);
    output << endl;

    //end of using Ganter optimized algorithm

    //start of using Ganter and Ganter optimized algorithm

    output << "canonical base algorithm 1: " << ganterAlgorithm << endl
           << "closure function 1: " << clName << endl
           << "canonical base algorithm 2: " << ganterOptimizedAlgorithm << endl
           << "closure function 2: " << clName << endl;
    IsBasisComputedByGanterAndGanterOptimizedIdentical<FCA::Closure, FCA::Closure>(fileNames, output, clName, clName);
    output << endl;		

    output << "canonical base algorithm 1: " << ganterAlgorithm << endl
           << "closure function 1: " << lcName << endl
           << "canonical base algorithm 2: " << ganterOptimizedAlgorithm << endl
           << "closure function 2: " << lcName << endl;
    IsBasisComputedByGanterAndGanterOptimizedIdentical<FCA::LinClosure, FCA::LinClosure>(fileNames, output, lcName, lcName);
    output << endl;

    output << "canonical base algorithm 1: " << ganterAlgorithm << endl
           << "closure function 1: " << lciName << endl
           << "canonical base algorithm 2: " << ganterOptimizedAlgorithm << endl
           << "closure function 2: " << lciName << endl;
    IsBasisComputedByGanterAndGanterOptimizedIdentical<FCA::LinClosureImproved, FCA::LinClosureImproved>(fileNames, output, lciName, lciName);
    output << endl;

    //end of using Ganter and Ganter optimized algorithm

    output.close();
}

void RunCloseFunctionIdentityTest(string inputFileName, string outputFileName)
{
    std::string clName("Closure");	
    std::string lcName("LinClosure");
    std::string lciName("LinClosureImproved");

    vector<string> fileNames;		
    ifstream input(inputFileName.c_str());
    fileNames = ReadFileNames(input);
    input.close();

    ofstream output(outputFileName.c_str());

    output << "closure function 1: " << clName << endl
           << "closure function 2: " << lcName << endl;
    IsResultOfClosureFunctionsIdentical<FCA::Closure, FCA::LinClosure>(fileNames, output, clName, lcName);
    output << endl;	

    output << "closure function 1: " << clName << endl
           << "closure function 2: " << lciName << endl;
    IsResultOfClosureFunctionsIdentical<FCA::Closure, FCA::LinClosureImproved>(fileNames, output, clName, lciName);
    output << endl;

    output << "closure function 1: " << lcName << endl
           << "closure function 2: " << lciName << endl;
    IsResultOfClosureFunctionsIdentical<FCA::LinClosure, FCA::LinClosureImproved>(fileNames, output, lcName, lciName);
    output << endl;
    
    output.close();
}

void RunProperReadAndPrintTest(string inputFileName, string outputFileName)
{
    ifstream input;
    ofstream output(outputFileName.c_str());

    input.open(inputFileName.c_str());
    ReadContextAndPrintProperBasis(input, output);
    input.close();

    output.close();
}

void RunBuildBasisAndCloseSetTest(string inputFileName, string outputFileName, const double probability, const size_t rep)
{
    vector<string> fileNames;
    ifstream input(inputFileName.c_str());	
    fileNames = ReadFileNames(input);
    input.close();

    ofstream output(outputFileName.c_str());

    BuildBasisAndCloseSet(fileNames, output, probability, rep);

    output.close();
}

void RunBuildBasisAndCloseSetOptTest(string inputFileName, string outputFileName, const double probability, const size_t rep)
{
    vector<string> fileNames;
    ifstream input(inputFileName.c_str());	
    fileNames = ReadFileNames(input);
    input.close();

    ofstream output(outputFileName.c_str());

    BuildBasisAndCloseSetOpt(fileNames, output, probability, rep);

    output.close();
}

int main()
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif    

    try
    {
        //RunReadAndPrintTest("contexts/breast-w.cxt", "test_res/output.txt");
        RunBasisBuilderSpeedTest("test_res/filenames.txt", "test_res/speedtestContext.txt");
        //RunCloseFunctionSpeedTest("filenamesImplAll.txt", "speedtestImpl_rev.txt", 1000, true);
        //RunBasisBuilderIdentityTest("fileNamesContext.txt", "identitytestContext.txt");
        //RunCloseFunctionIdentityTest("filenamesImpl.txt", "identitytestImpl.txt");
        //RunProperReadAndPrintTest("input.txt", "output.txt");
        //RunBuildBasisAndCloseSetTest("filenamesContextAll.txt", "speedtestOper.txt", 0.5, 1000);
        //RunBuildBasisAndCloseSetOptTest("filenamesContextAll.txt", "speedtestOperOpt.txt", 0.5, 1000);        

    }	
    catch (std::exception &exc)
    {
        cout << exc.what() << endl;
    }

    return 0;
}