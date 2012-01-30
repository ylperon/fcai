# pragma once

# ifndef TEST_FUNCTIONS_H_
# define TEST_FUNCTIONS_H_

# include <fstream>
# include <vector>
# include <string>

# include "fca_context.h"
# include "fca_algorithms.h"
# include "test_timer.h"
# include "test_time.h"

std::vector<std::string> ReadFileNames(std::ifstream &input);

void ReadContext(FCA::Context &c, std::istream &in);

void ReadImplicatons(std::ifstream &input, std::vector<FCA::Implication> &implications);

void PrintImplications(std::ofstream &output, const std::vector<FCA::Implication> &implications);

void ReadImplicationsAndSets(std::vector<FCA::ImplicationInd> &implications, std::vector<FCA::BitSet> &bitsets, std::ifstream &in);

FCA::BitSet StringToBitset(const std::string &str);

FCA::BitSet GetRandomBitSet(const size_t n, const double prob);

bool IsVectorOfImplicationsIdentical(std::vector<FCA::Implication> v1, std::vector<FCA::Implication> v2);

void ReadContextAndPrintProperBasis(std::istream &input, std::ofstream &output);

void ReadContextAndPrintDGBasisUsingProperBasis(std::istream &input, std::ofstream &output);

void ReadContextAndPrintDGBasisUsingObjIncremental(std::istream &input, std::ofstream &output);

void ReadContextAndPrintDGBasisUsingMinGen1(std::istream &input, std::ofstream &output);

template <typename CloseFunction>
void ReadContextAndPrintDGBasisUsingGanter(std::istream &input, std::ofstream &output, const std::string &cfName);

template <typename CloseFunction>
void ReadContextAndPrintDGBasisUsingGanterOptimized(std::istream &input, std::ofstream &output, const std::string &cfName);

template <typename CloseFunction>
void SpeedTestUsingGanter(std::vector<std::string> fileNames, std::ofstream &output,
                          const std::string &cfName);

template <typename CloseFunction>
void SpeedTestUsingGanterOptimized(std::vector<std::string> fileNames, std::ofstream &output,
                                   const std::string &cfName);

void SpeedTestUsingProperBasis(std::vector<std::string> fileNames, std::ofstream &output);

void SpeedTestUsingObjIncremental(std::vector<std::string> fileNames, std::ofstream &output);

void SpeedTestUsingMinGen1(std::vector<std::string> fileNames, std::ofstream &output);

void BuildBasisAndCloseSet(std::vector<std::string> fileNames, std::ofstream &output, const double probability, const size_t rep);

void BuildBasisAndCloseSetOpt(std::vector<std::string> fileNames, std::ofstream &output, const double probability, const size_t rep);

template <typename CloseFunction>
void SpeedTest(std::vector<std::string> fileNames, std::ofstream &output, const std::string &cfName, const size_t rep, const bool rev);

template <typename CloseFunction1, typename CloseFunction2>
void IsBasisComputedByGanterIdentical(std::vector<std::string> fileNames, std::ofstream &output,
                                      const std::string &cf1Name, const std::string &cf2Name);

template <typename CloseFunction1, typename CloseFunction2>
void IsBasisComputedByGanterOptimizedIdentical(std::vector<std::string> fileNames, std::ofstream &output,
                                               const std::string &cf1Name, const std::string &cf2Name);

template <typename CloseFunction1, typename CloseFunction2>
void IsBasisComputedByGanterAndGanterOptimizedIdentical(std::vector<std::string> fileNames, std::ofstream &output,
                                                        const std::string &cf1Name, const std::string &cf2Name);

template <typename CloseFunction1, typename CloseFunction2>
void IsResultOfClosureFunctionsIdentical(std::vector<std::string> fileNames, std::ofstream &output,
                                         const std::string &cf1Name, const std::string &cf2Name);

//=====================================================================================================================
//==========================================Realization of templates==========================================================
//=====================================================================================================================

# include "test_timer.h"

