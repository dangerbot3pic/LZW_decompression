#include <iostream>
#include <fstream>
#include <bitset>

using Byte = std::bitset<8>;
using Nibble = std::bitset<4>;
using Word = std::bitset<12>;

using namespace std;

int main(int argc, char **argv)
{
    ifstream infile;
    infile.open(argv[1]);
    char tmp_char = '0';

    do
    {
        char in[1];
            char in_char[1];
            infile.read(in_char, sizeof(in_char));
            Byte in_byte(in_char[0]);
            cout<<in_byte<<std::endl;
    }
    while (!infile.eof());
}