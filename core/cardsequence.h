#ifndef CARDSEQUENCE_H
#define CARDSEQUENCE_H

#include "core/card.h"
template <class T> class QList;

class CardSequence
{
public:
    CardSequence();
    CardSequence(const CardSequence &rhs);
    CardSequence & operator=(const CardSequence &rhs);

    void append(Card *card);
    bool remove(Card *card);
    void removeAt(int index);
    void clear();
    void sortCards();
    void shuffle();

    Card* takeFirst();
    Card* takeLast();
    Card* takeAt(int n);
    Card* take(Card *card);

    inline bool isEmpty() const { return cardSequence.isEmpty(); }
    inline QList<Card *> toQlist() const { return cardSequence; }
    inline Card* first() const { return cardSequence.first(); }
    inline Card* last() const { return cardSequence.last(); }
    inline Card* at(int index) { return cardSequence.at(index); }
    inline int size() const { return cardSequence.size(); }
    inline int karoCount() const { return karoCount_; }
    inline int kupaCount() const { return kupaCount_; }
    inline int sinekCount() const { return sinekCount_; }
    inline int macaCount() const { return macaCount_; }
    inline bool contains(Card *card) const { return cardSequence.contains(card); }
    inline bool isKozBroken() const { return hasMaca(); }
    int count(Card *card) const;

    Card* highestRankedCardFor(Card::Suit suit) const;
    Card* lowestRankedCardFor(Card::Suit suit) const;

    bool hasKaro() const;
    bool hasKupa() const;
    bool hasSinek() const;
    bool hasMaca() const;
    bool hasOtherThan(Card::Suit suit) const;
    bool hasOtherThan(int value) const;
    bool hasGreaterThan(int value) const;
    bool hasGreaterThan(Card *card) const;
    bool hasSuit(Card::Suit suit) const;

    CardSequence filterOut(Card::Suit suit) const;
    CardSequence filterOut(int value) const;
    CardSequence filterOutLessThan(Card *card) const;
    CardSequence filterBySuit(Card::Suit suit) const;
    CardSequence filterByValue(int value) const;

private:
    bool hasCard(Card *card) const;

    /* helper functions */
    void incSuitCount(Card::Suit suit);
    void decSuitCount(Card::Suit suit);
    int find(Card *card);

    QList<Card *> cardSequence;
    int karoCount_, kupaCount_, sinekCount_, macaCount_;
};

bool lessThan(Card *lhs, Card *rhs);

#endif // CARDSEQUENCE_H
