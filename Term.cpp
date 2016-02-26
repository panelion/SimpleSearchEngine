
#include "Term.h"

Term::Term(string keyword)
{
    mKeyword = keyword;
    mFrequency = 1;
    mOffsets = {-1};
}

Term::Term(string keyword, int offset)
{
    mKeyword = keyword;
    mFrequency = 1;
    mOffsets = {offset};
}

string Term::getKeyword() const
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

vector<int> Term::getOffsets() const
{
    return mOffsets;
}

void Term::setOffset(int offset)
{
    mOffsets.clear();
    mOffsets.push_back(offset);
}

void Term::addOffset(int offset)
{
    mOffsets.push_back(offset);
}

