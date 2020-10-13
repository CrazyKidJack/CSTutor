#include "../../Headers/Dictionary/DictionaryNode.hpp"

using namespace std;
using namespace Dict;

//DictionaryNode::DictionaryNode() = default;

DictionaryNode::DictionaryNode(string const &str, string const &lemma, double const &freq)
: str_(str), lemma_(lemma), freq_(freq){}

string const DictionaryNode::lemma() const{ return lemma_; }

string const DictionaryNode::str() const{ return str_; }

double const DictionaryNode::freq() const{ return freq_; }

string to_string(DictionaryNode const &node){
  if(!node.lemma().empty())
    return "[" + node.lemma() + ", " + std::to_string(node.freq()) + "]";
  else if(!node.str().empty())
    return "[" + node.str() + "]";
  else
    return "[]";
}

ostream &operator<<(ostream &os, DictionaryNode const &node){
  os << to_string(node);
  return os;
}