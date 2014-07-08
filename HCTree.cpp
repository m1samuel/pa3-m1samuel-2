//Malcolm Samuel <m1samuel>

#include <stack>
#include "HCTree.hpp"

/*
  Destructor for Huffman Code tree.
*/
HCTree::~HCTree(){
    deforest(root);
}
/*
  Function to recursively delete each node in huffman code tree.
  @param node to began the deletion on. Start at root to delete whole tree.
  @return none
*/
void HCTree::deforest(HCNode *node){
    if (node) {
        deforest(node->get0child());
        deforest(node->get1child());
        delete node;
    }
}
/*
  This is a function that builds the huffman coding tree to be used.
  @param a vector of the count of occurences of each byte
  @return none.
*/
void HCTree::build(const vector<int> &freqs){
    for (int i = 0; i < freqs.size(); i++) {
        if (freqs[i] != 0) {
            leaves[i] = new HCNode(freqs[i], i,nullptr,nullptr,nullptr);
            trees.push(leaves[i]);
        } else
            leaves[i] = nullptr;
    }
    while (trees.size() > 1) {
        HCNode *node = new HCNode();
        node->set0child(trees.top());
        trees.top()->setparent(node);
        trees.pop();
        node->set1child(trees.top());
        trees.top()->setparent(node);
        trees.pop();
        node->setCount(node->get0child()->getCount() + node->get1child()->getCount());
        trees.push(node);
    }
    if (trees.size() > 0)
        root = trees.top();
}
/*
  Function that will encode each byte from input file using huffman code tree.
  @param byte to be encoded, BitOutputStream to use to write bits at a time to file.
  @return none
*/
void HCTree::encode(byte symbol, BitOutputStream& out) const{
    HCNode *p = leaves[symbol]->getp();
    HCNode *c = leaves[symbol];
    stack<int> bits;
    while (p != nullptr) {
        if (p->get0child() == c)
            bits.push(0);
        else if (p->get1child() == c)
            bits.push(1);
        c = p;
        p = p->getp();
    }
    while (!bits.empty()) {
        out.writeBit(bits.top());
        bits.pop();
    }
}
/*
  Function to decode bytes from input file.
  @param BitInputStream to use to read one bit at a time from file.
  @return decoded byte.
*/
byte HCTree::decode(BitInputStream &in) const{
    HCNode *leaf = root;
    int bit;
    while (leaf->get1child() != nullptr && leaf->get0child() != nullptr) {
        bit = in.readBit();
        if (bit == 0)
            leaf = leaf->get0child();
        else if (bit == 1)
            leaf = leaf->get1child();
    }
    return leaf->getSymbol();
}
