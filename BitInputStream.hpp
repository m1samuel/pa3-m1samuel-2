//Malcolm Samuel <m1samuel>

#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <fstream>
#include <bitset>
#include <iostream>

/** A class for reading bits (and ints) from an ifstream
 */
class BitInputStream {
private:
  std::ifstream& in;
  char buf;
  int bufi;
public:
  BitInputStream(std::ifstream& s) : in(s), buf(0), bufi(0) { }
  void fill();
  int readBit();
};

#endif // BITINPUTSTREAM_HPP
