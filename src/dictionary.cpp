#include <iostream>
#include <fstream>
#include <string>
#include "dictionary.h"


Dictionary::Dictionary(string filename)
{
    std::ifstream inp;
    inp.open(filename);
    if (!inp.good())
        throw std::invalid_argument("This file can't be open!");
    string word = "";
    while (inp.good())
    {
        inp >> word;
        this->insert(word);
    }
    inp.close();
}
