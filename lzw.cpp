#include "lzw.hpp"

LZW::LZW()
{
    // Need to initialise first 256  ASCII values
    for (int i = 0 ; i < init_dictionary_size; i++)
    {
        Dictionary.emplace(i, std::to_string((char)i));
    }
    curr_offset = 256; // To track how 'full' the dictionary is
}


void LZW::decompress(std::ifstream &infile, std::ostream &out)
{
    C = get_lzw(infile);
    if (inDictionary(C)) // Word exists in dictionary
    {
        out<<Dictionary.find(C)->second;
    }
    else 
    {

    }
    addToDictionary();
}


int LZW::get_lzw(std::ifstream &infile) const
{
    char in = '0';
    int result = 0;
    for (int i = 0; i < lzw_size; i++)
    {
        infile>>in;
        result = (result<<2) + in;
    }
    return result;
}


bool LZW::inDictionary(int word) 
{
    if (Dictionary.find(word) != Dictionary.end()) return true;
    return false;
}


void LZW::addToDictionary()
{
    std::string tmp = Dictionary.find(P)->second + Dictionary.find(C)->second;
    Dictionary.emplace(curr_offset, tmp);
    curr_offset++;
}