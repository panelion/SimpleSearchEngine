
#include "DocumentParser.h"


DocumentParser::DocumentParser(shared_ptr<SearchEngine> searchEngine) : mSearchEngine(searchEngine)
{

}


void DocumentParser::addDocument(const std::string& documentFilePath)
{
    std::ifstream readFileStream;
    readFileStream.open(documentFilePath);

    // Illegal file path
    if (!readFileStream.good())
    {
        // return false;
        std::cerr << "file not founds." << std::endl;
        return;
    }

    // Read file.
    std::string readData, startTag, endTag;
    std::string strDocumentID, strDocumentContents;

    while (!readFileStream.eof())
    {
        std::getline(readFileStream, readData, '<');
        std::getline(readFileStream, startTag, '>');
        std::getline(readFileStream, readData, '<');
        std::getline(readFileStream, endTag, '>');

        if (startTag == "id")
        {
            strDocumentID = readData;
        }
        else if (startTag == "contents")
        {
            strDocumentContents = readData;
        }

        if (!strDocumentID.empty() && !strDocumentContents.empty())
        {
            // convert string document id to uint64_t
            std::stringstream ss(strDocumentID);
            uint64_t documentID = 0;
            ss >> documentID;

            // Create Document Object.
            cout << "Indexing...." << endl;
            mSearchEngine->addDocument(documentID, strDocumentContents);
            cout << "Completed Indexed. Document ID : " << documentID << endl;

            strDocumentID.clear();
            strDocumentContents.clear();
        }

        startTag.clear();
        readData.clear();
        endTag.clear();
    }

    readFileStream.close();
}