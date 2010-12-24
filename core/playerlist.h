#ifndef PLAYERLIST_H
#define PLAYERLIST_H

#include <QObject>

class Player;
class PlayerList : public QObject
{
    Q_OBJECT
public:
    explicit PlayerList(int playerNum, QObject *parent = 0);
    explicit PlayerList(QObject *parent = 0);

    enum POSITION {
        SOUTH = 0,
        EAST = 1,
        NORTH = 2,
        WEST = 3
    };

    void insert(Player *player);
    void insert(Player *player, PlayerList::POSITION);
    bool remove(Player *player);
    bool remove(PlayerList::POSITION);

    Player* nextPlayer();
    Player* currentPlayer() const;
    int currentPlayerIndex() const;
    int size() const;
    void setSize(int size);
    bool isEmpty() const;
    void setCurrentPlayer(Player *player);
    void setCurrentPlayer(PlayerList::POSITION);
    void clear();
    void swap(PlayerList::POSITION pos1, PlayerList::POSITION pos2);

signals:
    void ready();
    void sizeChanged(int);

public slots:

private:
    QList<Player *> playerList_;
    int current_;
    int count_;

};

#endif // PLAYERLIST_H
