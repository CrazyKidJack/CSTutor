#ifndef DICTIONARYNODE_HPP
#define DICTIONARYNODE_HPP

//////////////////////////////////////////////////////////////////////////////
//INCLUDE FILES & NAMESPACES
//////////////////////////////////////////////////////////////////////////////
//types
#include <string>
#include <memory> //smart pointers

//containers
#include <map>

//////////////////////////////////////////////////////////////////////////////
//CLASS DictionaryNode
//////////////////////////////////////////////////////////////////////////////
class DictionaryNode{
public:
  DictionaryNode() = default;
  DictionaryNode(std::string const &lemma, double const &freq = -1.0);

  std::string const lemma() const;
  double const freq() const;
  DictionaryNode& operator[](char const key) const;


protected:
  std::string lemma_;
  double freq_;
  std::map<char, DictionaryNode> transLst_;

  friend class Dictionary;
};

class DictionaryNode : public std::map<char, DictionaryNode>{
public:
  DictionaryNode() = default;
  DictionaryNode(std::string const &lemma, double const &freq = -1.0);

  std::string const lemma() const;
  double const freq() const;  

protected:
  std::string lemma_;
  double freq_;

  friend class Dictionary;
};

#endif