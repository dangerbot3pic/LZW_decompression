#include "lzw.hpp"

LZW::LZW()
{
    // Need to initialise first 128  ASCII values
    for (unsigned int i = 0 ; i < init_dictionary_size; i++)
    {
        Dictionary.insert(std::pair<int, std::string>(i, std::string(1, static_cast<char>(i))));
    }
    curr_offset = 256; // To track how 'full' the dictionary is
    prev = "";
    curr = "";
    C = 0;
}


void LZW::decompress(std::ifstream &infile, std::ostream &out)
{
    C = get_lzw(infile); // Obtain and process first character
    prev = Dictionary.find(C)->second;
    out<<prev;

    while (!infile.eof())
    {
        C = get_lzw(infile);
        if (inDictionary(C)) // If word exists in dictionary
        {
            curr = Dictionary.find(C)->second;
            out<<curr;
            prev = prev + curr[0];
            addToDictionary(prev);
        }
        /*else // Word not present in dictionary
        {
            std::cerr<<"Prev before: "<<prev<<std::endl;
            prev = prev + prev[0];
            std::cerr<<"Prev after: "<<prev<<std::endl;
            addToDictionary(prev);
            prev = Dictionary.find(C)->second;
            out<<prev;
        }*/
        out<<std::endl;
    }
}


int LZW::get_lzw(std::ifstream &infile) const
{
    char in = '0';
    int result = 0;
    for (int i = 0; i < 12; i++)
    {
        infile>>in;
        if (in == '1') result = (result<<1) + 1;
        else result = result<<1;
    }
    return result;
}


bool LZW::inDictionary(int word) 
{
    if (Dictionary.find(word) != Dictionary.end()) return true;
    return false;
}


void LZW::addToDictionary(const std::string new_word)
{
    Dictionary.insert(std::pair<int, std::string>(curr_offset, new_word));
    curr_offset++;
}