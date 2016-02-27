
#ifndef __TERM_H__
#define __TERM_H__

#include <string>
#include <vector>

using namespace std;

class Term
{

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

protected:
    string mKeyword;
    int mFrequency;
    vector<int> mOffsets;

};

#endif //__TERM_H__
