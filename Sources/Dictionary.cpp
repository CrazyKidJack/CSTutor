#include "../Headers/Dictionary.hpp"

using namespace std;
using namespace Dict;

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
  DNshPtr currNodePtr(DNshPtr{}, this);
  //cerr << "[]-->";
  while(dictStrm >> freq >> freq >> lemma){
    for (char const& ch : lemma){
      currNodePtr = (*currNodePtr)[ch];
      if (currNodePtr == nullptr){
        currNodePtr = make_shared<DictionaryNode>();
      }
      ++size_;
      //cerr << "[" << ch << "]-->"
    }

    currNodePtr->freq_ = freq;
    currNodePtr->lemma_ = lemma;
    cerr << "[" << currNodePtr->lemma_ << ", " << std::to_string(currNodePtr->freq_) << "]-->";
  }
  dictStrm.close();
}

string to_string(Dictionary const& dict){
  stringstream rtnStream;

  stack<DNConstShPtr> prntStack;
  DNConstShPtr currNodePtr(DNConstShPtr{}, &dict);//non-owning pointer
  prntStack.push(currNodePtr);

  while(!prntStack.empty()){
    currNodePtr = prntStack.top();
    prntStack.pop();

    rtnStream << *currNodePtr << "-->";

    for(auto const& [trans, node] : *currNodePtr)
      prntStack.push(node);
  }

  return rtnStream.str();
}//end to_string(Dictionary)

ostream& operator<<(ostream& os, Dictionary const& dict){
  os << to_string(dict);
  return os;
}