template <typename CloseFunction>
void ReadContextAndPrintDGBasisUsingGanter(std::istream &input, std::ofstream &output, const std::string &cfName)
{
    FCA::Context cntx;
    ReadContext(cntx, input);

    std::vector<FCA::ImplicationInd> impsBool;
    std::vector<FCA::Implication> imps;

    std::cout << "Ganter" << " " << cfName << std::endl;

    impsBool = FCA::ComputeDGBasis<CloseFunction>(cntx);	
    imps = FCA::Convert(impsBool, cntx.getAttributes());
    
    PrintImplications(output, imps);
}

template <typename CloseFunction>
void ReadContextAndPrintDGBasisUsingGanterOptimized(std::istream &input, std::ofstream &output, const std::string &cfName)
{
    FCA::Context cntx;
    ReadContext(cntx, input);

    std::vector<FCA::ImplicationInd> impsBool;
    std::vector<FCA::Implication> imps;

    std::cout << "Ganter" << " " << cfName << std::endl;

    impsBool = FCA::ComputeDGBasisOptimized<CloseFunction>(cntx);	
    imps = FCA::Convert(impsBool, cntx.getAttributes());
    
    PrintImplications(output, imps);
}

template <typename CloseFunction>
void SpeedTestUsingGanter(std::vector<std::string> fileNames, std::ofstream &output,
                          const std::string &cfName)
{
    std::ifstream input;
    for (size_t fileInd = 0; fileInd < fileNames.size(); ++fileInd)
    {
        input.open(fileNames[fileInd].c_str());
        FCA::Context context;			

        ReadContext(context, input);
        input.close();		

        std::cout << "Ganter" << " " << cfName << " \"" << fileNames[fileInd] << '\"';

        Timer timer;						
        timer.StartTiming();
        std::vector<FCA::ImplicationInd> implications = FCA::ComputeDGBasis<CloseFunction>(context);			
        timer.StopTiming();

        output << fileInd + 1 << ". " << Time(timer.GetUserSeconds()) << " " << implications.size() << std::endl;
        std::cout << " complete in " << Time(timer.GetUserSeconds()) << " " << implications.size() << " implications" << std::endl;		
    }
}

template <typename CloseFunction>
void SpeedTestUsingGanterOptimized(std::vector<std::string> fileNames, std::ofstream &output,
                                   const std::string &cfName)
{
    std::ifstream input;	
    for (size_t fileInd = 0; fileInd < fileNames.size(); ++fileInd)
    {
        input.open(fileNames[fileInd].c_str());
        FCA::Context context;

        ReadContext(context, input);
        input.close();

        std::cout << "Ganter Optimized" << " " << cfName << " \"" << fileNames[fileInd] << '\"';

        Timer timer;
        timer.StartTiming();
        std::vector<FCA::ImplicationInd> implications = FCA::ComputeDGBasisOptimized<CloseFunction>(context);		
        timer.StopTiming();

        output << fileInd + 1 << ". " << Time(timer.GetUserSeconds()) << " " << implications.size() << std::endl;
        std::cout << " complete in " << Time(timer.GetUserSeconds()) << " " << implications.size() << " implications" << std::endl;		
    }
}

template <typename CloseFunction>
void SpeedTest(std::vector<std::string> fileNames, std::ofstream &output, const std::string &cfName, const size_t rep, const bool rev)
{
    std::ifstream input;		
    for (size_t fileInd = 0; fileInd < fileNames.size(); ++fileInd)
    {
        input.open(fileNames[fileInd].c_str());

        std::vector<FCA::BitSet> sets;
        std::vector<FCA::ImplicationInd> implications;	
        ReadImplicationsAndSets(implications, sets, input);
        if (rev)
        {
            std::reverse(implications.begin(), implications.end());
        }

        std::cout << cfName << " \"" << fileNames[fileInd] << "\"" << " on the way" << std::endl;
        output << fileNames[fileInd] << " " << implications.size() << std::endl;

        for (size_t i = 0; i < sets.size(); ++i)
        {
            std::cout << i << " ";
            output << i << " ";
            FCA::BitSet current = sets[i];	

            Timer timer;
            FCA::BitSet resTmp;
            timer.StartTiming();
            for (size_t j = 0; j < rep; ++j)
            {
                CloseFunction::Apply(current, implications, resTmp);						
            }
            timer.StopTiming();

            output << Time(timer.GetUserSeconds());
            output << current.count() << std::endl;
        
        }
        std::cout << std::endl;

        input.close();
    }
}

