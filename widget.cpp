#include "widget.h"
#include "ui_widget.h"

#define TESTT
#define TEST_CONST
#undef TEST_CONST
#define PROB 0

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->gridLayout->setSpacing(0);

    game = NULL;
    currentPlayerIndex = 0;

    mapper = new QSignalMapper(this);
    // connect(mapper, SIGNAL(mapped(QObject *)), this, SLOT(cardClicked(QObject *)));
    connect(mapper, SIGNAL(mapped(QObject *)), this, SLOT(n_cardClicked(QObject*)));

    this->setWindowTitle("Card Game");
    centerMyWindow();
    ui->southHand->setCursor(Qt::UpArrowCursor);

    ui->tableCenter->setEnabled(false);
    ui->tableSouth->setEnabled(false);
    ui->tableEast->setEnabled(false);
    ui->tableNorth->setEnabled(false);
    ui->tableWest->setEnabled(false);

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

    //prepareNetworkUI();

    // modifiedstart();
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
    Person *players = game->getPlayers();
    QList<Card *> playersHand;

    QHBoxLayout *hb = new QHBoxLayout;
    ui->northHand->setLayout(hb);
    hb->setContentsMargins(100, 0, 100, 0);

    for (int i = 0; i < game->getNumberOfOnlinePlayer(); i++) {
        playersHand = players[i].getHand();
        for (int j = 0; j < players[i].getHand().size(); j++) {
            QToolButton *but = game->createButton(playersHand.at(j));

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
    maxpoint = 101;

    QFrame *frame;
    QLayout *currentLayout;
    QHBoxLayout *hbox;
    QVBoxLayout *vbox;
    QList<Card *> playersHand;
    QString pos;
    bool myself = false;
    Person *currentPlayer;

    game->createCards();
    players = game->getPlayers();

    for (int i = 0; i < 4; i++) {
        Card *c = game->getCards().takeFirst();
        game->appendToPlayedCards(c);
    }

    for (int i = 0; i < 4; i++) {
        game->distributeCards(players[i], 4);
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
                game->distributeCards(*currentPlayer, 4);
            }
        }

        if (playerIndex == 0)
            currentLayout = ui->southHand->layout();

        Card *lastcard = game->lastPlayedCard();
        Card *c = currentPlayer->play(lastcard);
        game->appendToPlayedCards(c);
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

        if (game->pisti(currentPlayer)) {
            QList<Card *> &l = game->getPlayedCards();

            for (int i = 0; i < l.size(); i++) {
                QWidget *widget = (QWidget *) l.at(i)->buttonPtr;
                grid->removeWidget(widget);
                widget->hide();
            }
            
            currentPlayer->collectCards(l);
        }

        playerIndex = (playerIndex + 1) % 4;
        currentPlayer = &players[playerIndex];

        if (game->getCards().size() == 0 && currentPlayer->getNumberOfCards() == 0)
            play = false;

        counter++;
        if(counter == 42)
            qDebug() <<  "42 ";
    }

    QList<Card *> &cardsOnTable = game->getPlayedCards();
    for (int i = 0; i < cardsOnTable.size(); i++) {
        QWidget *widget = (QWidget *) cardsOnTable.at(i)->buttonPtr;
        grid->removeWidget(widget);
        widget->hide();
    }
    game->getlastWinner()->collectCards(cardsOnTable);

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
    QFrame *frame;
    QWidget *button;
    int row, column, parentWidth, width, parentHeight, height;
    int x, y;

    switch (position) {
    case 0: // south
        row = 3;
        column = 2;
        frame = ui->tableSouth;
        break;
    case 1: // east
        row = 2;
        column = 3;
        frame = ui->tableEast;
        break;
    case 2: // north
        row = 1;
        column = 2;
        frame = ui->tableNorth;
        break;
    case 3: // west
        row = 2;
        column = 1;
        frame = ui->tableWest;
        break;
    case 4:
        frame = ui->tableCenter;
        break;
    default:
        frame = ui->tableCenter;
    }

    /* c->getButton() */
    /* (QWidget *) c->buttonPtr */
    QSize parentWidgetSize = frame->size();
    QSize buttonSize;

    parentWidth = parentWidgetSize.width();
    parentHeight = parentWidgetSize.width();

    button = static_cast<QWidget *>(c->buttonPtr);
    button->setParent(frame);

    // TODO: must be dynamically resized
    button->resize(60, 70);
    buttonSize = button->size();

    width = buttonSize.width();
    height = buttonSize.height();
    x = (parentWidth - width) / 2;
    y = (parentHeight - height) / 2;
    y -= y / 2;

    button->move(x, y);
    button->show();
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

    players = game->getPlayers();
    game->createCards();

    /* Yere ucu kapali dort kart at */
    for (int i = 0; i < 3; i++) {
        Card *c = game->getCards().takeFirst();
        game->appendToPlayedCards(c);
    }
    /* vale disinda bir kart ac */
    for (int i = 0; i < game->getCards().size(); i++)
        if (game->getCards().at(i)->cardNumber != 11) {
        game->appendToPlayedCards(game->getCards().takeAt(i));
        break;
    }

    QToolButton *but = new QToolButton(ui->tableCenter);
    but->setStyleSheet(QString("border-image: url(./graphics/back/3h.png)"));
    but->setMinimumSize(75, 55);
    but->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));

    Card *card = game->getPlayedCards().last();
    // TODO: getButton()
    // card->getButton();
    (static_cast<QWidget *>(card->buttonPtr))->setParent(ui->tableCenter);

    // TODO: i < numbeerOfPlayers
    for (int i = 0 ; i < game->getNumberOfOnlinePlayer(); i++) {
        //-- currentPlayer = &players[i];
        currentPlayer = game->nextPlayer();
        game->distributeCards( *currentPlayer, 4 );
    }

    for (int i = 1 ; i <= 3; i++) {
        showPlayerHand(i);
    }
    
    //-- currentPlayer = &players[0];
    currentPlayer = game->myself();
    // connect button signals to slots
    for (int i = 0; i < currentPlayer->getNumberOfCards(); i++) {
        QList<Card *> l = currentPlayer->getHand();
        connect(static_cast<QToolButton *>(l.at(i)->buttonPtr), SIGNAL(clicked()),
                mapper, SLOT(map()));
        mapper->setMapping(static_cast<QObject *>(l.at(i)->buttonPtr),
                           static_cast<QObject *>(l.at(i)));
        ui->southHand->layout()->addWidget(static_cast<QWidget *>(l.at(i)->buttonPtr));
    }
}

