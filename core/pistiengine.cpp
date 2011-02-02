#include "pistiengine.h"
#define MINIMUM_NUMBER_OF_CARDS 4

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

void PistiEngine::loopGame()
{
    /* loop until we find a real player */
    Player *currentPlayer;
    Card *card;

    for (currentPlayer = playerList_.nextPlayer();
    playerList_.currentPlayerPosition() != PlayerList::SOUTH;
    currentPlayer = playerList_.nextPlayer()) {

        if (currentPlayer->handSize() < 1 &&
            deckSize() >= (MINIMUM_NUMBER_OF_CARDS * playerList_.size())) {
            /* do something reasonable */
            distributeCards(MINIMUM_NUMBER_OF_CARDS);
        }

        if ((card = currentPlayer->dummyPlay(state)) != NULL) {
            state.append(card);
            if (wins()) {
                if (pisti())
                    currentPlayer->pistiCount++;
                currentPlayer->collectCards(state.cardsOnBoard());
                state.clearBoard();
            }
        }
    }
}

bool PistiEngine::pisti() const
{
    CardSequence seq = state.cardsOnBoard();
    Card *last, *nextToLast;

    if (seq.size() == 2) {
        last = seq.first();
        nextToLast = seq.at(seq.size() - 2);
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

    last = seq.last();
    nextToLast = seq.at(seq.size() - 2);

    if (last->value == nextToLast->value)
        return true;
    else if (last->value == 11)
        return true;
    else
        return false;
}

void PistiEngine::waitForPlayer()
{
}

void PistiEngine::cardClicked(Card *card)
{
    Player *currentPlayer = playerList_.currentPlayer();

    if (currentPlayer->handSize() < 1 &&
        deckSize() >= (MINIMUM_NUMBER_OF_CARDS * playerList_.size())) {
        /* do something reasonable */
        distributeCards(MINIMUM_NUMBER_OF_CARDS);
    }

    if (currentPlayer->getHand().isEmpty()) {
        qWarning() << "Error in PistiEngine::cardClicked method";
        qWarning() << "current player has no cards.";
        return;
    }

    Card *retVal = currentPlayer->play(card);
    state.append(retVal);
    if (wins()) {
        if (pisti())
            currentPlayer->pistiCount++;
        currentPlayer->collectCards(state.cardsOnBoard());
    }

    /* continue loop */
    loopGame();
}
