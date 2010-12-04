#ifndef CARDSEQUENCE_H
#define CARDSEQUENCE_H

#include "core/card.h"
template <class T> class QList;

class CardSequence
{
public:
    CardSequence();
    CardSequence(const CardSequence &rhs);

    void append(Card *card);
    bool remove(Card *card);
    void removeAt(int index);
    void clear();

    Card* takeFirst();
    Card* takeLast();
    Card* takeAt(int n);
    Card* take(Card *card);

    inline const QList<Card *> getSequence() const { return cardSequence; }
    inline const Card* first() const { return cardSequence.last(); }
    inline const Card* last() const { return cardSequence.first(); }
    inline const Card* at(int index) { return cardSequence.at(index); }
    inline int size() const { return cardSequence.size(); }
    inline int karoCount() const { return karoCount_; }
    inline int kupaCount() const { return kupaCount_; }
    inline int sinekCount() const { return sinekCount_; }
    inline int macaCount() const { return macaCount_; }
    inline bool contains(Card *card) const { return cardSequence.contains(card); }
    inline bool isKozBroken() const { return hasMaca(); }

    const Card* highestRankedCardFor(Card::Suit suit) const;
    const Card* lowestRankedCardFor(Card::Suit suit) const;

    bool hasKaro() const;
    bool hasKupa() const;
    bool hasSinek() const;
    bool hasMaca() const;
    bool hasOtherThan(Card::Suit suit) const;

private:
    bool hasSuit(Card::Suit suit) const;
    bool hasCard(Card *card) const;
    void sortCards();

    /* helper functions */
    void incSuitCount(Card::Suit suit);
    void decSuitCount(Card::Suit suit);
    int find(Card *card);

    QList<Card *> cardSequence;
    int karoCount_, kupaCount_, sinekCount_, macaCount_;
};

bool lessThan(Card *lhs, Card *rhs);

#endif // CARDSEQUENCE_H
