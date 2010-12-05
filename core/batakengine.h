#ifndef BATAKENGINE_H
#define BATAKENGINE_H

#include "gameengine.h"

class QObject;
class Player;
class State;

class BatakEngine : public GameEngine
{
public:
    BatakEngine(int playerNumber, QObject *parent = 0);
    bool checkState(Player *player, State *state);
};

#endif // BATAKENGINE_H
