//Malcolm Samuel <m1samuel>

#include "BitOutputStream.hpp"

/*
  Flushes the char buffer if it is full.  Also put the contents of buffer to out before flushing.
*/
void BitOutputStream::flush(){
    out.write(&buf,1);
    //out.flush();
    buf = bufi = 0;
}
/*
  Writes 1 bit at a time to the char buffer.
  @param the bit to be written to the char buffer.
*/
void BitOutputStream::writeBit(int bit){
    if (bufi == 8)
        flush();
    buf = buf|(bit<<(7-bufi));
    bufi++;
}
