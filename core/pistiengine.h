#ifndef PISTIENGINE_H
#define PISTIENGINE_H

#include "gameengine.h"

class PistiEngine : public GameEngine
{
public:
    PistiEngine(int playerNumber, QObject *parent = 0);
    bool checkState(Player *player);
};

#endif // PISTIENGINE_H
