//
// Created by woodavid on 2016. 2. 23..
//

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>
#include "Term.h"
#include "utils.h"


class Document
{
protected:
    const std::string SEPARATOR = " ";
    uint64_t mId;
    std::string mContents;
    std::vector<Term> mTermsVector;

    void createTerm();

public:
    Document();
    Document(uint64_t id, string contents);
    ~Document();

    uint64_t getId() const;
    std::string getContents() const;
    bool getTerm(const std::string& sTerm, Term*& returnTerm);
    vector<Term>& getTerms();
};

#endif //DOCUMENT_H
