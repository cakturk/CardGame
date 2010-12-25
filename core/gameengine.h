#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include "card.h"
#include "pistiplayer.h"
#include "core/cardsequence.h"
#include "core/playerlist.h"
#include "state.h"

class GameEngine : public QObject
{
    Q_OBJECT

public:
    explicit GameEngine(QObject *parent = 0);
    explicit GameEngine(int playerNum, QObject *parent = 0);
    ~GameEngine();

    void distributeCards(int number);
    void distributeCards(Player *player, int number);

private:
    CardSequence deck_;
    State state;
    PlayerList playerList_;

    void createCards();
#if 0
public:
    explicit GameEngine(QObject *parent = 0);
    explicit GameEngine(int playerNumber, QObject *parent = 0);
    explicit GameEngine(bool deneme, int num, QObject *parent = 0);
    ~GameEngine();

    void createCards();
    void distributeCards(int number);
    void distributeCards(Player &p, int number);
    void appendToPlayedCards(Card *);
    void add(Player *player, int pos = -1);
    void tAdd(Player *player, int pos = -1);
    void tAdd(int);

    inline void tSetMyself(bool b) { t_Myself = b;}
    inline Player** getTPlayers() { return tPlayers; }
    inline Player* toSouth() { tIndex = 0; return tPlayers[0]; }
    inline Player* toEast() { tIndex = 1; return tPlayers[1]; }
    inline Player* toNorth() { tIndex = 2; return tPlayers[2]; }
    inline Player* toWest() { tIndex = 3; return tPlayers[3]; }
    inline int numberOfCards() const { return cards.size(); }

    int getNumberOfPlayer() const;
    int playerIndex();
    int tSize();

    bool pisti();
    bool pisti(bool);
    bool pisti(Player *p);
    bool tGetMyself() { return t_Myself; }
    virtual bool checkRound(Player *player);

    QList<Card *> & getCards();
    QList<Card *> & cardsOnTable();
    const CardSequence & playedCards() const;

    Player* getPlayers();
    Player* nextPlayer();
    Player* tNextPlayer();
    Player* myself();
    Player* getlastWinner() const;
    const Player* me() const;
    Player* at(int index);
    Card* lastPlayedCard();

protected:
    QList<Card *> cards_on_table;
    Player *currentPlayer, *lastWinner;

private:
    CardSequence played_cards;
    QList<Card *> cards;
    QList<Player *> gamePlayers;
    QVector<Player *> vector;
    QListIterator<Player *> *it;

    // TODO: o an bagli olan oyuncu sayisini tutsun
    int numberOfPlayer;
    int size;
    int current_index;
    int increment;
    int tIndex;
    int tInc;
    bool t_Myself;

    // Player players[4];
    Player *tPlayers[4];
    Player *sPlayer, *nPlayer, *ePlayer, *wPlayer;

    bool cardsEquals(Card *first, Card *sec);
    void computePlayerScore(Player *player) const;

signals:
    void ready();
#endif
};

#endif // GAMEENGINE_H
