#include <iostream>

#include <vector>

#include <filesystem>

#include "../Headers/Dictionary.hpp"

using namespace std;
using filesystem::path;

int main(){

  path dictFilePath;
  cout << "Dictionary file name: ";
  cin  >> dictFilePath;
  if(!exists(dictFilePath))
    cerr << "File" << dictFilePath << " doesn't exist" << endl;

  Dictionary dict(dictFilePath);
  string phrase = "hellogoodbyesir";

  vector<vector<string>> wordTable;
  vector<string> wordLst;
  //LOOP THRU PARSE PHRASE
  DictionaryNode& currNode = dict;
  for(char const& ch : phrase){
    if(!currNode.lemma().empty()){
      wordLst.push_back(currNode.lemma());
    }
    //some logic to see if dict[ch] exists
    else if(currNode.count(ch))
      currNode = currNode[ch];
  }//END LOOP THRU PARSE PHRASE
  //here, wordLst contains all possible words
  //  that start at index 0 of phrase
  //so....
  //append wordLst to wordTable
  
  /*
  0     1             2   3
0 [the] [bee]        [is] [a]
1 ..    [beekeeper]      
2 ..
  */

  /*
  static vector<string> Dictionary::parse(dict, string, strtIdx){
    vector<string> rtn;
    //traverse dict until finish a word
    //put that word in rtn
    //
    //if no word found
    return rtn; //which is empty
    
    vector<string> recursiveRtn = parse(dict, string, currIdx + 1);
    if(recursiveRtn.empty()){
      rtn.clear();
      return rtn;
    }

    for(string const& word : recursiveRtn)
      rtn.push_back(word);

    return rtn;
  }

  Dictionary dict();
  phrase = "hellogoodbyesir"
  vector<string> wordLst = parse(dict, phrase, 0);

  phrase = "hellogoodbyelaws"
  0,  hello
  5,  good
  9,  bye
  12, laws
  
  hellbeholdenslave

  hell beholden slave
  hell behold enslave

  []-h->[]-e->[he]-l->[]-l->[hell]
          -o->[]-l->[]-d->[hold]
    -b->[]-e->[be]-h->[]-o->[]-l->[]-d->[behold]-e->[]-n->[beholden]
    -e->[]-n->[]-s->[]-l->[]-a->[]-v->[]-e->[enslave]
    -s->[]-l->[]-a->[]-v->[]-e->[slave]

  0,  he, hell
  4,  be, behold, beholden
  6,  hold
  10, enslave
  12, slave

  hell be hold enslave
  hell behold enslave
  hell beholden slave


1 - 1
2 - 2
3 - 4
4 - 7

  1 2 3 4
  12 3 4
  123 4
  1234
  1 23 4
  1 234
  1 2 34
  12 34

  *hello good bye sir duh frank
  *hellogood bye sir duh frank
  *hellogoodbye sir duh frank
  *hellogoodbyesir duh frank
  //hellogoodbyesirduh frank
  //hellogoodbyesirduhfrank
  *hello goodbye sir duh frank
  *hello goodbyesir duh frank
  //hello goodbyesirduh frank
  //hello goodbyesirduhfrank
  *hello good byesir duh frank
  //hello good byesirduh frank
  //hello good byesirduhfrank
  hello good bye sirduh frank
  hello good bye sirduhfrank
  hello good bye sir duhfrank
2^n-1

  //if found word
  parse(phrase, currIdx + 1);

 []-h->[]-e->[he]-l->[]-l->[hell]-o->[hello]
   -g->[]-o->[go]-o->[goo]-d->[good]-b->[]-y->[]-e->[goodbye]
   -b->[]-y->[by]-e->[bye]
   -s->[]-i->[]-r->[sir]

  [he,hell,hello]
  [go,goo,good,goodbye]
  [by,bye]
  [sir]

  []
 */

  list<string> wordLst;
  vector<vector<string&>> wordTree;
  wordTree.push_back({wordLst.front()});
  wordTree[0].push_back(wordLst.front().next());
  wordTree.push_back({wordTree[0][0], "beekeeper"});

  //END LOOP

  //string phrase = "hellogoodbyesir";

  //loop thru characters of phrase
  //  searching dict[character] each time for next node

  return 0;
}