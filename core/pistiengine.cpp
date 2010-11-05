#include "pistiengine.h"

PistiEngine::PistiEngine(int playerNumber, QObject *parent) :
        GameEngine(playerNumber, parent)
{
}

bool PistiEngine::checkState(Player *player)
{
    currentPlayer = player;

    if (cards_on_table.size() < 2)
        return false;

    Card *currentCard = cards_on_table.at(cards_on_table.size() -1);
    Card *lastPlayedCard = cards_on_table.at(cards_on_table.size() -2);
    bool retVal = false;

    if (currentCard->equals(lastPlayedCard)) {
        if (cards_on_table.size() == 2) {
            currentPlayer->pistiCount++;
        }

        lastWinner = currentPlayer;
        retVal = true;
    } else if (currentCard->value == 11) {
        lastWinner = currentPlayer;
        retVal = true;
    }

    return retVal;
}
