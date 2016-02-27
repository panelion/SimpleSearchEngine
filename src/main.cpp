#include <iostream>
#include "SearchEngine.h"
#include "DocumentParser.h"

using namespace std;


void run();

/**
 * Document 의 정보를 입력 받아 Indexing 하는 Command 를 수행한다.
 *
 * @param shared_ptr<SearchEngine> SearchEngine Pointer
 */
void commandInputDocument(shared_ptr<SearchEngine> engine);


/**
 * Document file path 를 받아 Document data 를 파싱하여 Indexing 하는 Command 를 수행한다.
 *
 * @param shared_ptr<DocumentParser> DocumentParser Pointer
 */
void commandInputDocumentFiles(shared_ptr<DocumentParser> documentParser);

/**
 * Query 를 입력 받아 검색을 수행한다
 *
 * @param shared_ptr<SearchEngine> SearchEngine Pointer
 */
void commandSearch(shared_ptr<SearchEngine> engine);


int main()
{
    run();
    return 0;
}

void run()
{
    std::shared_ptr<SearchEngine> engine = std::make_shared<SearchEngine>();
    std::shared_ptr<DocumentParser> documentParser = std::make_shared<DocumentParser>(engine);

    int commandNumber = 0;
    bool done = false;

    while(!done)
    {
        cout << endl << "=========================================================" << endl;
        cout << "1 Input document data manually." << endl;
        cout << "2 Input document data from file." << endl;
        cout << "3 Search." << endl;
        cout << "4 Quit." << endl;
        cout << endl << "=========================================================" << endl;

        cout << "Input your command number." << endl;
        cin >> commandNumber;
        cin.ignore();

        if (cin.good())
        {
            switch (commandNumber)
            {
                case 1:
                    commandInputDocument(engine);
                    break;
                case 2:
                    commandInputDocumentFiles(engine);
                    break;
                case 3:
                    commandSearch(engine);
                    break;
                case 4:
                    done = true;
                    break;
                default:
                    cout << "Wrong command. Please input correct command." << endl;
                    break;
            }

            cin.clear();
        }
        else
        {
            cout << "Wrong command. Please input correct command." << endl;
            cin.clear();
            cin.ignore();
        }
    }
}


void commandInputDocument(std::shared_ptr<SearchEngine> engine)
{
    uint64_t documentID = 0;
    string strDocumentID, documentContents;

    while (strDocumentID.empty() || documentContents.empty())
    {
        if (strDocumentID.empty())
        {
            cout << "Input Document ID : (Number) " << endl;

            while (getline(cin, strDocumentID))
            {
                std::stringstream ss(strDocumentID);

                if (ss >> documentID)
                {
                    if (ss.eof())
                    {
                        // Succeed
                        break;
                    }
                }

                std::cout << "You can input only number type. please retry : " << std::endl;
            }
        }

        if (documentContents.empty())
        {
            cout << "Input Document Contents : (string) " << endl;
            getline(cin, documentContents);
            cin.clear();
            cin.ignore();
        }
    }

    cout << "Indexing...." << endl;
    engine->addDocument(documentID, documentContents);
    cout << "Completed indexed." << endl;
}

void commandInputDocumentFiles(shared_ptr<DocumentParser> documentParser)
{
    string strDocumentFilePath;

    while (strDocumentFilePath.empty())
    {
        if (strDocumentFilePath.empty())
        {
            cout << "Input document file path: " << endl;
            getline(cin, strDocumentFilePath);
            cin.clear();
        }
    }

    documentParser->addDocument(strDocumentFilePath);
}


void commandSearch(shared_ptr<SearchEngine> engine)
{
    string query;

    while (query.empty())
    {
        if (query.empty())
        {
            cout << "Input Search Query : " << endl;
            getline(cin, query);
            cin.clear();
        }
    }

    cout << "===============Searching===============" << endl;

    std::vector<Hits> searchResult = engine->search(query);

    cout << "===============Completed===============" << endl << endl;

    if (searchResult.size() > 0)
    {
        cout << searchResult.size() << " Found(s)." << endl << endl;

        for (auto vectorIterator = searchResult.begin(); vectorIterator != searchResult.end(); ++vectorIterator)
        {
            cout << "Found Document ID : " << (*vectorIterator).getDocument()->getId() << " ";
            cout << "(Score : " << (*vectorIterator).getScore() << ")" << endl;
        }
    }
    else
    {
        cout << endl << "No Search Result(s)." << endl << endl;
    }
}