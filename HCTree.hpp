//Malcolm Samuel <m1samuel>

#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <queue>
#include <vector>
#include <fstream>
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

class HCNodePtrComp {
public:
    bool operator()(HCNode*& lhs, HCNode*& rhs) const {
        return *lhs < *rhs;
    }
};

/** A Huffman Code Tree class.
 */
class HCTree {
private:
    HCNode* root;
    vector<HCNode*> leaves;
    std::priority_queue<HCNode*,std::vector<HCNode*>,HCNodePtrComp> trees;
    int numWritten;
public:
    explicit HCTree() : root(0), numWritten(0) {
        leaves = vector<HCNode*>(256, (HCNode*) 0);
    }
    ~HCTree();
    void deforest(HCNode* node);
    void build(const vector<int>& freqs);
    void encode(byte symbol, BitOutputStream& out) const;
    byte decode(BitInputStream& in) const;
};

#endif // HCTREE_HPP
