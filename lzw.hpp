#ifndef LSW_HPP
#define LSW_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <bitset>

const unsigned int byte_size = 8;
const unsigned int lzw_size = 12;
const unsigned int init_dictionary_size = 255;

using Byte = std::bitset<byte_size>; // 8 bits
using Nibble = std::bitset<byte_size/2>; // 4 bits
using Char = std::bitset<lzw_size>; // 12 bits

class LZW
{
    public: 
    ~LZW() {}
    LZW ();

    void decompress(std::ifstream &infile, std::ostream &out);

    private: 
    int C; // Store current code value
    int C_prev; // Store previous code value
    std::unordered_map<int, std::string> Dictionary; // Store dictionary in hashmap
    Nibble *next_nibble;

    int get_lzw(std::ifstream &infile);
    bool inDictionary(int word);
    void addToDictionary(const std::string new_word);
    std::string translate(int loc) const;
    bool atLimit() const;
    void Reset();
};

#endif