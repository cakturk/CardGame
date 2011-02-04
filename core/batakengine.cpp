#include "gameengine.h"
#include "batakengine.h"
#include "state.h"
#define MINIMUM_NUMBER_OF_CARDS 13

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

void BatakEngine::loopGame()
{
    Player *currentPlayer;
    Card *card;

    for (currentPlayer = playerList_.nextPlayer();
    /*playerList_.currentPlayerPosition() != PlayerList::SOUTH*/;
    currentPlayer = playerList_.nextPlayer()) {

        if ((card = currentPlayer->dummyPlay(state)) != NULL) {
            state.append(card);
            map[card] = currentPlayer;
            emit cardPlayed(playerList_.currentPlayerPosition(), card);

            if (state.sizeofCardsOnBoard() == 4) {
                Card *wCard = winingCard();
                Player *wPlayer = map[wCard];
                map.clear();
                wPlayer->score++;
                state.clearBoard();
                emit clearBoard();
            }
        }

        if (isRoundOver()) {
            handleRoundOver();
            break;
        }
    }
}

Card* BatakEngine::winingCard() const
{
    CardSequence seq = state.cardsOnBoard();
    CardSequence tmp;
    Card *leadingCard, *highestRankedCard;

    if (seq.size() < 4)
        return false;

    leadingCard = seq.first();

    if (seq.hasMaca()) {
        tmp = seq.filterBySuit(Card::MACA);
        tmp.sortCards();
        highestRankedCard = tmp.last();
    } else {
        tmp = seq.filterBySuit(leadingCard->suit);
        if (!tmp.isEmpty()) {
            tmp.sortCards();
            highestRankedCard = tmp.last();
        }
    }

    return highestRankedCard;
}

void BatakEngine::startGame()
{
    distributeCards(MINIMUM_NUMBER_OF_CARDS);
    Player *player;
    for (int i = 0; i < playerList_.size(); ++i) {
        player = playerList_.nextPlayer();
        player->makeBidDecision();
    }

    loopGame();
}

void BatakEngine::startNextRound()
{
    Player *player;

    resetDeck();
    distributeCards(MINIMUM_NUMBER_OF_CARDS);

    for (int i = 0; i < playerList_.size(); ++i) {
        player = playerList_.nextPlayer();
        player->makeBidDecision();
    }

    loopGame();
}

void BatakEngine::handleRoundOver()
{
    Player *player;

    resetDeck();
    distributeCards(MINIMUM_NUMBER_OF_CARDS);
    for (int i = 0; i < playerList_.size(); ++i) {
        player = playerList_.nextPlayer();
        qDebug() << player->makeBidDecision();
    }
}

bool BatakEngine::isRoundOver()
{
    if (state.sizeofPlayedCards() == 52)
        return true;
    return false;
}

void BatakEngine::cardClicked(Card *card)
{
    Player *currentPlayer = playerList_.currentPlayer();
    Card *playedCard = currentPlayer->play(card, state);

    if (playedCard == NULL) {
        emit invalidCardSelected(playerList_.currentPlayerPosition());
        return;
    }

    state.append(playedCard);
    map[card] = currentPlayer;
    emit cardPlayed(playerList_.currentPlayerPosition(), card);

    if (state.sizeofCardsOnBoard() == 4) {
        Card *wCard = winingCard();
        Player *wPlayer = map[wCard];
        map.clear();
        wPlayer->score++;
        state.clearBoard();
        emit clearBoard();
    }
}
