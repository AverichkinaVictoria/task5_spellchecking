////////////////////////////////////////////////////////////////////////////////
// Averichkina Victoria
// 184-1
// Date:         6.12.2019
////////////////////////////////////////////////////////////////////////////////





#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <set>
#include <iomanip> // setw


#include "dictionary.h"

using namespace std;

void lower(string& s);
string stripPunct(const string& s);
void checkSpelling(ifstream& in, Dictionary& dict);
void transposing(string& word, Dictionary& dict, set <string>& noDuplicateWords);
void removing(string& word, Dictionary& dict, set <string>& noDuplicateWords);
void replacing(string& word, Dictionary& dict, set <string>& noDuplicateWords);
void inserting(string& word, Dictionary& dict, set <string>& noDuplicateWords);

// program arguments to run, example: main.exe ../../res/wordlist.txt ../../res/test.txt
int main(int argc, char* argv[]) {

	// Output usage message if improper command line args were given.
	if (argc != 3)
    {
		cerr << "Usage: " << argv[0] << " wordlist_filename input_file\n";
		return EXIT_FAILURE;
	}

	ifstream inf(argv[2]);
	if (! inf) 
    {
		cerr << "Could not open " << argv[2] << "\n";
		return EXIT_FAILURE;
	}
	
	// Read dictionary, but let user know what we are working on.
	cout << "Loading dictionary, this may take awhile...\n";

	Dictionary d(argv[1]);
    
	checkSpelling(inf, d);

	inf.close();

	return EXIT_SUCCESS;
}

void checkSpelling(ifstream& in, Dictionary& dict)
{
    int line_number = 0;

    while (in)
    {
        line_number++;
        set<string> totest;
        string line;
        getline(in, line);

        stringstream ss (stringstream::in | stringstream::out);
        ss << line;

        string word;
        while (ss >> word)
        {
            word = stripPunct(word);
            lower(word);
            if (!dict.search(word))
            {
                transposing(word, dict, totest);
                removing(word,dict,totest);
                replacing(word,dict,totest);
                inserting(word,dict,totest);

                cout << "\n";
                cout  << word << " (" << line_number << " line:" ;
               // cout << "Correct variants: \n";
                for (string vrnts : totest)
                    cout << " " << vrnts ;
                cout << ")\n";
                totest.clear();
            }
        }
    }
}

void lower(string& s) {

    // Ensures that a word is lowercase
	for (int i = 0; i < s.length(); i++)
    {
		s[i] = tolower(s[i]);
	}
}

string stripPunct(const string& s) {

	// Remove any single trailing
	// punctuation character from a word.  
	if (ispunct(s[s.length() - 1]) ) 
    {
		return s.substr (0, s.length() - 1);
	}
	else 
    {
		return s;
	}
}

void transposing(string& word, Dictionary& dict, set <string>& noDuplicateWords)
{
    for (int i = 0; i < word.length()-1; ++i)
    {
        string extra = word;
        swap(extra[i], extra[i+1]);
        if (dict.search(extra))
            noDuplicateWords.insert(extra);
    }
}
void removing(string& word, Dictionary& dict, set <string>& noDuplicateWords)
{
    for (int i = 0; i < word.length(); ++i)
    {
        string extra = word;
        extra.erase(i,1);
        if (dict.search(extra))
            noDuplicateWords.insert(extra);
    }
}
void replacing(string& word, Dictionary& dict, set <string>& noDuplicateWords)
{
    for (int i = 0; i < word.length(); ++i)
    {
        for (char ch = 'a'; ch <= 'z' ; ++ch)
        {
            string extra = word;
            extra[i] = ch;
            if (dict.search(extra))
                noDuplicateWords.insert(extra);
        }
    }
}

void inserting(string& word, Dictionary& dict, set <string>& noDuplicateWords)
{
    string extra = word;
    string::const_iterator i = extra.begin();
    while (i < extra.end())
    {
        for (char ch = 'a'; ch <= 'z'; ++ch)
        {
            i = extra.insert(i, ch);
            if (dict.search(extra))
                noDuplicateWords.insert(extra);
            i = extra.erase(i);
        }
        i += 1;
    }
}
