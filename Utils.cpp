//
// Created by woodavid on 2016. 2. 26..
//

#include "Utils.h"
#include <iostream>


/**
 * 주어진 문자열에 대해 delimiters 를 이용하여 Vector<string> 형식으로 Tokenize 한다
 *
 * @param string: Tokenize 를 하기 위한 원본 문자열
 * @param vector<string>
 */
void Utils::Tokenize(const string& str, vector<string>& tokens, const string& delimiters)
{
    // delimiter 로 시작 하는 경우를 방지 한다
    string::size_type startPosition = str.find_first_not_of(delimiters, 0);
    string::size_type nextPosition = str.find_first_of(delimiters, startPosition);

    while (string::npos != nextPosition || string::npos != startPosition)
    {
        string word = str.substr(startPosition, nextPosition - startPosition);

        if (!word.empty() || word != "\n")
        {
            tokens.push_back(str.substr(startPosition, nextPosition - startPosition));
        }

        startPosition = str.find_first_not_of(delimiters, nextPosition);
        nextPosition = str.find_first_of(delimiters, startPosition);
    }
}


/**
 * 문자열에서 해당되는 Pattern 을 Replace 문자로 대체 한다
 *
 * @param string str: 문자열
 * @param string pattern: 문자열에서 치환해야할 문자
 * @param string replace: 치환해야할 부분의 대체 문자.
 *
 * @return string: 대체된 문자열
 */
string Utils::ReplaceAll(const string &str, const string &pattern, const string &replace)
{
    string result = str;
    string::size_type position = 0;
    string::size_type offset = 0;

    while((position = result.find(pattern, offset)) != string::npos)
    {
        result.replace(result.begin() + position, result.begin() + position + pattern.size(), replace);
        offset = position + replace.size();
    }

    return result;
}

std::string Utils::RemoveSpecialCharacter(const std::string &str)
{
    int i = 0;
    size_t strLength = str.length();
    string temp = str;

    while (i < strLength)
    {
        char c = temp[i];

        if (( c >= '0' && c <= '9')
            || (c >= 'A' && c <= 'Z')
            || (c >= 'a' && c <= 'z')
            || (c == ' '))
        {
            if (c>='A' && c<='Z')
            {
                // make lower case.
                temp[i] += 32;
            }
            ++i;
        }
        else
        {
            temp.erase((unsigned long)i, 1);
            --strLength;
        }
    }

    std::cout << temp << endl;

    return temp;
}

static std::string Utils::ToLowerCase(const std::string& str)
{
    std::string data = str;
    std::transform(data.begin(), data.end(), data.begin(), ::tolower);

    return data;
}
