
#include "Document.h"

Document::Document()
{

}

Document::Document(uint64_t id, string contents)
{
    mId = id;
    mContents = contents;

    createTerm();
}

Document::~Document()
{

}

uint64_t Document::getId() const
{
    return mId;
}

string Document::getContents() const
{
    return mContents;
}

void Document::createTerm()
{
    // 특수 문자 및 개행 문자 등을 제거 한다
    std::string clearContents = Utils::RemoveSpecialCharacter(getContents());

    // Tokenize
    vector<string> keywords = Utils::Tokenize(clearContents);

    for (int i = 0; i < keywords.size(); i++)
    {
        string keyword = keywords[i];

        auto mapIterator = mTermsMap.find(keyword);

        if (mapIterator == mTermsMap.end())
        {
            // 새로운 Term 을 생성한다
            mTermsMap.insert(std::make_pair(keyword, Term(keyword)));
        }
        else
        {
            // 이미 존재하는 Term 이므로, 기존의 Term 의 Frequency 값을 1 증가한다.
            mapIterator->second.increaseFrequency(1);
        }
    }
}

Term* Document::getTerm(const string& keyword)
{
    auto mapIterator = mTermsMap.find(keyword);

    if (mapIterator == mTermsMap.end())
    {
        return nullptr;
    }

    return &(mapIterator->second);
}

std::map<std::string, Term>* Document::getTerms()
{
    return &mTermsMap;
}