#include <iostream>
#include <fstream>

#include "lzw.hpp"


int main (int argc, char **argv)
{
    std::string pathname;
    if (argc == 0) // Obtain path to file and filename
    {
        std::cout<<"Enter pathname to file: ";
        std::cin>>pathname;
    }
    else pathname = argv[1];

    std::ifstream infile;
    try
    {
        infile.open(pathname.c_str(), std::ios::in | std::ios::binary);
    }
    catch (std::ifstream::failure &e)
    {
        std::cerr<<"ERROR: Invalid file/path to file. Please check.";
        exit(1);
    }

    LZW playtime(); // Initialise the decompression object

    if (infile.is_open())
    {
        playtime.decompress(infile, std::cout);
    }
}