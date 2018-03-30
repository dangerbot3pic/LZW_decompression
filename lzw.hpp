#ifndef LSW_HPP
#define LSW_HPP

#include <string>
#include <unordered_map>
#include <fstream>
#include <bitset>

const unsigned int lzw_size = 12;
const unsigned int init_dictionary_size = 256;

class LZW
{
    public: 
    ~LZW() {}
    LZW ();

    void decompress(std::ifstream &infile, std::ostream &out);

    private: 
    int P; // Store string
    int  C; // Store current value
    std::unordered_map<int, std::string> Dictionary; // Store dictionary in hashmap
    int curr_offset;

    int get_lzw(std::ifstream &infile) const;
    bool inDictionary(int word);
    void addToDictionary();
};

#endif