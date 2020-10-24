//////////////////////////////////////////////////////////////////////////////
// INCLUDE FILES & NAMESPACES
//////////////////////////////////////////////////////////////////////////////
#include "../../Headers/Dict/Dictionary.hpp"

using namespace std;
using namespace Dict;

//////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
//Dictionary::Dictionary() = default;

//----------------------------------------------------------------------------
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
  DNshPtr const rootPtr(DNshPtr{}, this);
  DNshPtr currNodePtr(rootPtr);
  //LOOP THRU READ INPUT FILE
  while(dictStrm >> freq >> freq >> lemma){
    //LOOP THRU LEMMA
    for (char const& ch : lemma){
      //get next node
      //or create new one
      DNshPtr& newNodePtr = (*currNodePtr)[ch];
      if (newNodePtr == nullptr){
        //add new node
        newNodePtr = make_shared<DictionaryNode>(currNodePtr->str()+ch);
        ++size_;
      }
      currNodePtr = newNodePtr; //traverse Dictionary
    }//END LOOP THRU LEMMA

    currNodePtr->freq_ = freq;
    currNodePtr->lemma_ = lemma;
    currNodePtr = rootPtr;
  }//END LOOP THRU READ INPUT FILE

  dictStrm.close();
}//end init constructor

//////////////////////////////////////////////////////////////////////////////
// ACCESSORS
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
int const Dictionary::getSize() const{
  return size_;
}

//////////////////////////////////////////////////////////////////////////////
// PRINTING
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
string to_string(Dictionary const& dict){
  stringstream rtnStream;

  stack<pair<string, DNConstShPtr>> prntStack;
  DNConstShPtr currNodePtr(DNConstShPtr{}, &dict);//non-owning pointer
  string depthPrefix = "";
  prntStack.push({depthPrefix, currNodePtr});

  while(!prntStack.empty()){
    depthPrefix = prntStack.top().first;
    currNodePtr = prntStack.top().second;
    prntStack.pop();

    rtnStream << depthPrefix << *currNodePtr << endl;

    for(auto const& [trans, node] : *currNodePtr)
      prntStack.push({depthPrefix+"  ", node});
  }

  return rtnStream.str();
}//end to_string(Dictionary)

//----------------------------------------------------------------------------
ostream& operator<<(ostream& os, Dictionary const& dict){
  os << to_string(dict);
  return os;
}