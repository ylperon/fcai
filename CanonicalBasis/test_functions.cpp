# include <iostream>
# include <iomanip>

# include <algorithm>

# include <cstdlib>
# include <climits>
# include <cmath>

# include "test_functions.h"
# include "fca_algorithms.h"
# include "fca_closure_operators.h"

void ReadContext(FCA::Context &c, std::istream &in)
{
    size_t objNum;
    size_t attrNum;
    std::vector<std::string> obj, attr;
    std::vector<std::vector<bool> > table;
    std::string burmeister;

    in >> burmeister >> objNum >> attrNum;	

    table.resize(objNum);
    obj.resize(objNum);
    attr.resize(attrNum);
    std::getline(in, obj[0]);
    std::getline(in, obj[0]);
    for (size_t i = 0; i < objNum; ++i)
    {		
        std::getline(in, obj[i]);
    }

    for (size_t i = 0; i < attrNum; ++i)
    {
        std::getline(in, attr[i]);
    }
    
    for (size_t i = 0; i < objNum; ++i)
    {
        table[i].resize(attrNum);

        std::string lineCur;
        std::getline(in, lineCur);
        for (size_t j = 0; j < attrNum; ++j)
            table[i][j] = (lineCur[j] == '.' ? false : true);
    }

    c = FCA::Context(obj, attr, table);
}

void PrintImplications(std::ofstream &output, const std::vector<FCA::Implication> &implications)
{
    output << implications.size() << std::endl;
    for (size_t i = 0; i < implications.size(); ++i)
    {
        for (size_t j = 0; j < implications[i].Premise().size(); ++j)
            output << implications[i].Premise()[j] << (j + 1 == implications[i].Premise().size() ? "" : ", ");
        output << " --> ";
        for (size_t j = 0; j < implications[i].Conclusion().size(); ++j)
            output << implications[i].Conclusion()[j] << (j + 1 == implications[i].Conclusion().size() ? "" : ", ");
        output << std::endl;
    }
}

std::vector<std::string> ReadFileNames(std::ifstream &input)
{
    size_t number;
    std::vector<std::string> res;

    input >> number;
    res.resize(number);
    getline(input, res[0]);
    for (size_t i = 0; i < number; ++i)
    {
        getline(input, res[i]);
    }

    return res;
}

bool IsVectorOfImplicationsIdentical(std::vector<FCA::Implication> v1, std::vector<FCA::Implication> v2)
{
    std::vector<std::pair<std::vector<std::string>, std::vector<std::string> > > v1p(v1.size()), v2p(v2.size());	

    for (size_t i = 0; i < v1.size(); ++i)
    {
        v1p[i].first = v1[i].Premise();
        v1p[i].second = v1[i].Conclusion();
    }

    for (size_t i = 0; i < v2.size(); ++i)
    {
        v2p[i].first = v2[i].Premise();
        v2p[i].second = v2[i].Conclusion();
    }

    std::sort(v1p.begin(), v1p.end());
    std::sort(v2p.begin(), v2p.end());

    for (size_t i = 0; i < v1p.size(); ++i)
    {
        std::sort(v1p[i].first.begin(), v1p[i].first.end());
        std::sort(v1p[i].second.begin(), v1p[i].second.end());		
    }

    for (size_t i = 0; i < v1p.size(); ++i)
    {
        std::sort(v2p[i].first.begin(), v2p[i].first.end());
        std::sort(v2p[i].second.begin(), v2p[i].second.end());		
    }

    return v1p == v2p;
}

FCA::BitSet StringToBitset(const std::string &str)
{
    FCA::BitSet res(str.size());

    for (size_t i = 0; i < str.size(); ++i)
        if (str[i] == '1')
        {
            res.set(i);
        }
        else
        {
            res.reset(i);
        }

    return res;
}

void ReadImplicationsAndSets(std::vector<FCA::ImplicationInd> &implications, std::vector<FCA::BitSet> &bitsets, std::ifstream &in)
{	
    size_t implNumber;
    size_t setsNumber;
    size_t attrNumber;				

    in >> setsNumber >> implNumber >> attrNumber;

    implications.clear();
    bitsets.clear();	

    for (size_t setInd = 0; setInd < setsNumber; ++setInd)
    {
        FCA::BitSet tmpSet(attrNumber);
        tmpSet.reset();
        size_t setNumber;

        in >> setNumber;
        for (size_t i = 0 ; i < setNumber; ++i)		
        {
            size_t tmp;
            in >> tmp;
            tmpSet.set(tmp);
        }

        bitsets.push_back(tmpSet);
    }

    FCA::ImplicationInd implTmp;
    implTmp.Premise().resize(attrNumber);
    implTmp.Conclusion().resize(attrNumber);

    for (size_t implInd = 0; implInd < implNumber; ++implInd)
    {				
        implTmp.Premise().reset();		
        implTmp.Conclusion().reset();

        size_t premiseNumber;
        size_t conclusionNumber;

        in >> premiseNumber >> conclusionNumber;
        for (size_t i = 0; i < premiseNumber; ++i)
        {
            size_t tmp;
            in >> tmp;
            implTmp.Premise().set(tmp);
        }

        for (size_t i = 0; i < conclusionNumber; ++i)
        {
            size_t tmp;
            in >> tmp;
            implTmp.Conclusion().set(tmp);
        }

        implTmp.Conclusion() |= implTmp.Premise();
        implications.push_back(implTmp);
    }
}

