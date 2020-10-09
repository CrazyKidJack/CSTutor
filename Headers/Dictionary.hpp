#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <string>

#include <filesystem>

#include "DictionaryNode.hpp"

class Dictionary : public DictionaryNode{
public:
  Dictionary() = default;
  Dictionary(std::filesystem::path const& filePath);

private:
};

#endif