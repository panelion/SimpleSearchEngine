#include <iostream>
#include "SearchEngine.h"


using namespace std;


/**
 * Document 의 정보를 입력 받아 저장하는 Command 를 수행한다
 */
void CommandInputDocument(SearchEngine& engine);

/**
 * Query 를 입력 받아 검색을 수행한다
 */
void commandSearch(SearchEngine& engine);


int main() {

    SearchEngine engine = SearchEngine();

    int commandNumber = 0;
    bool done = false;

    while(!done)
    {
        cout << "===================" << endl;
        cout << "1 Input Document." << endl;
        cout << "2 Search." << endl;
        cout << "3 Quit." << endl;
        cout << "===================" << endl;

        cout << "Input your command number." << endl;
        cin >> commandNumber;
        cin.ignore();

        if (cin.good())
        {
            switch (commandNumber)
            {
                case 1:
                    CommandInputDocument(engine);
                    break;
                case 2:
                    commandSearch(engine);
                    break;
                case 3:
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

    return 0;
}


void CommandInputDocument(SearchEngine& engine)
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
    engine.addDocument(documentID, documentContents);
    cout << "Completed indexed." << endl;
}

void commandSearch(SearchEngine& engine)
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

    cout << "Searching...." << endl;

    std::vector<uint64_t> searchResult = engine.search(query);

    if (searchResult.size() > 0)
    {
        cout << searchResult.size() << " Found." << endl;

        for (auto vectorIterator = searchResult.begin(); vectorIterator != searchResult.end(); ++vectorIterator)
        {
            cout << "Found Document ID : " << *vectorIterator << endl;
        }
    }
    else
    {
        cout << endl << "No Search Results." << endl << endl;
    }

    cout << endl << "Completed search." << endl;
}