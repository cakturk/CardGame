#include "widget.h"
#include "ui_widget.h"

#include "state.h"
#include "batakplayer.h"

#include "core/pistiengine.h"
#include "pistiplayer.h"

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

    currentPlayer = NULL;
    game = NULL;
    currentPlayerIndex = 0;

    mapper = new QSignalMapper(this);
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

    test();
    // modifiedstart();
}

void Widget::test()
{
#if 0
    State state;
    GameEngine *engine = new GameEngine(this);

    PistiPlayer *mazhar = new PistiPlayer;
    CardSequence seq;
    for (int j = 0; j < 4; ++j)
        seq.append(engine->getCards().takeFirst());

    mazhar->setHand(seq);

    foreach (Card *kart, engine->getCards()) {
        static int count = 0;
        state.append(kart);

        if (++count == 40)
            break;
        qDebug() << "break";
    }

    //CardSequence board = state.takeCardsFromBoard();
    mazhar->dummyPlay(state);
#else
    GameEngine *engine = new PistiEngine(4, this);
    engine->addPlayer(new PistiPlayer("Terry", 0, this));
    engine->addPlayer(new PistiPlayer("Quin", 0, this));
    engine->addPlayer(new PistiPlayer("Kathy", 0, this));
    engine->addPlayer(new PistiPlayer("Perry", 0, this));

    engine->distributeCards(4);
    engine->loopGame();

    QString();
#endif
}


Widget::~Widget()
{
    delete ui;
    delete mapper;
    delete game;
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
    parentHeight = parentWidgetSize.height() * 0.80;

    button = static_cast<QWidget *>(c->buttonPtr);
    button->setParent(frame);

    // TODO: must be dynamically resized
    // button->resize(60, 70);
    button->resize(QSize(parentHeight * 0.75, parentHeight));
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
#if 0
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
#endif
    return NULL;
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
            QList<Card *> &l = game->cardsOnTable();

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
            game->getlastWinner()->collectCards(game->cardsOnTable());
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
            QList<Card *> &l = game->cardsOnTable();

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
}

void Widget::on_styletoolSingle_clicked()
{
}

void Widget::on_buttonToggle_toggled(bool checked)
{
    if (checked)
        this->showFullScreen();
    else
        this->showNormal();
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

void Widget::n_show_card_ontable(QTcpSocket *)
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
    currentPlayer->setTurn(true);
    ui->southHand->setEnabled(true);
}

void Widget::n_not_current_player()
{
    currentPlayer->setTurn(false);
    ui->southHand->setEnabled(false);
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
}

void Widget::n_preNetwork_start(bool b)
{
    host = b;
    connect(mapper, SIGNAL(mapped(QObject *)), this, SLOT(SCardClicked(QObject*)));

    if (host == true) {
        connect(game, SIGNAL(ready()), this, SLOT(SNetworkStart()));
    } else {
        socket = network->getClientSoc();
        Player *newPlayer;
        currentPlayer = newPlayer = new PistiPlayer;
        if (name.isEmpty())
            name = "Remote player";
        newPlayer->setPlayerName(name);
        newPlayer->setMyself(true);
        // connect(socket, SIGNAL(connected()), this, SLOT(prepareNetworkUI()));
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

void Widget::sendPrepareUi()
{
    network->broadcast(GameNet::PREPARE_NETWORK_UI);
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
    QString chatMessage = ui->lineEditChatMessagee->text();
    QString nick;

    ui->lineEditChatMessagee->clear();
    chatMessage = chatMessage.trimmed();

    if (chatMessage.isEmpty())
        return;

    nick = "<b style=\"color: blue\">" + name + ":</b> ";
    ui->textEditChatMessage->append(nick + chatMessage);
    ui->textEditChatMessage->ensureCursorVisible();

    QList<QString> list;
    list << name << chatMessage;

    if (host == true)
        network->broadcastString(GameNet::CHAT_MESSAGE, list);
    else
        network->sendMessageString(socket, GameNet::CHAT_MESSAGE, list);
}

void Widget::resizeEvent(QResizeEvent *)
{
    int x, y;
    QWidget *child;
    QSize parentWidgetSize, childSize;
    QList<QFrame *> frames;
    QList<QWidget *> widgets;

    frames << ui->tableSouth << ui->tableEast << ui->tableNorth << ui->tableWest << ui->tableCenter;
    foreach (QFrame *container, frames) {
        widgets = container->findChildren<QWidget *>();

        while (widgets.size() > 0) {
            parentWidgetSize = container->size();
            child = widgets.takeFirst();
            child->resize(QSize(parentWidgetSize.height() * 0.60, parentWidgetSize.height() * 0.80));
            childSize = child->size();
            x = (parentWidgetSize.width() - childSize.width()) / 2;
            y = (parentWidgetSize.height() - childSize.height()) / 2;
            y -= y / 2;
            child->move(QPoint(x, y));
        }
    }
}

void Widget::on_buttonSinglePlayer_clicked()
{
#if 0
    Player *newPlayer = 0;

    if (ui->comboSinglePlayer->currentIndex() == 0) {
        game = new GameEngine(true, 4, this);
        for (int i = 0; i < 4; ++i) {
            newPlayer = new PistiPlayer(QString("Player %1").arg(QString::number(i)), i, game);
            game->tAdd(newPlayer, i);
            qDebug() << "i = " << i;
        }
    } else {
        game = new GameEngine(true, 2, this);
        newPlayer = new PistiPlayer(QString::fromUtf8("Güney"), 0, game);
        game->tAdd(newPlayer, 0);
        newPlayer = new PistiPlayer(QString::fromUtf8("Kuzey"), 2, game);
        game->tAdd(newPlayer, 2);
    }

    game->at(0)->setMyself(true);

    ui->frame_2->setVisible(false);
    ui->stackedWidget->setCurrentIndex(1);
    connect(mapper, SIGNAL(mapped(QObject *)), this, SLOT(cardClicked(QObject *)));
#endif
}
