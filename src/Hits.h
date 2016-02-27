#ifndef __HITS_H__
#define __HITS_H__

#include "Document.h"

/******************************************************************************
 *
 * - Hits
 *
 * 검색 결과를 기록 하는 객체.
 *
 * 검색 결과의 Document 정보를 기록하며,
 * 해당 Document 의 키워드별 빈도수의 합을 Score 로 하여 기록한다.
 *
 ******************************************************************************/
class Hits {
public:
    /**
     * Constructor
     */
    Hits(int score, std::shared_ptr<Document> document);

    /**
     * Document 의 검색 결과 점수를 반환한다
     *
     * @return int score
     */
    int getScore() const;

    /**
     * Document 객체의 Pointer 를 반환한다.
     *
     * @return shared_ptr<Document> Document Pointer
     */
    std::shared_ptr<Document> getDocument() const;

    /**
     * 검색 결과의 score 를 기반으로 내림차순 정렬 한다
     *
     * @param Hits Hits Object
     * @param Hits 비교할 Hits Object
     *
     * @return bool 비교 결과
     */
    static bool scoreCompare(const Hits& hits, const Hits& compareHits);

protected:
    std::shared_ptr<Document> mDocument;
    int mScore;
};


#endif //__HITS_H__
