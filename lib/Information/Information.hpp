#pragma once
#include "iostream"
#include "vector"
#include "unordered_map"
#include "sstream"
#include "fstream"
#include "cmath"
#include "algorithm"

class Information {


public:
    explicit Information(size_t amount_of_documents_);
private:
    struct DocumentInformation {
        DocumentInformation() = default;
        double score = 0;
        std::string file_name = "";
        size_t amount_of_documents_in_catalog;
        size_t avg_document_size;
        size_t repetitions;
        std::vector<size_t> lines;
        DocumentInformation(size_t amount_of_documents_in_catalog_, size_t avg_document_size_, const std::vector<size_t>& lines_);
        bool operator<(const DocumentInformation& other) const;
    };

public:
    std::vector<DocumentInformation> GetRankedFiles();
    void AddDocument(size_t key, const DocumentInformation& value);
    Information operator*(const Information& other);
    Information operator+(const Information& other);

private:
    std::unordered_map<size_t, DocumentInformation> documents;
    double GetScore(double tf, double df, double dl, double avdl, double N, double k1 = 2, double b = 0.75);
    std::pair<size_t , std::string> FindDocumentById(size_t id);
    size_t amount_of_documents;
};