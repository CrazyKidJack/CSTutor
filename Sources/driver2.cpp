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

//CUSTOM
#include "../Headers/Dictionary/Dictionary.hpp"

using namespace std;
using namespace Dict;
using filesystem::path;

//////////////////////////////////////////////////////////////////////////////
// FUNCTION DECLARATIONS
//////////////////////////////////////////////////////////////////////////////
vector<vector<DNshPtr>> getPhrases(
  map<int, pair<DNshPtr, vector<DNshPtr>>> const &wordTable,
  int idx
);

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

  cerr << "Dictionary: " << endl
       << dict << endl
       << endl;

  string phrase;
  cout << "phrase: ";
  cin  >> phrase;

  map<int, pair<DNshPtr, vector<DNshPtr>>> wordTable;
  wordTable.emplace(
    0,
    make_pair(DNshPtr(DNshPtr{}, &dict), vector<DNshPtr>())
  );

  //LOOP THRU PARSE PHRASE
  for (int idx = 0; idx < phrase.length(); ++idx){
    char const &ch = phrase[idx];


    map<int, pair<DNshPtr, vector<DNshPtr>>> newWordTable;
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
          make_pair(DNshPtr(DNshPtr{}, &dict), vector<DNshPtr>())
        );
      }//end if currNode is a word
    }//END LOOP THRU wordTable

    for(auto& elem : newWordTable) wordTable.insert(move(elem));
  }//END LOOP THRU PARSE PHRASE

  erase_if(wordTable, [](auto const &elem) {
    vector<DNshPtr> const &wordLst = elem.second.second;
    return wordLst.empty();
  });

  for (auto const &[key, val] : wordTable){
    cout << "wordTable[" << key << "] = {";
    for (int idx = 0; idx < val.second.size(); ++idx){
      if(idx == 0) cout << *(val.second[idx]);
      else cout << ", " << *(val.second[idx]);
    }
    cout << "}" << endl;
  }

  vector<vector<DNshPtr>> phraseLst(getPhrases(wordTable, 0));

  double maxFreq = 0.0;
  string maxPhrase;
  double currFreq = 0.0;
  string currPhrase;
  for(vector<DNshPtr> const& phrase : phraseLst){
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
  }

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
vector<vector<DNshPtr>> getPhrases(
  map<int, pair<DNshPtr, vector<DNshPtr>>> const& wordTable,
  int idx
){
  if(!(wordTable.contains(idx))) return vector<vector<DNshPtr>>();

  vector<vector<DNshPtr>> rtn;

  for(DNshPtr ptr : wordTable.at(idx).second){
    int newIdx = idx + ptr->lemma().length();
    for(vector<DNshPtr>& phrase : getPhrases(wordTable, newIdx)){
      phrase.insert(phrase.begin(), ptr);
      rtn.push_back(phrase);
    }

    if(rtn.empty())
      rtn.push_back({ptr});
  }

  return rtn;
}//end foo













