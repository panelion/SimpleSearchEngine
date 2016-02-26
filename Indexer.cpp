//
// Created by woodavid on 2016. 2. 23..
//

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

        // Keyword 에 내제된 특수문자들을 제거 후, 소문자로 통일한다
        string cleanKeyword = Utils::RemoveSpecialCharacter(keyword);

        mIndexStore.insert(std::make_pair(cleanKeyword, values));
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