//
// Created by woodavid on 2016. 2. 25..
//

#include "QueryParser.h"


void QueryParser::setQuery(const std::string& query)
{
    std::string cloneQuery = query;

    cloneQuery = Utils::ReplaceAll(cloneQuery, "(", " ( ");
    cloneQuery = Utils::ReplaceAll(cloneQuery, ")", " ) ");

    istringstream iss(cloneQuery);
    vector<string> tokens;

    string temp;
    while (!iss.eof())
    {
        iss >> temp;
        tokens.push_back(temp);
    }

    mQueryTokens.clear();
    stack<string> stackToken;

    for (int i = 0; i < tokens.size(); i++)
    {
        if (tokens[i] == "(")
        {
            stackToken.push(tokens[i]);
        }
        else if (tokens[i] == ")")
        {
            while (!stackToken.empty() && stackToken.top() != "(")
            {
                mQueryTokens.push_back(stackToken.top());
                stackToken.pop();
            }
            stackToken.pop();
        }
        else if (tokens[i] == "AND" || tokens[i] == "OR")
        {
            while (!stackToken.empty() && stackToken.top() != "(")
            {
                mQueryTokens.push_back(stackToken.top());
                stackToken.pop();
            }
            stackToken.push(tokens[i]);
        }
        else
        {
            // Lower case.
            std::string data = Utils::ToLowerCase(tokens[i]);
            mQueryTokens.push_back(data);
        }
    }

    while(!stackToken.empty())
    {
        mQueryTokens.push_back(stackToken.top());
        stackToken.pop();
    }
}

std::vector<std::string> QueryParser::getQueryTokens() const
{
    return mQueryTokens;
}

bool QueryParser::isOperator(const std::string &str)
{
    return isANDOperator(str) || isOROperator(str);
}

bool QueryParser::isANDOperator(const std::string& str)
{
    return str == "AND";
}

bool QueryParser::isOROperator(const std::string& str)
{
    return str == "OR";
}