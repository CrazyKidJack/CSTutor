#include "../Headers/Dictionary.hpp"

using namespace std;
using filesystem::path;
using DNshPtr = shared_ptr<DictionaryNode>;
using DNwkPtr = weak_ptr<DictionaryNode>;
using DNConstshPtr = shared_ptr<DictionaryNode const>;
using DNConstwkPtr = weak_ptr<DictionaryNode const>;

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
  //DictionaryNode *currNodePtr = this;
  DNshPtr currNodePtr(DNshPtr{}, this);//non-controlling pointer
  //cerr << "[]-->";
  while(dictStrm >> freq >> freq >> lemma){
    for (char const& ch : lemma){
      currNodePtr = (*currNodePtr)[ch];
      if(currNodePtr == nullptr)
        currNodePtr = make_shared<DictionaryNode>();
      ++size_;
      //cerr << "[" << ch << "]-->"
    }
      
    
    currNodePtr->freq_ = freq;
    currNodePtr->lemma_ = lemma;
    cerr << "[" << currNodePtr->lemma_ << ", "
         << std::to_string(currNodePtr->freq_) << "]-->";
  }
  dictStrm.close();
}

string to_string(Dictionary const& dict){
  stringstream rtnStream;

  stack<DNConstshPtr> prntStack;

  DNConstshPtr currNodePtr(DNConstshPtr{}, &dict);//non-controlling pointer
  prntStack.push(currNodePtr);

  while(!prntStack.empty()){
    currNodePtr = prntStack.top();
    prntStack.pop();

    rtnStream << *currNodePtr << "-->";

    for(auto const& [trans, node] : *currNodePtr)
      prntStack.push(node);
  }

  return rtnStream.str();
}

ostream& operator<<(ostream& os, Dictionary const& dict){
  os << to_string(dict);
  return os;
}