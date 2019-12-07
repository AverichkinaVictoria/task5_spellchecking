#ifndef  _DICTIONARY_H_ 
#define  _DICTIONARY_H_

#include  <iostream>
#include  <vector>
#include  <list>
#include  <algorithm>
#include  <string>
#include  <stdlib.h>

#include  "hashset.h"
#include  "hashset.cpp"

using namespace std;

class hash_function
{
public:

    //Can't remember algorith from lectures, so i find this (hope even better)
    //Rot13 (https://sohabr.net/habr/post/219139/) and wikipedia
    unsigned int operator()( const string& s )  const
    {
        unsigned int hash = 0;
        for (int i = 0; i < s.length(); ++i)
        {
            hash += s[i];
            hash -= (hash << 13) | (hash >> 19);
        }
        return hash;
    }
};

class equality
{
public:
    equality() {}
    bool  operator()( const string& A, const string& B )  const 
    {
        return  (A == B);
    }
};

class Dictionary: public HashSet<string, hash_function, equality> {

public:
	Dictionary(string filename);

};
#endif // _DICTIONARY_H_
