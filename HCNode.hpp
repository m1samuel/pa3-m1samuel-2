//Malcolm Samuel <m1samuel>

#ifndef HCNODE_HPP
#define HCNODE_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** A class, instances of which are nodes in an HCTree.
 */
class HCNode {
public:
    HCNode() : count(0), c0(nullptr), c1(nullptr), p(nullptr){};
    HCNode(int c, byte s, HCNode* c_0, HCNode* c_1, HCNode* _p);

  /** Less-than comparison, so HCNodes will work in std::priority_queue
   *  We want small counts to have high priority.
   *  And we want to break ties deterministically.
   */
    bool operator<(const HCNode& other);
    int getCount() const;
    byte getSymbol() const;
    void setCount(int c);
    void setSymbol(byte s);
    HCNode *get0child();
    HCNode *get1child();
    HCNode *getp();
    void set0child(HCNode *c_0);
    void set1child(HCNode *c_1);
    void setparent(HCNode *_p);
private:
    HCNode *c0, *c1, *p; // pointer to '0' child, pointer to '1' child, pointer to parent
    byte symbol; // byte in the file we're keeping track of
    int count; //number of occurences of symbol
};

/** For printing an HCNode to an ostream
 *  Possibly useful for debugging.
 */
ostream& operator<<(ostream&, const HCNode&) __attribute__((weak)); // shut the linker up
ostream& operator<<(ostream& stm, const HCNode& n) {
    stm << "[" << n.getCount() << "," << (int) (n.getSymbol()) << "]";
    return stm;
}


#endif // HCNODE_HPP
