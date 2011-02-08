#include "playerlist.h"
#include <QDebug>
#include "core/player.h"

PlayerList::PlayerList(int playerNum, QObject *parent) :
        QObject(parent), current_(-1), count_(0)
{
    setSize(playerNum);
}

PlayerList::PlayerList(QObject *parent) :
        QObject(parent), current_(-1), count_(0)
{ }

void PlayerList::insert(Player *player)
{

    if (count_ > 4) {
        qWarning() << "Error in PlayerList::insert function "
                   << "PlayerList limit exceeded" << count_;
        return;
    }

    playerList_[count_] = player;
    current_ = 0;
    ++count_;

    emit sizeChanged(count_);
    if(count_ == playerList_.size())
        emit ready();
}

void PlayerList::insert(Player *player, PlayerList::POSITION pos)
{
    if (pos < 0 || pos >= playerList_.size()) {
        qWarning() << "Error in Playerlist::insert function" << pos;
        return;
    }

    playerList_[pos] = player;
    current_ = 0;
    ++count_;

    emit sizeChanged(count_);
    if(count_ == playerList_.size())
        emit ready();
}

bool PlayerList::remove(Player *player)
{
    for (int i = 0; i < playerList_.size(); ++i) {
        if (player == playerList_.at(i)) {
            playerList_.removeAt(i);
            delete player;
            --count_;
            emit sizeChanged(count_);
            return true;
        }
    }

    return false;
}

bool PlayerList::remove(PlayerList::POSITION pos)
{
    if (pos < 0 || pos >= playerList_.size())
        return false;

    Player *player = playerList_.takeAt(pos);
    delete player;
    --count_;
    emit sizeChanged(count_);

    return true;
}

Player* PlayerList::nextPlayer()
{
    current_ = (current_ + 1) % playerList_.size();
    return currentPlayer();
}

Player* PlayerList::currentPlayer() const
{
    return playerList_.at(current_);
}

Player* PlayerList::previousPlayer()
{
    current_ = (current_ + playerList_.size() - 1) % playerList_.size();
    return playerList_.at(current_);
}

PlayerList::POSITION PlayerList::currentPlayerPosition() const
{
    switch (currentPlayerIndex()) {
    case SOUTH:
        return PlayerList::SOUTH;
    case EAST:
        return PlayerList::EAST;
    case NORTH:
        return PlayerList::NORTH;
    case WEST:
        return PlayerList::WEST;
    default:
        qWarning() << "Error in Playerlist::currentPlayerPosition function!";
        return PlayerList::ILLEGAL;
    }
}

PlayerList::POSITION PlayerList::position(Player *player)
{
    Player *tmp;
    for (int i = 0; i < playerList_.size(); ++i) {
        tmp = playerList_[i];
        if (player == tmp) {
            switch (i) {
            case SOUTH:
                return PlayerList::SOUTH;
            case EAST:
                return PlayerList::EAST;
            case NORTH:
                return PlayerList::NORTH;
            case WEST:
                return PlayerList::WEST;
            }
        }
    }

    qWarning() << "Error in Playerlist::currentPlayerPosition function!";
    return PlayerList::ILLEGAL;
}

int PlayerList::currentPlayerIndex() const
{
    return current_;
}

int PlayerList::size() const
{
    return playerList_.size();
}


bool PlayerList::isEmpty() const
{
    return playerList_.isEmpty();
}

void PlayerList::setSize(int size)
{
    for (int i = 0; i < size; ++i)
        playerList_.append(NULL);
}

void PlayerList::setCurrentPlayer(Player *player)
{
    for (int i = 0; i < playerList_.size(); ++i) {
        if (player == playerList_.at(i)) {
            current_ = i;
            return;
        }
    }

    qWarning() << "Error in Playerlist::setCurrentPlayer function";
}

void PlayerList::setCurrentPlayer(PlayerList::POSITION pos)
{
    if (pos < 0 || pos >= playerList_.size()) {
        qWarning() << "Error in Playerlist::setCurrentPlaer function";
        return;
    }

    current_ = pos;
}

void PlayerList::clear()
{
    current_ = -1;
    qDeleteAll(playerList_);
    playerList_.clear();
}

void PlayerList::swap(PlayerList::POSITION pos1, PlayerList::POSITION pos2)
{
    if ( pos1 < 0 || pos1 >= playerList_.size() ||
         pos2 < 0 || pos2 >= playerList_.size() ||
         pos1 == pos2) {
        qWarning() << "Error in Playerlist::swap, returning from function...";
        return;
    }

    Player *temp = playerList_.at(pos1);
    playerList_[pos1] = playerList_.at(pos2);
    playerList_[pos2] = temp;
}
