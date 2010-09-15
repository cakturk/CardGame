#include "widget.h"
#include "ui_widget.h"
#include <QThread>

#define TESTT
#define TEST_CONST
#undef TEST_CONST

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    currentPlayerIndex = 0;
    mapper = new QSignalMapper(this);
    connect(mapper, SIGNAL(mapped(QObject *)), this, SLOT(cardClicked(QObject *)));

    this->setWindowTitle("Card Game");
    centerMyWindow();

    /* set layouts */
    grid = new QGridLayout(ui->table);
    ui->table->setLayout(grid);
    ui->table->setEnabled(false); // disable table so no one can click on it.

    QToolButton *dummybutton;
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++) {
            dummybutton = new QToolButton;
            dummybutton->setStyleSheet(QString("border-image: url(./graphics/53.png)"));
            grid->addWidget(dummybutton, row, col);
            dummybutton->hide();
            dummybutton->setMinimumSize(QSize(50, 50));
    }

    hbox = new QHBoxLayout(ui->southHand);
    hbox->setAlignment(Qt::AlignCenter);
    hbox->setContentsMargins(200, 0, 200, 0);
    ui->southHand->setLayout(hbox);
    hbox = new QHBoxLayout(ui->northHand);
    hbox->setAlignment(Qt::AlignCenter);
    ui->northHand->setLayout(hbox);

    vbox = new QVBoxLayout(ui->eastHand);
    vbox->setAlignment(Qt::AlignCenter);
    ui->eastHand->setLayout(vbox);
    vbox = new QVBoxLayout(ui->westHand);
    vbox->setAlignment(Qt::AlignCenter);
    ui->westHand->setLayout(vbox);

#ifdef TEST_CONST
    g.createCards();
    players = g.getPlayers();
    g.distributeCards(players[0], 4);
    QList<Card *> playersHand = players[0].getHand();
    QWidget *wid = (QWidget *) playersHand.at(0)->buttonPtr;
    ui->southHand->layout()->addWidget(wid);
#endif

    // start();
    modifiedstart();

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
    delete mapper;
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
#if 0
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
#endif

