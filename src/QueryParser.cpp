
#include "QueryParser.h"


void QueryParser::setQuery(const std::string& query)
{
    std::string cloneQuery = query;

    /**
     * '(', ')' 가 문자열과 붙어 있는 경우, (ex> (this is test) ) 의 분리를 위해 공백을 추가한다
     */
    cloneQuery = Utils::ReplaceAll(cloneQuery, "(", " ( ");
    cloneQuery = Utils::ReplaceAll(cloneQuery, ")", " ) ");

    // Tokenize using ' '
    std::vector<std::string> tokens = Utils::Tokenize(cloneQuery);
    mQueryTokens.clear();

    /**
     * reverse polish notation (https://en.wikipedia.org/wiki/Reverse_Polish_notation) 을 이용,
     * 다음과 같은 형태로 연산을 변환한다.
     *
     * ex> A OR ( B AND C ) -> B C AND A OR
     */
    std::stack<std::string> stackToken;

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
        else if (isOperator(tokens[i]))
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

//    for (auto token : mQueryTokens)
//    {
//        std::cout << "Query token : " << token << " ";
//    }
//
//    std::cout << std::endl;
}

std::vector<std::string> QueryParser::getQueryTokens() const
{
    return mQueryTokens;
}

bool QueryParser::isOperator(const std::string& token)
{
    return isANDOperator(token) || isOROperator(token);
}

bool QueryParser::isANDOperator(const std::string& token)
{
    return token == "AND";
}

bool QueryParser::isOROperator(const std::string& token)
{
    return token == "OR";
}