//////////////////////////////////////////////////////////////////////////////
// INCLUDE FILES & NAMESPACES
//////////////////////////////////////////////////////////////////////////////
#include "../../Headers/Dictionary/Dictionary.hpp"

using namespace std;
using namespace Dict;

//////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS
//////////////////////////////////////////////////////////////////////////////
//Dictionary::Dictionary() = default;

Dictionary::Dictionary(path const& filePath){
  dictSize_ = 0;

  if(!exists(filePath))  {
    cerr << "File " << filePath << " doesn't exist..." << endl
         << "Terminating..." << endl;
    exit(EXIT_FAILURE);
  }
  
  ifstream dictStrm(filePath.string());
  double freq;
  string lemma;
  DNshPtr headNodePtr(DNshPtr{}, this);//non-controlling pointer
  DNshPtr currNodePtr(headNodePtr);//non-controlling pointer
  
  while(dictStrm >> freq >> freq >> lemma){
    string str;
    str.reserve(lemma.size());
    for (char const& ch : lemma){
      str += ch;
      DNshPtr& newNodePtr = (*currNodePtr)[ch];
      int i = 0;
      if(newNodePtr == nullptr){
        newNodePtr = make_shared<DictionaryNode>(str);
        ++dictSize_;
      }
      currNodePtr = newNodePtr;
    }
    
    currNodePtr->freq_ = freq;
    currNodePtr->lemma_ = lemma;
    currNodePtr = headNodePtr;
  }
  dictStrm.close();
}

//////////////////////////////////////////////////////////////////////////////
// ACCESSORS
//////////////////////////////////////////////////////////////////////////////
int const Dictionary::getSize() const { return dictSize_; }

//////////////////////////////////////////////////////////////////////////////
// PRINTING
//////////////////////////////////////////////////////////////////////////////
string to_string(Dictionary const& dict){
  stringstream rtnStream;
  stack<pair<string, DNConstshPtr>> prntStack;
  DNConstshPtr currNodePtr(DNConstshPtr{}, &dict);//non-controlling pointer
  string depth = "";
  prntStack.push({depth, currNodePtr});

  while(!prntStack.empty()){
    depth = prntStack.top().first;
    currNodePtr = prntStack.top().second;
    prntStack.pop();

    rtnStream << depth << *currNodePtr << endl;

    for(auto const [trans, node] : *currNodePtr)
      prntStack.push({depth+"  ", node});
  }//END LOOP WHILE ! stack.empty()

  return rtnStream.str();
}//end to_string(Dictionary const&)

ostream& operator<<(ostream& os, Dictionary const& dict){
  os << to_string(dict);
  return os;
}