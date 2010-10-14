#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include "card.h"
#include "person.h"

class GameEngine : public QObject
{
    Q_OBJECT

public:
    explicit GameEngine(QObject *parent = 0);
    explicit GameEngine(int playerNumber, QObject *parent = 0);
    explicit GameEngine(bool deneme, int num, QObject *parent = 0);

    void createCards();
    void distributeCards(int number);
    void distributeCards(Person &p, int number);
    void dummyStart();
    void start();
    void appendToPlayedCards(Card *);
    void add(Person *player, int pos = -1);
    void tAdd(Person *player, int pos = -1);
    void tAdd(int);

    inline void tSetMyself(bool b) { t_Myself = b;}
    inline Person** getTPlayers() { return tPlayers; }
    inline Person* toSouth() { tIndex = 0; return tPlayers[0]; }
    inline Person* toEast() { tIndex = 1; return tPlayers[1]; }
    inline Person* toNorth() { tIndex = 2; return tPlayers[2]; }
    inline Person* toWest() { tIndex = 3; return tPlayers[3]; }

    int getNumberOfPlayer() const;
    int playerIndex();
    int tSize();

    bool pisti();
    bool pisti(bool);
    bool pisti(Person *p);
    bool tGetMyself() {return t_Myself;}

    QList<Card *> & getCards();
    QList<Card *> & getPlayedCards();


    Person* getPlayers();
    Person* nextPlayer();
    Person* tNextPlayer();
    Person* myself();
    Person* getlastWinner() const;
    const Person* me() const;
    Person* at(int index);

    Card* lastPlayedCard();

private:
    QList<Card *> playedCards;
    QList<Card *> cards;
    QList<Person *> gamePlayers;
    QVector<Person *> vector;
    QListIterator<Person *> *it;

    // TODO: o an bagli olan oyuncu sayisini tutsun
    int numberOfPlayer;
    int size;
    int current_index;
    int increment;
    int tIndex;
    int tInc;
    bool t_Myself;

    Person players[4];
    Person *tPlayers[4];
    Person *currentPlayer, *lastWinner;
    Person *sPlayer, *nPlayer, *ePlayer, *wPlayer;

    bool cardsEquals(Card *first, Card *sec);
    void computePlayerScore(Person *player) const;
    void startGameSession();

signals:
	void ready();

public slots:

};

#endif // GAMEENGINE_H
