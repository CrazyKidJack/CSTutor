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

namespace Dict { class DictionaryNode; }
std::ostream& operator<<(std::ostream &os, Dict::DictionaryNode const& node);

//////////////////////////////////////////////////////////////////////////////
// NAMESPACE Dict
//////////////////////////////////////////////////////////////////////////////
namespace Dict{


//////////////////////////////////////////////////////////////////////////////
//CLASS DictionaryNode
//////////////////////////////////////////////////////////////////////////////
class DictionaryNode
  : public std::map<char, std::shared_ptr<DictionaryNode>>{
public:
  DictionaryNode() = default;
  DictionaryNode(//init constructor
    std::string const& str,
    std::string const &lemma = "",
    double const &freq = -1.0
  );

  std::string const lemma() const;
  std::string const str() const;
  double const freq() const;

  //std::string to_string() const;
  friend std::ostream& ::operator<<(std::ostream &os, DictionaryNode const& node);

protected:
  std::string lemma_;
  std::string str_;
  double freq_;

  friend class Dictionary;
};


}
//////////////////////////////////////////////////////////////////////////////
// END NAMESPACE Dict
//////////////////////////////////////////////////////////////////////////////

std::string to_string(Dict::DictionaryNode const& node);

#endif