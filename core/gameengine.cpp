#include "gameengine.h"

GameEngine::GameEngine(QObject *parent) :
        QObject(parent), lastWinner(0)
{ }

GameEngine::GameEngine(int playerNum, QObject *parent) :
        QObject(parent), lastWinner(0)
{
    if (playerNum < 1 || playerNum > 4) {
        qWarning() << "Error in GameEngine constructor!";
        return;
    }

    playerList_.setSize(playerNum);
}

GameEngine::~GameEngine()
{ }

void GameEngine::distributeCards(int number)
{
    CardSequence hand;
    Player *player;

    for (int i = 0; i < playerList_.size(); ++i) {
        for (int i = 0; i < number; ++i)
            hand.append(deck_.takeFirst());

        player = playerList_.nextPlayer();
        player->setHand(hand);
    }
}

void GameEngine::distributeCards(Player *player, int number)
{
    CardSequence hand;

    for (int i = 0; i < number; ++i)
        hand.append(deck_.takeFirst());
    player->setHand(hand);
}

void GameEngine::createCards()
{
    Card *newCard;

    for (int i = 0; i < 4; i++)
        for (int j = 1; j <= 13; j++) {
           newCard = new Card(i, j);
           this->deck_.append(newCard);
        }

    deck_.shuffle();
}

#if 0
GameEngine::GameEngine(QObject *parent) :
    QObject(parent), lastWinner(0)
{
    size = 0;
    numberOfPlayer = 2;
    vector.resize(4);
}

GameEngine::GameEngine(int playerNumber, QObject *parent) :
        QObject(parent), numberOfPlayer(playerNumber), lastWinner(0)
{
    vector.resize(4);
    /* dagitanin sagindaki oyuncu ilk karti atar */
    if (numberOfPlayer == 1) {
        sPlayer = new PistiPlayer(QString("So Client"));
        gamePlayers << sPlayer;
        currentPlayer = sPlayer;
        current_index = 0;
    }

    if (numberOfPlayer == 2) {
        increment = 2;
        sPlayer = new PistiPlayer(QString("Gokay"));
        nPlayer = new PistiPlayer(QString("Selin"));
        gamePlayers << sPlayer << nPlayer;
        currentPlayer = nPlayer;
        current_index = 2;
    }

    if (numberOfPlayer > 2) {
        numberOfPlayer = 4;
        increment = 1;

        sPlayer = new PistiPlayer(QString("Gokay"));
        ePlayer = new PistiPlayer(QString("Mert"));
        nPlayer = new PistiPlayer(QString("Selin"));
        wPlayer = new PistiPlayer(QString("Mr. Pink"));

        gamePlayers << sPlayer << ePlayer << nPlayer << wPlayer;
        currentPlayer = ePlayer;
        current_index = 1;
    }

    it = new QListIterator<Player *>(gamePlayers);
    it->next(); it->next();
}

GameEngine::GameEngine(bool, int num, QObject *parent) :
        QObject(parent), numberOfPlayer(num), lastWinner(0)
{
    size = 0;
    tIndex = 0;
    for (int i = 0; i < 4; ++i)
        tPlayers[i] = NULL;

    if (numberOfPlayer == 4)
        tInc = 1;
    else
    	tInc = 2;
    createCards();
}

GameEngine::~GameEngine()
{
    Player *p = 0;
    Card *card = 0;

    if (tSize() > 0) {
        for (int i = 0; i < tSize(); ++i) {
            p = tPlayers[i];
            if (p != 0)
                delete p;
        }
    }

    if (cards.size() > 0) {
        foreach (card, cards) {
            delete card ;
        }
    }

    if (cards_on_table.size() > 0) {
        foreach (card, cards_on_table) {
            delete card;
        }
    }
}

/* Create cards and map them to card graphics */
void GameEngine::createCards()
{
    Card *newCard;

    for (int i = 0; i < 4; i++)
        for (int j = 1; j <= 13; j++) {
           newCard = new Card(i, j);
           cards.append(newCard);
        }

    Card::shuffleList(cards);
}

//void GameEngine::distributeCards(int number)
//{
//    QList<Card *> tmp;

