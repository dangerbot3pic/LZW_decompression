# LZW_decompression

LZW Decompression algorithm written for an internship coding excercise.

Fixed 12 bit codes, with 256 initial dictionary entries and a maximum dictionary size of 4096.

Compile using
  g++ decode.cpp lzw.cpp -o decode

Provide an input file for decompressing in terminal when running the executable, or the progam will ask for one.
