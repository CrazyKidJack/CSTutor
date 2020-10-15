#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <memory>

#include <vector>
#include <stack>

#include <filesystem>

#include "DictionaryNode.hpp"

namespace Dict{ class Dictionary; }
std::ostream & operator<<(std::ostream &stream, Dict::Dictionary const &dict);


//////////////////////////////////////////////////////////////////////////////
// NAMESPACE Dict
//////////////////////////////////////////////////////////////////////////////
namespace Dict{



using std::filesystem::path;

class Dictionary : public DictionaryNode{
public:
  Dictionary() = default;
  Dictionary(path const &filePath);

  //std::string to_string() const;
  friend std::ostream & ::operator<<(std::ostream &stream, Dictionary const &dict);

private:
  int size_;
};



}
//////////////////////////////////////////////////////////////////////////////
// END NAMESPACE Dict
//////////////////////////////////////////////////////////////////////////////

std::string to_string(Dict::Dictionary const& dict);

#endif