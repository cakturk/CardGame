#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QDesktopWidget>
#include <QToolButton>
#include <QTime>
#include <QDebug>
#include <QSignalMapper>
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

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Widget *ui;
    GameEngine g;
    Person *players;
    int maxpoint;
    QSignalMapper *mapper;

    /* layouts */
    QGridLayout *grid;
    QHBoxLayout *hbox;
    QVBoxLayout *vbox;

    void start();
    void modifiedstart();
    void createUi();
    void centerMyWindow();
    void showCardOnTable(Card *c, int playerindex);
    void showCardOnFrame(Card *c, int playerindex);
    void simulateOthers();

private slots:
    void on_pushButton_clicked();
    void cardClicked(QObject *obj);

};

#endif // WIDGET_H
