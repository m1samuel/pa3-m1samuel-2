//Malcolm Samuel <m1samuel>

#include "BitInputStream.hpp"

/*
  Function to use to fill the char buffer.
*/
void BitInputStream::fill() {
  buf = in.get();
  bufi = 8;
}
/*
  Reads 1 bit at a time from the char buffer.
  @return the bit that was read from the char buffer.
*/
int BitInputStream::readBit(){
    if (bufi == 0)
        fill();
    bufi--;
    return ((buf>>bufi)&1);
}
