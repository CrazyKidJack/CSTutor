#include <iostream>
#include <fstream>

#include "../Headers/dictionary.hpp"

using namespace std;
using filesystem::path;

//Dictionary::Dictionary() = default;

Dictionary::Dictionary(path const& filePath){
  if(!exists(filePath))  {
    cerr << "File " << filePath << " doesn't exist..." << endl
         << "Terminating..." << endl;
    exit(EXIT_FAILURE);
  }
  
  ifstream dictStrm(filePath.string());
  double freq;
  string lemma;
  DictionaryNode &currNode = *this;
  while(dictStrm >> freq >> freq >> lemma){
    for (char const& ch : lemma)
      currNode = currNode[ch];
      
    currNode.freq_ = freq;
    currNode.lemma_ = lemma;
  }
  dictStrm.close();
}