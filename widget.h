#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QGridLayout>
#include <QDesktopWidget>
#include <QToolButton>
#include <QTime>
#include <QDebug>
#include <QSignalMapper>
#include <QMessageBox>
#include "core/card.h"
#include "core/gameengine.h"
#include "core/gamenet.h"
#include "avahi/avahibrowser.h"
#include "avahi/avahiresolver.h"
#include "avahi/avahiregistrar.h"
#include "core/player.h"
#include "pistiplayer.h"
#include <assert.h>

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
    virtual void resizeEvent(QResizeEvent *);

private:
    Ui::Widget *ui;

    GameEngine *game;
    GameNet *network;
    Player *players;
    Player *currentPlayer, *nextPlayer;
    Player *me;

    int currentPlayerIndex; // unused
    int posRelative; /* TODO: locate player's pos */
    int maxpoint;

    bool host;

    QString name;
    QSignalMapper *mapper;
    QTcpSocket *socket;
    QList<QTcpSocket *> peers;

    /* layouts */
    QGridLayout *grid;
    QHBoxLayout *hbox;
    QVBoxLayout *vbox;

    QPushButton *pushSouth;
    QPushButton *pushEast;
    QPushButton *pushNorth;
    QPushButton *pushWest;

    AvahiBrowser *browser;
    AvahiResolver *resolver;
    AvahiRegistrar *registrar;

    void preNetStart(bool);
    void centerMyWindow();
    void showCardOnTable(Card *c, int playerindex);
    void showCardOnFrame(Card *c, int playerindex);
    void simulateOthers();
    void clearPanel(QWidget *widget, bool dealloc = false);
    void showPlayerHand(int index, int size = 4);
    void statistics();
    inline void delay(int count, int sleep = 10000);
    int computeRelativePosition(int position);

    void n_simulateOthers();
    void n_set_hand();
    void n_set_player_name();
    void n_set_player_pos(QTcpSocket *sc);
    void n_get_player_pos();
    void n_clear_table();
    void n_clear_frame();
    void n_show_card_ontable(QTcpSocket *sock);
    void n_current_player();
    void n_not_current_player();
    void n_play();
    void n_prepare_network_ui();
    void n_show_player_hand(QTcpSocket *sock);
    void n_request_hand();
    void n_show_card_back();
    void n_show_scoreboard();
    void n_chat_message(QTcpSocket *sock);
    void n_preNetwork_start(bool server);
    void renewTurn();
    void gameOver(bool multiplayer = true);

    QFrame *getCurrentPlayerFrame() const;
    QFrame *getPlayerFrame(int pos) const;

private slots:
    void on_buttonSinglePlayer_clicked();
    void on_buttonSend_clicked();
    void on_buttonEnterName_clicked();
    void updateRecords(const QList<AvahiRecord> &);
    void on_buttonConnect_clicked();
    void on_buttonToggle_toggled(bool checked);
    void on_buttonMultiplayer_clicked();
    void on_styletoolMulti_clicked();
    void on_styletoolSingle_clicked();
    void on_pushButton_clicked();

    void connectToServer(const QHostInfo &hostinfo, quint16 port);
    void sendPrepareUi();
};

#endif // WIDGET_H
