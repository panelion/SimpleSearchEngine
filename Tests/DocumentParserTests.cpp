
#include <string>
#include "../src/SearchEngine.h"
#include "../src/DocumentParser.h"

void testReadFiles(std::shared_ptr<SearchEngine> engine)
{
    DocumentParser parser(engine);
    std::string testFilePath = "../data/test_document.txt";
    parser.addDocument(testFilePath);
}

int main()
{
    std::shared_ptr<SearchEngine> engine = std::make_shared<SearchEngine>();
    testReadFiles(engine);
}

