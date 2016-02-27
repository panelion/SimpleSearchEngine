
#ifndef __DOCUMENT_H__
#define __DOCUMENT_H__

#include <string>
#include <vector>
#include <map>
#include <set>
#include "Term.h"
#include "Utils.h"


/******************************************************************************
 *
 * - Document
 *
 * 문서의 정보를 저장하는 객체
 *
 * 정수형으로 이루어진 Document ID 와 원본 내용을 저장한다.
 * 원본 내용에서 분석된 Term 목록을 가지고 있다.
 *
 ******************************************************************************/
class Document
{

public:
    /**
     * Constructor
     */
    Document(uint64_t id, std::string contents);

    /**
     * Destructor
     */
    ~Document();

    /**
     * Document 의 ID 값을 반환한다.
     *
     * @return uint64_t Document ID 값
     */
    uint64_t getId() const;

    /**
     * Document 의 내용을 반환한다
     *
     * @return string Document 의 내용
     */
    std::string getContents() const;

    /**
     * 해당 Keyword 를 이용하여 존재하는 Term 객체를 반환한다
     *
     * @param string Term 객체의 keyword
     *
     * @return vector<Term> Term 객체의 목록
     */
    const Term* getTerm(const std::string& keyword) const;

    /**
     * Document 의 Contents 로 부터 형태소 분석 된 단어의 목록을 반환한다.
     *
     * @return vector<Term> Term 객체의 목록
     */
    const std::map<std::string, Term>* getTerms() const;

    /**
     * operator 재정의
     */
    bool operator==(const Document& compareDocument) const;
    bool operator> (const Document& compareDocument) const;
    bool operator< (const Document& compareDocument) const;

    /**
     * Keyword 목록을 받아, 각각의 키워드 빈도수의 합을 구한다.
     *
     * @param set<string> keyword 의 목록
     *
     * @return 합산값.
     */
    int getSumFrequencyByKeywords(std::set<std::string> keywords);

protected:
    uint64_t mId;
    std::string mContents;
    std::map<std::string, Term> mTermsMap;

    void createTerm();
};

#endif //__DOCUMENT_H__
