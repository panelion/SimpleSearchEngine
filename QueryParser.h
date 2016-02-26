//
// Created by woodavid on 2016. 2. 25..
//

#ifndef QUERYPARSER_H
#define QUERYPARSER_H

#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include <algorithm>
#include "utils.h"


class QueryParser {

public:
    void setQuery(const std::string& query);
    bool isOperator(const std::string& str);
    bool isANDOperator(const std::string& str);
    bool isOROperator(const std::string& str);
    std::vector<std::string> getQueryTokens() const;

protected:
    std::vector<std::string> mQueryTokens;
};


#endif //QUERYPARSER_H
