
#include "Utils.h"


std::vector<std::string> Utils::Tokenize(const std::string& str)
{
    /**
     * 공백을 기준으로 query 문자열을 분리하여 vector 에 저장한다.
     */
    std::vector<std::string> tokens;
    std::string temp;
    istringstream iss(str);

    while (!iss.eof())
    {
        iss >> temp;
        tokens.push_back(temp);
    }

    return tokens;
}


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

    return temp;
}


std::string Utils::ToLowerCase(const std::string& str)
{
    std::string data = str;
    std::transform(data.begin(), data.end(), data.begin(), ::tolower);

    return data;
}
