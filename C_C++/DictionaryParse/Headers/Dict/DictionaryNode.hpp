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

namespace Dict{ class DictionaryNode; }
std::ostream& operator<<(std::ostream &os, Dict::DictionaryNode const &node);


//////////////////////////////////////////////////////////////////////////////
// NAMESPACE Dict
//////////////////////////////////////////////////////////////////////////////
namespace Dict{


  
using DNshPtr = std::shared_ptr<DictionaryNode>;
using DNwkPtr = std::weak_ptr<DictionaryNode>;
using DNConstShPtr = std::shared_ptr<DictionaryNode const>;
using DNConstWkPtr = std::weak_ptr<DictionaryNode const>;

//////////////////////////////////////////////////////////////////////////////
//CLASS DictionaryNode
//////////////////////////////////////////////////////////////////////////////
class DictionaryNode : public std::map<char, std::shared_ptr<DictionaryNode>>{
public:
  DictionaryNode() = default;
  DictionaryNode(
    std::string const& str,
    std::string const &lemma="",
    double const &freq = -1.0
  );

  std::string const lemma() const;
  double const freq() const;
  std::string const str() const;

  //std::string to_string() const;
  friend std::ostream & ::operator<<(std::ostream &os, DictionaryNode const &node);

protected:
  std::string lemma_;
  double freq_;
  std::string str_;

  friend class Dictionary;
}; //end class DictionaryNode



}
//////////////////////////////////////////////////////////////////////////////
// END NAMESPACE Dict
//////////////////////////////////////////////////////////////////////////////


std::string to_string(Dict::DictionaryNode const& node);

#endif