//
// Created by woodavid on 2016. 2. 24..
//

#include "SearchEngine.h"

SearchEngine::SearchEngine()
{
    mIndexer = Indexer();
    mQueryParser = QueryParser();
}

SearchEngine::~SearchEngine()
{

}

bool SearchEngine::addDocument(uint64_t documentId, const string& documentContents)
{
    auto mapIterator = mDocumentsMap.find(documentId);

    if (mapIterator == mDocumentsMap.end())
    {
        Document newDocument = Document(documentId, documentContents);

        // Save to Document Map.
        mDocumentsMap.insert(std::make_pair(newDocument.getId(), newDocument));

        // 새로이 생성된 Document 객체로 부터 Terms 를 받아 Indexing 한다
        std::vector<Term> terms = newDocument.getTerms();

        for (auto vectorIterator = terms.begin(); vectorIterator != terms.end(); ++vectorIterator)
        {
            Term term = *vectorIterator;
            mIndexer.insertKeyword(term.getKeyword(), newDocument.getId());
        }

        return true;
    }

    return false;
}

bool SearchEngine::search(const string& query) {

    // Query Parsing.
    mQueryParser.setQuery(query);
    std::vector<string> queryToken = mQueryParser.getQueryTokens();

    // 지난 결과 값을 초기화 한다
    mSearchResult.clear();

    std::stack<std::vector<uint64_t>> queryResultsStack;

    for (auto vectorIterator = queryToken.begin(); vectorIterator != queryToken.end(); ++vectorIterator)
    {
        if (mQueryParser.isANDOperator(*vectorIterator))
        {
            // AND
            std::vector<uint64_t> result1 = queryResultsStack.top();
            queryResultsStack.pop();

            while (!queryResultsStack.empty())
            {
                result1 = conjunct(result1, queryResultsStack.top());
                queryResultsStack.pop();
            }

            queryResultsStack.push(result1);
        }
        else if (mQueryParser.isOROperator(*vectorIterator))
        {
            // OR
            std::vector<uint64_t> result1 = queryResultsStack.top();
            queryResultsStack.pop();

            while (!queryResultsStack.empty())
            {
                result1 = disjunct(result1, queryResultsStack.top());
                queryResultsStack.pop();
            }

            queryResultsStack.push(result1);
        }
        else
        {
            if (mIndexer.search(*vectorIterator))
            {
                queryResultsStack.push(mIndexer.getResult());
            }
        }
    }

    // Stack 에 남아 있는 결과를 AND 연산을 이용하여 정리한다
    if (!queryResultsStack.empty())
    {
        std::vector<uint64_t> result1 = queryResultsStack.top();
        queryResultsStack.pop();

        while (!queryResultsStack.empty())
        {
            result1 = conjunct(result1, queryResultsStack.top());
            queryResultsStack.pop();
        }

        mSearchResult = result1;
    }

    // TODO: Sort Result.

    return mSearchResult.size() > 0;
}

std::vector<uint64_t> SearchEngine::getResult() const
{
    return mSearchResult;
}

vector<uint64_t> SearchEngine::conjunct(vector<uint64_t> documentIds, vector<uint64_t> compareDocumentIds)
{
    auto it1Begin = documentIds.begin(), it1End = documentIds.end();
    auto it2Begin = compareDocumentIds.begin(), it2End = compareDocumentIds.end();

    vector<uint64_t> result;

    while (it1Begin < it1End && it2Begin < it2End)
    {
        if (*it1Begin == *it2Begin)
        {
            result.push_back(*it1Begin);

            it1Begin++;
            it2Begin++;
        }
        else if (*it1Begin < *it2Begin)
        {
            it1Begin++;
        }
        else
        {
            it2Begin++;
        }
    }

    return result;
}

vector<uint64_t> SearchEngine::disjunct(vector<uint64_t> documentIds, vector<uint64_t> compareDocumentIds)
{
    auto it1Begin = documentIds.begin(), it1End = documentIds.end();
    auto it2Begin = compareDocumentIds.begin(), it2End = compareDocumentIds.end();

    vector<uint64_t> result;

    while (it1Begin < it1End && it2Begin < it2End)
    {
        if (*it1Begin == *it2Begin)
        {
            result.push_back(*it1Begin);

            it1Begin++;
            it2Begin++;
        }
        else if (*it1Begin < *it2Begin)
        {
            result.push_back(*it1Begin);
            it1Begin++;
        }
        else
        {
            result.push_back(*it2Begin);
            it2Begin++;
        }
    }

    while (it1Begin != it1End)
    {
        result.push_back(*it1Begin);
        it1Begin++;
    }

    while (it2Begin != it2End)
    {
        result.push_back(*it2Begin);
        it2Begin++;
    }

    return result;
}

vector<Document> SearchEngine::getDocuments(vector<uint64_t>& documentIds)
{
    std::vector<Document> returnDocuments;

    for (auto vectorIterator = documentIds.begin(); vectorIterator != documentIds.end(); ++vectorIterator)
    {
        auto mapIterator = mDocumentsMap.find(*vectorIterator);

        if (mapIterator != mDocumentsMap.end())
        {
            returnDocuments.push_back(mapIterator->second);
        }
    }

    return returnDocuments;
}