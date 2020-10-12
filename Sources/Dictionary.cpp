#include "../Headers/Dictionary.hpp"

using namespace std;
using filesystem::path;
using DNshPtr = shared_ptr<DictionaryNode>;
using DNwkPtr = weak_ptr<DictionaryNode>;
using DNConstShPtr = shared_ptr<const DictionaryNode>;
using DNConstwkPtr = weak_ptr<const DictionaryNode>;

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

string to_string(Dictionary const& dict){
  stringstream rtnStream;

  stack<DNConstShPtr> prntStack;
  cerr << "Here0.0.0" << endl;
  DNConstShPtr currNode(DNConstShPtr{}, &dict);//non-owning pointer
  cerr << "Here0.0.1" << endl;
  prntStack.push(currNode);

  while(!prntStack.empty()){
    currNode = prntStack.top();
    prntStack.pop();

    rtnStream << currNode << "-->";

    for(auto const& [key, node] : *currNode)
      prntStack.push(node);
  }

  return rtnStream.str();
}

ostream& operator<<(ostream& os, Dictionary const& dict){
  os << to_string(dict);
  return os;
}