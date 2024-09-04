#include "Searcher.hpp"

std::vector<std::string> Searcher::ParseQuery(const std::string &query) {
    std::vector<std::string> result;
    std::string temp;
    for (char c: query) {
        if (c == '(') {
            if (!temp.empty()) {
                result.push_back(temp);
                temp.clear();
            }
            result.push_back("(");
        } else if (c == ')') {
            if (!temp.empty()) {
                result.push_back(temp);
                temp.clear();
            }
            result.push_back(")");
        } else if (c == ' ') {
            if (!temp.empty()) {
                result.push_back(temp);
                temp.clear();
            }
        } else {
            temp += c;
        }
    }
    if (!temp.empty()) {
        result.push_back(temp);
    }
    size_t counter_open = 0;
    size_t counter_close = 0;
    size_t counter_words = 0;
    size_t counter_operations = 0;
    for (auto& i: result) {
        if (i == "(") {
            counter_open += 1;
        }
        else if (i == ")") {
            counter_close += 1;
        }
        else if (i == "AND" || i == "OR") {
            counter_operations += 1;
        } else {
            counter_words += 1;
        }
    }
    if (counter_open != counter_close || (counter_words - 1) != counter_operations) {
        std::cerr << "Wrong query";
        exit(1);
    }
    return result;

}

Information Searcher::ProcessQuery(const std::vector<std::string> &commands) {
    std::stack<Information> stack;
    std::stack<char> operations;
    for (auto& i: commands) {
        if (i == "(") {
            operations.push('(');
        } else if (i == ")") {
            while (!operations.empty() && operations.top() != '(') {
                Information rhs = stack.top();
                stack.pop();
                Information lhs = stack.top();
                stack.pop();
                if (operations.top() == '+') {
                    stack.push(rhs + lhs);
                } else if (operations.top() == '*') {
                    stack.push(rhs * lhs);
                }
                operations.pop();
            }
            operations.pop();
        } else if (i == "AND") {
            operations.push('*');
        } else if (i == "OR") {
            while (!operations.empty() && operations.top() == '*') {
                Information rhs = stack.top();
                stack.pop();
                Information lhs = stack.top();
                stack.pop();
                operations.pop();
                stack.push(rhs * lhs);
            }
            operations.push('+');
        } else {
            stack.push(index.GetFiles(i));
        }
    }
    while (!operations.empty()) {
        auto rhs = stack.top();
        stack.pop();
        auto lhs = stack.top();
        stack.pop();
        if (operations.top() == '+') {
            stack.push(rhs + lhs);
        } else if (operations.top() == '*') {
            stack.push(rhs * lhs);
        }
        operations.pop();
    }
    return stack.top();

}

std::vector<std::pair<std::string, std::vector<size_t>>> Searcher::GetFiles(const std::string &query) {
    std::vector<std::string> parsed_query = ParseQuery(query);
    Information inf = ProcessQuery(parsed_query);
    auto res = inf.GetRankedFiles();
    std::vector<std::pair<std::string, std::vector<size_t>>> result;
    for (auto& i: res) {
        result.push_back({i.file_name, i.lines});
    }
    return result;
}
