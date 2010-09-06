#include "widget.h"
#include "ui_widget.h"
#include <QThread>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("Card Game");
    centerMyWindow();

    start();

//    g.createCards();
//    g.dummyStart();
//    createUi();
    
#if 0
    Card *c = g.getCards().first();
    QToolButton *tb = g.createButton(c);

    layout = new QGridLayout;
    ui->table->setLayout(layout);

    QPushButton *button, *button2, *button3, *button4;
    button = new QPushButton("New Button");
    button2 = new QPushButton("Click");
    button3 = new QPushButton("Button 3");
    button4 = new QPushButton("Button 4");

    layout->addWidget(tb, 2, 1);
    layout->addWidget(button2, 1, 2);
    layout->addWidget(button3, 1, 0);
    layout->addWidget(button4, 0, 1);
#endif
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Widget::centerMyWindow() {
    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth, width;
    int screenHeight, height;
    int x, y;
    QSize windowSize;

    screenWidth = desktop->width(); // get width of screen
    screenHeight = desktop->height(); // get height of screen

    windowSize = size(); // size of our application window
    width = windowSize.width();
    height = windowSize.height();

    // little computations
    x = (screenWidth - width) / 2;
    y = (screenHeight - height) / 2;

    // move window to desired coordinates
    move ( x, y );
}

/* create card game UI */
void Widget::createUi()
{
    // QLayout *frameLayout = ui->southHand->layout();
    Person *players = g.getPlayers();
    QList<Card *> playersHand;

    QHBoxLayout *hb = new QHBoxLayout;
    ui->northHand->setLayout(hb);
    hb->setContentsMargins(100, 0, 100, 0);

    for (int i = 0; i < g.getNumberOfOnlinePlayer(); i++) {
        playersHand = players[i].getHand();
        for (int j = 0; j < players[i].getHand().size(); j++) {
            QToolButton *but = g.createButton(playersHand.at(j));

            switch (i) {
            case 0:
                ui->southHand->layout()->addWidget(but);
                break;
            case 1:
                ui->northHand->layout()->addWidget(but);
                break;
            case 2:
                ui->westHand->layout()->addWidget(but);
                break;
            case 3:
                ui->eastHand->layout()->addWidget(but);
                break;
            }
        }
    }
}

void Widget::start()
{
    // test value
    maxpoint = 100;

    // Initial adjustment
    QFrame *frame;
    QLayout *currentLayout;
    QHBoxLayout *hbox;
    // hbox->setContentsMargins(100, 0, 100, 0);
    QVBoxLayout *vbox;
    // vbox->setContentsMargins(0, 100, 0, 100);
    QList<Card *> playersHand;
    QString pos;
    bool myself = false;
    Person *currentPlayer;
    int row, column;

    g.createCards();

    players = g.getPlayers();

    for (int i = 0; i < 4; i++) {
        Card *c = g.getCards().takeFirst();
        g.appendToPlayedCards(c);
    }

    for (int i = 0; i < 4; i++) {
        g.distributeCards(players[i], 4);
    }

    for (int i = 0; i < 4; i++) {
        currentPlayer = &players[i];
        playersHand = currentPlayer->getHand();

        switch (i) {
        case 0:
            frame = ui->southHand;
            hbox = new QHBoxLayout;
            currentLayout = hbox;
            hbox->setContentsMargins(200, 0, 200, 0);
            frame->setLayout(hbox);
            myself = true;
            break;
        case 1:
            frame = ui->eastHand;
            vbox = new QVBoxLayout;
            currentLayout = vbox;
            frame->setLayout(vbox);
            myself = false;
            pos = 'v';
            break;
        case 2:
            frame = ui->northHand;
            hbox = new QHBoxLayout;
            currentLayout = hbox;
            frame->setLayout(hbox);
            hbox->setContentsMargins(11, 0, 11, 0);
            myself = false;
            pos = 'h';
            break;
        case 3:
            frame = ui->westHand;
            vbox = new QVBoxLayout;
            currentLayout = vbox;
            frame->setLayout(vbox);
            myself = false;
            pos = 'v';
            break;
        }

        for (int j = 0; j < currentPlayer->getHand().size(); j++) {
            QToolButton *but;
            if (myself) {
                but = g.createButton(playersHand.at(j));
                but->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
                currentLayout->addWidget(but);
            } else {
                but = new QToolButton;
                but->setStyleSheet(QString("border-image: url(./graphics/back/4%1.png);").arg(pos));
                but->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
                currentLayout->addWidget(but);
                break;
            }
        }
    }

    currentPlayer = &players[0];

    int playerIndex = 0;
    bool play = true;
    while (play) {
        /* El bittiyse kart dagit */ 
        if (currentPlayer->getNumberOfCards() == 0) {
            for (int i = 0; i < 4; i++) {
                playerIndex = (playerIndex + 1) % 4; // Next player
                currentPlayer = &players[playerIndex];
                g.distributeCards(*currentPlayer, 4);
            }
        }

        Card *lastcard = g.lastPlayedCard();
        if (lastcard != NULL) {
            Card *c = currentPlayer->play(lastcard);
            g.appendToPlayedCards(c);
        }

        QList<QToolButton *> list;
        if (g.pisti(true)) {
            QList<QToolButton *> list = ui->table->findChildren<QToolButton *>();

            for (int i = 0; list.size(); i++)
                currentLayout->removeWidget(list.at(i));
        }

        playerIndex = (playerIndex + 1) % 4;

        if (g.getCards().size() == 0)
            play = false;
    }
}
