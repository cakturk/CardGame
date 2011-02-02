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

private:
    Card* winingCard() const;
    Player *winingPlayer(Card *card) const;

    QMap<Card *, Player *> map;
};

#endif // BATAKENGINE_H
