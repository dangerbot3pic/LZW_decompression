#include <iostream>
#include <bitset>

using namespace std;

int main ()
{
    char C = '?';
    cout<<std::bitset<8>(C)<<std::endl;
    cout<<bitset<8>(C & 0b1111)<<std::endl;
}