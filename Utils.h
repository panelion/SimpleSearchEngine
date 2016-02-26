//
// Created by woodavid on 2016. 2. 26..
//

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

using namespace std;

class Utils {

public:
    static void Tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters);
    static std::string ReplaceAll(const std::string &str, const std::string &pattern, const std::string &replace);
    static std::string RemoveSpecialCharacter(const std::string& str);
    static std::string ToLowerCase(const std::string& str);
};


#endif //UTILS_H
