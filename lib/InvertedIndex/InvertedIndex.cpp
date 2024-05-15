#include "InvertedIndex.hpp"

Information InvertedIndex::GetFiles(const std::string &w) {
    std::string word;
    for (auto& i: w) {
        word += std::tolower(i);
    }
    size_t amount_of_documents, amount_of_documents_in_catalog, avg_document_size;
    std::string temp;
    std::string wrd;
    table.open("table.txt");
    table >> amount_of_documents;
    Information result(amount_of_documents);
    while (std::getline(table, temp )) {
        std::stringstream line(temp);
        line >> wrd >> amount_of_documents_in_catalog >> avg_document_size;
        if (wrd == word) {
            size_t file_id, repetitions;
            while (line >> file_id >> repetitions) {
                std::vector<size_t> lines;
                for (size_t i = 0; i < repetitions; ++i) {
                    size_t temp2;
                    line >> temp2;
                    lines.push_back(temp2);
                }
                result.AddDocument(file_id, {amount_of_documents_in_catalog, avg_document_size,lines});
            }
            break;
        }
    }
    table.close();
    return result;
}



