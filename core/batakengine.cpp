#include "gameengine.h"
#include "batakengine.h"
#include "state.h"

BatakEngine::BatakEngine(QObject *parent) :
        GameEngine(parent)
{ }

BatakEngine::BatakEngine(int playerNum, QObject *parent) :
        GameEngine(playerNum, parent)
{ }

BatakEngine::~BatakEngine()
{ }

void BatakEngine::checkState(State &)
{
}