void Widget::cardClicked(QObject *obj)
{
    // disable my panel
    ui->southHand->setEnabled(false);

    Card *c = static_cast<Card *>(obj);
    int del = currentPlayer->getHand().indexOf(c);
    currentPlayer->getHand().removeAt(del);
    ui->southHand->layout()->removeWidget(static_cast<QWidget *>(c->buttonPtr));
    game->appendToPlayedCards(c);
    showCardOnTable(c, game->playerIndex());

    if (game->pisti(currentPlayer)) {
        QList<Card *> &l = game->getPlayedCards();

        delay(150);

        // yerdeki kartlari topla
        clearPanel(ui->tableCenter);
        clearPanel(ui->tableEast);
        clearPanel(ui->tableNorth);
        clearPanel(ui->tableWest);
        clearPanel(ui->tableSouth);
        //-- players[0].collectCards(l);
        currentPlayer->collectCards(l);
    }

    if (currentPlayer->getNumberOfCards() <= 1 && game->getCards().size() < 10) {
        qDebug() << "condition";
    }

    qDebug() << c->cardImageName;
    simulateOthers();
}

void Widget::simulateOthers()
{
    QWidget *currentPlayerFrame;

    while ((currentPlayer = game->nextPlayer()) != game->me()) {
        /* bu kosul nedeniyle oyuncu son kartini oynamadan oyun bitiyor */
        if ((game->getCards().size() == 0 || currentPlayer->getNumberOfCards() == 0 )
            && game->me()->getNumberOfCards() == 0) {
            clearPanel(ui->tableCenter);
            clearPanel(ui->tableEast);
            clearPanel(ui->tableNorth);
            clearPanel(ui->tableWest);
            clearPanel(ui->tableSouth);

            game->getlastWinner()->collectCards(game->getPlayedCards());
            statistics();
            return;
        }

        switch (game->playerIndex()) {
        case 1:
            currentPlayerFrame = ui->eastHand;
            break;
        case 2:
            currentPlayerFrame = ui->northHand;
            break;
        case 3:
            currentPlayerFrame = ui->westHand;
            break;
        }
        delay(150);

        Card *lastCard = game->lastPlayedCard();
        Card *recentCard = currentPlayer->dummyPlay(lastCard);
        game->appendToPlayedCards(recentCard);

        clearPanel(currentPlayerFrame, true);
        showPlayerHand(game->playerIndex(), currentPlayer->getNumberOfCards());
        showCardOnTable(recentCard, game->playerIndex());
        delay(150);

        if (game->pisti(currentPlayer)) {
            QList<Card *> &l = game->getPlayedCards();

            clearPanel(ui->tableCenter);
            clearPanel(ui->tableEast);
            clearPanel(ui->tableNorth);
            clearPanel(ui->tableWest);
            clearPanel(ui->tableSouth);

            currentPlayer->collectCards(l);
            delay(150);
        }
    }

    if (currentPlayer->getNumberOfCards() == 0 && game->getCards().size() != 0) {
        for (int i = 0; i < game->getNumberOfOnlinePlayer(); i++) {
            game->distributeCards( *currentPlayer, 4);

            if (currentPlayer != game->me()) {
                showPlayerHand(game->playerIndex(), currentPlayer->getNumberOfCards());
            } else {
                for (int j = 0; j < currentPlayer->getNumberOfCards(); j++) {
                    QList<Card *> m = currentPlayer->getHand();
                    connect(static_cast<QToolButton *>(m.at(j)->buttonPtr), SIGNAL(clicked()), mapper, SLOT(map()));
                    mapper->setMapping(static_cast<QObject *>(m.at(j)->buttonPtr), static_cast<QObject *>(m.at(j)));
                    ui->southHand->layout()->addWidget(static_cast<QWidget *>(m.at(j)->buttonPtr));
                }
            }
            currentPlayer = game->nextPlayer();
        }
    }

    ui->southHand->setEnabled(true);
}