template <typename CloseFunction1, typename CloseFunction2>
void IsBasisComputedByGanterIdentical(std::vector<std::string> fileNames, std::ofstream &output,
                                      const std::string &cf1Name, const std::string &cf2Name)
{
    std::ifstream input;
    FCA::Context context;
    std::vector<FCA::Implication> implications1;
    std::vector<FCA::Implication> implications2;
    std::vector<FCA::ImplicationInd> implications1Bool;
    std::vector<FCA::ImplicationInd> implications2Bool;
    std::vector<bool> results;
    bool res = true;
    size_t firstFalseInd = fileNames.size();

    for (size_t fileInd = 0; fileInd < fileNames.size(); ++fileInd)
    {
        input.open(fileNames[fileInd].c_str());
        ReadContext(context, input);

        std::cout << "Ganter" << " " << cf1Name << " " << "Ganter" << " " << cf2Name 
                  << " \"" << fileNames[fileInd] << '\"' << std::endl;
        
        implications1Bool = FCA::ComputeDGBasis<CloseFunction1>(context);		
        implications2Bool = FCA::ComputeDGBasis<CloseFunction2>(context);
        implications1 = FCA::Convert(implications1Bool, context.getAttributes());
        implications2 = FCA::Convert(implications2Bool, context.getAttributes());
        
        results.push_back(IsVectorOfImplicationsIdentical(implications1, implications2));
        res &= results.back();
        if (!res)
            firstFalseInd = firstFalseInd < fileInd ? firstFalseInd : fileInd;

        input.close();
    }

    std::string trueString("true");
    std::string falseString("false");	

    if (!res)
        output << falseString  << " " << firstFalseInd << std::endl;	
    else
        output << trueString << std::endl;

    for (size_t i = 0; i < results.size(); ++i)
        output << i + 1 << ". " << (results[i] ? trueString : falseString) << std::endl;
}

template <typename CloseFunction1, typename CloseFunction2>
void IsBasisComputedByGanterOptimizedIdentical(std::vector<std::string> fileNames, std::ofstream &output,
                                               const std::string &cf1Name, const std::string &cf2Name)
{
    std::ifstream input;
    FCA::Context context;
    std::vector<FCA::Implication> implications1;
    std::vector<FCA::Implication> implications2;
    std::vector<FCA::ImplicationInd> implications1Bool;
    std::vector<FCA::ImplicationInd> implications2Bool;
    std::vector<bool> results;
    bool res = true;
    size_t firstFalseInd = fileNames.size();

    for (size_t fileInd = 0; fileInd < fileNames.size(); ++fileInd)
    {
        input.open(fileNames[fileInd].c_str());
        ReadContext(context, input);

        std::cout << "Ganter Optimized" << " " << cf1Name << " " << "Ganter Optimized" << " " << cf2Name 
                  << " \"" << fileNames[fileInd] << '\"' << std::endl;
        
        implications1Bool = FCA::ComputeDGBasisOptimized<CloseFunction1>(context);		
        implications2Bool = FCA::ComputeDGBasisOptimized<CloseFunction2>(context);
        implications1 = FCA::Convert(implications1Bool, context.getAttributes());
        implications2 = FCA::Convert(implications2Bool, context.getAttributes());
        
        results.push_back(IsVectorOfImplicationsIdentical(implications1, implications2));
        res &= results.back();
        if (!res)
            firstFalseInd = firstFalseInd < fileInd ? firstFalseInd : fileInd;

        input.close();
    }

    std::string trueString("true");
    std::string falseString("false");	

    if (!res)
        output << falseString  << " " << firstFalseInd << std::endl;	
    else
        output << trueString << std::endl;

    for (size_t i = 0; i < results.size(); ++i)
        output << i + 1 << ". " << (results[i] ? trueString : falseString) << std::endl;
}

