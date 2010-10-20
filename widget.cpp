#include "widget.h"
#include "ui_widget.h"

#define TESTT
#define TEST_CONST
#undef TEST_CONST
#define PROB 0

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),game(0), network(0), browser(0), resolver(0), registrar(0)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->gridLayout->setSpacing(0);

    game = NULL;
    currentPlayerIndex = 0;

    mapper = new QSignalMapper(this);
    // connect(mapper, SIGNAL(mapped(QObject *)), this, SLOT(cardClicked(QObject *)));
    connect(mapper, SIGNAL(mapped(QObject *)), this, SLOT(SCardClicked(QObject*)));
    connect(ui->lineEditServerName, SIGNAL(returnPressed()), ui->buttonCreateServer, SLOT(click()));
    connect(ui->lineEditName, SIGNAL(returnPressed()), ui->buttonEnterName, SLOT(click()));

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

inline void Widget::delay(int count, int sleep)
{
    count = 30;
    while (count--) {
        usleep(sleep);
        QApplication::processEvents();
    }
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

void Widget::statistics()
{
    QString resultStr;
    const int SIZE = game->getNumberOfPlayer();
    int scores[SIZE], pisti[SIZE], pistiA = 0, pistiB = 0, scoreA = 0, scoreB = 0;

    currentPlayer = game->myself();
    for (int i = 0; i < game->getNumberOfPlayer(); i++) {
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
    for (int i = 0 ; i < game->getNumberOfPlayer(); i++) {
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
        for (int i = 0; i < game->getNumberOfPlayer(); i++) {
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
        currentPlayerIndex = (currentPlayerIndex + 1) % game->getNumberOfPlayer();
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
        for (int i = 0 ; i < game->getNumberOfPlayer(); i++) {
            game->distributeCards( *currentPlayer, 4 );
            if (game->playerIndex() != 0)
                showPlayerHand(i);
            tmpindex = (tmpindex + 1) % game->getNumberOfPlayer();
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

void Widget::on_styletoolSingle_clicked()
{
    if (ui->comboSinglePlayer->currentIndex() == 0) {
        game = new GameEngine(4);
    } else if (ui->comboSinglePlayer->currentIndex() == 1) {
        game = new GameEngine(2);
    }

    modifiedstart();
    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::on_buttonToggle_toggled(bool checked)
{
    if (checked)
        this->showFullScreen();
    else
        this->showNormal();
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
    qDebug() << "processMessage :" << network->getReceivedCommand();
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
        n_show_scoreboard();
        break;
    case GameNet::SHOW_CARD_ONTABLE: // server to client
        n_show_card_ontable(sc);
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
    case GameNet::PREPARE_NETWORK_UI:
        n_prepare_network_ui();
        break;
    case GameNet::SHOW_PLAYER_HAND:
        n_show_player_hand(sc);
        break;
    case GameNet::REQUEST_HAND:
        n_request_hand();
        break;
    case GameNet::SHOW_CARD_BACK:
    	n_show_card_back();
    	break;
    case GameNet::CHAT_MESSAGE:
        n_chat_message(sc);
        break;
    }
}

void Widget::n_set_hand()
{
    qDebug() << "n_set_hand";
    QList<int> args = network->arguments();

    if (args.isEmpty())
        return;

    int pos = args.takeFirst();

    QList<Card *> list;
    QListIterator<int> it(args);

    while (it.hasNext()) {
        int type, num;
        type = it.next();
        num = it.next();
        Card *card = new Card(type, num);
        list.append(card);
    }

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

    args.clear();
    args << currentPlayer->getPosition() << currentPlayer->getNumberOfCards();
    network->sendMessage(socket, GameNet::SHOW_PLAYER_HAND, args);
}

void Widget::n_set_player_name()
{
    // TODO: argument list must be QString
    QList<QString> args = network->stringArguments();

    if (args.isEmpty())
        return;

    int pos = args.takeFirst().toInt();
    QString player_name = args.first();

    game->at(pos)->setPlayerName(player_name);
}

/**
 * user selects where to sit on the table adds
 * user to GameEngine on the server side.
 */
void Widget::n_set_player_pos(QTcpSocket *sc)
{
    qDebug() << "n_set_player_pos";
    QList<int> args = network->arguments();

    if (args.isEmpty())
        return;

    int position = args.first();

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

    if (host == true) {
        Person *newPlayer = new Person;
        newPlayer->setPosition(position);
        newPlayer->setPlayerName(QString("Player %1").arg(QString::number(position)));
        newPlayer->setSocket(sc);

        game->tAdd(newPlayer, position);
        network->broadcast(GameNet::SET_PLAYER_POS, args, sc);
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

void Widget::n_show_card_ontable(QTcpSocket *sock)
{
    qDebug() << "show card on the table";
    QList<int> args = network->arguments();

    if (args.isEmpty())
        return;

    int cardPos, outgoingPos;
    outgoingPos = cardPos = args.takeFirst();
    if (cardPos == currentPlayer->getPosition())
        return;

    if (cardPos != 4)
    	cardPos = (cardPos + posRelative) % 4;

    int type, num;
    type = args.takeFirst();
    num = args.takeFirst();

    Card *card = new Card(type, num);
    showCardOnTable(card, cardPos);

    args.clear();
    args << outgoingPos << type << num;
    // network->broadcast(GameNet::SHOW_CARD_ONTABLE, sock);

    if (cardPos < 0 || cardPos > 3)
        qDebug() << "Breakpoint " << cardPos;
}

void Widget::n_current_player()
{
    qDebug() << "set current player";

//    qDebug() << "num of cards :" << currentPlayer->getNumberOfCards();
//    if (currentPlayer->getNumberOfCards() == 0) {
//        if (host == true) {
//            renewTurn();
//        } else {
//            /* player have no cards. */
//            network->sendMessage(currentPlayer->getSocket(), GameNet::REQUEST_HAND);
//        }
//    }

    currentPlayer->setTurn(true);
    ui->southHand->setEnabled(true);
}

void Widget::n_not_current_player()
{
    currentPlayer->setTurn(false);
    ui->southHand->setEnabled(false);
}

// Server mode
void Widget::n_play()
{
    QList<int> args = network->arguments();
    int cardIndex, cardPos;

    if (args.isEmpty())
        return;

    cardPos = args.takeFirst();
    cardIndex = args.takeFirst();
    // Card *card = currentPlayer->play(cardIndex);
    Card *card = game->at(cardPos)->play(cardIndex);
    game->appendToPlayedCards(card);

    /* inform others about played cards */
    args.clear();
    args << cardPos << card->cardType << card->cardNumber;
    network->broadcast(GameNet::SHOW_CARD_ONTABLE, args);
    delay(150);

    // int cardPos = (currentPlayer->getPosition() + posRelative) % 4;
    cardPos = (cardPos + posRelative) % 4;
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

    currentPlayer = game->tNextPlayer();
    if (currentPlayer->getNumberOfCards() == 0) {
        if (game->numberOfCards() > 42) {
            qDebug() << "deck :" << game->numberOfCards();
            renewTurn();
        } else {
            gameOver();
            return;
        }
    }

    if (! currentPlayer->myself()) {
        network->sendMessage(currentPlayer->getSocket(), GameNet::CURRENT_PLAYER);
        delay(150);
        return;
    }
    ui->southHand->setEnabled(true);
}

void Widget::n_prepare_network_ui()
{
    prepareNetworkUI();
}

void Widget::n_show_player_hand(QTcpSocket *sock)
{
    qDebug() << "n_show_player_hand";
    QList<int> args = network->arguments();

    if (args.isEmpty())
        return;

    int cardPos = args.first();
    int size = args.at(1);

    cardPos = (cardPos + posRelative) % 4;
    clearPanel(getPlayerFrame(cardPos), true);
    showPlayerHand(cardPos, size);

    if (host == true)
        network->broadcast(GameNet::SHOW_PLAYER_HAND, args, sock);
}

void Widget::n_request_hand()
{
    renewTurn();
}

void Widget::n_show_card_back()
{
    qDebug() << "n_show_card_back";
    QList<int> args;
    args = network->arguments();

    if (args.isEmpty())
        return;

    int number = args.takeFirst();

    QToolButton *button = new QToolButton(ui->tableCenter);
    button->setStyleSheet(QString("border-image: url(./graphics/back/%1h.png)").arg(QString::number(number)));
    button->setMinimumSize(150, 70);
    button->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    button->show();
}

void Widget::n_show_scoreboard()
{
    qDebug() << "n_show_scoreboard";
    QString string;
    QList<QString> list = network->stringArguments();

    if (list.isEmpty())
        return;

    string = list.first();
    ui->resultlabel->setText(string);
    ui->stackedWidget->setCurrentIndex(2);
}

void Widget::n_chat_message(QTcpSocket *sock)
{
    QList<QString> list = network->stringArguments();
    QString nick, message;

    if (list.isEmpty())
        return;

    nick = "<b style=\"color: blue\">" + list.at(0) + ":</b>";
    message = list.at(1);

    ui->textEditChatMessage->append(nick + " " + message);
    ui->textEditChatMessage->ensureCursorVisible();

    if (host == true)
        network->broadcastString(GameNet::CHAT_MESSAGE, list, sock);
    list.clear();
    qDebug() << nick << " " << message;
}

void Widget::on_styletoolMulti_clicked()
{
    int numOfPlayer = 0;
    numOfPlayer = (ui->comboSinglePlayer->currentIndex() == 0) ? 4 : 2;

//    if (ui->checkBox->isChecked() == true) {
//        game = new GameEngine(true, numOfPlayer);
//        network = new GameNet(this, true, numOfPlayer);
//        connect(network, SIGNAL(messageReceived(QTcpSocket*)), this, SLOT(processMessage(QTcpSocket*)));
//        n_preNetwork_start(true);
//    } else {
//        network = new GameNet(this, false, numOfPlayer);
//        connect(network, SIGNAL(messageReceived(QTcpSocket*)), this, SLOT(processMessage(QTcpSocket*)));
//        n_preNetwork_start(false);
//    }
}

void Widget::on_buttonCreateServer_clicked()
{
    int buttonId = ui->buttonGroup->checkedId();
    if (buttonId == -1)
        return;

    if (ui->lineEditServerName->text().isEmpty()) {
        QMessageBox message;
        message.setText("Please, enter server name");
        message.setIcon(QMessageBox::Information);
        message.exec();
        return;
    }

    ui->buttonCreateServer->setEnabled(false);
    ui->buttonConnect->setEnabled(false);
    game = new GameEngine(true, buttonId, this);
    network = new GameNet(this, true, buttonId - 1);
    connect(network, SIGNAL(messageReceived(QTcpSocket*)), this, SLOT(processMessage(QTcpSocket*)));
    connect(network, SIGNAL(serverReady()), SLOT(sendPrepareUi()));

    QString serverName = ui->lineEditServerName->text();
    serverName = serverName.isEmpty() ?
                         " Game server on " + QHostInfo::localHostName() :
                         serverName+ " on " + QHostInfo::localHostName();

    registrar = new AvahiRegistrar(this);
    AvahiRecord record(serverName, QString("_bilkon._tcp"), QLatin1String(""));
    registrar->registerService(record, 33333);

    n_preNetwork_start(true);
}

void Widget::preNetStart(bool server)
{
    host = server;
    network = new GameNet(this, server);
    connect(network, SIGNAL(messageReceived(QTcpSocket*)), this, SLOT(processMessage(QTcpSocket*)));

    // client
    if (server == false)
        connect(network->getClientSoc(), SIGNAL(connected()), this, SLOT(networkStart()));
    else
    	connect(network, SIGNAL(serverReady()), this, SLOT(networkStart()));
}

void Widget::n_cardClicked(QObject *obj)
{
    ui->southHand->setEnabled(false);

    if (host == true)
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

    if (host == true)
        game->appendToPlayedCards(card);

    if (host) {
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

    if (host == true) {
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

void Widget::n_preNetwork_start(bool b)
{
    host = b;

    if (host == true) {
        connect(game, SIGNAL(ready()), this, SLOT(SNetworkStart()));
        prepareNetworkUI();
    } else {
        socket = network->getClientSoc();
        Person *newPlayer;
        currentPlayer = newPlayer = new Person;
        if (name.isEmpty())
            name = "Remote player";
        newPlayer->setPlayerName(name);
        newPlayer->setMyself(true);
        // connect(socket, SIGNAL(connected()), this, SLOT(prepareNetworkUI()));
    }
}

void Widget::SNetworkStart()
{
    qDebug() << "SNetworkStart";
    if (host == true) {

        Card *card;
        QList<int> operand;

        for (int j = 0; j < 3; ++j) {
            card = game->getCards().takeFirst();
            game->appendToPlayedCards(card);
        }
        operand << 3;
        network->broadcast(GameNet::SHOW_CARD_BACK, operand);

        for (int j = 0; j < game->getCards().size(); j++)
            if (game->getCards().at(j)->cardNumber != 11) {
            game->appendToPlayedCards(game->getCards().takeAt(j));
            break;
        }
        operand.clear();
        card = game->getPlayedCards().last();
        operand << 4 << card->cardType << card->cardNumber;
        network->broadcast(GameNet::SHOW_CARD_ONTABLE, operand);

        QToolButton *button = new QToolButton(ui->tableCenter);
        button->setStyleSheet(QString("border-image: url(./graphics/back/3h.png)"));
        button->setMinimumSize(150, 70);
        button->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
        button->show();
        (static_cast<QWidget *>(card->buttonPtr))->setParent(ui->tableCenter);
        (static_cast<QWidget *>(card->buttonPtr))->show();

        currentPlayer = game->toSouth();
        for (int i = 0; i < game->tSize(); ++i) {
            game->distributeCards( *currentPlayer, 4 );

            if (currentPlayer->myself()) {
                QList<Card *> l = currentPlayer->getHand();

                for (int j = 0; j < l.size(); j++) {
                    connect(static_cast<QToolButton *>(l.at(j)->buttonPtr), SIGNAL(clicked()),
                            mapper, SLOT(map()));
                    mapper->setMapping(static_cast<QObject *>(l.at(j)->buttonPtr),
                                       static_cast<QObject *>(l.at(j)));
                    ui->southHand->layout()->addWidget(static_cast<QWidget *>(l.at(j)->buttonPtr));
                }

                QList<int> list;
                if (i == 0)
                    qDebug() << "breakpoint";
                list << currentPlayer->getPosition() << currentPlayer->getNumberOfCards();
                network->broadcast(GameNet::SHOW_PLAYER_HAND, list);

            } else {
                QList<Card *> &m = currentPlayer->getHand();
                QList<int> args;

                args << currentPlayer->getPosition();
                foreach (Card *card, m) {
                    args << card->cardType << card->cardNumber;
                }

                if (currentPlayer->getSocket() != 0) {
                    network->sendMessage(currentPlayer->getSocket(), GameNet::SET_HAND, args);
                    qDebug() << "player " << currentPlayer->getPosition() << "kart sayisi :" << currentPlayer->getNumberOfCards();
                } else {
                    qDebug() << "socket error";
                }
            }

            currentPlayer = game->tNextPlayer();
        }
    }

    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::prepareNetworkUI()
{
    // pushSouth = new QPushButton("Otur", this);
    pushEast = new QPushButton("Otur", this);
    pushNorth = new QPushButton("Otur", this);
    pushWest = new QPushButton("Otur", this);
    // ui->southHand->layout()->addWidget(pushSouth);
    ui->eastHand->layout()->addWidget(pushEast);
    ui->northHand->layout()->addWidget(pushNorth);
    ui->westHand->layout()->addWidget(pushWest);

    QSignalMapper *pushMapper = new QSignalMapper(this);
    // connect(pushSouth, SIGNAL(clicked()), pushMapper, SLOT(map()));
    connect(pushEast, SIGNAL(clicked()), pushMapper, SLOT(map()));
    connect(pushNorth, SIGNAL(clicked()), pushMapper, SLOT(map()));
    connect(pushWest, SIGNAL(clicked()), pushMapper, SLOT(map()));

    // pushMapper->setMapping(pushSouth, 0);
    pushMapper->setMapping(pushEast, 1);
    pushMapper->setMapping(pushNorth, 2);
    pushMapper->setMapping(pushWest, 3);

    if (host == true) {
        Person *newPlayer;
        currentPlayer = newPlayer = new Person();
        if (name.isEmpty())
            name = "Host player";
        newPlayer->setPlayerName(name);
        newPlayer->setMyself(true);
        newPlayer->setTurn(true);
        game->tAdd(newPlayer, 0);
        posRelative = computeRelativePosition(0);

        pushEast->hide();
        pushNorth->hide();
        pushWest->hide();
    }

    connect(pushMapper, SIGNAL(mapped(int)), this, SLOT(slotPrepareNetworkUI(int)));
    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::slotPrepareNetworkUI(int n)
{
    qDebug() << "slotPrepareNetworkUI";
    Person *newPlayer = NULL;
    QList<int> args;
    QList<QString> str_args;
    args << n;

    if (host == true) {
/*
        currentPlayer = newPlayer = new Person();
        newPlayer->setPlayerName(QString("Host player"));
        newPlayer->setMyself(true);
        newPlayer->setTurn(true);
        game->tAdd(newPlayer, n);
        posRelative = computeRelativePosition(n);
        network->broadcast(GameNet::SET_PLAYER_POS, args);
        // delay(150);
*/

    } else {
        network->sendMessage(socket, GameNet::SET_PLAYER_POS, args);
        str_args << QString::number(n) << name;
        network->sendMessageString(socket, GameNet::SET_PLAYER_NAME, str_args);
        currentPlayer->setPosition(n);
        currentPlayer->setTurn(false);
        posRelative = computeRelativePosition(n);
        // delay(150);
    }

    ui->southHand->setEnabled(currentPlayer->isMyTurn());
    // pushSouth->hide();
    pushEast->hide();
    pushNorth->hide();
    pushWest->hide();
    // delay(150);
}

void Widget::SCardClicked(QObject *obj)
{
    ui->southHand->setEnabled(false);

    if (host == true)
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

    if (host == true)
        game->appendToPlayedCards(card);

    int location = currentPlayer->getPosition();

    if (host) {
        args << location << card->cardType << card->cardNumber;
        network->broadcast(GameNet::SHOW_CARD_ONTABLE, args);
        args.clear();
        args << location << currentPlayer->getNumberOfCards();
        network->broadcast(GameNet::SHOW_PLAYER_HAND, args);
    } else {
        args << location << cardIndex;
        network->sendMessage(socket, GameNet::PLAY, args);
        args.clear();
        args << location << currentPlayer->getNumberOfCards();
        network->sendMessage(socket, GameNet::SHOW_PLAYER_HAND, args);
    }

    location = (location + posRelative) % 4;
    showCardOnTable(card, location);

    delay(150);

    if (host == true) {
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
        }
        delay(150);

        currentPlayer = game->tNextPlayer();
        assert(currentPlayer != 0);

        network->sendMessage(currentPlayer->getSocket(), GameNet::CURRENT_PLAYER);
        delay(150);
    }
}

int Widget::computeRelativePosition(int position)
{
    if (position == 0)
        return 0;

    return (4 - position);
}

void Widget::on_buttonMultiplayer_clicked()
{
    ui->buttonGroup->setId(ui->radioButton_0, 2);
    ui->buttonGroup->setId(ui->radioButton_1, 4);
    ui->radioButton_0->setChecked(true);

    browser = new AvahiBrowser(this);
    connect(browser, SIGNAL(currentAvahiRecordsChanged(QList<AvahiRecord>)),
            this, SLOT(updateRecords(QList<AvahiRecord>)));
    browser->browseForService("_bilkon._tcp");
    ui->stackedWidget->setCurrentIndex(3);
}

void Widget::on_buttonConnect_clicked()
{
    QList<QListWidgetItem *> items = ui->listWidget->selectedItems();

    if (! items.isEmpty()) {
        //network = new GameNet(true, this);
        ui->buttonConnect->setEnabled(false);
        ui->buttonCreateServer->setEnabled(false);
        if (resolver == 0) {
            resolver = new AvahiResolver(this);
            connect(resolver, SIGNAL(avahiRecordResolved(QHostInfo,quint16)),
                    this, SLOT(connectToServer(QHostInfo,quint16)));
        }

        QListWidgetItem *item = items.first();
        QVariant variant = item->data(Qt::UserRole);
        resolver->resolveAvahiRecord(variant.value<AvahiRecord>());
    }
}

void Widget::connectToServer(const QHostInfo &hostinfo, quint16 port)
{
    QList<QHostAddress> addresses = hostinfo.addresses();
    if (addresses.isEmpty())
        return;

    QHostAddress addr = addresses.first();
    network = new GameNet(this, addr, port);
    connect(network, SIGNAL(messageReceived(QTcpSocket*)), this, SLOT(processMessage(QTcpSocket*)));

    n_preNetwork_start(false);
}

void Widget::updateRecords(const QList<AvahiRecord> &list)
{
    ui->listWidget->clear();

    foreach (AvahiRecord record, list) {
        QVariant variant;
        variant.setValue(record);
        QListWidgetItem *item = new QListWidgetItem(record.servName + " " + record.replyDomain, ui->listWidget);
        item->setData(Qt::UserRole, variant);
    }

    if (! list.isEmpty())
        ui->listWidget->setCurrentRow(0);
}

void Widget::clientInit(QTcpSocket *)
{
    QList<int> places;
    Person **p = game->getTPlayers();
    for (int i = 0; i < game->tSize(); i++) {
        if (p[i] != 0)
            places[i] = 1;
        else
            places[i] = 0;
    }
}

void Widget::sendPrepareUi()
{
    network->broadcast(GameNet::PREPARE_NETWORK_UI);
}

void Widget::renewTurn()
{
    for (int i = 0; i < game->tSize(); ++i) {
        game->distributeCards(*currentPlayer, 4);

        if (currentPlayer->myself()) {
            QList<Card *> hand = currentPlayer->getHand();

            for (int j = 0; j < hand.size(); ++j) {
                connect(static_cast<QToolButton *>(hand.at(j)->buttonPtr), SIGNAL(clicked()),
                        mapper, SLOT(map()));
                mapper->setMapping(static_cast<QObject *>(hand.at(j)->buttonPtr),
                                   static_cast<QObject *>(hand.at(j)));
                ui->southHand->layout()->addWidget(static_cast<QWidget *>(hand.at(j)->buttonPtr));
            }

            QList<int> list;
            list << currentPlayer->getPosition() << currentPlayer->getNumberOfCards();
            network->broadcast(GameNet::SHOW_PLAYER_HAND, list);

        } else {
            QList<Card *> hand = currentPlayer->getHand();
            QList<int> list;

            list << currentPlayer->getPosition();
            foreach (Card *card, hand) {
                list << card->cardType << card->cardNumber;
            }

            if (currentPlayer->getSocket() != 0) {
                network->sendMessage(currentPlayer->getSocket(), GameNet::SET_HAND, list);
            } else {
                qDebug() << "socket error";
            }
        }

        currentPlayer = game->tNextPlayer();
    }
}

void Widget::gameOver()
{
    qDebug() << "gameOver()";

    QString resultString, firstTeam, secondTeam;
    QList<QString> stringList, nameList;
    Person *player;
    int PLAYER_NUMBER = game->tSize();
    int score[PLAYER_NUMBER], pisticount[PLAYER_NUMBER], cardcount[PLAYER_NUMBER];
    int score_a = 0, score_b, pisti_a = 0, pisti_b = 0;

    clearPanel(ui->tableCenter);
    clearPanel(ui->tableEast);
    clearPanel(ui->tableNorth);
    clearPanel(ui->tableWest);
    clearPanel(ui->tableSouth);

    Person *lastWinner = game->getlastWinner();
    if (lastWinner != 0)
        lastWinner->collectCards(game->getPlayedCards());

    network->broadcast(GameNet::CLEAR_TABLE);

    if ((player = game->toSouth()) == 0)
        return;

    for (int j = 0; j < PLAYER_NUMBER; ++j) {
        currentPlayer->computePlayerScore();
        score[j] = currentPlayer->score;
        pisticount[j] = currentPlayer->pistiCount;
        cardcount[j] = currentPlayer->numberOfScoredCards();
        nameList.append(currentPlayer->getPlayerName());

        currentPlayer = game->tNextPlayer();
    }

    if (PLAYER_NUMBER == 2) {
        score_a = score[0];
        pisti_a = pisticount[0];
        score_b = score[1];
        pisti_b = pisticount[1];

        firstTeam = nameList.takeFirst();
        firstTeam.append('\t');
        secondTeam = nameList.takeFirst();

        if (cardcount[0] > cardcount[1])
            score_a += 3;
        else
            score_b += 3;

    } else {
        score_a = score[0] + score[2];
        score_b = score[1] + score[3];
        pisti_a = pisticount[0] + pisticount[2];
        pisti_b = pisticount[1] + pisticount[3];

        firstTeam = nameList.at(0);
        firstTeam.append(" & ");
        firstTeam.append(nameList.at(2));

        secondTeam = nameList.at(1);
        secondTeam.append(" & ");
        secondTeam.append(nameList.at(3));

        if (cardcount[0] + cardcount[2] > cardcount[1] + cardcount[3])
            score_a += 3;
        else
            score_b += 3;
    }

    qDebug() << firstTeam << " " << secondTeam;

    resultString.append('\t');
    resultString.append(firstTeam);
    resultString.append('\t');
    resultString.append('\t');
    resultString.append(secondTeam);
    resultString.append('\n');

    resultString.append("Pisti:");
    resultString.append('\t');
    resultString.append(QString::number(pisti_a));
    resultString.append('\t');
    resultString.append('\t');
    resultString.append('\t');
    resultString.append(QString::number(pisti_b));
    resultString.append('\n');

    resultString.append("Total:");
    resultString.append('\t');
    resultString.append(QString::number(score_a));
    resultString.append('\t');
    resultString.append('\t');
    resultString.append('\t');
    resultString.append(QString::number(score_b));
    resultString.append('\n');

    stringList << resultString;
    network->broadcastString(GameNet::SHOW_SCOREBOARD, stringList);

    ui->resultlabel->setText(resultString);
    ui->stackedWidget->setCurrentIndex(2);

    qDebug() << resultString;
}

void Widget::on_buttonEnterName_clicked()
{
    name = ui->lineEditName->text();
    name = name.simplified();
    ui->buttonEnterName->setEnabled(false);
    ui->lineEditName->setEnabled(false);
}

void Widget::on_buttonSend_clicked()
{
    qDebug() << "on_buttonSend_clicked";
    QString chatMessage = ui->lineEditChatMessagee->text();
    QString nick;

    ui->lineEditChatMessagee->clear();
    chatMessage = chatMessage.trimmed();
    qDebug() << "chatmessage :" << chatMessage;

    if (chatMessage.isEmpty())
        return;

    nick = "<b style=\"color: blue\">" + name + ":</b> ";
    ui->textEditChatMessage->append(nick + chatMessage);
    ui->textEditChatMessage->ensureCursorVisible();

    QList<QString> list;
    list << name;
    list << chatMessage;

    if (host == true)
        network->broadcastString(GameNet::CHAT_MESSAGE, list);
    else
        network->sendMessageString(socket, GameNet::CHAT_MESSAGE, list);
}
