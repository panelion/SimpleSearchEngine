#ifndef __SEARCHENGINE_H__
#define __SEARCHENGINE_H__

#include <map>
#include <string>
#include <vector>
#include <set>
#include "Indexer.h"
#include "Document.h"
#include "QueryParser.h"
#include "Hits.h"


typedef std::vector<std::shared_ptr<Document>> DocumentsVectorPointer;


/******************************************************************************
 *
 * - SearchEngine
 *
 * 검색 엔진
 *
 * 1. Document 를 생성하고 관리하며, 생성된 Document 의 Index 를 생성한다.
 *  1) Document 객체를 생성한다.
 *  2) Document 의 contents 를 Tokenize 하여, Term 을 생성한다.
 *  3) 생성된 Term 을 Indexing 한다.
 *
 * 2. Indexing 된 정보를 이용하여 검색을 수행 한다. 검색은 다음과 같은 형식으로 구성된다
 *  1) QueryParser 를 이용하여, Text 형식의 Search Query 를 분석한다.
 *  2) 분석된 Query 를 reverse polish notation 형태로 변환한다.
 *  3) 분석된 Query 의 keyword 별, 검색을 수행한다.
 *  4) AND, OR 연산을 통해 검색 결과를 교집합 또는 합집합 한다.
 *  5) 최종 검색 결과의 키워드별 빈도수의 합을 구해, 그 값으로 내림차순 정렬한다.
 *  6) 검색 결과를 반환한다.
 *
 ******************************************************************************/

class SearchEngine
{

public:
    /**
     * Constructor
     */
    SearchEngine();

    /**
     * Destructor
     */
    ~SearchEngine();

    /**
     * Document 를 저장한다. 저장된 Document 객체를 토대로 Index 를 구성한다.
     *
     * @param uint64_t document 의 ID
     * @param string   document 의 내용
     */
    void addDocument(uint64_t documentId, const std::string& documentContents);

    /**
     * 검색어를 입력 받아 결과를 조회 한다
     *
     * @param string query string
     *
     * @return vector<uint64_t> 검색 결과의 document ID 의 목록을 반환한다.
     */
    std::vector<Hits> search(const std::string& query);

protected:
    std::map<uint64_t, std::shared_ptr<Document>> mDocumentsMap;
    Indexer mIndexer;
    QueryParser mQueryParser;

    /**
     * Keyword 를 기반으로 Indexing 한다
     *
     * @param string Keyword
     * @param shared_ptr<Document> Document 의 Pointer.
     */
    void Indexing(const std::string& keyword, const std::shared_ptr<Document> document);

    /**
     * 두 개의 Document 목록을 비교하여, 교집합 한다
     *
     * @param DocumentsVectorPointer Document Pointer 의 목록
     * @param DocumentsVectorPointer 비교될 Document Pointer 의 목록
     *
     * @return 교집합된 Document 의 목록.
     */
    DocumentsVectorPointer conjunct(const DocumentsVectorPointer& documents,
                                    const DocumentsVectorPointer& compareDocuments);

    /**
     * 두 개의 Document 목록을 비교하여, 합집합 한다
     *
     * @param DocumentsVectorPointer Document Pointer 의 목록
     * @param DocumentsVectorPointer 비교될 Document Pointer 의 목록
     *
     * @return 합집합된 Document 의 목록.
     */
    DocumentsVectorPointer disjunct(const DocumentsVectorPointer& documents,
                                    const DocumentsVectorPointer& compareDocuments);


    /**
     * 검색 결과 Document 정보의 검색 키워드의 빈도수 합을 이용하여 내림차순으로 정렬한다
     *
     * @param DocumentsVectorPointer Document Pointer 의 목록
     * @param DocumentsVectorPointer 결과 값이 존재하는 검색 Keyword.
     *
     * @return Hits 정렬된 검색 결과의 목록.
     */
    std::vector<Hits> sorting(const DocumentsVectorPointer& resultDocuments,
                              const std::set<std::string>& keywords);
};

#endif //__SEARCHENGINE_H__
