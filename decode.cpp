#include <iostream>
#include <fstream>

#include "lzw.hpp"


int main (int argc, char **argv)
{
    std::string pathname;
    if (argc == 1) // Obtain path to file and filename if not provided
    {
        std::cout<<"Enter pathname to file: ";
        std::cin>>pathname;
    }
    else pathname = argv[1];

    std::ifstream infile;

    infile.open(pathname.c_str(), std::ios::in | std::ios::binary);

    LZW playtime; // Initialise the decompression object

    if (infile.is_open()) // If file is open, decompress
    {
        playtime.decompress(infile, std::cout);
    }
    else 
    {
        std::cout<<"File didn't open"<<std::endl;
    }

    infile.close();
}