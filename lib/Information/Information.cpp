#include "Information.hpp"


std::vector<Information::DocumentInformation> Information::GetRankedFiles() {
    std::vector<DocumentInformation> result;
    for (auto& i: documents) {
        auto document_info = FindDocumentById(i.first);
        double score = GetScore(i.second.repetitions,
                                i.second.amount_of_documents_in_catalog,
                                document_info.first,
                                i.second.avg_document_size,
                                amount_of_documents);
        documents[i.first].score = score;
        documents[i.first].file_name = document_info.second;
        result.push_back(documents[i.first]);
    }
    std::sort(result.rbegin(), result.rend());
    return result;
}

Information Information::operator+(const Information &other) {
    for (auto& i: other.documents) {
        documents.insert({i.first, i.second});
    }
    return *this;
}

Information Information::operator*(const Information &other) {
    std::unordered_map<size_t, DocumentInformation> new_map;
    for (auto& i: other.documents) {
        if (documents.contains(i.first)) {
            new_map.insert({i.first, documents[i.first]});
        }
    }
    documents = new_map;
    return *this;
}

double Information::GetScore(double tf, double df, double dl, double avdl, double N, double k1, double b) {
    double IDF = std::log((N - df + 0.5) / (df + 0.5));
    double TF = (tf * (k1 + 1)) / (tf + k1 * (1 - b + b * (dl / avdl)));
    return IDF * TF;
}

std::pair<size_t, std::string> Information::FindDocumentById(size_t id) {
    std::ifstream files_file("files.txt");
    std::pair<size_t, std::string> result;
    std::string temp;
    while (std::getline(files_file, temp)) {
        std::stringstream st_line(temp);
        size_t cur_id, number_of_words;
        std::string name;
        st_line >> cur_id >> number_of_words;
        std::getline(st_line, name, ' ');
        std::getline(st_line, name);
        if (cur_id == id) {
            result.first = number_of_words;
            result.second = name;
            files_file.close();
            return result;
        }
    }
    files_file.close();
    return std::make_pair(SIZE_MAX, "");
}



void Information::AddDocument(size_t key, const Information::DocumentInformation &value) {
    documents.insert({key, value});
}

Information::Information(size_t amount_of_documents_)
: amount_of_documents(amount_of_documents_)
{}


bool Information::DocumentInformation::operator<(const Information::DocumentInformation &other) const {
    return score < other.score;
}

Information::DocumentInformation::DocumentInformation(size_t amount_of_documents_in_catalog_, size_t avg_document_size_,
                                                      const std::vector<size_t> &lines_)
                                                      : amount_of_documents_in_catalog(amount_of_documents_in_catalog_)
                                                      , avg_document_size(avg_document_size_)
                                                      , lines(lines_)
                                                      , repetitions(lines_.size()){

}


