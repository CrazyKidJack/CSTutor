#include "../Headers/DictionaryNode.hpp"

using namespace std;

//DictionaryNode::DictionaryNode() = default;

DictionaryNode::DictionaryNode(string const &lemma, double const &freq)
: lemma_(lemma), freq_(freq){}

string const DictionaryNode::lemma() const{
    return lemma_;
}

double const DictionaryNode::freq() const{
    return freq_;
}

string to_string(DictionaryNode const &node){
  return "[" + node.lemma() + ", " + std::to_string(node.freq()) + "]";
}

ostream &operator<<(ostream &os, DictionaryNode const &node){
  os << to_string(node);
  return os;
}