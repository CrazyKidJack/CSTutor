#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>

#include <vector>
#include <stack>

#include <filesystem>

#include "DictionaryNode.hpp"

class Dictionary : public DictionaryNode{
public:
  Dictionary() = default;
  //Dictionary(Dictionary const &dict);
  Dictionary(std::filesystem::path const& filePath);
  //virtual ~Dictionary();

  //std::string to_string() const;
  friend std::ostream& operator<<(std::ostream &stream, Dictionary const& dict);

private:
  int size_;
};

std::string to_string(Dictionary const& dict);

#endif