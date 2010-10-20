#ifndef GAMENET_H
#define GAMENET_H

#include <QTcpServer>
#include <QHostAddress>
#include <QTcpSocket>
#include <QHostInfo>
#include <QStringList>

class GameNet : public QTcpServer
{
    Q_OBJECT

public:
    GameNet(QObject *parent = 0, bool server = false, int conn_number = 1);
    GameNet(QObject *parent, QHostAddress &address, quint16 port);
    ~GameNet();

    enum commands {
        SET_HAND,           // | playerPos : int | cards (cardType, cardNumber) : QList<int> |
        TAKE_CARD,          // unsupported operation
        SET_PLAYER_NAME,    // | name : QString |
        SET_PLAYER_POS,     // | pos : int | playerName : QString |
        GET_PLAYER_POS,     // | pos : int |
        COLLECT,            // unsupported operation
        CLEAR_TABLE,
        CLEAR_FRAME,        // | realPos : int |
        SHOW_SCOREBOARD,
        SHOW_CARD_ONTABLE,  // | realPos : int | cards (cardType, cardNumber | 9
        L_PLAYED_CARD,
        RESTART,
        GAME_OVER,
        CURRENT_PLAYER,
        NOT_CURRENT_PLAYER,
        INITIAL_GUI_STATE,         // | realPos : int | numberOfCards : int |
        PLAY,                // | index|
        PREPARE_NETWORK_UI,
        SHOW_PLAYER_HAND,     // 18
        REQUEST_HAND,
        SHOW_CARD_BACK,
        CHAT_MESSAGE
    };

    void sendMessage(QTcpSocket *sock, commands com, QList<int> operand);
    void sendMessage(QTcpSocket *sock, commands com);
    void sendMessageString(QTcpSocket *sock, commands com, QList<QString> operand);
    void broadcast(commands com, QList<int>, QTcpSocket *exclude = 0);
    void broadcast(commands com, QTcpSocket *exclude = 0);
    void broadcastString(commands com, QList<QString> operand, QTcpSocket *exclude = 0);
    inline int getReceivedCommand() const { return receivedCommand; }
    inline QList<int> arguments() const { return argument_list; }
    inline QList<QString> stringArguments() const { return string_argument_list; }
    inline QList<QTcpSocket *> getPeers() const { return sockets; }
    inline QTcpSocket* getClientSoc() const { return clientSoc; }

signals:
    void serverReady();
    void messageReceived(QTcpSocket *);

private:
    QList<QTcpSocket *> sockets;
    QList<int> argument_list;
    QList<QString> string_argument_list;
    QTcpSocket *clientSoc;

    quint16 blocksize;
    int receivedCommand;
    int conn_num;

    void getReply(QTcpSocket *sock);
    void processCommand();

private slots:
    bool startServer(QHostAddress addr = QHostAddress::Any);
    bool startServerFor(int playernum, QHostAddress addr = QHostAddress::Any);
    bool hasNewCard();
    void addPlayer();
    void startClient();
    void setupServer();
    void connectToServer(const QHostAddress &address, quint16 port);
    void clientDisconnected();

public slots:
    void readMessage();

};

#endif // GAMENET_H
