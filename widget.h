#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QDesktopWidget>
#include <QToolButton>
#include <QTime>
#include <QDebug>
#include "card.h"
#include "gameengine.h"

namespace Ui {
    class Widget;
}

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void start();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Widget *ui;
    QGridLayout *grid;
    GameEngine g;
    Person *players;
    int maxpoint;

    void createUi();
    void centerMyWindow();
    void showCardOnTable(Card *c, int playerindex);
};

#endif // WIDGET_H
