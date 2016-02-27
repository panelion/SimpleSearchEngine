
#include "SearchEngine.h"


SearchEngine::SearchEngine(): mIndexer(), mQueryParser()
{

}

SearchEngine::~SearchEngine()
{

}

void SearchEngine::addDocument(uint64_t documentId, const std::string& documentContents)
{
    auto mapIterator = mDocumentsMap.find(documentId);

    if (mapIterator == mDocumentsMap.end())
    {
        // Document newDocument = Document(documentId, documentContents);
        std::shared_ptr<Document> newDocument = std::make_shared<Document>(documentId, documentContents);

        std::cout << "created document id : " << documentId << std::endl;

        // Save Document to Map.
        mDocumentsMap.insert(std::make_pair(newDocument->getId(), newDocument));

        // 새로 생성된 Document 객체로 부터 Terms 를 받아 Index 를 구현한다
        const std::map<std::string, Term>* termsMap = newDocument->getTerms();

        for (auto termsIterator = termsMap->begin(); termsIterator != termsMap->end(); ++termsIterator)
        {
            // Indexing
            Indexing(termsIterator->first, newDocument);
        }
    }
}

std::vector<Hits> SearchEngine::search(const std::string &query)
{
    // 질의어를 분석 하여 reverse polish notation 형태로 만든다.
    mQueryParser.setQuery(query);
    std::vector<std::string> queryToken = mQueryParser.getQueryTokens();

    // search result.
    DocumentsVectorPointer searchResult;

    // 검색 결과 임시 저장 Stack
    std::stack<DocumentsVectorPointer> queryResultsStack;

    // 검색 Keyword 목록을 저장
    std::set<std::string> keywordsSet;

    for (auto vectorIterator = queryToken.begin(); vectorIterator != queryToken.end(); ++vectorIterator)
    {
        if (mQueryParser.isANDOperator(*vectorIterator))
        {
            // AND 연산인 경우, 지난 검색 결과들을 교집합 한다.
            DocumentsVectorPointer tempResult = queryResultsStack.top();
            queryResultsStack.pop();

            while (!queryResultsStack.empty())
            {
                tempResult = conjunct(tempResult, queryResultsStack.top());
                queryResultsStack.pop();
            }

            queryResultsStack.push(tempResult);
        }
        else if (mQueryParser.isOROperator(*vectorIterator))
        {
            // OR 연산인 경우, 지난 검색 결과들을 합집합 한다.
            DocumentsVectorPointer tempResult = queryResultsStack.top();
            queryResultsStack.pop();

            while (!queryResultsStack.empty())
            {
                tempResult = disjunct(tempResult, queryResultsStack.top());
                queryResultsStack.pop();
            }

            queryResultsStack.push(tempResult);
        }
        else
        {
            // Keyword 를 이용하여 Indexer 에서 검색 후, Stack 에 저장한다.
            DocumentsVectorPointer indexSearchResult = mIndexer.search(*vectorIterator);

            // 검색 결과 저장 (검색 결과가 없을 경우에도 저장한다)
            queryResultsStack.push(indexSearchResult);

            if (indexSearchResult.size() > 0)
            {
                // 검색 결과가 존재하는 Keyword 만을 저장한다.
                keywordsSet.insert(*vectorIterator);
            }
        }
    }

    // Stack 에 남아 있는 결과를 AND 연산을 이용하여 교집합 한다
    if (!queryResultsStack.empty())
    {
        DocumentsVectorPointer tempResult = queryResultsStack.top();
        queryResultsStack.pop();

        while (!queryResultsStack.empty())
        {
            tempResult = conjunct(tempResult, queryResultsStack.top());
            queryResultsStack.pop();
        }

        searchResult = tempResult;
    }

    // 검색 결과가 존재 한다면
    if (searchResult.size() > 0)
    {
        return sorting(searchResult, keywordsSet);
    }

    return std::vector<Hits>();
}

void SearchEngine::Indexing(const std::string& keyword, const std::shared_ptr<Document> document)
{
    mIndexer.insertKeyword(keyword, document);
}

DocumentsVectorPointer SearchEngine::conjunct(const DocumentsVectorPointer& documents,
                                              const DocumentsVectorPointer& compareDocuments)
{
    auto it1Begin = documents.begin(), it1End = documents.end();
    auto it2Begin = compareDocuments.begin(), it2End = compareDocuments.end();

    DocumentsVectorPointer result;

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

DocumentsVectorPointer SearchEngine::disjunct(const DocumentsVectorPointer& documents,
                                              const DocumentsVectorPointer& compareDocuments)
{
    auto it1Begin = documents.begin(), it1End = documents.end();
    auto it2Begin = compareDocuments.begin(), it2End = compareDocuments.end();

    DocumentsVectorPointer result;

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

std::vector<Hits> SearchEngine::sorting(const DocumentsVectorPointer& resultDocuments,
                                             const std::set<std::string>& keywords)
{
    std::vector<Hits> hitsVector;
    // 검색 키워드 별 빈도수를 Document 객체로 부터 조회하여 합산한다.
    for (auto vectorIterator = resultDocuments.begin(); vectorIterator != resultDocuments.end(); ++vectorIterator)
    {
        int sumFrequency = (*vectorIterator)->getSumFrequencyByKeywords(keywords);
        hitsVector.push_back(Hits(sumFrequency, *vectorIterator));
    }

    // 합산 결과값을 기준으로 sorting 한다. (내림차순)
    sort(hitsVector.begin(), hitsVector.end(), Hits::scoreCompare);

    return hitsVector;
}