void ReadContextAndPrintProperBasis(std::istream &input, std::ofstream &output)
{
    FCA::Context cxt;
    ReadContext(cxt, input);

    std::vector<FCA::ImplicationInd> implsInd = FCA::ComputeProperBasis(cxt);
    std::vector<FCA::Implication> impls = FCA::Convert(implsInd, cxt.getAttributes());

    PrintImplications(output, impls);
}

void ReadContextAndPrintDGBasisUsingProperBasis(std::istream &input, std::ofstream &output)
{
    FCA::Context cntx;
    ReadContext(cntx, input);

    std::vector<FCA::ImplicationInd> properBasis;
    std::vector<FCA::ImplicationInd> impsBool;
    std::vector<FCA::Implication> imps;

    std::cout << "Impec algorithm to construct DG basis" << std::endl;

    properBasis = FCA::ComputeProperBasis(cntx);
    impsBool = FCA::MinimalCover(properBasis);	
    imps = FCA::Convert(impsBool, cntx.getAttributes());
    
    PrintImplications(output, imps);
}

void ReadContextAndPrintDGBasisUsingMinGen1(std::istream &input, std::ofstream &output)
{
    FCA::Context cntx;
    ReadContext(cntx, input);

    std::vector<FCA::ImplicationInd> mingen;
    std::vector<FCA::ImplicationInd> impsBool;
    std::vector<FCA::Implication> imps;

    std::cout << "MinGen algorithm to construct DG basis" << std::endl;

    mingen = FCA::MinGen1(cntx);
    std::cout << "MinGen size is " << mingen.size() << std::endl;
    impsBool = FCA::MinimalCover(mingen);
    imps = FCA::Convert(impsBool, cntx.getAttributes());
    
    PrintImplications(output, imps);
}

void SpeedTestUsingProperBasis(std::vector<std::string> fileNames, std::ofstream &output)
{
    std::ifstream input;
    for (size_t fileInd = 0; fileInd < fileNames.size(); ++fileInd)
    {
        input.open(fileNames[fileInd].c_str());

        FCA::Context context;			
        ReadContext(context, input);
        input.close();

        std::cout << "Impec algorithm and convertion" << " \"" << fileNames[fileInd] << '\"' << std::endl;		
        
        
        Timer timer;
        timer.StartTiming();
        std::vector<FCA::ImplicationInd> properBasis = FCA::ComputeProperBasis(context);													
        timer.StopTiming();
        double timeComputingProperBasis = timer.GetUserSeconds();

        std::cout << "proper basis complete in " << Time(timeComputingProperBasis) << " " << properBasis.size() << " proper basis" << std::endl;
        
        timer.StartTiming();
        std::vector<FCA::ImplicationInd> implications = FCA::MinimalCover(properBasis);											
        timer.StopTiming();
        double timeConverting = timer.GetUserSeconds();

        output << fileInd + 1 << ". " << Time(timeComputingProperBasis + timeConverting) << " " << implications.size() << std::endl;
        output << "proper basis size " << properBasis.size() << std::endl;
        std::cout << "converting complete in " << Time(timeConverting) << " " << implications.size() << " implications" << std::endl;		
    }
}

