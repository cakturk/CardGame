#include "gamenet.h"

GameNet::GameNet(QObject *parent, bool server, int conn_number) :
        QTcpServer(parent),blocksize(0), conn_num(conn_number)
{
    if (server) {
        startServer();
    } else {
        startClient();
    }
}

/* TODO: change constructor signature */
GameNet::GameNet(QObject *parent, QHostAddress &address, quint16 port) :
        QTcpServer(parent), clientSoc(0), blocksize(0)
{
    connectToServer(address, port);
}

GameNet::~GameNet() { qDebug() << "see you in another life brotha!"; }

// TODO: port numarasi secilebilmeli
bool GameNet::startServer(QHostAddress addr)
{
    bool retval = listen(addr, (quint16) 33333);
    if (retval) {
        connect(this, SIGNAL(newConnection()), this, SLOT(addPlayer()));
        /* ? */
        connect(this, SIGNAL(serverReady()), this, SLOT(setupServer()));
        qDebug() << "Server started";
    }

    return retval;
}

bool GameNet::startServerFor(int, QHostAddress)
{
    return true;
}

bool GameNet::hasNewCard()
{
    return true;
}

// TODO: Connect to newConnection signal
void GameNet::addPlayer()
{
    QTcpSocket *newsocket = nextPendingConnection();
    sockets.append(newsocket);
    connect(newsocket, SIGNAL(readyRead()), this, SLOT(readMessage()));

    if (sockets.size() == conn_num) {
        // no more connections
        setMaxPendingConnections(0);
        emit serverReady();
    }
}

void GameNet::sendMessage(QTcpSocket *sock, commands com, QList<int> operand)
{
    qDebug() << "sendMessage operand :" << com;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_5);

    out << (quint16) 0;
    out << com;
    out << operand;

    out.device()->seek(0);
    out << (quint16) (block.size() - sizeof(quint16));

    qint64 by = sock->write(block);
    qDebug() << by << " bytes data written";
}

void GameNet::sendMessage(QTcpSocket *sock, commands com)
{
    qDebug() << "sendMessage :" << com;
    QList<int> operand;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_5);

    out << (quint16) 0;
    out << com;
    out << operand;

    out.device()->seek(0);
    out << (quint16) (block.size() - sizeof(quint16));

    qint64 by = sock->write(block);
    qDebug() << by << " bytes data written";
}

void GameNet::sendMessageString(QTcpSocket *sock, commands com, QList<QString> operand)
{
    qDebug() << "sendMessageString :" << com << " " << operand.first();

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_5);

    out << (quint16) 0;
    out << com;
    out << operand;

    out.device()->seek(0);
    out << (quint16) (block.size() - sizeof(quint16));

    sock->write(block);
}

void GameNet::broadcastString(commands com, QList<QString> operand, QTcpSocket *exclude)
{
    qDebug() << "sendMessageString";
    if (sockets.isEmpty())
        return;

    foreach (QTcpSocket *peer, sockets) {
        if (peer != exclude)
            sendMessageString(peer, com, operand);
    }
}

void GameNet::broadcast(commands com, QList<int> args, QTcpSocket *exclude)
{
    if (sockets.isEmpty())
        return;

    foreach (QTcpSocket *peer, sockets) {
        if (peer != exclude)
            sendMessage(peer, com, args);
    }
}

void GameNet::broadcast(commands com, QTcpSocket *exclude)
{
    if (sockets.isEmpty())
        return;

    foreach (QTcpSocket *peer, sockets) {
        if (peer != exclude)
            sendMessage(peer, com);
    }
}

void GameNet::getReply(QTcpSocket *sock)
{
    int recentcommand;

    QDataStream in(sock);
    in.setVersion(QDataStream::Qt_4_5);

    if (sock->bytesAvailable()) {
        in >> recentcommand;

        switch (recentcommand) {
        case PLAY:
            /* append to played cards */
            break;
        case TAKE_CARD:
            break;
        }
    }
}


void GameNet::processCommand()
{
    GameNet::commands r_command;

    switch (receivedCommand) {
    case TAKE_CARD:
        r_command = GameNet::TAKE_CARD;
        break;
    case SET_PLAYER_NAME:
        r_command = GameNet::SET_PLAYER_NAME;
        break;
    case COLLECT:
        r_command = GameNet::COLLECT;
        break;
    case PLAY:
        r_command = GameNet::PLAY;
        break;
    case SHOW_SCOREBOARD:
        r_command = GameNet::SHOW_SCOREBOARD;
        break;
    case L_PLAYED_CARD:
        r_command = GameNet::L_PLAYED_CARD;
        break;
    }
}

void GameNet::startClient()
{
    clientSoc = new QTcpSocket(this);
    clientSoc->connectToHost("192.168.2.10", 33333);
    connect(clientSoc, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(clientSoc, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
}

void GameNet::connectToServer(const QHostAddress &address, quint16 port)
{
    clientSoc = new QTcpSocket(this);
    clientSoc->connectToHost(address, port);
    connect(clientSoc, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(clientSoc, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
}

void GameNet::setupServer()
{
    qDebug() << "setupServer";
    for (int i = 0; i < sockets.size(); i++) {
        connect(sockets.at(i), SIGNAL(readyRead()), this, SLOT(readMessage()));
    }
}

void GameNet::readMessage()
{
    qDebug() << "*****begin*****";
/*
    qDebug() << "reading message";
*/
    QTcpSocket *soc = static_cast<QTcpSocket *>(QObject::sender());

    if (soc == NULL)
        return;
    again:
    // qDebug() << "blocksize :" << soc->bytesAvailable() << " byte";

    QDataStream in(soc);
    in.setVersion(QDataStream::Qt_4_5);

    if (blocksize == 0) {
        if (soc->bytesAvailable() < (qint64) sizeof(quint16))
            return;

        in >> blocksize;
    }

    // qDebug() << "packet size :" << blocksize << " byte";

    if (soc->bytesAvailable() < blocksize)
        return;

    in >> receivedCommand;
    qDebug() << "receivedcommand " << receivedCommand;

    argument_list.clear();
    string_argument_list.clear();
    blocksize = 0;

    if (receivedCommand == GameNet::SHOW_SCOREBOARD
        || receivedCommand == GameNet::SET_PLAYER_NAME
        || receivedCommand == GameNet::CHAT_MESSAGE)
        in >> string_argument_list;
    else
        in >> argument_list;

    if (! argument_list.isEmpty() && argument_list.first() == 0)
        qDebug() << "breakpoint";
/*
    qDebug() << "blocksize :" << soc->bytesAvailable() << " byte";
    qDebug() << "qlist.size() " << argument_list.size();
    qDebug() << "info";
*/
    emit messageReceived(soc);
    // qDebug() << "****end****";
    if (soc->bytesAvailable())
        goto again;
}

void GameNet::clientDisconnected()
{
    qDebug() << "socket disconnected";
}
