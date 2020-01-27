/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <iostream>
#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */

    ifstream wordsFile(filename) ;
    string word ;

    if (wordsFile.is_open() )
    {
      while ( getline(wordsFile, word) )
      {
        string curr = word ;
        string word1 = curr ;
        std::sort(word1.begin(), word1.end() ) ;

        auto anag = dict.find( word1 ) ;

        if ( anag != dict.end() )
          anag->second.push_back( curr ) ;

        else
        {
          vector<string> ana_list ;
          ana_list.push_back(curr) ;

          dict.insert( std::pair<string, vector<string> > (word1, ana_list ) ) ;
        }


      }
    }


}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */

    for ( unsigned long i = 0 ; i < words.size() ; i ++ )
    {
      string curr = words.at(i) ;
      string word1 = curr ;
      std::sort(word1.begin(), word1.end() ) ;

      auto anag = dict.find( word1 ) ;

      if ( anag != dict.end() )
        anag->second.push_back( curr ) ;

      else
      {
        vector<string> ana_list ;
        ana_list.push_back(curr) ;

        dict.insert( std::pair<string, vector<string> > (word1, ana_list ) ) ;
      }

    }

}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */

    string word1 = word ;
    std::sort(word1.begin(), word1.end() ) ;

    return dict.find(word1)->second ;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */

    vector< vector<string> > all_anag ;

    for ( auto anag = dict.begin() ; anag != dict.end() ; anag++ )
    {
      if ( anag->second.size() >= 2 )
        all_anag.push_back(anag->second) ;
    }

    return all_anag ;
}
