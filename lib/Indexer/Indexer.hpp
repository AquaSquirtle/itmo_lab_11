#pragma once
#include "fstream"
#include "filesystem"
#include "unordered_map"
#include "unordered_set"
#include "vector"
#include "cstdint"

class Indexer {
public:
    Indexer();
    void Parse(const std::string& dir_path);
private:
    void ParseFile(const std::filesystem::path& path);
    void AddWord(std::string& word);
    void Write();
    bool CheckSymbol(const char& c);

    size_t cur_file = 0;
    size_t cur_line = 0;
    size_t words_amount = 0;

    std::unordered_map<size_t, size_t> words_in_documents;
    std::unordered_map<std::string, std::unordered_map<size_t, std::pair<std::vector<size_t>, size_t>>> inverted_index;
    std::ofstream files_file;
    std::ofstream table;
};


