#include "lzw.hpp"

LZW::LZW()
{
    C = 0;
    next_nibble = NULL;
}

// Decompress the input file and print output to output stream
void LZW::decompress(std::ifstream &infile, std::ostream &out)
{
    C = get_lzw(infile); // Ger code for first character
    C_prev = C;
    out<<translate(C); // Print first character
    C = get_lzw(infile);
    std::string tmp;

    while (!infile.eof()) // Consume character till file end of file
    {
        if (inDictionary(C)) tmp = translate(C_prev) + translate(C).at(0); // If code is in dictionary
        else tmp = translate(C_prev) + translate(C_prev).at(0); // If new code

        addToDictionary(tmp);
        out<<translate(C);
        C_prev = C;

        C = get_lzw(infile); // Get next code
    }
    out<<std::endl;
}

// Translate code to character(s)
std::string LZW::translate(int loc) const 
{
    std::string output;
    if (loc <= init_dictionary_size) output = static_cast<char>(loc);
    else output = Dictionary.find(loc-init_dictionary_size)->second;
    return output;
}

// Check if dictionary is at size limit (4096)
bool LZW::atLimit() const
{
    if (Dictionary.size() == 3840) return true;
    return false;
}

// Clear the dictionary
void LZW::Reset()
{
    Dictionary.clear();
}

// Obtain the next code
int LZW::get_lzw(std::ifstream &infile)
{
    char char_in[1];
    infile.read(char_in, sizeof(char_in));
    Byte in_byte(char_in[0]);
    Char in_word;

    // If first four bits haven't already been extracted then extract sixteen bits
    // using only the first twelve and store remaining four
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

    // Otherwise use stored four bits as first four bits of next code
    // and extract only eight bits from file
    for (int i = 11; i >= 8; i--) in_word[i] = (*next_nibble)[i-8];
    for (int i = 7; i >= 0; i--) in_word[i] = in_byte[i];
    delete next_nibble;
    next_nibble = NULL;
    return (int)in_word.to_ulong();
}

// Check if code is in dictionary
bool LZW::inDictionary(int word) // Check if the number is in the dictionary
{
    if (C <= init_dictionary_size) return true;
    if (word < init_dictionary_size+Dictionary.size()+1) return true;
    return false;
}

// Add a word to the dictionary
void LZW::addToDictionary(const std::string new_word) // Add a new word to dictionary
{
    if (atLimit()) Dictionary.clear(); // Ensure dictionary won't become oversized
    int tmp = Dictionary.size()+1;
    Dictionary.insert(std::pair<int, std::string>(tmp, new_word));
}