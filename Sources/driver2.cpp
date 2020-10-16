//////////////////////////////////////////////////////////////////////////////
// INCLUDE FILES & NAMESPACES
//////////////////////////////////////////////////////////////////////////////
//I_O
#include <iostream>

//TYPES
#include <memory> //smart pointers

//CONTAINERS
#include <vector>

//UTILITY
#include <filesystem> //path
#include <ctype.h>

//CUSTOM
#include "../Headers/Dictionary/Dictionary.hpp"

using namespace std;
using namespace Dict;
using filesystem::path;
using WordLst = vector<DNshPtr>;
using WordTable = map<int, pair<DNshPtr, WordLst>>;
using Phrase = vector<DNshPtr>;
using PhraseLst = vector<Phrase>;

//////////////////////////////////////////////////////////////////////////////
// FUNCTION DECLARATIONS
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
//gets a valid file path
path getDictPath();

//----------------------------------------------------------------------------
//changes wordTable to reflect all possible words in the phrase
//pre-condition: wordTable contains a single, empty wordLst
//                 and the tracking nodePtr for that list ponints
//                 to the root of the Dictionary
void parsePhrase(
  string const &phrase,
  WordTable &wordTable
);

//----------------------------------------------------------------------------
void prntWordTable(WordTable const &wordTable);

//----------------------------------------------------------------------------
//gets a list of possible phrases from the wordTable
PhraseLst getPhrases(
  WordTable const &wordTable,
  int idx,
  int const phraseLen = -1
);

//----------------------------------------------------------------------------
//MODIFIES maxPhrase and maxFreq to represet the phrase
//  with the highest possible cummulative frequency in the phraseLst
void findBestPhrase(
  PhraseLst const &phraseLst,
  string &maxPhrase,
  double &maxFreq
);

//////////////////////////////////////////////////////////////////////////////
// MAIN FUNCTION
//////////////////////////////////////////////////////////////////////////////
int main(){
  path dictFilePath(getDictPath());

  Dictionary dict(dictFilePath);

  char response;
  cout << "Dictionary size= " << dict.getSize() << endl;
  cout << "Are you sure you want to print the dictionary (y/n)? ";
  cin  >> response;
  response = tolower(response);
  if(response == 'y'){
    cout << "Dictionary: " << endl
         << dict << endl
         << endl;
  }

  string phrase;
  cout << "phrase: ";
  cin  >> phrase;

//initialize wordTable to a single, empty wordLst
//  the tracking nodePtr for that list points to the
//  root of the dictionary to prepare for parsing
  WordTable wordTable{{
    0,
    {
      DNshPtr(DNshPtr{}, &dict),
      WordLst()
    }
  }};

  parsePhrase(phrase, wordTable);
  erase_if(wordTable, [](auto const &elem) {
    WordLst const &wordLst = elem.second.second;
    return wordLst.empty();
  });

  prntWordTable(wordTable);

  PhraseLst phraseLst(getPhrases(wordTable, 0));
  string maxPhrase;
  double maxFreq;
  findBestPhrase(phraseLst, maxPhrase, maxFreq);

  cout << "max phrase: " << maxPhrase << endl
       << "max frequency= " << maxFreq << endl;

  return 0;
}//end main
//////////////////////////////////////////////////////////////////////////////
// END MAIN FUNCTION
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// FUNCTION DEFINITIONS
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
path getDictPath(){
  path dictFilePath;
  cout << "Dictionary file name: ";
  cin  >> dictFilePath;
  if(!exists(dictFilePath))
    cerr << "File" << dictFilePath << " doesn't exist" << endl;

  return dictFilePath;
}//end getDictPath

//----------------------------------------------------------------------------
void parsePhrase(
  string const &phrase,
  WordTable &wordTable
){
  DNshPtr const dictPtr(wordTable.at(0).first);

  //LOOP THRU PARSE PHRASE
  for (int idx = 0; idx < phrase.length(); ++idx){
    char const &ch = phrase[idx];


    WordTable newWordTable;
    //LOOP THRU wordTable
    for (auto& [key, val] : wordTable){
      if(val.first == nullptr) continue;

      DNshPtr& currNodePtr = val.first;
      if(!(currNodePtr->contains(ch))){
        val.first = nullptr;
        continue;
      }

      currNodePtr = currNodePtr->at(ch);
      if (!(currNodePtr->lemma().empty())){//if currNode is a word
        val.second.push_back(currNodePtr);
        newWordTable.emplace(
          idx+1,
          make_pair(DNshPtr(DNshPtr{}, dictPtr.get()), WordLst())
        );
      }//end if currNode is a word
    }//END LOOP THRU wordTable

    for(auto& elem : newWordTable) wordTable.insert(move(elem));
  }//END LOOP THRU PARSE PHRASE
}//end parsePhrase

//----------------------------------------------------------------------------
void prntWordTable(WordTable const &wordTable){
  for (auto const &[key, val] : wordTable){
    cout << "wordTable[" << key << "] = {";
    for (int idx = 0; idx < val.second.size(); ++idx){
      if(idx == 0) cout << *(val.second[idx]);
      else cout << ", " << *(val.second[idx]);
    }
    cout << "}" << endl;
  }
}//end prntWordTable

//----------------------------------------------------------------------------
PhraseLst getPhrases(
  WordTable const& wordTable,
  int idx,
  int const phraseLen
){
  if(!(wordTable.contains(idx))) return PhraseLst();

  PhraseLst rtn;

  for(DNshPtr ptr : wordTable.at(idx).second){
    int newIdx = idx + ptr->lemma().length();
    for(Phrase& phrase : getPhrases(wordTable, newIdx)){
      phrase.insert(phrase.begin(), ptr);
      rtn.push_back(phrase);
    }

    if(rtn.empty())
      rtn.push_back({ptr});
  }

  if(idx == 0){
    erase_if(rtn, [&phraseLen](Phrase const &phrase) {
      int currLen = 0;
      for(DNConstshPtr nodePtr : phrase)
        currLen += nodePtr->lemma().length();

      return (currLen < phraseLen);
    });
  }

  return rtn;
}//end getPhrases

//----------------------------------------------------------------------------
void findBestPhrase(
  PhraseLst const &phraseLst,
  string& maxPhrase,
  double& maxFreq
){
  maxFreq = 0.0;
  maxPhrase = "";
  double currFreq = 0.0;
  string currPhrase;
  //LOOP THRU phraseLst
  for(Phrase const& phrase : phraseLst){
    for(DNshPtr const ptr : phrase){
      currFreq += ptr->freq();
      if(currPhrase.empty()) currPhrase = ptr->lemma();
      else currPhrase = currPhrase + " " + ptr->lemma();
    }

    if(currFreq > maxFreq){
      maxFreq = currFreq;
      maxPhrase = currPhrase;
    }
    currFreq = 0.0;
    currPhrase = "";
  }//END LOOP THRU phraseLst
}//end findBestPhrase













