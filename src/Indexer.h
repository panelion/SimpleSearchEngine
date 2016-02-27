#ifndef __INDEXER_H__
#define __INDEXER_H__

#include <string>
#include <map>
#include <vector>
#include "Document.h"

/******************************************************************************
 *
 * - Indexer
 *
 * Map<string, vector<uint64_t> 의 형식의 Index Store 자료 구조에
 * 검색 단어를 Key 로 하고, 해당 단어를 가진 Document 들의 ID 값을 Value 로 저장한다.
 *
 * 검색시에는 질의 요청 단어를 Index Store 에 해당 Key 로 가진지 여부를 조회한다.
 *
 * 조회 성공시, 해당 Key 가 가진 Value 즉, Document ID 의 목록을 반환한다.
 *
 *
 ******************************************************************************/
class Indexer
{

public:
    /**
     * Keyword 를 Key 로 하여, document ID 값을 Indexing 한다
     *
     * @param string    Keyword
     * @param uint64_t  document 의 ID 값
     */
    void insertKeyword(const std::string &keyword, uint64_t documentId);

    /**
     * Indexing data 에 질의한 keyword 를 이용하여 검색한다
     *
     * @param string    조회 Keyword
     *
     * @return bool     true: 검색 결과 존재, false: 검색 결과 존재 안함
     */
    bool search(const std::string &keyword);

    /**
     * 검색의 결과 값을 반환한다
     *
     * @return vector<uint64_t> document ids.
     */
    std::vector<uint64_t> getResult() const;

protected:
    std::map<std::string, std::vector<uint64_t>> mIndexStore;
    std::vector<uint64_t> mResultValues;
};


#endif //__INDEXER_H__
