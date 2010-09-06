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

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Widget *ui;
    QGridLayout *layout;
    GameEngine g;

    void createUi();
    void centerMyWindow();
};

#endif // WIDGET_H
