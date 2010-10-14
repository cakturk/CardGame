#include "gameengine.h"

GameEngine::GameEngine(QObject *parent) :
    QObject(parent)
{
    size = 0;
    numberOfPlayer = 2;
    vector.resize(4);
}

GameEngine::GameEngine(int playerNumber, QObject *parent) :
        QObject(parent), numberOfPlayer(playerNumber)
{
    vector.resize(4);
    /* dagitanin sagindaki oyuncu ilk karti atar */
    if (numberOfPlayer == 1) {
        sPlayer = new Person(QString("So Client"));
        gamePlayers << sPlayer;
        currentPlayer = sPlayer;
        current_index = 0;
    }

    if (numberOfPlayer == 2) {
        increment = 2;
        sPlayer = new Person(QString("Gokay"));
        nPlayer = new Person(QString("Selin"));
        gamePlayers << sPlayer << nPlayer;
        currentPlayer = nPlayer;
        current_index = 2;
    }

    if (numberOfPlayer > 2) {
        numberOfPlayer = 4;
        increment = 1;

        sPlayer = new Person(QString("Gokay"));
        ePlayer = new Person(QString("Mert"));
        nPlayer = new Person(QString("Selin"));
        wPlayer = new Person(QString("Mr. Pink"));

        gamePlayers << sPlayer << ePlayer << nPlayer << wPlayer;
        currentPlayer = ePlayer;
        current_index = 1;
    }

    it = new QListIterator<Person *>(gamePlayers);
    it->next(); it->next();
}

GameEngine::GameEngine(bool deneme, int num, QObject *parent) :
        QObject(parent), numberOfPlayer(num)
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

void GameEngine::distributeCards(int number)
{
    QList<Card *> tmp;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < number; j++) {
            tmp.append(cards.takeFirst());
        }

        players[i].setHand(tmp);
        tmp.clear();
    }
}

/* overloaded distrubuteCards() */
void GameEngine::distributeCards(Person &p, int number)
{
    QList<Card *> tmp;

    for (int i = 0; i < number; i++) {
        tmp.append(cards.takeFirst());
    }

    p.setHand(tmp);
}

bool GameEngine::pisti()
{
    // TODO currentPlayer son karti atan oyuncu olmali

    if (playedCards.size() < 2)
        return false;

    Card *currentCard = playedCards.at(playedCards.size() - 1);
    Card *lastPlayedCard =
            playedCards.at(playedCards.size() - 2);

    bool retVal = false;
    if (currentCard->equals(lastPlayedCard)) {
        /* Pisti */
        if (playedCards.size() == 2) {
            currentPlayer->pistiCount++;
            retVal = true;
        }

        /* Yerdeki kartlari topla  */
        currentPlayer->collectCards(playedCards);
        lastWinner = currentPlayer;

    // Vale
    } else if (currentCard->cardNumber == 11) {
        currentPlayer->collectCards(playedCards);
        lastWinner = currentPlayer;
        retVal = true;
    }

    return retVal;
}

bool GameEngine::pisti(bool b)
{
    // TODO currentPlayer son karti atan oyuncu olmali

    if (playedCards.size() < 2)
        return false;

    Card *currentCard = playedCards.at(playedCards.size() - 1);
    Card *lastPlayedCard =
            playedCards.at(playedCards.size() - 2);

    bool retVal = false;
    if (currentCard->equals(lastPlayedCard)) {
        /* Pisti */
        if (playedCards.size() == 2) {
            currentPlayer->pistiCount++;
            retVal = true;
        }

        lastWinner = currentPlayer;

        // Vale
    } else if (currentCard->cardNumber == 11) {
        lastWinner = currentPlayer;
        retVal = true;
    }

    return retVal;
}

bool GameEngine::pisti(Person *p)
{
    currentPlayer = p;

    if (playedCards.size() < 2)
        return false;

    Card *currentCard = playedCards.at(playedCards.size() - 1);
    Card *lastPlayedCard =
            playedCards.at(playedCards.size() - 2);

    bool retVal = false;
    if (currentCard->equals(lastPlayedCard)) {
        /* Pisti */
        if (playedCards.size() == 2) {
            currentPlayer->pistiCount++;
            qDebug() << "pisti";
        }

        lastWinner = currentPlayer;
        retVal = true;

        // Vale
    } else if (currentCard->cardNumber == 11) {
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

void GameEngine::computePlayerScore(Person *player) const
{
    int pCount = player->pistiCount;
    while (pCount--)
        player->score += 10;

    pCount = 0;

    QList<Card *> tmplist = player->getScoredCards();

    for (int i = 0; i < tmplist.size(); i++) {
        Card *card = tmplist.at(i);

        if (card->cardNumber == 1)
            player->score++;
        if (card->cardNumber == 11)
            player->score++;
        if (card->type == Card::SINEK && card->cardNumber == 2)
            player->score += 2;
        if (card->type == Card::KARO && card->cardNumber == 10)
            player->score += 3;
    }
}

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
        playedCards.append(c);
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
        playedCards.append(c);
        pisti();

        currentPlayer = &players[1];
        random = qrand() % currentPlayer->getNumberOfCards();
        c = currentPlayer->play(random);
        qDebug() << "Major" << c->toString() << "atti.";
        playedCards.append(c);
        pisti();

        play = (cards.size() == 0 && currentPlayer->getNumberOfCards() == 0)
               ? false : true;
    }

    // Yerde son kalan kartlar
    lastWinner->collectCards(playedCards);

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

QList<Card *> & GameEngine::getCards()
{
    return cards;
}

int GameEngine::getNumberOfPlayer() const
{
    return numberOfPlayer;
}

Person* GameEngine::getPlayers()
{
    return players;
}

void GameEngine::dummyStart()
{
    players[0].setPlayerName("Xaero");
    players[1].setPlayerName("Major");
    createCards();
    distributeCards(players[0], 4);
    distributeCards(players[1], 4);
}

void GameEngine::start()
{
    for (int i = 0; i < 4; i++) {
        distributeCards(players[i], 4);
    }

    for (int i = 0; i < 4; i++) {

    }
}

void GameEngine::appendToPlayedCards(Card *c)
{
    playedCards.append(c);
}

Card* GameEngine::lastPlayedCard()
{
    if (playedCards.isEmpty())
    return NULL;

    // return cards.last();
    return playedCards.last();
}

QList<Card *> & GameEngine::getPlayedCards()
{
    return playedCards;
}

Person* GameEngine::getlastWinner() const
{
    return lastWinner;
}

Person* GameEngine::nextPlayer()
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

Person* GameEngine::myself()
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

const Person* GameEngine::me() const
{
    return sPlayer;
}

void GameEngine::add(Person *player, int pos)
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

void GameEngine::tAdd(Person *player, int pos)
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
	Person *p = new Person;
	tAdd(p, pos);
}

Person* GameEngine::tNextPlayer()
{
    tIndex = (tIndex + tInc) % 4;
    return tPlayers[tIndex];
}

int GameEngine::tSize()
{
	return size;
}

Person* GameEngine::at(int index)
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
