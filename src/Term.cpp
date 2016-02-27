
#include "Term.h"

Term::Term(std::string keyword): mKeyword(keyword), mFrequency(1), mOffsets({-1})
{

}

Term::Term(std::string keyword, int offset): mKeyword(keyword), mFrequency(1), mOffsets({offset})
{

}

std::string Term::getKeyword() const
{
    return mKeyword;
}

void Term::increaseFrequency(int count)
{
    mFrequency += count;
}

void Term::setFrequency(int count)
{
    mFrequency = count;
}

int Term::getFrequency() const
{
    return mFrequency;
}

std::set<int> Term::getOffsets() const
{
    return mOffsets;
}

void Term::addOffset(int offset)
{
    mOffsets.insert(offset);
}