template <typename CloseFunction1, typename CloseFunction2>
void IsBasisComputedByGanterAndGanterOptimizedIdentical(std::vector<std::string> fileNames, std::ofstream &output,
                                                        const std::string &cf1Name, const std::string &cf2Name)
{
    std::ifstream input;
    FCA::Context context;
    std::vector<FCA::Implication> implications1;
    std::vector<FCA::Implication> implications2;
    std::vector<FCA::ImplicationInd> implications1Bool;
    std::vector<FCA::ImplicationInd> implications2Bool;
    std::vector<bool> results;
    bool res = true;
    size_t firstFalseInd = fileNames.size();

    for (size_t fileInd = 0; fileInd < fileNames.size(); ++fileInd)
    {
        input.open(fileNames[fileInd].c_str());
        ReadContext(context, input);

        std::cout << "Ganter" << " " << cf1Name << " " << "Ganter Optimized" << " " << cf2Name 
                  << " \"" << fileNames[fileInd] << '\"' << std::endl;
        
        implications1Bool = FCA::ComputeDGBasis<CloseFunction1>(context);		
        implications2Bool = FCA::ComputeDGBasisOptimized<CloseFunction2>(context);
        implications1 = FCA::Convert(implications1Bool, context.getAttributes());
        implications2 = FCA::Convert(implications2Bool, context.getAttributes());
        
        results.push_back(IsVectorOfImplicationsIdentical(implications1, implications2));
        res &= results.back();
        if (!res)
            firstFalseInd = firstFalseInd < fileInd ? firstFalseInd : fileInd;

        input.close();
    }

    std::string trueString("true");
    std::string falseString("false");	

    if (!res)
        output << falseString  << " " << firstFalseInd << std::endl;	
    else
        output << trueString << std::endl;

    for (size_t i = 0; i < results.size(); ++i)
        output << i + 1 << ". " << (results[i] ? trueString : falseString) << std::endl;
}

template <typename CloseFunction1, typename CloseFunction2>
void IsResultOfClosureFunctionsIdentical(std::vector<std::string> fileNames, std::ofstream &output,
                                         const std::string &cf1Name, const std::string &cf2Name)
{
    std::ifstream input;	
    FCA::BitSet res1, res2, current;
    std::vector<FCA::ImplicationInd> implications;
    std::vector<FCA::BitSet> sets;
    std::vector<bool> results;	
    bool res = true;
    size_t firstFalseInd = fileNames.size();

    for (size_t fileInd = 0; fileInd < fileNames.size(); ++fileInd)
    {
        input.open(fileNames[fileInd].c_str());
        ReadImplicationsAndSets(implications, sets, input);

        std::cout << cf1Name << " " << cf2Name << " \"" << fileNames[fileInd] << '\"' << std::endl;

        for (size_t i = 0; i < sets.size(); ++i)
        {
            current = sets[i];
            CloseFunction1::Apply(current, implications, res1);		
            CloseFunction2::Apply(current, implications, res2);
        
            results.push_back(res1 == res2);
            res &= results.back();
            if (!res)
                firstFalseInd = firstFalseInd < fileInd ? firstFalseInd : fileInd;
        }

        input.close();
    }

    std::string trueString("true");
    std::string falseString("false");	

    if (!res)
        output << falseString  << " " << firstFalseInd << std::endl;	
    else
        output << trueString << std::endl;

    for (size_t i = 0; i < results.size(); ++i)
        output << i + 1 << ". " << (results[i] ? trueString : falseString) << std::endl;
}

# endif TEST_FUNCTIONS_H_