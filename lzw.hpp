#ifndef LSW_HPP
#define LSW_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <bitset>

const unsigned int byte_size = 8;
const unsigned int lzw_size = 12;
const unsigned int init_dictionary_size = 256;

using Byte = std::bitset<byte_size>;
using Nibble = std::bitset<byte_size/2>;
using Char = std::bitset<lzw_size>;

class LZW
{
    public: 
    ~LZW() {}
    LZW ();

    void decompress(std::ifstream &infile, std::ostream &out);

    private: 
    int C; // Store current value
    int C_prev;
    std::string prev;
    std::string curr;
    std::unordered_map<int, std::string> Dictionary; // Store dictionary in hashmap
    Nibble *next_nibble;

    int get_lzw(std::ifstream &infile);
    bool inDictionary(int word);
    void addToDictionary(const std::string new_word);
    std::string translate(int loc) const;
    void printDic();
};

#endif