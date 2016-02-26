
#include "Indexer.h"

void Indexer::insertKeyword(const std::string &keyword, uint64_t documentId)
{
    auto findIterator = mIndexStore.find(keyword);

    if (findIterator != mIndexStore.end())
    {
        findIterator->second.push_back(documentId);
        sort(findIterator->second.begin(), findIterator->second.end());
    }
    else
    {
        std::vector<uint64_t> values = { documentId };
        mIndexStore.insert(std::make_pair(keyword, values));
    }
}

bool Indexer::search(const std::string &keyword)
{
    mResultValues.clear();

    auto mapIterator = mIndexStore.find(keyword);

    if (mapIterator != mIndexStore.end())
    {
        mResultValues = mapIterator->second;
        return true;
    }

    return false;
}

std::vector<uint64_t> Indexer::getResult() const
{
    return mResultValues;
}