#ifndef BATAKENGINE_H
#define BATAKENGINE_H

#include "gameengine.h"

class QObject;
class Player;
class State;

class BatakEngine : public GameEngine
{
public:
    explicit BatakEngine(QObject *parent = 0);
    explicit BatakEngine(int playerNumber, QObject *parent = 0);
    ~BatakEngine();

};

#endif // BATAKENGINE_H
