
#include "Hits.h"


Hits::Hits(int score, std::shared_ptr<Document> document): mScore(score), mDocument(document)
{

}

int Hits::getScore() const
{
    return mScore;
}

std::shared_ptr<Document> Hits::getDocument() const
{
    return mDocument;
}

bool Hits::scoreCompare(const Hits& hits, const Hits& compareHits)
{
    // std::cout << "hits.getScore() : " << hits.getScore() << endl;
    // std::cout << "compareHits.getScore() : " << compareHits.getScore() << endl << endl;
    return hits.getScore() > compareHits.getScore();
}

