#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QDebug>
#include <QToolButton>
#include <QList>
#include "card.h"

class Person : public QObject
{
    Q_OBJECT

public:
    explicit Person(QObject *parent = 0);
    explicit Person(QString name, QObject *parent = 0);

    void setHand(QList<Card *> &h);
    void collectCards(QList<Card *> &c);
    void reset();
    void computePlayerScore();
    int getNumberOfCards();
    const QList<Card *> &getScoredCards();
    QList<Card *> & getHand();
    Card* play(int index);
    Card* play(Card* lastPlayedCard);
    Card* dummyPlay(Card* lastPlayedCard);
    void setTurn(bool b);

    void setPlayerName(QString name)
    {
        this->playerName = name;
    }

    QString getPlayerName()
    {
        return this->playerName;
    }


    int pistiCount;
    int score;

signals:

public slots:

private:
    QList<Card *> hand;
    QList<Card *> scoredCards;
    QString playerName;
    bool turn;

    virtual bool isAcceptable(Card *c);

    bool isMyTurn()
    {
        return turn;
    }
};

#endif // PERSON_H
