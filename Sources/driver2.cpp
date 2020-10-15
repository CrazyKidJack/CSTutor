#include <iostream>

#include <memory>

#include <vector>

#include <filesystem>

#include "../Headers/Dictionary.hpp"

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
  /*
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
*/
  return 0;
}