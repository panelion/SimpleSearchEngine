//
// Created by woodavid on 2016. 2. 23..
//

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>
#include "Term.h"
#include "utils.h"


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
    Document();
    Document(uint64_t id, string contents);

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


    bool getTerm(const std::string& sTerm, Term*& returnTerm);

    /**
     * Document 의 Contents 로 부터 형태소 분석 된 단어의 목록을 반환한다.
     *
     * @return vector<Term> Term 객체의 목록
     */
    vector<Term>& getTerms();

protected:
    const std::string SEPARATOR = " ";
    uint64_t mId;
    std::string mContents;
    std::vector<Term> mTermsVector;

    void createTerm();
};

#endif //DOCUMENT_H
