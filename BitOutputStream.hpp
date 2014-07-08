//Malcolm Samuel <m1samuel>

#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>
#include <bitset>
#include <fstream>

/** A class for writing bits (and chars and ints) to an ostream
 */
class BitOutputStream {

private:
  std::ofstream& out; 
  char buf;
  int bufi;

public:
  BitOutputStream(std::ofstream& s) : out(s), buf(0), bufi(0) { }
  void writeBit(int bit);
  void flush();
};

#endif // BITOUTPUTSTREAM_HPP
