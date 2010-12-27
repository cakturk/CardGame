#ifndef PISTIENGINE_H
#define PISTIENGINE_H

#include "gameengine.h"

class PistiEngine : public GameEngine
{
public:
    explicit PistiEngine(QObject *parent = 0);
    explicit PistiEngine(int playerNum, QObject *parent = 0);
    ~PistiEngine();

    void checkState(State &state);
};

#endif // PISTIENGINE_H
