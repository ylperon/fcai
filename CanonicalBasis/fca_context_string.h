# ifndef FCA_CONTEXT_STRING_H_
# define FCA_CONTEXT_STRING_H_

# include <vector>
# include <string>
# include <cstdio>

# include "fca_context.h"

namespace FCA
{
    class ContextString : public FCA::Context
    {
    public:
        ContextString();
        ContextString(const FCA::Context& cxt);
        ContextString(const ContextString& cxt);
        ContextString(const size_t& objSize, const size_t& attrSize);
        ContextString(const size_t& objSize, const size_t& attrSize, 
                      const std::vector<std::string>& objName, const std::vector<std::string>& attrName); 
        explicit ContextString(const std::vector<std::vector<bool> >& table);        
        ContextString(const std::vector<std::vector<bool> >& table,
                      const std::vector<std::string>& objName, const std::vector<std::string>& attrName);        
        explicit ContextString(const std::vector<FCA::BitSet>& table);
        ContextString(const std::vector<FCA::BitSet>& table,
                      const std::vector<std::string>& objName, const std::vector<std::string>& attrName);       

        ContextString& operator =(const ContextString& cxt);

        void SetObjName(const size_t& objInd, const std::string& name);
        const std::string& GetObjName(const size_t& objInd) const;

        void SetAttrName(const size_t& attrInd, const std::string& name);
        const std::string& GetAttrName(const size_t& attrInd) const;

        virtual ~ContextString() throw();

    protected:
        std::vector<std::string> mObjName;
        std::vector<std::string> mAttrName;
    };

    void Read(FILE* input, ContextString& cxt);
    void Write(FILE* output, const ContextString& cxt);
};

# endif //FCA_CONTEXT_STRING_H_