//
// Created by woodavid on 2016. 2. 26..
//

#ifndef __DOCUMENTPARSER_H__
#define __DOCUMENTPARSER_H__

#include <string>
#include <fstream>
#include <iostream>
#include "SearchEngine.h"


/******************************************************************************
 *
 * - DocumentParser
 *
 *
 * Text 파일 형식으로 기록된 Document 를 파싱한다.
 *
 * Document 는 다음과 같은 형식으로 이루어져 있다라 가정한다.
 *
 * <id>1</id>
 * <contents>this is test</contents>
 *
 * 하나의 파일에는 여러개의 document 가 위와 같은 형식으로 구성되어 있는것으로 가정한다.
 * Parsing 된 데이터를 이용하여, Document 객체를 생성한다.
 *
 ******************************************************************************/

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
