#include <iostream>

#include <memory>

#include <vector>

#include <filesystem>

#include "../Headers/Dict/Dictionary.hpp"

using namespace std;
using namespace Dict;
using filesystem::path;

int main(){
  path dictFilePath;
  cout << "Dictionary file name: ";
  cin  >> dictFilePath;
  if(!exists(dictFilePath))
    cerr << "File" << dictFilePath << " doesn't exist" << endl;

  Dictionary dict(dictFilePath);
  cerr << "Dictionary After:" << endl
       << "===========================================================" << endl
       << "===========================================================" << endl
       << dict << endl << endl;
  string phrase = "hellogoodbyesir";

  map<int, pair<DictionaryNode*, vector<DictionaryNode*>>> wordTable;
  wordTable.emplace(
    0,
    make_pair(&dict, vector<DictionaryNode*>())
  );
  /*
  int* a = new int(4);
  //a contains 0x0001

  delete a;

  //a still contains 0x0001

  */
  /*
  start: [ [he, hel], [l] ]
  end: [[he, hell][be, behold, beholden][..][...][...]]
  */
  //LOOP THRU PARSE PHRASE
  for (int idx = 0; idx < phrase.length(); ++idx){
    char const &ch = phrase[idx];

    for (auto& [key, val] : wordTable){
      if(val.first == nullptr) continue;

      DictionaryNode*& currNode = val.first;
      if(!(currNode->contains(ch))){
        val.first = nullptr;
        continue;
      }

      //implicit else
      currNode = &(currNode->at(ch));
      if (!currNode->lemma().empty()){//if currNode is a word
        val.second.push_back(currNode);
        wordTable.emplace(
          idx,
          make_pair(&dict, vector<DictionaryNode*>())
        );
      }
    }
  } //END LOOP THRU PARSE PHRASE

  cerr << "Here0.0.0" << endl;
  //here, wordLst contains all possible words
  //  that start at index 0 of phrase
  //so....
  //append wordLst to wordTable
  
  /*  
  hellbehold enslave

  hell beholden slave
  hell behold enslave

  map<int, DictionaryNode> currNodeLst = {{4,node},{6,node},{10,node}}

  [10]-h->[]-e->[he]-l->[]-l->[hell]
          -o->[]-l->[]-d->[6hold]
    -b->[]-e->[be]-h->[]-o->[]-l->[]-d->[4behold]-e->[]-n->[beholden]
    -e->[]-n->[]-s->[]-l->[]-a->[]-v->[]-e->[enslave]
    -s->[]-l->[]-a->[]-v->[]-e->[slave]

  //wordTable
  wordTable[0] = {[he], [hell]}
  wordTable[4] = {[be], [behold]}
  wordTable[6] = {[hold]}
  wordTable[10] = {}

  //wordTable
             v--currNode0
  wordTable[0] 0,  he, hell
  2, 
  wordTable[4] 4,  be, behold, beholden
  wordTable[6] 6,  hold
  wordTable[10] 10, enslave
  wordTable[12] 12, slave

  1) he BAD
  2) hell be hold enslave GOOD
  3) hell behold enslave GOOD
  4) hell beholen slave GOOD

  hell be hold enslave
  hell behold enslave
  hell beholden slave
 */

  return 0;
}