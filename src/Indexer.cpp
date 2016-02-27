
#include "Indexer.h"

void Indexer::insertKeyword(const std::string &keyword, std::shared_ptr<Document> document)
{
    auto findIterator = mIndexStore.find(keyword);

    if (findIterator != mIndexStore.end())
    {
        findIterator->second.push_back(document);
        sort(findIterator->second.begin(), findIterator->second.end());
    }
    else
    {
        std::vector<std::shared_ptr<Document>> values = { document };
        mIndexStore.insert(std::make_pair(keyword, values));
    }
}

DocumentsVectorPointer Indexer::search(const std::string &keyword)
{
    auto mapIterator = mIndexStore.find(keyword);

    if (mapIterator != mIndexStore.end())
    {
        return mapIterator->second;
    }

    return DocumentsVectorPointer();
}