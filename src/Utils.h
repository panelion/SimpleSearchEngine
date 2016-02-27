#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Utils {

public:

    /**
     * 주어진 문자열에 대해 delimiters 를 이용하여 Vector<string> 형식으로 Tokenize 한다
     *
     * @param string: Tokenize 를 하기 위한 원본 문자열
     *
     * @return vector<string> Tokenize 된 Vector 객체
     *
     */
    static std::vector<std::string> Tokenize(const std::string& str);

    /**
     * 문자열에서 해당되는 Pattern 을 Replace 문자로 대체 한다
     *
     * @param string str: 문자열
     * @param string pattern: 문자열에서 치환해야할 문자
     * @param string replace: 치환해야할 부분의 대체 문자.
     *
     * @return string: 대체된 문자열
     */
    static std::string ReplaceAll(const std::string &str, const std::string &pattern, const std::string &replace);

    /**
     * 문자열에서 A-Z, a-z, 0-9, ' ' 을 제외한 나머지 문자를 제거한다
     * 제거시 A-Z 는 a-z 형식으로 변환한다
     *
     * @param string str: 문자열
     *
     * @return string: 대체된 문자열
     */
    static std::string RemoveSpecialCharacter(const std::string& str);

    /**
     * 문자열을 모두 소문자로 변환한다
     *
     * @param string str: 문자열
     *
     * @return string: 대체된 문자열
     */
    static std::string ToLowerCase(const std::string& str);
};


#endif //__UTILS_H__
