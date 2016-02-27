
#include "Document.h"


Document::Document(uint64_t id, std::string contents): mId(id), mContents(contents)
{
    createTerm();
}

Document::~Document()
{

}

uint64_t Document::getId() const
{
    return mId;
}

std::string Document::getContents() const
{
    return mContents;
}

void Document::createTerm()
{
    // 특수 문자 및 개행 문자 등을 제거 한다
    std::string clearContents = Utils::RemoveSpecialCharacter(getContents());

    // Tokenize
    std::vector<std::string> keywords = Utils::Tokenize(clearContents);

    for (int i = 0; i < keywords.size(); i++)
    {
        std::string keyword = keywords[i];

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

            // 위치 정보를 추가 한다.
            mapIterator->second.addOffset(i);
        }
    }
}

const Term* Document::getTerm(const std::string& keyword) const
{
    auto mapIterator = mTermsMap.find(keyword);

    if (mapIterator == mTermsMap.end())
    {
        return nullptr;
    }

    return &(mapIterator->second);
}

const std::map<std::string, Term>* Document::getTerms() const
{
    return &mTermsMap;
}

bool Document::operator==(const Document& compareDocument) const
{
    if (*this == compareDocument)
    {
        return true;
    }

    return getId() == compareDocument.getId();
}

bool Document::operator>(const Document& compareDocument) const
{
    if (*this == compareDocument)
    {
        return false;
    }

    return getId() > compareDocument.getId();
}

bool Document::operator<(const Document& compareDocument) const
{
    if (*this == compareDocument)
    {
        return false;
    }

    return getId() < compareDocument.getId();
}

int Document::getSumFrequencyByKeywords(std::set<std::string> keywords)
{
    int sumFrequency = 0;

    for (auto keyword : keywords)
    {
        const Term* term = getTerm(keyword);

        if (term != nullptr)
        {
            sumFrequency += term->getFrequency();
        }
    }

    return sumFrequency;
}