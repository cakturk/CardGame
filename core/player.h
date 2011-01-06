#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QDebug>
#include <QToolButton>
#include <QList>
#include <QTcpSocket>
#include "card.h"
#include "core/cardsequence.h"

class CardSequence;
class State;
class Player : public QObject
{
    Q_OBJECT

public:
    explicit Player(int r_pos = 0, QObject *parent = 0);
    explicit Player(QString name, int pos = 0, QObject *parent = 0);
    ~Player();

    inline int handSize() { return hand.size(); }
    int getNumberOfCards() const;
    void setHand(CardSequence &rhs);
    void collectCards(QList<Card *> &c);
    void collectCards(CardSequence sequence);
    virtual void reset();

    virtual void computeScore() = 0;
    virtual Card* play(int index);
    virtual Card* dummyPlay(Card* lastPlayedCard);
    virtual Card* dummyPlay(State &state) = 0;
    Card* play(QObject *);
    Card* play(Card* lastPlayedCard);

    const QList<Card *> &getScoredCards();
    CardSequence & getHand();
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

    int score;
    int pistiCount;

protected:
    CardSequence hand;
    CardSequence m_scoredCards;
    QList<Card *> playedCards_;
    QList<Card *> cardsOnTable;
    QList<Card *> scoredCards;

    CardSequence *m_hand;
    State *state;

private:
    QString playerName;
    QTcpSocket *sock;

    int realPosition;
    bool turn;
    bool _myself;

    virtual bool isAcceptable(const Card *c) const;
};

#endif // PLAYER_H