#if 0
void Widget::simulateOthers()
{
    QWidget *currentPlayerFrame;
    QString alignment;
    currentPlayerIndex = 1;

    delay(150);

    for (int i = 1; currentPlayer != g.myself(); i++) {
        switch (currentPlayerIndex) {
        case 1:
            currentPlayerFrame = ui->eastHand;
            alignment = "v";
            break;
        case 2:
            currentPlayerFrame = ui->northHand;
            alignment = "h";
            break;
        case 3:
            currentPlayerFrame = ui->westHand;
            alignment = "v";
        }

        //-- currentPlayer = &players[currentPlayerIndex];
        currentPlayer = game->nextPlayer();
        Card *lastcard = game->lastPlayedCard();

        qDebug() << "before" << currentPlayer->getNumberOfCards();
        Card *c = currentPlayer->dummyPlay(lastcard);
        qDebug() << "after"<< currentPlayer->getNumberOfCards();
#if 0
        QLayoutItem *child;
        while ((child = currentPlayerLayout->takeAt(0)) != 0) {
            child->widget()->hide();
            delete child;
        }
#endif
        /* removes card back images */
        clearPanel(currentPlayerFrame, true);
        showPlayerHand(game->playerIndex(), currentPlayer->getNumberOfCards());
        game->appendToPlayedCards(c);
        showCardOnTable(c, game->playerIndex());

        delay(150);

        if (game->pisti(currentPlayer)) {
            QList<Card *> &l = game->getPlayedCards();

            // clearPanel(grid);
            clearPanel(ui->tableCenter);
            clearPanel(ui->tableEast);
            clearPanel(ui->tableNorth);
            clearPanel(ui->tableSouth);
            clearPanel(ui->tableWest);
            currentPlayer->collectCards(l);

            delay(150);
        }

        // TODO: Oyuncu sayisi dortten az olabilir
        qDebug() << "end of tour" << currentPlayer->getNumberOfCards();
        //-- currentPlayerIndex = (currentPlayerIndex + 1) % 4;
        currentPlayerIndex = (currentPlayerIndex + 1) % game->getNumberOfOnlinePlayer();
        qDebug() << "currentplayerindex :" << currentPlayerIndex;
        //-- currentPlayer = &players[currentPlayerIndex];
        currentPlayer = game->nextPlayer();

        /* Game over */
        if (game->getCards().size() == 0 && currentPlayer->getNumberOfCards() == 0) {
            /* yerdeki son kartlari al */
            game->getlastWinner()->collectCards(game->getPlayedCards());
            statistics();
            return;
        }
    }
#endif
#if 0
    do
    {
        switch (g.playerIndex()) {
        case 0:
            currentPlayerFrame = ui->southHand;
            break;
        case 1:
            currentPlayerFrame = ui->eastHand;
            alignment = "v";
            break;
        case 2:
            currentPlayerFrame = ui->northHand;
            alignment = "h";
            break;
        case 3:
            currentPlayerFrame = ui->westHand;
            alignment = "v";
        }

        currentPlayer = game->nextPlayer();
        Card *lastcard = game->lastPlayedCard();
        Card *c = currentPlayer->dummyPlay(lastcard);

        clearPanel(ui->eastHand, true);
        showPlayerHand(game->playerIndex(), currentPlayer->getNumberOfCards());
        game->appendToPlayedCards(c);
        showCardOnTable(c, game->playerIndex());

        if (game->pisti(currentPlayer)) {
            QList<Card *> &l = game->getPlayedCards();

            // clearPanel(grid);
            clearPanel(ui->tableCenter);
            clearPanel(ui->tableEast);
            clearPanel(ui->tableNorth);
            clearPanel(ui->tableSouth);
            clearPanel(ui->tableWest);
            currentPlayer->collectCards(l);

            delay(150);
        }

    } while (currentPlayer != g.myself());

    //-- currentPlayer = &players[currentPlayerIndex];    
    if (currentPlayer->getNumberOfCards() == 0) {
        //-- int tmpindex = currentPlayerIndex;
        int tmpindex = game->playerIndex();
        for (int i = 0 ; i < game->getNumberOfOnlinePlayer(); i++) {
            game->distributeCards( *currentPlayer, 4 );
            if (game->playerIndex() != 0)
                showPlayerHand(i);
            tmpindex = (tmpindex + 1) % game->getNumberOfOnlinePlayer();
            //-- currentPlayer = &players[tmpindex];
            currentPlayer = game->nextPlayer();
        }

        // connect button signals to slots
        //-- currentPlayer = &players[0];
        currentPlayer = game->myself();
        for (int i = 0; i < currentPlayer->getNumberOfCards(); i++) {
            QList<Card *> l = currentPlayer->getHand();
            connect(static_cast<QToolButton *>(l.at(i)->buttonPtr), SIGNAL(clicked()),
                    mapper, SLOT(map()));
            mapper->setMapping(static_cast<QObject *>(l.at(i)->buttonPtr),
                               static_cast<QObject *>(l.at(i)));
            ui->southHand->layout()->addWidget(static_cast<QWidget *>(l.at(i)->buttonPtr));
        }
    }

    // Enable my panel
    ui->southHand->setEnabled(true);
}
#endif

