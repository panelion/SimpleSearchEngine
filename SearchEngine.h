//
// Created by woodavid on 2016. 2. 24..
//

#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <map>
#include <string>
#include <vector>
#include "Indexer.h"
#include "Document.h"
#include "QueryParser.h"

class SearchEngine {
public:
    SearchEngine();
    ~SearchEngine();
    bool addDocument(uint64_t, const string& documentContents);
    bool search(const string& query);
    std::vector<uint64_t> getResult() const;

protected:
    map<uint64_t, Document> mDocumentsMap;
    std::vector<uint64_t> mSearchResult;
    Indexer mIndexer;
    QueryParser mQueryParser;

    vector<uint64_t> conjunct(vector<uint64_t> documentIds, vector<uint64_t> compareDocumentIds);
    vector<uint64_t> disjunct(vector<uint64_t> documentIds, vector<uint64_t> compareDocumentIds);
    vector<Document> getDocuments(vector<uint64_t>& documentIds);
};

#endif //SEARCHENGINE_H