void SpeedTestUsingMinGen1(std::vector<std::string> fileNames, std::ofstream &output)
{
    std::ifstream input;
    for (size_t fileInd = 0; fileInd < fileNames.size(); ++fileInd)
    {
        input.open(fileNames[fileInd].c_str());

        FCA::Context context;			
        ReadContext(context, input);
        input.close();

        std::cout << "MinGen1 algorithm and convertion" << " \"" << fileNames[fileInd] << '\"' << std::endl;		
        
        
        Timer timer;
        timer.StartTiming();
        std::vector<FCA::ImplicationInd> mingenBasis = FCA::MinGen1(context);													
        timer.StopTiming();
        double timeComputingMinGenBasis = timer.GetUserSeconds();

        std::cout << "mingen basis complete in " << Time(timeComputingMinGenBasis) << " " << mingenBasis.size() << " mingen basis" << std::endl;
        
        timer.StartTiming();
        std::vector<FCA::ImplicationInd> implications = FCA::MinimalCover(mingenBasis);											
        timer.StopTiming();
        double timeConverting = timer.GetUserSeconds();

        output << fileInd + 1 << ". " << Time(timeComputingMinGenBasis + timeConverting) << " " << implications.size() << std::endl;
        output << "mingen basis size " << mingenBasis.size() << std::endl;
        std::cout << "converting complete in " << Time(timeConverting) << " " << implications.size() << " implications" << std::endl;		
    }
}

void ReadContextAndPrintDGBasisUsingObjIncremental(std::istream &input, std::ofstream &output)
{
    FCA::Context cntx;
    ReadContext(cntx, input);

    std::vector<FCA::ImplicationInd> impsBool;
    std::vector<FCA::Implication> imps;

    std::cout << "ObjIncremental" << std::endl;

    impsBool = FCA::ObjIncremental(cntx);	
    imps = FCA::Convert(impsBool, cntx.getAttributes());
    
    PrintImplications(output, imps);
}

void SpeedTestUsingObjIncremental(std::vector<std::string> fileNames, std::ofstream &output)
{
    std::ifstream input;	
    for (size_t fileInd = 0; fileInd < fileNames.size(); ++fileInd)
    {
        input.open(fileNames[fileInd].c_str());
        FCA::Context context;

        ReadContext(context, input);
        input.close();

        std::cout << "ObjIncremental" << " \"" << fileNames[fileInd] << '\"';

        Timer timer;
        timer.StartTiming();
        std::vector<FCA::ImplicationInd> implications = FCA::ObjIncremental(context);	
        timer.StopTiming();
        Time buildingTime = Time(timer.GetUserSeconds());
        size_t directBasisSize = implications.size();

        std::cout << std::endl << "basis complite, minimizing..." << std::endl;
        timer.StartTiming();
        implications = FCA::MinimizeBasis(implications);
        timer.StopTiming();
        Time minimizationTime = Time(timer.GetUserSeconds());

        output << fileInd + 1 << ". " << buildingTime << " - algo" << std::endl
                                      << minimizationTime << " - minimization" << std::endl
                                      << directBasisSize << " - direct basis size" << std::endl
                                      << implications.size() << " - dq basis size" << std::endl;
        std::cout << " complete in " << Time(timer.GetUserSeconds()) << " " << implications.size() << " implications" << std::endl;		
    }
}

FCA::BitSet GetRandomBitSet(const size_t n, const double probability)
{
    FCA::BitSet res(n);
    res.reset();

    for (size_t i = 0; i < n; ++i)
    {
        double val = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
        if (val < probability)
        {
            res.set(i);
        }
    }

    return res;
}

void BuildBasisAndCloseSet(std::vector<std::string> fileNames, std::ofstream &output, const double probability, const size_t rep)
{
    output << probability << std::endl << std::endl;
    std::ifstream input;
    for (size_t fileInd = 0; fileInd < fileNames.size(); ++fileInd)
    {
        input.open(fileNames[fileInd].c_str());
        FCA::Context context;			

        ReadContext(context, input);
        input.close();		

        std::cout << fileNames[fileInd] << " is on the way" << std::endl;

        std::vector<FCA::ImplicationInd> implications = FCA::ComputeDGBasis<FCA::LinClosure>(context);					
        FCA::BitSet s = GetRandomBitSet(context.getAttributesCnt(), probability);
        FCA::BitSet tmp;
        Timer timer;

        timer.StartTiming();
        for (size_t i = 0; i < rep; ++i)
        {
            FCA::Closure::Apply(s, implications, tmp);
        }
        timer.StopTiming();
        Time timeClosure = Time(timer.GetUserSeconds());

        timer.StartTiming();
        for (size_t i = 0; i < rep; ++i)
        {
            FCA::LinClosure::Apply(s, implications, tmp);
        }
        timer.StopTiming();
        Time timeLinClosure = Time(timer.GetUserSeconds());

        timer.StartTiming();
        for (size_t i = 0; i < rep; ++i)
        {
            tmp = FCA::LinClosureImproved::Apply(s, implications, tmp);
        }
        timer.StopTiming();
        Time timeLinClosureImproved = Time(timer.GetUserSeconds());

        output << fileInd << std::endl
               << "Closure " << timeClosure << std::endl	
               << "LinClosure " << timeLinClosure << std::endl
               << "LinClosureImproved " << timeLinClosureImproved << std::endl
               << "implications number is " << implications.size() << std::endl << std::endl;
    }
}