void Widget::start()
{
    // test value
    maxpoint = 100;

    QFrame *frame;
    QLayout *currentLayout;
    QHBoxLayout *hbox;
    QVBoxLayout *vbox;
    QList<Card *> playersHand;
    QString pos;
    bool myself = false;
    Person *currentPlayer;

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
            vbox->setAlignment(Qt::AlignCenter);
            currentLayout = vbox;
            frame->setLayout(vbox);
            myself = false;
            pos = 'v';
            break;
        case 2:
            frame = ui->northHand;
            hbox = new QHBoxLayout;
            hbox->setAlignment(Qt::AlignCenter);
            currentLayout = hbox;
            frame->setLayout(hbox);
            hbox->setContentsMargins(11, 0, 11, 0);
            myself = false;
            pos = 'h';
            break;
        case 3:
            frame = ui->westHand;
            vbox = new QVBoxLayout;
            vbox->setAlignment(Qt::AlignCenter);
            currentLayout = vbox;
            frame->setLayout(vbox);
            myself = false;
            pos = 'v';
            break;
        }

        for (int j = 0; j < currentPlayer->getHand().size(); j++) {
            QWidget *but;
            if (myself) {
                // playersHand.at(j)->getButton() olmayacak
                // but = (QWidget *) playersHand.at(j)->buttonPtr;
                //playersHand.at(j)->getButton();
                // QWidget *voidButt = (QWidget *) playersHand.at(j)->buttonPtr;
                // qDebug() << voidButt->styleSheet() << voidButt->geometry() << voidButt;
                // but->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
                // ui->southHand->layout()->addWidget(voidButt);
                // voidButt->show();

                // players[0].getHand().at(0)->getButton();
                showCardOnTable(players[0].getHand().at(0), 1);

            } else {
#if 0
                but = new QToolButton;
                but->setStyleSheet(QString("border-image: url(./graphics/back/4%1.png);").arg(pos));
                but->setMinimumSize(75, 75);
                but->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
                currentLayout->addWidget(but);
#endif
                QList<Card *> bar = players[2].getHand();
                // currentLayout->addWidget(static_cast<QWidget *>(bar.at(3)->buttonPtr));
                qDebug() << bar.at(0)->buttonPtr << (QWidget *) bar.at(0)->buttonPtr;
                // bar.at(0)->getButton();
                qDebug() << bar.at(0)->buttonPtr << (QWidget *) bar.at(0)->buttonPtr;
                QToolButton *debugvar = (QToolButton *) bar.at(0)->buttonPtr;
                qDebug() << bar.at(0)->buttonPtr << (QWidget *) bar.at(0)->buttonPtr;
                // QWidget *debugvatGet = bar.at(0)->getButton();
                //debugvar->setParent(ui->table);
                grid->addWidget(bar.at(0)->getButton(), 1, 2);
                break;
            }
        }
    }

 /*
    Card *cd = players[0].getHand().at(3);
    QWidget *test = ui->southHand->layout()->itemAt(2)->widget();
    ui->southHand->layout()->removeWidget(test);
    test->hide();
*/

    currentPlayer = &players[0];

    int playerIndex = 0;
    bool play = true;

    int counter = 0;
    while (play) {
        /* El bittiyse kart dagit */ 
        if (currentPlayer->getNumberOfCards() == 0) {
            for (int i = 0; i < 4; i++) {
                playerIndex = (playerIndex + 1) % 4; // Next player
                currentPlayer = &players[playerIndex];
                g.distributeCards(*currentPlayer, 4);
            }
        }

        if (playerIndex == 0)
            currentLayout = ui->southHand->layout();

        Card *lastcard = g.lastPlayedCard();
        Card *c = currentPlayer->play(lastcard);
        g.appendToPlayedCards(c);
        showCardOnTable(c, playerIndex);

/*
        if (currentPlayer == &players[0]) {
            QWidget *w = (QWidget *) c->buttonPtr;
            QLayout *lay = ui->southHand->layout();
            int index = lay->indexOf(w);
            lay->removeWidget(w);
            w->hide();
        }
*/

        if (g.pisti(currentPlayer)) {
            QList<Card *> &l = g.getPlayedCards();

            for (int i = 0; i < l.size(); i++) {
                QWidget *widget = (QWidget *) l.at(i)->buttonPtr;
                grid->removeWidget(widget);
                widget->hide();
            }
            
            currentPlayer->collectCards(l);
        }

        playerIndex = (playerIndex + 1) % 4;
        currentPlayer = &players[playerIndex];

        if (g.getCards().size() == 0 && currentPlayer->getNumberOfCards() == 0)
            play = false;

        counter++;
        if(counter == 42)
            qDebug() <<  "42 ";
    }

    QList<Card *> &cardsOnTable = g.getPlayedCards();
    for (int i = 0; i < cardsOnTable.size(); i++) {
        QWidget *widget = (QWidget *) cardsOnTable.at(i)->buttonPtr;
        grid->removeWidget(widget);
        widget->hide();
    }
    g.getlastWinner()->collectCards(cardsOnTable);

#ifdef TEST
    // test begin
    QWidget *tmpwidget = ui->southHand->layout()->itemAt(0)->widget();
    ui->southHand->layout()->removeWidget(tmpwidget);
    tmpwidget->hide();
    // test end
#endif

}

void Widget::showCardOnTable(Card *c, int position)
{
    int row, column;
    switch (position) {
    case 0: // south
        row = 2;
        column = 1;
        break;
    case 1: // east
        row = 1;
        column = 3;
        break;
    case 2: // north
        row = 0;
        column = 1;
        break;
    case 3: // west
        row = 1;
        column = 0;
        break;
    }

    /* c->getButton() */
    /* (QWidget *) c->buttonPtr */
    grid->addWidget((QWidget *) c->buttonPtr, row, column);
}

