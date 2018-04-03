#include "lzw.hpp"

LZW::LZW()
{
    prev = "";
    curr = "";
    C = 0;
    next_nibble = NULL;
}


void LZW::decompress(std::ifstream &infile, std::ostream &out)
{
    C = get_lzw(infile); // Obtain and process first character
    C_prev = C;
    out<<static_cast<char>(C);

    do
    {
        C = get_lzw(infile);
        if (!inDictionary(C)) // If code doesn't exist in dictionary
        {
            std::cerr<<"Not present"<<std::endl;
            addToDictionary(translate(C_prev) + translate(C_prev).at(0));
            out<<translate(C_prev) + translate(C_prev).at(0);
        }
        else // Code present in dictionary
        {
            std::cerr<<"Present"<<std::endl;
            addToDictionary(translate(C_prev) + translate(C).at(0));
            out<<translate(C);
        }
        std::cerr<<C<<" "<<C_prev<<std::endl;
        std::cerr<<translate(C_prev)<<" "<<translate(C)<<std::endl;
        std::cerr<<translate(Dictionary.size()+init_dictionary_size-1)<<" "<<Dictionary.size()+255<<std::endl<<std::endl;
        C_prev = C;
    }
    while (!infile.eof());
    out<<std::endl;
    //printDic();
}

std::string LZW::translate(int loc) const 
{
    std::string output;
    if (loc < init_dictionary_size) output = static_cast<char>(loc);
    else output = Dictionary.find(loc-init_dictionary_size)->second;
    return output;
}

void LZW::printDic()
{
    for (int it = 0; it < Dictionary.size(); it++)
    {
        std::cerr<<translate(it+init_dictionary_size)<<std::endl;
    }
}


int LZW::get_lzw(std::ifstream &infile)
{
    char char_in[1];
    infile.read(char_in, sizeof(char_in));
    Byte in_byte(char_in[0]);
    Char in_word;

    if (next_nibble == NULL)
    {
        char char_next[1];
        infile.read(char_next, sizeof(char_next));

        Nibble in_nibble(char_next[0] >> 4);
        next_nibble = new Nibble(char_next[0] & 0b1111);

        for (int i = 11; i > 3; i--) in_word[i] = in_byte[i-4];
        for (int i = 3; i >= 0; i--) in_word[i] = in_nibble[i];
        return (int)in_word.to_ulong();
    }
    for (int i = 11; i >= 8; i--) in_word[i] = (*next_nibble)[i-8];
    for (int i = 7; i >= 0; i--) in_word[i] = in_byte[i];
    delete next_nibble;
    next_nibble = NULL;
    return (int)in_word.to_ulong();
}


bool LZW::inDictionary(int word) // Check if the number is in the dictionary
{
    if (C < init_dictionary_size) return true;
    if (Dictionary.find(word) != Dictionary.end()) return true;
    return false;
}


void LZW::addToDictionary(const std::string new_word) // Add a new word to dictionary
{
    Dictionary.insert(std::pair<int, std::string>(Dictionary.size(), new_word));
}