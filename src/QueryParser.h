
#ifndef __QUERYPARSER_H__
#define __QUERYPARSER_H__

#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Utils.h"


/******************************************************************************
 *
 * - QueryParser
 *
 * 검색을 위한 Query 를 Parsing 하여 Operator ( AND, OR )  및 검색 keyword 를 분석 한다
 *
 ******************************************************************************/
class QueryParser
{

public:

    /**
     * String 형태의 검색 Query 를 저장후, Token 형태로 저장한다.
     *
     * @param string 검색을 위한 Text 형식의 질의 구문.
     */
    void setQuery(const std::string& query);

    /**
     * 해당 Token 이 Operator 인지 여부를 판단한다
     *
     * @param string 비교 Token 값
     *
     * @return bool true: Operator (AND, OR) Token 이 맞음, false: OR Token 이 아님.
     */
    bool isOperator(const std::string& token);

    /**
     * 해당 Token 이 AND Operator 인지 여부를 판단한다
     *
     * @param string 비교 Token 값
     *
     * @return bool true: AND Token 이 맞음, false: OR Token 이 아님.
     */
    bool isANDOperator(const std::string& token);

    /**
     * 해당 Token 이 OR Operator 인지 여부를 판단한다
     *
     * @param string 비교 Token 값
     *
     * @return bool true: OR Token 이 맞음, false: OR Token 이 아님.
     */
    bool isOROperator(const std::string& token);

    /**
     * Query 로 부터 Parsing 된 Query Token 목록을 반환한다
     *
     * @return vector<string> Query Tokens
     */
    std::vector<std::string> getQueryTokens() const;

protected:
    std::vector<std::string> mQueryTokens;
};

#endif //__QUERYPARSER_H__
