#ifndef DICTIONARYNODE_HPP
#define DICTIONARYNODE_HPP

//////////////////////////////////////////////////////////////////////////////
//INCLUDE FILES & NAMESPACES
//////////////////////////////////////////////////////////////////////////////
//types
#include <iostream>

#include <string>
#include <memory> //smart pointers

//containers
#include <map>

//////////////////////////////////////////////////////////////////////////////
//CLASS DictionaryNode
//////////////////////////////////////////////////////////////////////////////
class DictionaryNode : public std::map<char, shared_ptr<DictionaryNode>>{
public:
  DictionaryNode() = default;
  DictionaryNode(std::string const &lemma, double const &freq = -1.0);

  std::string const lemma() const;
  double const freq() const;

  //std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &os, DictionaryNode const& node);

protected:
  std::string lemma_;
  double freq_;

  friend class Dictionary;
};

std::string to_string(DictionaryNode const& node);

#endif