
#include "SearchEngine.h"

SearchEngine::SearchEngine(): mIndexer(), mQueryParser()
{

}

SearchEngine::~SearchEngine()
{

}

void SearchEngine::addDocument(uint64_t documentId, const string& documentContents)
{
    auto mapIterator = mDocumentsMap.find(documentId);

    if (mapIterator == mDocumentsMap.end())
    {
        // TODO: Document Content 의 크기가 큰 경우, memory 에 부하가 생길 수 있으므로, 원본 데이터의 경우, 별도로 저장하는 것이 좋음.
        Document newDocument = Document(documentId, documentContents);

        std::cout << "created document id : " << documentId << std::endl;

        // Save Document to Map.
        mDocumentsMap.insert(std::make_pair(newDocument.getId(), newDocument));

        // 새로이 생성된 Document 객체로 부터 Terms 를 받아 Indexing 한다
        std::map<std::string, Term>* termsMap = newDocument.getTerms();

        for (auto termsIterator = termsMap->begin(); termsIterator != termsMap->end(); ++termsIterator)
        {
            // Term term = termsIterator->second;
            mIndexer.insertKeyword(termsIterator->first, newDocument.getId());
        }
    }
}

std::vector<uint64_t> SearchEngine::search(const string &query)
{
    // Query Parsing.
    mQueryParser.setQuery(query);
    std::vector<string> queryToken = mQueryParser.getQueryTokens();

    // search result.
    vector<uint64_t> searchResult;

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

        searchResult = result1;
    }

    // TODO: Sort Result.

    return searchResult;
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