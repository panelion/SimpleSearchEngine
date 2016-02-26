//
// Created by woodavid on 2016. 2. 23..
//

#ifndef TERM_H
#define TERM_H

#include <string>
#include <vector>

using namespace std;

class Term
{
protected:
    string mKeyword;
    int mFrequency;
    vector<int> mOffsets;

public:
    Term(string keyword);
    Term(string keyword, int offset);
    string getKeyword() const;
    void increaseFrequency(int count);
    void setFrequency(int count);
    int getFrequency() const;
    vector<int> getOffsets() const;
    void setOffset(int offset);
    void addOffset(int offset);
};


#endif //TERM_H
