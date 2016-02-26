
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

bool Document::getTerm(const string& sTerm, Term*& returnTerm)
{
    for (auto vectorIterator = mTermsVector.begin(); vectorIterator != mTermsVector.end(); ++vectorIterator)
    {
        if (vectorIterator->getKeyword() == sTerm)
        {
            returnTerm = &(*vectorIterator);
            return true;
        }
    }

    return false;
}

void Document::createTerm()
{
    vector<string> keywords;

    // 개행문자를 제거 한다
    std::string clearContents = Utils::ReplaceAll(getContents(), "\n", "");

    // Tokenize
    Utils::Tokenize(clearContents, keywords, SEPARATOR);

    for (int i = 0; i < keywords.size(); i++)
    {
        string keyword = keywords[i];

        Term* createdTerm = nullptr;

        if (!getTerm(keyword, createdTerm))
        {
            // 새로운 Term 을 생성한다
            mTermsVector.push_back(Term(keyword, i));
        }
        else
        {
            // 기존의 Term 의 Frequency 값을 1 증가한다.
            createdTerm->increaseFrequency(1);
        }
    }
}

vector<Term>& Document::getTerms()
{
    return mTermsVector;
}