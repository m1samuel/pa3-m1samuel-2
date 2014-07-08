// Malcolm Samuel <m1samuel>
// This file is used to read the contents of a file and use a huffman coding tree to
// write compressed output to an outfile.

#include <vector>
#include <iostream>
#include <fstream>
#include "HCTree.hpp"

int main(int argc, const char * argv[])
{
    if (argc < 3) {
        std::cerr << "./compress called with incorrect arguments.\n"
                  << "Usage: ./compress infile outfile\n";
        exit(-1);
    }
    std::string infile = argv[1];
    std::string outfile = argv[2];
    std::ifstream in(infile, std::ifstream::binary);
    if (!in.is_open()) {
        std::cerr << "Input file failed to open.\n";
        exit(-1);
    }
    std::vector<int> freqsv(256); //vector to keep track of byte count
    int freqs[256] = {0}; //array to use to write frequencies to file in binary
    int c;
    int bytecount = 0;
    int usym = 0;
    std::cout << "Reading from file \"" << infile << "\"... ";
    while (1) {
        c = in.get();
        if (!in.good()) break;
        bytecount++;
        freqs[c]++;
	freqsv[c]++;
    }
    in.close();
    for (int i = 0; i < freqsv.size(); i++)
      if (freqsv[i] != 0)
            usym++;
    std::cout << "done.\n";
    std::cout << "Found " << usym << " unique symbols in input file of size " << bytecount << " bytes.\n";
    HCTree *trie = new HCTree();
    std::cout << "Building Huffman code tree... ";
    trie->build(freqsv);
    std::cout << "done.\n";
    std::cout << "Writing to file \"" << outfile << "\"... ";
    std::ofstream out(outfile, std::ofstream::binary);
    if (!out.is_open()) {
        std::cerr << "Output file failed to open.\n";
        exit(-1);
    }
    out.flush();
    out.write((char*)&freqs,sizeof(int)*256);
    BitOutputStream bout(out);
    in.open(infile, std::ifstream::binary);
    if (!in.is_open()) {
        std::cerr << "Input file failed to open.\n";
        exit(-1);
    }
    if (bytecount > 0) {
      for (int i = 0; i < bytecount; i++){
	c = in.get();
	trie->encode(c, bout);
      }
    }
    std::cout << "done.\n";
    bout.flush();
    in.close();
    out.close();
    in.open(outfile);
    in.seekg(0, std::ifstream::end);
    int compbytecount = in.tellg();
    in.close();
    std::cout << "Output file has size " << compbytecount << " bytes.\n";
    std::cout << "Compression ratio: " << (double)compbytecount/bytecount << "\n";
    delete trie;
    return 0;
}
