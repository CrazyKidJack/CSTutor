#include "../Headers/Dictionary.hpp"

using namespace std;
using filesystem::path;

//Dictionary::Dictionary() = default;

Dictionary::Dictionary(path const& filePath){
  size_ = 0;

  if(!exists(filePath))  {
    cerr << "File " << filePath << " doesn't exist..." << endl
         << "Terminating..." << endl;
    exit(EXIT_FAILURE);
  }
  
  ifstream dictStrm(filePath.string());
  double freq;
  string lemma;
  DictionaryNode *currNode = this;
  //cerr << "[]-->";
  while(dictStrm >> freq >> freq >> lemma){
    for (char const& ch : lemma){
      currNode = &((*currNode)[ch]);
      ++size_;
      //cerr << "[" << ch << "]-->"
    }
      
      
    currNode->freq_ = freq;
    currNode->lemma_ = lemma;
    cerr << "[" << currNode->lemma_ << ", " << std::to_string(currNode->freq_) << "]-->";
  }
  dictStrm.close();
}

string Dictionary::to_string() const{
  stringstream rtnStream;

  stack<DictionaryNode> prntStack;
  cerr << "Here0.0.0" << endl;
  DictionaryNode currNode = *this;
  cerr << "Here0.0.1" << endl;
  prntStack.push(currNode);

  while(!prntStack.empty()){
    currNode = prntStack.top();
    prntStack.pop();

    rtnStream << currNode << "-->";

    for(auto const& elem : currNode)
      prntStack.push(elem.second);
  }

  return rtnStream.str();
}

ostream& operator<<(ostream& os, Dictionary const& dict){
  os << dict.to_string();
  return os;
}