#ifndef __SEARCHENGINE_H__
#define __SEARCHENGINE_H__

#include <map>
#include <string>
#include <vector>
#include "Indexer.h"
#include "Document.h"
#include "QueryParser.h"

/**
 *
 */
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
    void addDocument(uint64_t documentId, const string& documentContents);

    /**
     * 검색어를 입력 받아 결과를 조회 한다
     *
     * @param string query string
     *
     * @return vector<uint64_t> 검색 결과의 document ID 의 목록을 반환한다.
     */
    std::vector<uint64_t> search(const string& query);

protected:
    map<uint64_t, Document> mDocumentsMap;
    Indexer mIndexer;
    QueryParser mQueryParser;

    vector<uint64_t> conjunct(vector<uint64_t> documentIds, vector<uint64_t> compareDocumentIds);
    vector<uint64_t> disjunct(vector<uint64_t> documentIds, vector<uint64_t> compareDocumentIds);
    vector<Document> getDocuments(vector<uint64_t>& documentIds);
};

#endif //__SEARCHENGINE_H__