//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < number; j++) {
//            tmp.append(cards.takeFirst());
//        }

//        players[i].setHand(tmp);
//        tmp.clear();
//    }
//}

/* overloaded distrubuteCards() */
void GameEngine::distributeCards(Player &p, int number)
{
    CardSequence tmp;

    for (int i = 0; i < number; i++) {
        tmp.append(cards.takeFirst());
    }

    p.setHand(tmp);
}

bool GameEngine::pisti()
{
    // TODO currentPlayer son karti atan oyuncu olmali

    if (cards_on_table.size() < 2)
        return false;

    Card *currentCard = cards_on_table.at(cards_on_table.size() - 1);
    Card *lastPlayedCard =
            cards_on_table.at(cards_on_table.size() - 2);

    bool retVal = false;
    if (currentCard->equals(lastPlayedCard)) {
        /* Pisti */
        if (cards_on_table.size() == 2) {
            currentPlayer->pistiCount++;
            retVal = true;
        }

        /* Yerdeki kartlari topla  */
        currentPlayer->collectCards(cards_on_table);
        lastWinner = currentPlayer;

    // Vale
    } else if (currentCard->value == 11) {
        currentPlayer->collectCards(cards_on_table);
        lastWinner = currentPlayer;
        retVal = true;
    }

    return retVal;
}

bool GameEngine::pisti(bool)
{
    // TODO currentPlayer son karti atan oyuncu olmali

    if (cards_on_table.size() < 2)
        return false;

    Card *currentCard = cards_on_table.at(cards_on_table.size() - 1);
    Card *lastPlayedCard =
            cards_on_table.at(cards_on_table.size() - 2);

    bool retVal = false;
    if (currentCard->equals(lastPlayedCard)) {
        /* Pisti */
        if (cards_on_table.size() == 2) {
            currentPlayer->pistiCount++;
            retVal = true;
        }

        lastWinner = currentPlayer;

        // Vale
    } else if (currentCard->value == 11) {
        lastWinner = currentPlayer;
        retVal = true;
    }

    return retVal;
}

bool GameEngine::pisti(Player *p)
{
    currentPlayer = p;

    if (cards_on_table.size() < 2)
        return false;

    Card *currentCard = cards_on_table.at(cards_on_table.size() - 1);
    Card *lastPlayedCard =
            cards_on_table.at(cards_on_table.size() - 2);

    bool retVal = false;
    if (currentCard->equals(lastPlayedCard)) {
        /* Pisti */
        if (cards_on_table.size() == 2) {
            currentPlayer->pistiCount++;
            qDebug() << "pisti";
        }

        lastWinner = currentPlayer;
        retVal = true;

        // Vale
    } else if (currentCard->value == 11) {
        lastWinner = currentPlayer;
        retVal = true;
    }

    return retVal;
}

#if 0
bool GameEngine::cardsEquals(Card *first, Card *sec)
{
    if (first->cardNumber == sec->cardNumber)
        return true;

    return false;
}
#endif

void GameEngine::computePlayerScore(Player *player) const
{
    int pCount = player->pistiCount;
    while (pCount--)
        player->score += 10;

    pCount = 0;

    QList<Card *> tmplist = player->getScoredCards();

    for (int i = 0; i < tmplist.size(); i++) {
        Card *card = tmplist.at(i);

        if (card->value == 1)
            player->score++;
        if (card->value == 11)
            player->score++;
        if (card->type == Card::SINEK && card->value == 2)
            player->score += 2;
        if (card->type == Card::KARO && card->value == 10)
            player->score += 3;
    }
}

