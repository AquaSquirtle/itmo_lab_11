#pragma once
#include "iostream"
#include "fstream"
#include "sstream"
#include "Information.hpp"



class InvertedIndex {
public:
    InvertedIndex() = default;
    Information GetFiles(const std::string& word);

private:
    std::ifstream table;
};


