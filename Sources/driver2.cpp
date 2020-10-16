//////////////////////////////////////////////////////////////////////////////
// INCLUDE FILES & NAMESPACES
//////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include <memory>

#include <vector>

#include <filesystem>
#include <ctype.h>

#include "../Headers/Dict/Dictionary.hpp"

using namespace std;
using namespace Dict;
using filesystem::path;
using WordTable = map<int, pair<DNConstShPtr, vector<DNConstShPtr>>>;
using Phrase = vector<DNConstShPtr>;
using WordLst = vector<DNConstShPtr>;
using PhraseLst = vector<Phrase>;

//////////////////////////////////////////////////////////////////////////////
// FUNCTION DECLARATIONS
//////////////////////////////////////////////////////////////////////////////
PhraseLst getPhrases(
  WordTable const &wordTable,
  int const idx,
  int const phraseLen = -1
);
Phrase const &chooseBestPhrase(PhraseLst const &phraseLst);

//////////////////////////////////////////////////////////////////////////////
// MAIN FUNCTION
//////////////////////////////////////////////////////////////////////////////
int main(){
  path dictFilePath;
  cout << "Dictionary file name: ";
  cin  >> dictFilePath;
  if(!exists(dictFilePath))
    cerr << "File" << dictFilePath << " doesn't exist" << endl;

  Dictionary dict(dictFilePath);
  cerr << "dict size= " << dict.getSize() << endl;
  cerr << "Do you want to print the dictionary (y/n)? ";
  char print;
  cin >> print;
  print = tolower(print);
  if(print == 'y'){
    cerr << "Dictionary After:" << endl
       << "===========================================================" << endl
       << "===========================================================" << endl
       << dict << endl << endl;
  }

  string phrase;
  cout << "Phrase: ";
  cin  >> phrase;

  WordTable wordTable;
  wordTable.emplace(
    0,
    make_pair(DNConstShPtr(DNConstShPtr{}, &dict), WordLst())
  );
  
  //LOOP THRU PARSE PHRASE
  for (int idx = 0; idx < phrase.length(); ++idx){
    char const &ch = phrase[idx];

    WordTable newWordLsts;
    for (auto& [key, val] : wordTable){
      if(val.first == nullptr) continue;

      DNConstShPtr& currNodePtr = val.first;
      WordLst& currWordLst = val.second;
      if(!(currNodePtr->contains(ch))){
        currNodePtr = nullptr;
        continue;
      }

      //implicit else
      currNodePtr = currNodePtr->at(ch);
      if (!currNodePtr->lemma().empty()){//if currNode is a word
        currWordLst.push_back(currNodePtr);
        newWordLsts.emplace(
          idx+1,
          make_pair(DNConstShPtr(DNConstShPtr{}, &dict), WordLst())
        );
      }
    }

    for(auto& elem : newWordLsts)
      wordTable.insert(move(elem));
  } //END LOOP THRU PARSE PHRASE

  erase_if(wordTable, [](auto &elem) { return elem.second.second.empty(); });

  for(auto const& [key, val] : wordTable){
    cerr << "wordTable[" << key << "]= ";
    for (int idx = 0; idx < val.second.size(); ++idx){
      if(idx == 0)
        cerr << *(val.second[idx]);
      else
        cerr << ", " << *(val.second[idx]);
    }
    cerr << endl;
  }
  cerr << endl << endl;

  PhraseLst phraseLst = getPhrases(wordTable, 0, phrase.length());

  for (int phraseIdx = 0; phraseIdx < phraseLst.size(); ++phraseIdx){
    cerr << "Phrase " << phraseIdx << ":";
    for(DNConstShPtr nodePtr : phraseLst[phraseIdx]){
      cerr << " " << *nodePtr;
    }
    cerr << endl;
  }
  cerr << endl << endl;

  Phrase const& maxPhrase = chooseBestPhrase(phraseLst);

  cout << "Max Phrase:";
  for(DNConstShPtr nodePtr : maxPhrase){
    cout << " " << *nodePtr;
  }
  cout << endl;

  return 0;
}//END MAIN
//////////////////////////////////////////////////////////////////////////////
// END MAIN FUNCTION
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// FUNCTION DEFINITIONS
//////////////////////////////////////////////////////////////////////////////
PhraseLst getPhrases(
  WordTable const& wordTable,
  int const idx,
  int const phraseLen
){
  PhraseLst rtn;

  if(!(wordTable.contains(idx))) return rtn;

  WordLst const& currLst = wordTable.at(idx).second;
  for(DNConstShPtr nodePtr : currLst){
    PhraseLst phraseLst = getPhrases(wordTable, idx + nodePtr->lemma().length());
    if(phraseLst.empty()){
      rtn.push_back({nodePtr});
      continue;///!!!NEXT LOOP ITERATION HERE!!!///
    }
      
    for(Phrase& phrase : phraseLst){
      phrase.insert(phrase.begin(), nodePtr);
      rtn.push_back(move(phrase));
    }
  }


  if(idx == 0){
    erase_if(rtn, [&phraseLen](Phrase const &phrase) {
      int currLen = 0;
      for(DNConstShPtr nodePtr : phrase)
        currLen += nodePtr->lemma().length();

      return (currLen != phraseLen);
    });
  }
  return rtn;
}//end getPhrases

Phrase const& chooseBestPhrase(PhraseLst const& phraseLst){
  int maxFreq = -1, maxIdx = -1;
  int currFreq = 0, currIdx = 0;

  //LOOP THRU PHRASES
  for (currIdx; currIdx < phraseLst.size(); ++currIdx){
    for(DNConstShPtr nodePtr : phraseLst[currIdx])
      currFreq += nodePtr->freq();
    if(currFreq > maxFreq){
      maxFreq = currFreq;
      maxIdx = currIdx;
    }

    currFreq = 0;
  }//END LOOP THRU PHRASES

  if(maxIdx == -1){
    cerr << "No phrases in list... Terminating" << endl;
    exit(EXIT_FAILURE);
  }

  return phraseLst.at(maxIdx);
}//END chooseBestPhrase