void Widget::on_pushButton_clicked()
{
    modifiedstart();
}

inline void Widget::delay(int count, int sleep)
{
    count = 30;
    while (count--) {
        usleep(sleep);
        QApplication::processEvents();
    }
}

void Widget::clearPanel(QWidget *widget, bool dealloc)
{
    QList<QWidget *> widgets = widget->findChildren<QWidget *>();
    QWidget *child;
    while (widgets.size() > 0) {
        child = widgets.takeFirst();
        child->hide();
        if (dealloc == true)
            delete child;
    }
}

void Widget::showPlayerHand(int index, int size)
{
    QLayout *layout;
    QString alignment;

    if (size < 1) return;

    switch (index) {
    case 0:
        layout = ui->southHand->layout();
        alignment = "h";
        break;
    case 1:
        layout = ui->eastHand->layout();
        alignment = "v";
        break;
    case 2:
        layout = ui->northHand->layout();
        alignment = "h";
        break;
    case 3:
        layout = ui->westHand->layout();
        alignment = "v";
    }

    QString style;
    QToolButton *but = new QToolButton;
    style = QString("border-image: url(./graphics/back/%1%2.png)").arg(size).arg(alignment);
    but->setMinimumSize(QSize(60, 60));
    but->setStyleSheet(style);
    layout->addWidget(but);
}

void Widget::statistics()
{
    QString resultStr;
    const int SIZE = game->getNumberOfOnlinePlayer();
    int scores[SIZE], pisti[SIZE], pistiA = 0, pistiB = 0, scoreA = 0, scoreB = 0;

    currentPlayer = game->myself();
    for (int i = 0; i < game->getNumberOfOnlinePlayer(); i++) {
        currentPlayer->computePlayerScore();
        scores[i] = currentPlayer->score;
        pisti[i] = currentPlayer->pistiCount;
        currentPlayer = game->nextPlayer();
    }

    if (SIZE > 2) {
        pistiA = pisti[0] + pisti[2];
        scoreA = scores[0] + scores[2];
        pistiB = pisti[1] + pisti[3];
        scoreB = scores[1] + scores[3];
    } else {
        pistiA = pisti[0];
        scoreA = scores[0];
        pistiB = pisti[1];
        scoreA = scores[1];
    }

    resultStr.append('\t');
    resultStr.append("First Team");
    resultStr.append('\t');
    resultStr.append('\t');
    resultStr.append("Second Team");
    resultStr.append('\n');

    resultStr.append("Pisti:");
    resultStr.append('\t');
    resultStr.append(QString::number(pistiA));
    resultStr.append('\t');
    resultStr.append('\t');
    resultStr.append(QString::number(pistiB));
    resultStr.append('\n');

    resultStr.append("Result:");
    resultStr.append('\t');
    resultStr.append(QString::number(scoreA));
    resultStr.append('\t');
    resultStr.append('\t');
    resultStr.append(QString::number(scoreB));
    resultStr.append('\n');

    ui->resultlabel->setText(resultStr);
    ui->stackedWidget->setCurrentIndex(2);
}

