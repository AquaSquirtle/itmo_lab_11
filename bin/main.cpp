#include "Indexer/Indexer.hpp"
#include "InvertedIndex/InvertedIndex.hpp"
#include "Searcher/Searcher.hpp"
#include <string.h>

int main (int argc, char** argv) {
    std::string query;
    std::string dir;
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "-dir") == 0){
            int count = 0;
            for (int j = i + 1; j < argc; ++j) {
                dir += argv[j];
                if (count != 0) {
                    dir += " ";
                }
                ++count;
            }
        }
        if (strcmp(argv[i], "-find") == 0){
            for (int j = i + 1; j < argc; ++j) {
                query += argv[j];
                query += " ";
            }
        }
    }
    if (!dir.empty()) {
        Indexer indexer;
        indexer.Parse(dir);
        std::cout << "Inverted index prepared!\n";
    } else if (!query.empty()) {
        std::cout << query << '\n';
        Searcher searcher;
        auto k = searcher.GetFiles(query);
        std::cout << "Files found:\n";
        for (int i = 0; i < k.size(); ++i) {
            std::cout << "File number" << ' ' << i + 1 << ": " <<  k[i].first << '\n';
            std::cout << "Lines where files were found: ";
            int counter = 0;
            for (auto& j: k[i].second) {
                if (counter > 5) {
                    std::cout << "...";
                    break;
                }
                std::cout << j << ' ';
                ++counter;
            }
            std::cout << '\n' << '\n';
        }
    }
}