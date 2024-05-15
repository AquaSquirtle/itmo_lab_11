#pragma once
#include "iostream"
#include "vector"
#include "lib/InvertedIndex/InvertedIndex.hpp"
#include "stack"

class Searcher {
public:
    std::vector<std::pair<std::string, std::vector<size_t>>> GetFiles(const std::string& query);

private:
    std::vector<std::string> ParseQuery(const std::string& query);
    Information ProcessQuery (const std::vector<std::string>& commands);
    InvertedIndex index;
};

