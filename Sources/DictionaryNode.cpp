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

string DictionaryNode::to_string() const{
  return "[" + lemma_ + ", " + std::to_string(freq_) + "]";
}

ostream &operator<<(ostream &os, DictionaryNode const &node){
  os << node.to_string();
  return os;
}