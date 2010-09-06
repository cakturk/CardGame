#include "gameengine.h"

GameEngine::GameEngine(QObject *parent) :
    QObject(parent)
{
    numberOfOnlinePlayer = 2;
//    startGameSession();

#if 0
    createCards();
    Card *c = cards.first();
    QToolButton *tb = createButton(c);

    createCards();
    distributeCards(4);

    Card *c;
    int j = 4;
    while (j--) {
        c = players[j].play(2);
        playedCards.append(c);
    }

    players[1].collectCards(playedCards);
    computePlayerScore(&players[1]);
#endif
}

/* Create cards and map them to card graphics */
void GameEngine::createCards()
{
    Card *newCard;

    for (int i = 0; i < 4; i++)
        for (int j = 1; j <= 13; j++) {
           newCard = new Card(i, j);
           cards.append(newCard);

#if 0
           QString pngName = ":/graph_items/graphics/" + (newCard->cardName).toLower();
           pngName.append(".png");
           pngMapping.insert(newCard, pngName);
#endif
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

#if 0
bool GameEngine::cardsEquals(Card *first, Card *sec)
{
    if (first->cardNumber == sec->cardNumber)
        return true;

    return false;
}
#endif

void GameEngine::computePlayerScore(Person *player)
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

// TODO: define a method that returns image name
QString GameEngine::getButtonPngName(QToolButton *b)
{
    QString retVal;

    return retVal;
}

QToolButton* GameEngine::createButton(Card *c)
{
#if 0
    QString str;
    if (pngMapping.contains(c))
        str = pngMapping[c];
#endif

    QString str = c->cardImageName;

    QToolButton *tb = new QToolButton();
    tb->setMinimumSize(QSize(50, 50));
    tb->setStyleSheet(QString("border-image: url(%1);").arg(str));

    buttonMapping.insert(tb, c);

    return tb;
}

QList<Card *> & GameEngine::getCards()
{
    return cards;
}

int GameEngine::getNumberOfOnlinePlayer() const
{
    return numberOfOnlinePlayer;
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
    if (cards.size() > 0)
    return cards.last();

    return NULL;
}
