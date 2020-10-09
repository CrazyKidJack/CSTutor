#include "../Headers/DictionaryNode.hpp"

using namespace std;

//DictionaryNode::DictionaryNode() = default;

DictionaryNode::DictionaryNode(string const &lemma, double const &freq = -1.0)
: lemma_(lemma), freq_(freq){}

string const DictionaryNode::lemma(){
    return lemma_;
}

double const DictionaryNode::freq(){
    return freq_;
}

DictionaryNode& DictionaryNode::operator[](char const key){
    return transLst_.at(key);
}