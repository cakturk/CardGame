#include "pistiengine.h"

PistiEngine::PistiEngine(QObject *parent) :
        GameEngine(parent)
{ }

PistiEngine::PistiEngine(int playerNum, QObject *parent) :
        GameEngine(playerNum, parent)
{ }

PistiEngine::~PistiEngine()
{ }

void PistiEngine::checkState(State &state)
{
    CardSequence seq = state.cardsOnBoard();
    Card *last, *nextToLast;

    if (seq.size() > 1) {
        last = seq.first();
        nextToLast = seq.at(seq.size() - 1);

        if (last->equals(nextToLast)) {
            if (seq.size() == 2) {
                // TODO: pisti sayacini bir artir.
            }
        }

    } else {
    }
}
