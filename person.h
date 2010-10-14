#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QDebug>
#include <QToolButton>
#include <QList>
#include <QTcpSocket>
#include "card.h"

class Person : public QObject
{
    Q_OBJECT

public:
    explicit Person(int r_pos = 0, QObject *parent = 0);
    explicit Person(QString name, int pos = 0, QObject *parent = 0);
    ~Person();

    void setHand(QList<Card *> &h);
    void collectCards(QList<Card *> &c);
    void reset();
    void computePlayerScore();
    int getNumberOfCards() const;
    const QList<Card *> &getScoredCards();
    QList<Card *> & getHand();
    Card* play(int index);
    Card* play(Card* lastPlayedCard);
    Card* dummyPlay(Card* lastPlayedCard);
    void setTurn(bool b);

    inline void setPlayerName(QString name) { this->playerName = name; }
    inline QString getPlayerName() const { return this->playerName; }
    inline void setPosition(int pos) { realPosition = pos; }
    inline int getPosition() const { return realPosition; }
    inline QTcpSocket* getSocket() const { return sock; }
    inline void setSocket(QTcpSocket* s) { sock = s; }
    inline bool myself() const { return _myself; }
    inline void setMyself(bool b) { _myself = b; }
    inline bool isMyTurn() const { return turn; }

    int pistiCount;
    int score;

signals:

public slots:

private:
    QList<Card *> hand;
    QList<Card *> scoredCards;
    QString playerName;
    QTcpSocket *sock;

    int realPosition;
    bool turn;
    bool _myself;

    virtual bool isAcceptable(Card *c);
};

#endif // PERSON_H
