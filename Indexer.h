#ifndef INDEXER_H
#define INDEXER_H

#include <string>
#include <map>
#include <vector>
#include "Document.h"

class Indexer {

public:
    void insertKeyword(const std::string &keyword, uint64_t documentId);
    bool search(const std::string &keyword);
    std::vector<uint64_t> getResult() const;

protected:
    std::map<std::string, std::vector<uint64_t>> mIndexStore;
    std::vector<uint64_t> mResultValues;
};


#endif //INDEXER_H
