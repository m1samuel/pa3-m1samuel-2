// Malcolm Samuel <m1samuel>
// This file is used to read compressed data from a file and uncompress it using 
// a huffman coding tree which is build using data from the top of the input file
// which should be 255 consecutive integers which are bytecounts.

#include <iostream>
#include <fstream>
#include "HCTree.hpp"

int main(int argc, const char * argv[])
{
  if (argc < 3) {
    std::cerr << "./uncompress called with incorrect arguments.\n"
	      << "Usage: ./uncompress infile outfile\n";
    exit(-1);
  }
  std::string infile = argv[1];
  std::string outfile = argv[2];
  std::ifstream in(infile, std::ifstream::binary);
  std::vector<int> freqsv(256); //vector to keep track of byte count
  int freqs[256] = {0};
  if (!in.is_open()) {
    std::cerr << "Input file failed to open.\n";
    exit(-1);
  }
  int bytecount = 0;
  int usym = 0;
  std::cout << "Reading header from file \"" << infile << "\"... ";
  in.seekg(0,std::ifstream::beg);
  in.read((char*)&freqs,256*sizeof(int));
  for(int i = 0; i < freqsv.size(); i++ )
    {
      freqsv[i] = freqs[i];
      if (!in.good()) {
	std::cerr << "Error reading file header\n";
	exit(-1);
      }
      if (freqsv[i] != 0)
	usym++;
      bytecount += freqsv[i];
    }
  std::cout << "done\n";
  std::cout << "Uncompressed file will have " << usym << " unique symbols and size " << bytecount << " bytes.\n";
  HCTree *trie = new HCTree();
  std::cout << "Building Huffman code tree... ";
  trie->build(freqsv);
  std::cout << " done.\n";
  std::ofstream out(outfile, std::ofstream::binary);
  std::cout << "Writing to file \"" << outfile << "\"... ";
  if (!out.is_open()) {
    std::cerr << "Output file failed to open.\n";
    exit(-1);
  }
  BitInputStream bin(in);
  if (bytecount > 0){
    for (int i = 0; i < bytecount; i++)
      out << trie->decode(bin);
  }
  std::cout << "done.\n";
  in.close();
  out.close();
  in.open(infile);
  int compbytecount = 0;
  while (in.is_open()) {
    in.get();
    if (!in.good()) break;
    compbytecount++;
  }
  in.close();
  std::cout << "Uncompression ratio: " << (double)bytecount/compbytecount << "\n";
  delete trie;
  return 0;
}
