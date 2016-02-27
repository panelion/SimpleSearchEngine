//
// Created by woodavid on 2016. 2. 26..
//

#ifndef __DOCUMENTPARSER_H__
#define __DOCUMENTPARSER_H__

#include <string>
#include <fstream>
#include <iostream>
#include "SearchEngine.h"


class DocumentParser {
public:

    /**
     * Constructor
     */
    DocumentParser(std::shared_ptr<SearchEngine> searchEngine);

    /**
     * Document file 경로에 존재하는 데이터를 읽어 Document 객체를 생성한다.
     *
     * @param string document file path
     */
    void addDocument(const std::string& documentFilePath);

protected:
        std::shared_ptr<SearchEngine> mSearchEngine;

};


#endif //__DOCUMENTPARSER_H__
