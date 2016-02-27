#ifndef __INDEXER_H__
#define __INDEXER_H__

#include <string>
#include <map>
#include <vector>
#include "Document.h"

typedef std::vector<std::shared_ptr<Document>> DocumentsVectorPointer;

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
     * @param shared_ptr<Document> document pointer
     */
    void insertKeyword(const std::string &keyword, std::shared_ptr<Document> document);

    /**
     * Indexing data 에 Keyword 를 이용하여 해당 Keyword 의 데이터가 존재하는지 검색한다
     *
     * @param string    조회 Keyword
     *
     * @return std::vector<shared_ptr<Document>> 검색된 Document 객체의 목록
     */
    DocumentsVectorPointer search(const std::string &keyword);


protected:
    std::map<std::string, DocumentsVectorPointer> mIndexStore;
};


#endif //__INDEXER_H__
