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

    void setHand(QList<Card *> &h);
    void collectCards(QList<Card *> &c);
    const QList<Card *> &getScoredCards();
    QList<Card *> & getHand();
    void reset();
    int getNumberOfCards();
    Card* play(int index);

    void setPlayerName(QString name)
    {
        this->playerName = name;
    }

    QString getPlayerName()
    {
        return this->playerName;
    }

    void setTurn(bool b)
    {
        turn = b;
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
