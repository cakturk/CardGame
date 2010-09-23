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

    void createCards();
    void distributeCards(int number);
    void distributeCards(Person &p, int number);
    void dummyStart();
    void start();
    void appendToPlayedCards(Card *);

    int getNumberOfOnlinePlayer() const;
    int playerIndex();

    bool pisti();
    bool pisti(bool);
    bool pisti(Person *p);

    QToolButton* createButton(Card *);
    QString getButtonPngName(QToolButton *);

    QList<Card *> & getCards();
    QList<Card *> & getPlayedCards();


    Person* getPlayers();
    Person* nextPlayer();
    Person* myself();
    Person* getlastWinner() const;
    const Person* me() const;

    Card* lastPlayedCard();

private:
    QList<Card *> playedCards;
    QList<Card *> cards;
    QList<Person *> gamePlayers;
    QListIterator<Person *> *it;

    QMap<Card *, QToolButton *> buttonMapping;

    // TODO: o an bagli olan oyuncu sayisini tutsun
    int numberOfOnlinePlayer;
    int current_index;
    int increment;

    Person players[4];
    Person *currentPlayer, *lastWinner;
    Person *sPlayer, *nPlayer, *ePlayer, *wPlayer;

    bool cardsEquals(Card *first, Card *sec);
    void computePlayerScore(Person *player) const;
    void startGameSession();

signals:

public slots:

};

#endif // GAMEENGINE_H