void BuildBasisAndCloseSetOpt(std::vector<std::string> fileNames, std::ofstream &output, const double probability, const size_t rep)
{
    std::cout <<  "Precounting..." << std::endl << std::endl;

    const size_t testNum = fileNames.size();
    std::vector<std::vector<FCA::ImplicationInd> > basises(testNum);
    std::vector<FCA::BitSet> sets(testNum);
    std::vector<size_t> attrNum(testNum);

    std::ifstream input;
    for (size_t fileInd = 0; fileInd < fileNames.size(); ++fileInd)
    {
        input.open(fileNames[fileInd].c_str());
        FCA::Context context;			

        ReadContext(context, input);
        input.close();		

        basises[fileInd] = FCA::ComputeDGBasis<FCA::LinClosure>(context);
        sets[fileInd] = GetRandomBitSet(context.getAttributesCnt(), probability);
        attrNum[fileInd] = context.getAttributesCnt();
    }

    Timer timer;

    output << "Closure" << std::endl << std::endl;
    for (size_t i = 0; i < testNum; ++i)
    {
        FCA::BitSet tmp(attrNum[i]);
        timer.StartTiming();
        for (size_t j = 0; j < rep; ++j)
        {
            FCA::Closure::Apply(sets[i], basises[i], tmp);
        }
        timer.StopTiming();

        output << i << ". " << Time(timer.GetUserSeconds()) << " " << basises[i].size() << std::endl;
    }
    output << std::endl;

    output << "LinClosure" << std::endl << std::endl;
    for (size_t i = 0; i < testNum; ++i)
   { 
        std::vector<size_t> premiseCount;
        std::vector<std::vector<size_t> > list(attrNum[i]);
        size_t prevImplSetSize = 0;

        FCA::BitSet tmp(attrNum[i]);
        FCA::LinClosure::Apply(sets[i], basises[i], premiseCount, list, prevImplSetSize, tmp);
        timer.StartTiming();
        for (size_t j = 0; j < rep; ++j)
        {
            FCA::LinClosure::Apply(sets[i], basises[i], premiseCount, list, prevImplSetSize, tmp);
        }
        timer.StopTiming();

        output << i << ". " << Time(timer.GetUserSeconds()) << " " << basises[i].size() << std::endl;
    }
    output << std::endl;

    output << "LinClosureImproved" << std::endl << std::endl;
    for (size_t i = 0; i < testNum; ++i)
    {
        std::vector<FCA::BitSet> list(attrNum[i]);
        size_t prevImplSetSize = 0;

        FCA::BitSet tmp(attrNum[i]);
        FCA::LinClosureImproved::Apply(sets[i], basises[i], list, prevImplSetSize, tmp);
        timer.StartTiming();
        for (size_t j = 0; j < rep; ++j)
        {
            FCA::LinClosureImproved::Apply(sets[i], basises[i], list, prevImplSetSize, tmp);
        }
        timer.StopTiming();

        output << i << ". " << Time(timer.GetUserSeconds()) << " " << basises[i].size() << std::endl;
    }
    output << std::endl;
}

void ReadContextAndPrintDGBasisUsingAttrIncremental(std::istream &input, std::ofstream &output)
{
    FCA::Context cntx;
    ReadContext(cntx, input);

    std::vector<FCA::ImplicationInd> impsBool;
    std::vector<FCA::Implication> imps;

    /*std::cout << "Ganter" << " " << cfName << std::endl;*/
    std::cout << "Attribute incremental" << std::endl;

    impsBool = FCA::ComputeDGBasisAttrIncremental(cntx);	
    imps = FCA::Convert(impsBool, cntx.getAttributes());
    
    PrintImplications(output, imps);
}

void SpeedTestUsingAttrIncremental(std::vector<std::string> fileNames, std::ofstream &output)                                   
{
    std::ifstream input;	
    for (size_t fileInd = 0; fileInd < fileNames.size(); ++fileInd)
    {
        input.open(fileNames[fileInd].c_str());
        FCA::Context context;

        ReadContext(context, input);
        input.close();

        std::cout << "Attribute incremental" << " \"" << fileNames[fileInd] << '\"';

        Timer timer;
        timer.StartTiming();
        std::vector<FCA::ImplicationInd> implications = FCA::ComputeDGBasisAttrIncremental(context);		
        timer.StopTiming();

        output << fileInd + 1 << ". " << Time(timer.GetUserSeconds()) << " " << implications.size() << std::endl;
        std::cout << " complete in " << Time(timer.GetUserSeconds()) << " " << implications.size() << " implications" << std::endl;		
    }
}