void Widget::on_styletoolSingle_clicked()
{
    if (ui->stylecombo->currentIndex() == 0) {
        game = new GameEngine(4);
    } else if (ui->stylecombo->currentIndex() == 1) {
        game = new GameEngine(2);
    }

    modifiedstart();
    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::on_pushButton_2_toggled(bool checked)
{
    if (checked)
        this->showFullScreen();
    else
        this->showNormal();
}

QFrame* Widget::getCurrentPlayerFrame() const
{
    QFrame *currentPlayerFrame;
    switch (game->playerIndex()) {
    case 0:
        currentPlayerFrame = ui->southHand;
        break;
    case 1:
        currentPlayerFrame = ui->eastHand;
        break;
    case 2:
        currentPlayerFrame = ui->northHand;
        break;
    case 3:
        currentPlayerFrame = ui->westHand;
        break;
    }

    return currentPlayerFrame;
}

QFrame* Widget::getPlayerFrame(int pos) const
{
	QFrame *currentPlayerFrame;
	switch (pos) {
	case 0:
		currentPlayerFrame = ui->southHand;
		break;
	case 1:
		currentPlayerFrame = ui->eastHand;
		break;
	case 2:
		currentPlayerFrame = ui->northHand;
		break;
	case 3:
		currentPlayerFrame = ui->westHand;
		break;
	}

	return currentPlayerFrame;
}

void Widget::networkStart()
{
#if 0
    QList<int> args;
    QList<Card *> m;

    qDebug() << "network start";
    if (hostMachine) {
        game = new GameEngine(2);
        peers = network->getPeers();
        game->createCards();

        for (int i = 0 ; i < game->getNumberOfOnlinePlayer(); i++) {
            currentPlayer = game->nextPlayer();
            game->distributeCards( *currentPlayer, 4 );

            m = currentPlayer->getHand();
            foreach (Card *c, m) {
                args << c->cardType << c->cardNumber;
            }
            // network->sendMessage(peers[i], GameNet::SET_HAND, args);
        }

        posInterval = 4 - game->playerIndex();

        network->broadcast(GameNet::SET_HAND, args);

        for (int i = 1 ; i < game->getNumberOfOnlinePlayer(); i++) {
            showPlayerHand(i);
        }

        currentPlayer = game->myself();
        for (int i = 0; i < currentPlayer->getNumberOfCards(); i++) {
            QList<Card *> l = currentPlayer->getHand();
            connect(static_cast<QToolButton *>(l.at(i)->buttonPtr), SIGNAL(clicked()),
                    mapper, SLOT(map()));
            mapper->setMapping(static_cast<QObject *>(l.at(i)->buttonPtr),
                               static_cast<QObject *>(l.at(i)));
            ui->southHand->layout()->addWidget(static_cast<QWidget *>(l.at(i)->buttonPtr));
        }

    } else {
        socket = network->getClientSoc();
        currentPlayer = me = new Person();
    }

    ui->stackedWidget->setCurrentIndex(1);
#endif

#if PROB
    if(hostMachine == true) {
        peers = network->getPeers();
        game = new GameEngine;
        game->createCards();

        Person *pl_a = new Person(0);
        Person *pl_b = new Person(2);
        me = currentPlayer = pl_a;

        game->add(pl_a, 0);
        game->add(pl_b, 2);

        game->distributeCards(*pl_a, 4);
        game->distributeCards(*pl_b, 4);
        posRelative = 4 - pl_a->getPosition();

        currentPlayer = pl_a;
        for (int i = 0; i < pl_a->getNumberOfCards(); i++) {
            QList<Card *> l = pl_a->getHand();
            connect(static_cast<QToolButton *>(l.at(i)->buttonPtr), SIGNAL(clicked()),
                    mapper, SLOT(map()));
            mapper->setMapping(static_cast<QObject *>(l.at(i)->buttonPtr),
                               static_cast<QObject *>(l.at(i)));
            ui->southHand->layout()->addWidget(static_cast<QWidget *>(l.at(i)->buttonPtr));
        }

        QList<int> args;
        QList<Card *> &m = pl_b->getHand();
        foreach (Card *card, m) {
            args << card->cardType << card->cardNumber;
        }
        network->broadcast(GameNet::SET_HAND, args);
        showPlayerHand(2);

    } else {
        socket = network->getClientSoc();
        currentPlayer = me = new Person(0);
    }
#endif

    if (hostMachine == true) {
    	QList<int> args;

    	peers = network->getPeers();
    	game = new GameEngine(true, 2);
    	game->createCards();

    	game->tAdd(0);
    	game->tAdd(2);

    	game->toSouth()->setMyself(true);
        game->toSouth()->setPlayerName(QString("Cihangir"));
        game->toSouth()->setPosition(0);

    	me = game->toSouth();
    	posRelative = 0;

    	if (! peers.isEmpty())
    		game->toNorth()->setSocket(peers.at(0));

    	currentPlayer = game->toSouth();
    	game->distributeCards(*currentPlayer, 4);

    	// north
    	currentPlayer = game->tNextPlayer();
    	game->distributeCards(*currentPlayer, 4);

        qDebug() << "game->tSize()" << game->tSize();

        // south
    	currentPlayer = game->toSouth();
        for (int i = 0; i < currentPlayer->getNumberOfCards(); i++) {
            QList<Card *> l = currentPlayer->getHand();
            connect(static_cast<QToolButton *>(l.at(i)->buttonPtr), SIGNAL(clicked()),
                    mapper, SLOT(map()));
            mapper->setMapping(static_cast<QObject *>(l.at(i)->buttonPtr),
                               static_cast<QObject *>(l.at(i)));
            ui->southHand->layout()->addWidget(static_cast<QWidget *>(l.at(i)->buttonPtr));
        }

        // north
    	currentPlayer = game->tNextPlayer();
        QList<Card *> &m = currentPlayer->getHand();
        foreach (Card *card, m) {
            args << card->cardType << card->cardNumber;
        }

        network->broadcast(GameNet::SET_HAND, args);

    	qDebug() << "peers size " <<  peers.size();
    } else {
        // We don't need a GameEngine
        game = NULL;
    }

    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::SNetworkStart()
{
	currentPlayer = game->toSouth();

	for (int i = 0; i < game->tSize(); ++i) {
		game->distributeCards( *currentPlayer, 4 );

		if (currentPlayer->myself()) {
			for (int i = 0; i < currentPlayer->getNumberOfCards(); i++) {
				QList<Card *> l = currentPlayer->getHand();
				connect(static_cast<QToolButton *>(l.at(i)->buttonPtr), SIGNAL(clicked()),
						mapper, SLOT(map()));
				mapper->setMapping(static_cast<QObject *>(l.at(i)->buttonPtr),
						static_cast<QObject *>(l.at(i)));
				ui->southHand->layout()->addWidget(static_cast<QWidget *>(l.at(i)->buttonPtr));
			}
		} else {
			QList<Card *> &m = currentPlayer->getHand();
			QList<int> args;

			foreach (Card *card, m) {
				args << currentPlayer->getPosition() << card->cardType << card->cardNumber;
			}
			network->sendMessage(socket, GameNet::SET_HAND, args);
		}

		currentPlayer = game->tNextPlayer();
	}

    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::n_cardClicked(QObject *obj)
{
    ui->southHand->setEnabled(false);

    if (hostMachine == true)
        currentPlayer = game->toSouth();

    QList<int> args;

    Card *card = static_cast<Card *>(obj);

    int cardIndex = 0;
    QList<Card *> &l_hand = currentPlayer->getHand();
    for (int i = 0; i < currentPlayer->getNumberOfCards(); ++i)
        if (card == l_hand.at(i))
            cardIndex = i;

    int del = currentPlayer->getHand().indexOf(card);
    currentPlayer->getHand().removeAt(del);
    ui->southHand->layout()->removeWidget(static_cast<QWidget *>(card->buttonPtr));

    if (hostMachine == true)
        game->appendToPlayedCards(card);

    //QList<int> args;

    if (hostMachine) {
        args << currentPlayer->getPosition() << card->cardType << card->cardNumber;
        network->broadcast(GameNet::SHOW_CARD_ONTABLE, args);
    } else {
        args << cardIndex;
        network->sendMessage(socket, GameNet::PLAY, args);
    }

    // showCardOnTable(card, game->playerIndex());
    int cardPos = (currentPlayer->getPosition() + posRelative) % 4;
    showCardOnTable(card, cardPos);

    delay(150);

    if (hostMachine == true) {
        if (game->pisti(currentPlayer)) {
            QList<Card *> &m = game->getPlayedCards();

            // TODO: appropriate way of clearing args list
            args.clear();

            clearPanel(ui->tableCenter);
            clearPanel(ui->tableEast);
            clearPanel(ui->tableNorth);
            clearPanel(ui->tableWest);
            clearPanel(ui->tableSouth);
            currentPlayer->collectCards(m);

            network->broadcast(GameNet::CLEAR_TABLE);

            // currentPlayer = game->tNextPlayer();
        }
        delay(150);
        network->broadcast(GameNet::CURRENT_PLAYER);
    }
}

void Widget::SCardClicked(QObject *obj)
{
    ui->southHand->setEnabled(false);

    QList<int> args;
    Card *card = static_cast<Card *>(obj);
    int cardPos = 0, del = 0, cardIndex = 0;

    if (hostMachine == true) {
        QList<Card *> &l_hand = currentPlayer->getHand();

        for (int i = 0; i < currentPlayer->getNumberOfCards(); ++i)
            if (card == l_hand.at(i))
                cardIndex = i;

        del = currentPlayer->getHand().indexOf(card);
        currentPlayer->getHand().removeAt(del);
        ui->southHand->layout()->removeWidget(static_cast<QWidget *>(card->buttonPtr));

        game->appendToPlayedCards(card);

        args << currentPlayer->getPosition() << card->cardType << card->cardNumber;
        network->broadcast(GameNet::SHOW_CARD_ONTABLE, args);
        delay(150);

        if (game->pisti(currentPlayer)) {
            QList<Card *> &m = game->getPlayedCards();
            args.clear();

            clearPanel(ui->tableCenter);
            clearPanel(ui->tableEast);
            clearPanel(ui->tableNorth);
            clearPanel(ui->tableWest);
            clearPanel(ui->tableSouth);
            currentPlayer->collectCards(m);

            network->broadcast(GameNet::CLEAR_TABLE);
            delay(150);
        }

        currentPlayer = game->tNextPlayer();
        socket = currentPlayer->getSocket();
        network->sendMessage(socket, GameNet::CURRENT_PLAYER);
        delay(150);

    } else {
        QList<Card *> &l_hand = currentPlayer->getHand();

        for (int i = 0; i < currentPlayer->getNumberOfCards(); ++i)
            if (card == l_hand.at(i))
                cardIndex = i;

        del = currentPlayer->getHand().indexOf(card);
        currentPlayer->getHand().removeAt(del);
        ui->southHand->layout()->removeWidget(static_cast<QWidget *>(card->buttonPtr));

        args << cardIndex;
        network->sendMessage(socket, GameNet::PLAY, args);

        cardPos = (currentPlayer->getPosition() + posRelative) % 4;
        showCardOnTable(card, cardPos);
        delay(150);
    }
}

void Widget::n_simulateOthers()
{
    QWidget *currentPlayerFrame;

    while ((currentPlayer = game->nextPlayer()) != game->me()) {
        switch (game->playerIndex()) {
        case 1:
            currentPlayerFrame = ui->eastHand;
            break;
        case 2:
            currentPlayerFrame = ui->northHand;
            break;
        case 3:
            currentPlayerFrame = ui->westHand;
            break;
        }

        // Card *recentCard = currentPlayer->dummyPlay(lastCard);
        network->broadcast(GameNet::CURRENT_PLAYER);
        delay(150);
    }

    //connect(network, SIGNAL(messageReceived(QTcpSocket*)), this, SLOT(deleteLater()));
}

void Widget::processMessage(QTcpSocket *sc)
{
    switch (network->getReceivedCommand()) {
    case GameNet::SET_HAND: // server to client
        n_set_hand();
        break;
    case GameNet::SET_PLAYER_NAME: // client to server
        n_set_player_name();
        break;
    case GameNet::SET_PLAYER_POS: // client to server
        n_set_player_pos(sc);
        break;
    case GameNet::GET_PLAYER_POS:
        n_get_player_pos();
        break;
    case GameNet::CLEAR_TABLE: // server to client
        n_clear_table();
        break;
    case GameNet::CLEAR_FRAME: // server to client
        n_clear_frame();
        break;
    case GameNet::SHOW_SCOREBOARD: // server to client
        // TODO: n_show_scoreboard()
        break;
    case GameNet::SHOW_CARD_ONTABLE: // server to client
        n_show_card_ontable();
        break;
    case GameNet::CURRENT_PLAYER: // server to client
        n_current_player();
        break;
    case GameNet::NOT_CURRENT_PLAYER: // server to client
        n_not_current_player();
        break;
    case GameNet::PLAY: // client to server
        n_play();
        break;
    case GameNet::UPDATE_GUI:
        n_update_gui();
        break;
    }
}

void Widget::n_set_hand()
{
    QList<int> args = network->arguments();

    if (args.isEmpty())
        return;

    QList<Card *> list;
    QListIterator<int> it(args);

    while (it.hasNext()) {
        int type, num;
        type = it.next();
        num = it.next();
        Card *card = new Card(type, num);
        list.append(card);
    }

    socket = network->getClientSoc();
    currentPlayer = me = new Person;
    currentPlayer->setPosition(2);
    currentPlayer->setPlayerName(QString("Rakip"));
    posRelative = 2;

    currentPlayer->setHand(list);

    for (int i = 0; i < currentPlayer->getNumberOfCards(); i++) {
        QList<Card *> l = currentPlayer->getHand();
        connect(static_cast<QToolButton *>(l.at(i)->buttonPtr), SIGNAL(clicked()),
                mapper, SLOT(map()));
        mapper->setMapping(static_cast<QObject *>(l.at(i)->buttonPtr),
                           static_cast<QObject *>(l.at(i)));
        ui->southHand->layout()->addWidget(static_cast<QWidget *>(l.at(i)->buttonPtr));
    }

    for (int i = 0; i < list.size(); i++)
        ui->southHand->layout()->addWidget(static_cast<QWidget *>(list.at(i)->buttonPtr));
}

void Widget::n_set_player_name()
{
    // TODO: argument list must be QString
    QList<int> args = network->arguments();
    QString name;

    if (args.isEmpty())
        return;

    name = args.first();
}

/**
 * user selects where to sit on the table adds
 * user to GameEngine on the server side.
 */
void Widget::n_set_player_pos(QTcpSocket *sc)
{
    QList<int> args = network->arguments();

    if (args.isEmpty())
        return;

    int position = args.takeFirst();

    switch (position) {
    case 0:
        pushSouth->hide();
        break;
    case 1:
        pushEast->hide();
        break;
    case 2:
        pushNorth->hide();
        break;
    case 3:
        pushWest->hide();
        break;
    default:
        break;
    }

    if (hostMachine == true) {
        Person *newPlayer = new Person;
        newPlayer->setPosition(position);
        newPlayer->setPlayerName(QString("Player %1").arg(QString::number(position)));
        newPlayer->setSocket(sc);

        game->tAdd(newPlayer, position);
    }
}

void Widget::n_get_player_pos()
{
    QList<int> args = network->arguments();

    if (args.isEmpty())
        return;
}

void Widget::n_clear_table()
{
    clearPanel(ui->tableCenter, true);
    clearPanel(ui->tableEast, true);
    clearPanel(ui->tableNorth, true);
    clearPanel(ui->tableWest, true);
    clearPanel(ui->tableSouth, true);
}

void Widget::n_clear_frame()
{
    QList<int> args = network->arguments();

    if (args.isEmpty())
        return;

    int index = args.first();
    index += posRelative;

    switch (index) {
    case 0:
        clearPanel(ui->southHand, true);
        break;
    case 1:
        clearPanel(ui->eastHand, true);
        break;
    case 2:
        clearPanel(ui->northHand, true);
        break;
    case 3:
        clearPanel(ui->westHand, true);
        break;
    default:
        qDebug() << "n_clear_frame() error";
    }
}

void Widget::n_show_card_ontable()
{
    QList<int> args = network->arguments();

    if (args.isEmpty())
        return;

    int cardPos = args.takeFirst();
    cardPos += posRelative;

    int type, num;
    type = args.takeFirst();
    num = args.takeFirst();

    Card *card = new Card(type, num);
    showCardOnTable(card, cardPos);

    if (cardPos < 0 || cardPos > 3)
        qDebug() << "Breakpoint " << cardPos;
}

void Widget::n_current_player()
{
    me->setTurn(true);
    ui->southHand->setEnabled(true);
}

void Widget::n_not_current_player()
{
    me->setTurn(false);
    ui->southHand->setEnabled(false);
}

// Server mode
void Widget::n_play()
{
    QList<int> args = network->arguments();
    currentPlayer = game->tNextPlayer();

    if (args.isEmpty())
        return;

    int cardIndex = args.first();
    Card *card = currentPlayer->play(cardIndex);
    game->appendToPlayedCards(card);
    
    int cardPos = (currentPlayer->getPosition() + posRelative) % 4;
    showCardOnTable(card, cardPos);

    if (game->pisti(currentPlayer)) {
        network->broadcast(GameNet::CLEAR_TABLE);

        QList<Card *> &m = game->getPlayedCards();
        delay(150);

        clearPanel(ui->tableCenter);
        clearPanel(ui->tableEast);
        clearPanel(ui->tableNorth);
        clearPanel(ui->tableWest);
        clearPanel(ui->tableSouth);
        currentPlayer->collectCards(m);
    }

    ui->southHand->setEnabled(true);
}

void Widget::n_update_gui()
{
    QList<int> args = network->arguments();

    if (args.isEmpty())
        return;

    int realPos = args.takeFirst();
    int cardNum = args.takeFirst();
    // if it's me discard message.
    if (realPos == game->playerIndex())
        return;

    QWidget *frame = getCurrentPlayerFrame();
    clearPanel(frame, true);
    showPlayerHand(realPos, cardNum);
}

void Widget::on_styletoolMulti_clicked()
{
    int numOfPlayer = 0;
    numOfPlayer = (ui->stylecombo->currentIndex() == 0) ? 4 : 2;

    if (ui->checkBox->isChecked() == true) {
        game = new GameEngine(true, numOfPlayer);
        network = new GameNet(this, true, numOfPlayer);
        connect(network, SIGNAL(messageReceived(QTcpSocket*)), this, SLOT(processMessage(QTcpSocket*)));
        n_preNetwork_start(true);
    } else {
        network = new GameNet(this, false, numOfPlayer);
        connect(network, SIGNAL(messageReceived(QTcpSocket*)), this, SLOT(processMessage(QTcpSocket*)));
        n_preNetwork_start(false);
    }
    connect(network, SIGNAL(messageReceived(QTcpSocket*)), this, SLOT(processMessage(QTcpSocket*)));
}

void Widget::preNetStart(bool server)
{
    hostMachine = server;
    network = new GameNet(this, server);
    connect(network, SIGNAL(messageReceived(QTcpSocket*)), this, SLOT(processMessage(QTcpSocket*)));

    // client
    if (server == false)
        connect(network->getClientSoc(), SIGNAL(connected()), this, SLOT(networkStart()));
    else
    	connect(network, SIGNAL(serverReady()), this, SLOT(networkStart()));
}

void Widget::n_preNetwork_start(bool b)
{
    hostMachine = b;

    if (hostMachine == false) {
    	socket = network->getClientSoc();
        connect(socket, SIGNAL(connected()), this, SLOT(prepareNetworkUI()));
    } else {
        connect(game, SIGNAL(ready()), this, SLOT(networkStart()));
        prepareNetworkUI();
    }
}

void Widget::prepareNetworkUI()
{
    pushSouth = new QPushButton("Otur", this);
    pushEast = new QPushButton("Otur", this);
    pushNorth = new QPushButton("Otur", this);
    pushWest = new QPushButton("Otur", this);
    ui->southHand->layout()->addWidget(pushSouth);
    ui->eastHand->layout()->addWidget(pushEast);
    ui->northHand->layout()->addWidget(pushNorth);
    ui->westHand->layout()->addWidget(pushWest);

    QSignalMapper *pushMapper = new QSignalMapper(this);
    connect(pushSouth, SIGNAL(clicked()), pushMapper, SLOT(map()));
    connect(pushEast, SIGNAL(clicked()), pushMapper, SLOT(map()));
    connect(pushNorth, SIGNAL(clicked()), pushMapper, SLOT(map()));
    connect(pushWest, SIGNAL(clicked()), pushMapper, SLOT(map()));

    pushMapper->setMapping(pushSouth, 0);
    pushMapper->setMapping(pushEast, 1);
    pushMapper->setMapping(pushNorth, 2);
    pushMapper->setMapping(pushWest, 3);

    connect(pushMapper, SIGNAL(mapped(int)), this, SLOT(slotPrepareNetworkUI(int)));
    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::slotPrepareNetworkUI(int n)
{
    Person *newPlayer = NULL;
    QList<int> args;
    args << n;

    if (hostMachine == true) {
        newPlayer = new Person();
        newPlayer->setPlayerName(QString("Host player"));
        newPlayer->setMyself(true);
        game->tAdd(newPlayer, n);
        network->broadcast(GameNet::SET_PLAYER_POS, args);
    } else {
        network->sendMessage(socket, GameNet::SET_PLAYER_POS, args);
    }

    pushSouth->hide();
    pushEast->hide();
    pushNorth->hide();
    pushWest->hide();
    delay(150);
}

