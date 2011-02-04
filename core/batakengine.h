#ifndef BATAKENGINE_H
#define BATAKENGINE_H

#include "gameengine.h"

class Player;
class State;

class BatakEngine : public GameEngine
{
    Q_OBJECT

public:
    explicit BatakEngine(QObject *parent = 0);
    explicit BatakEngine(int playerNumber, QObject *parent = 0);
    ~BatakEngine();

    void checkState(State &state);
    void loopGame();
    void startGame();
    void startNextRound();

private slots:
    void cardClicked(Card *card);

private:
    Card* winingCard() const;
    void handleRoundOver();
    bool isRoundOver();

    QMap<Card *, Player *> map;
};

#endif // BATAKENGINE_H