#if 0
void GameEngine::startGameSession()
{
    players[0].setPlayerName("Xaero");
    players[1].setPlayerName("Major");

    int random;
    Card *c;
    createCards();
    qsrand( QTime(0,0,0).secsTo(QTime::currentTime()));

    for (int i = 0; i < 4; i++) {
        Card *c = cards.takeFirst();
        cards_on_table.append(c);
    }

    bool play = true;
    while (play) {

        if(players[0].getNumberOfCards() == 0) {
            distributeCards(players[0], 4);
            distributeCards(players[1], 4);
        }

        currentPlayer = &players[0];
        random = qrand() % currentPlayer->getNumberOfCards();
        c = currentPlayer->play(random);
        qDebug() << "Xaero" << c->toString() << "atti.";
        cards_on_table.append(c);
        pisti();

        currentPlayer = &players[1];
        random = qrand() % currentPlayer->getNumberOfCards();
        c = currentPlayer->play(random);
        qDebug() << "Major" << c->toString() << "atti.";
        cards_on_table.append(c);
        pisti();

        play = (cards.size() == 0 && currentPlayer->getNumberOfCards() == 0)
               ? false : true;
    }

    // Yerde son kalan kartlar
    lastWinner->collectCards(cards_on_table);

    // TODO: computePlayerScore()
    if (players[0].getScoredCards().size() >
        players[1].getScoredCards().size())
        players[0].score += 3;
    else
        players[1].score += 3;

    computePlayerScore(&players[0]);
    computePlayerScore(&players[1]);

    qDebug() << "Oyun bitti!";
    qDebug() << players[0].getPlayerName() <<": "
            << players[0].pistiCount << "pisti yapti" << players[0].score;

    qDebug() << players[1].getPlayerName() <<": "
            << players[1].pistiCount << "pisti yapti" << players[1].score;

}
#endif

QList<Card *> & GameEngine::getCards()
{
    return cards;
}

int GameEngine::getNumberOfPlayer() const
{
    return numberOfPlayer;
}

#if 0
Player* GameEngine::getPlayers()
{
    return players;
}
#endif

void GameEngine::appendToPlayedCards(Card *c)
{
    cards_on_table.append(c);
    played_cards.append(c);
}

Card* GameEngine::lastPlayedCard()
{
    if (cards_on_table.isEmpty())
    return NULL;

    // return cards.last();
    return cards_on_table.last();
}

QList<Card *> & GameEngine::cardsOnTable()
{
    return cards_on_table;
}

Player* GameEngine::getlastWinner() const
{
    return lastWinner;
}

Player* GameEngine::nextPlayer()
{
    currentPlayer->setTurn(false);
    if (it->hasNext()) {
        currentPlayer = it->next();
        current_index = (current_index + increment) % 4;
    } else {
        it->toFront();
        currentPlayer = it->next();
        current_index = (current_index + increment) % 4;
    }
    currentPlayer->setTurn(true);

    return currentPlayer;
}

int GameEngine::playerIndex()
{
    return current_index;
}

Player* GameEngine::myself()
{
    if (! gamePlayers.isEmpty()) {
        currentPlayer->setTurn(false);
        current_index = 0;
        it->toFront();
        currentPlayer = it->next();
        currentPlayer->setTurn(true);
        return currentPlayer;
    }
    return NULL;
}

const Player* GameEngine::me() const
{
    return sPlayer;
}

void GameEngine::add(Player *player, int pos)
{
    static int count = 0;
    vector.resize(4);
    if (pos == -1)
        pos = player->getPosition();
    vector[pos] = player;
    if (count == numberOfPlayer) {
        gamePlayers = vector.toList();
        // vector.clear();
    }
}

void GameEngine::tAdd(Player *player, int pos)
{
    if (pos < 0 && pos > 3) {
        qDebug() << "tAdd error";
        return;
    }

    player->setPosition(pos);
    tPlayers[pos] = player;
    size++;

    if (size == numberOfPlayer)
    	emit ready();
}

void GameEngine::tAdd(int pos)
{
        Player *p = new PistiPlayer;
	tAdd(p, pos);
}

Player* GameEngine::tNextPlayer()
{
    tIndex = (tIndex + tInc) % 4;
    return tPlayers[tIndex];
}

int GameEngine::tSize()
{
	return size;
}

Player* GameEngine::at(int index)
{
    switch (index) {
    case 0:
        return tPlayers[0];
    case 1:
        return tPlayers[1];
    case 2:
        return tPlayers[2];
    case 3:
        return tPlayers[3];
    default:
        return NULL;
    }
}

const CardSequence & GameEngine::playedCards() const
{
    return played_cards;
}

bool GameEngine::checkRound(Player *)
{
    return false;
}
#endif