void Widget::showCardOnFrame(Card *c, int playerindex)
{
    if (playerindex == 0) {
        ui->southHand->layout()->addWidget((QWidget *) c->buttonPtr);
    }
}

void Widget::modifiedstart()
{
    // which player to play
    // int currentPlayerIndex = 0;

    players = g.getPlayers();
    g.createCards();

    /* Yere ucu kapali dort kart at */
    for (int i = 0; i < 4; i++) {
        Card *c = g.getCards().takeFirst();
        g.appendToPlayedCards(c);
    }
    QToolButton *but = new QToolButton;
    but->setStyleSheet(QString("border-image: url(./graphics/back/3h.png)"));
    but->setMinimumSize(75, 55);
    but->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    grid->addWidget(but, 1, 1);

    Card *card = g.getPlayedCards().last();
    // TODO: getButton()
    // card->getButton();
    grid->addWidget(static_cast<QWidget *>(card->buttonPtr), 1, 1);

    // TODO: i < numbeerOfPlayers
    for (int i = 0 ; i < 4; i++) {
        currentPlayer = &players[i];
        g.distributeCards( *currentPlayer, 4 );
    }

    currentPlayer = &players[0];
    // connect button signals to slots
    for (int i = 0; i < currentPlayer->getNumberOfCards(); i++) {
        QList<Card *> l = currentPlayer->getHand();
        connect(static_cast<QToolButton *>(l.at(i)->buttonPtr), SIGNAL(clicked()),
                mapper, SLOT(map()));
        mapper->setMapping(static_cast<QObject *>(l.at(i)->buttonPtr),
                           static_cast<QObject *>(l.at(i)));
        ui->southHand->layout()->addWidget(static_cast<QWidget *>(l.at(i)->buttonPtr));
    }

    // grid->addWidget(static_cast<QWidget *>(currentPlayer->getHand().at(1)->buttonPtr), 0, 3);
}

void Widget::cardClicked(QObject *obj)
{
    // disable my panel
    ui->southHand->setEnabled(false);

    Card *c = static_cast<Card *>(obj);
    g.appendToPlayedCards(c);
    showCardOnTable(c, 0);

    if (g.pisti(&players[0])) {
        QList<Card *> &l = g.getPlayedCards();

        delay(150);

        for (int i = 0; i < l.size(); i++) {
            QWidget *widget = static_cast<QWidget *>(l.at(i)->buttonPtr);
            grid->removeWidget(widget);
            widget->hide();
        }

        players[0].collectCards(l);
    }

    qDebug() << c->cardImageName;
    simulateOthers();
}

void Widget::simulateOthers()
{
    currentPlayerIndex = 1;

    delay(150);

    for (int i = 1; i <= 3; i++) {
        currentPlayer = &players[currentPlayerIndex];
        Card *lastcard = g.lastPlayedCard();
        Card *c = currentPlayer->play(lastcard);
        g.appendToPlayedCards(c);
        showCardOnTable(c, currentPlayerIndex);

        delay(150);

        if (g.pisti(currentPlayer)) {
            QList<Card *> &l = g.getPlayedCards();

            for (int i = 0; i < l.size(); i++) {
                QWidget *widget = static_cast<QWidget *>(l.at(i)->buttonPtr);
                grid->removeWidget(widget);
                widget->hide();
            }
            currentPlayer->collectCards(l);
        }

        // TODO: Oyuncu sayisi dortten az olabilir
        currentPlayerIndex = (currentPlayerIndex + 1) % 4;
        currentPlayer = &players[currentPlayerIndex];
    }

    // Enable my panel
    ui->southHand->setEnabled(true);
}

void Widget::on_pushButton_clicked()
{
    modifiedstart();
}

inline void Widget::delay(int count, int sleep)
{
    while (count--) {
        usleep(sleep);
        QApplication::processEvents();
    }
}
