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
    void pisti();
    QToolButton* createButton(Card *);
    QString getButtonPngName(QToolButton *);
    const QList<Card *> & getCards();
    int getNumberOfOnlinePlayer() const;
    Person* getPlayers();

    void dummyStart();

private:
    QList<Card *> playedCards;
    QList<Card *> cards;

    QMap<Card *, QString> pngMapping; // unused
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
