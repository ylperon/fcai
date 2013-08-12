# pragma once

# ifndef FCA_MAX_CLOSED_SUBSETS_H_
# define FCA_MAX_CLOSED_SUBSETS_H_

# include "fca_definitions.h"
# include "fca_datastructures.h"
# include "fca_closure_operators.h"


namespace FCA 
{
    class MaxClosedSubsetsIterator 
    {
    private:  
        const std::vector<ImplicationInd> &implications;
        const size_t bad_attribute;
        struct SearchNode;
        std::vector < SearchNode > tree_branch;

        struct SearchNode {
            MaxClosedSubsetsIterator* base;
            BitSet closed_set;
            size_t next_attribute_to_try;
            bool all_sons_bad;

            SearchNode(MaxClosedSubsetsIterator* base, const BitSet& bs, size_t next_attribute_to_try = 0) :
                base(base),
                closed_set(bs.size()),
                next_attribute_to_try(next_attribute_to_try) 
            {
                Closure::Apply(bs, base->implications, closed_set);
                all_sons_bad = true;
            }
            bool IsBad() {
                return closed_set.test(base->bad_attribute);
            }
            bool CanMakeNewSon() 
            {
                return next_attribute_to_try < closed_set.size();
            }
            bool CanSkipSon () 
            {
                return closed_set.test(next_attribute_to_try);
            }
            bool AreBadAllBefore(size_t end_attr) 
            {
                BitSet test(closed_set.size());
                size_t curr_attr = 0;
                for (size_t curr_attr = 0; curr_attr < end_attr; ++curr_attr) 
                {
                    if (closed_set.test(curr_attr)) continue;
                    closed_set.set(curr_attr);
                    Closure::Apply(closed_set, base->implications, test);
                    if (!test.test(base->bad_attribute)) return false;
                    closed_set.reset(curr_attr);
                }
                return true;
            }
        };
        
        bool TrySon() 
        {
            SearchNode& tree_list = tree_branch.back();

            while (tree_list.CanMakeNewSon() && tree_list.CanSkipSon()) 
            {
                ++tree_list.next_attribute_to_try;
            }
            if (!tree_list.CanMakeNewSon()) {
                return false;
            }

            tree_list.closed_set.set(tree_list.next_attribute_to_try++);
            tree_branch.push_back(SearchNode(this, tree_list.closed_set, tree_list.next_attribute_to_try));
            tree_list.closed_set.reset(tree_list.next_attribute_to_try - 1);

            if (tree_branch.back().IsBad()) {
                tree_branch.pop_back();
            } else {
                tree_list.all_sons_bad = false;
            }
            return true;
        }
        void SearchNextMax() {
            while (!tree_branch.empty()) 
            {
                while (TrySon());
                if (tree_branch.back().all_sons_bad) 
                {
                    if (tree_branch.size() == 1 || 
                        tree_branch.back().AreBadAllBefore((tree_branch.end() - 1)->next_attribute_to_try)) 
                        break;
                }
                tree_branch.pop_back();
            }
        }
    public: 
        MaxClosedSubsetsIterator(const std::vector<ImplicationInd> &implications, const size_t bad_attribute, const size_t max_elems) :
            implications(implications),
            bad_attribute(bad_attribute)
        {
            tree_branch.reserve(max_elems);
            tree_branch.push_back(SearchNode(this, BitSet(max_elems)));
            SearchNextMax();
        }
        MaxClosedSubsetsIterator &operator ++() 
        {
            tree_branch.pop_back();
            SearchNextMax();
            return *this;
        }
        const BitSet &operator * () {
            return tree_branch.back().closed_set;
        }
        bool IsEnd() 
        {
            return tree_branch.empty();
        }
    };
}

#endif // FCA_MAX_CLOSED_SUBSETS_H_
