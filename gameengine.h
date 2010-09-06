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

    void createCards();
    void distributeCards(int number);
    void distributeCards(Person &p, int number);
    bool pisti();
    bool pisti(bool);
    QToolButton* createButton(Card *);
    QString getButtonPngName(QToolButton *);
    QList<Card *> & getCards();
    int getNumberOfOnlinePlayer() const;
    Person* getPlayers();

    void dummyStart();
    void start();
    void appendToPlayedCards(Card *);
    Card* lastPlayedCard();

private:
    QList<Card *> playedCards;
    QList<Card *> cards;

    QMap<QToolButton *, Card *> buttonMapping;

    // TODO: o an bagli olan oyuncu sayisini tutsun
    int numberOfOnlinePlayer;
    Person players[4];
    Person *currentPlayer, *lastWinner;
    QWidget *guiHandle;

    bool cardsEquals(Card *first, Card *sec);
    void computePlayerScore(Person *player);
    void startGameSession();

signals:

public slots:

};

#endif // GAMEENGINE_H
