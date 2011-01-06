#ifndef PISTIENGINE_H
#define PISTIENGINE_H

#include "gameengine.h"

class PistiEngine : public GameEngine
{
    Q_OBJECT

public:
    explicit PistiEngine(QObject *parent = 0);
    explicit PistiEngine(int playerNum, QObject *parent = 0);
    ~PistiEngine();

    void checkState(State &state);
    void loopGame();

private:
    bool pisti() const;
    bool wins() const;
    void waitForPlayer();

private slots:
    void cardClicked(Card *card);
};

#endif // PISTIENGINE_H
