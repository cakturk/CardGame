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
    Player *currentPlayer;

    if (seq.size() > 1) {
        currentPlayer = playerList_.currentPlayer();
        last = seq.first();
        nextToLast = seq.at(seq.size() - 1);

        if (last->equals(nextToLast)) {
            if (seq.size() == 2) {
                currentPlayer->pistiCount++;
            }

            lastWinner = currentPlayer;
        }

    } else {
    }
}

bool PistiEngine::pisti() const
{
    CardSequence seq = state.cardsOnBoard();
    Card *last, *nextToLast;

    if (seq.size() == 2) {
        last = seq.first();
        nextToLast = seq.at(seq.size() - 1);
        return last->value == nextToLast->value;
    }

    return false;
}

bool PistiEngine::wins() const
{
    CardSequence seq = state.cardsOnBoard();
    Card *last, *nextToLast;

    if (seq.size() < 2)
        return false;

    last = seq.first();
    nextToLast = seq.at(seq.size() - 1);

    return last->value == nextToLast->value;
}
