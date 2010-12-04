#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QDebug>
#include <QToolButton>
#include <QList>
#include <QTcpSocket>
#include "card.h"
//#include "core/cardsequence.h"

class CardSequence;
class State;
class Player : public QObject
{
    Q_OBJECT

public:
    explicit Player(int r_pos = 0, QObject *parent = 0);
    explicit Player(QString name, int pos = 0, QObject *parent = 0);
    ~Player();

    int getNumberOfCards() const;
    void setHand(QList<Card *> &h);
    void collectCards(QList<Card *> &c);
    void reset();

    virtual void computeScore() = 0;
    virtual Card* play(int index);
    virtual Card* dummyPlay() = 0;
    virtual Card* dummyPlay(Card* lastPlayedCard);
    Card* play(QObject *);
    Card* play(Card* lastPlayedCard);

    const QList<Card *> &getScoredCards();
    QList<Card *> & getHand();
    void setTurn(bool b);

    inline QString getPlayerName() const { return this->playerName; }
    inline QTcpSocket* getSocket() const { return sock; }
    inline void setPlayerName(QString name) { this->playerName = name; }
    inline void setPosition(int pos) { realPosition = pos; }
    inline void setSocket(QTcpSocket* s) { sock = s; }
    inline void setMyself(bool b) { _myself = b; }
    inline bool myself() const { return _myself; }
    inline bool isMyTurn() const { return turn; }
    inline int getPosition() const { return realPosition; }
    inline int numberOfScoredCards() const { return scoredCards.size(); }
    inline void appendToPlayedCards(Card *card) { playedCards_.append(card); }
    inline const QList<Card *> playedCards() const { return playedCards_; }

    int pistiCount;
    int score;

protected:
    QList<Card *> hand;
    QList<Card *> playedCards_;
    QList<Card *> cardsOnTable;
    QList<Card *> scoredCards;

    CardSequence *m_hand;
    CardSequence *m_scoredCards;
    State *state;

private:
    QString playerName;
    QTcpSocket *sock;

    int realPosition;
    bool turn;
    bool _myself;

    virtual bool isAcceptable(Card *c);
};

#endif // PLAYER_H
