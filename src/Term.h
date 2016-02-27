
#ifndef __TERM_H__
#define __TERM_H__

#include <string>
#include <vector>
#include <set>


/******************************************************************************
 *
 * - Term
 *
 * Keyword 의 정보를 관리 하는 객체.
 *
 ******************************************************************************/

class Term
{

public:
    /**
     * Constructor
     */
    Term(std::string keyword);
    Term(std::string keyword, int offset);

    /**
     * 키워드를 반환한다
     *
     * @return string Keyword
     */
    std::string getKeyword() const;

    /**
     * 문서내에 키워드 발생 빈도수를 count 만큼 증가시킨다.
     *
     * @param int 증가할 빈도수의 값
     */
    void increaseFrequency(int count);

    /**
     * 문서내에 키워드 발생 빈도수를 설정 한다.
     *
     * @param int 문서내에 키워드 발생 빈도수의 값을 설정한다.
     */
    void setFrequency(int count);

    /**
     * 문서내에 키워드 발생 빈도수를 반환 한다.
     *
     * @return int 문서내에 키워드 발생 빈도수의 값
     */
    int getFrequency() const;

    /**
     * 문서내에 Keyword 의 위치 정보를 반환한다
     *
     * @return set<int> 위치 정보 목록
     */
    std::set<int> getOffsets() const;

    /**
     * 문서내에 Keyword 의 위차 정보를 추가한다.
     *
     * @param int 위치 정보.
     */
    void addOffset(int offset);

protected:
    std::string mKeyword;
    int mFrequency;
    std::set<int> mOffsets;

};

#endif //__TERM_H__
