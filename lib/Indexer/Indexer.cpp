#include "Indexer.hpp"
#include "iostream"

Indexer::Indexer() = default;

void Indexer::Parse(const std::string& dir_path) {
    files_file.open("files.txt");
    for (const auto& path : std::filesystem::recursive_directory_iterator(dir_path)) {
        if (std::filesystem::is_regular_file(path) && path.exists() && !path.is_directory()) {
            cur_line = 1;
            words_amount = 0;
            ParseFile(path.path());
            files_file << cur_file << ' ' << words_amount << ' ' << path.path().string() << '\n';
            words_in_documents[cur_file] = words_amount;
            ++cur_file;
        }
    }
    Write();
    files_file.close();
}

void Indexer::ParseFile(const std::filesystem::path& path) {
    std::ifstream file(path);
    char symbol;
    std::string word;
    while (file.get(symbol)) {
        if (CheckSymbol(symbol)) {
            word += (char)std::tolower(symbol) ;
        } else {
            if (symbol == '\n'){
                ++cur_line;
            }
            AddWord(word);
        }
    }
    AddWord(word);
}


bool Indexer::CheckSymbol(const char& c) {
    return c != ' ' && c != ',' && c != '.' && c != ':'
    && c != ';' && c != '\'' && c != '\"' && c != '!'
    && c != '?' && c != '\n' && c != '(' && c != ')'
    && c != '[' && c != ']' && c != '{' && c != '}'
    && c != '<' && c != '>' && c != '/' && c != '\\'
    && c != '&' && c != '#' && c != '%'&& c != '*'
    && c != '^' && c != '_' && c != '`' && c != '~'
    && c != '\t';
}

void Indexer::Write() {
    table.open("table.txt");
    table << cur_file << '\n';
    for (auto& i: inverted_index) {
        table << i.first << ' ' << i.second.size() << ' ';
        size_t amount_of_words = 0;
        for (auto & j: i.second) {
            amount_of_words += words_in_documents[j.first];
        }
        if (i.second.size() > 0) {
            table << (amount_of_words / i.second.size()) << ' ';
        } else {
            table << 0 << ' ';
        }

        for (auto& j: i.second) {
            table << j.first << ' ' << j.second.second << ' ';
            for (size_t k = 0; k < j.second.second; ++k) {
                table << j.second.first[k] << ' ';
            }
        }
        table << '\n';
    }
    inverted_index.clear();
    table.close();
}

void Indexer::AddWord(std::string &word) {
    if (!word.empty()) {
        ++words_amount;
        if (!inverted_index.contains(word)) {
            inverted_index.insert({word, {}});
            inverted_index[word][cur_file] = {{cur_line}, 1};
        } else {
            if (inverted_index[word].contains(cur_file)) {
                ++inverted_index[word][cur_file].second;
                inverted_index[word][cur_file].first.push_back(cur_line);
            } else {
                inverted_index[word][cur_file] = {{cur_line}, 1};
            }
        }
        word.clear();
    }

}



