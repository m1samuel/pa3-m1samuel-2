//Malcolm Samuel <m1samuel>

#include "HCNode.hpp"


HCNode::HCNode(int c, byte s, HCNode* c_0, HCNode* c_1, HCNode* _p)
{
    count = c;
    symbol = s;
    c0 = c_0;
    c1 = c_1;
    p = _p;
}

int HCNode::getCount() const{
    return count;
}

byte HCNode::getSymbol() const{
    return symbol;
}

void HCNode::setCount(int c) {
    count = c;
}

void HCNode::setSymbol(byte s){
    symbol = s;
}

void HCNode::set0child(HCNode *c_0){
    c0 = c_0;
}

void HCNode::set1child(HCNode *c_1){
    c1 = c_1;
}

void HCNode::setparent(HCNode *_p){
    p = _p;
}
HCNode *HCNode::get0child(){
    return c0;
}
HCNode *HCNode::get1child(){
    return c1;
}
HCNode *HCNode::getp(){
    return p;
}
bool HCNode::operator<(const HCNode& other){
    return count > other.count;
}