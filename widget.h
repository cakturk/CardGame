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
#include "card.h"
#include "gameengine.h"
#include "gamenet.h"
#include "avahibrowser.h"
#include "avahiresolver.h"
#include "avahiregistrar.h"
#include "assert.h"

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

    GameEngine *game;
    GameNet *network;
    Person *players;
    Person *currentPlayer, *nextPlayer;
    Person *me;

    int currentPlayerIndex; // unused
    int posRelative; /* TODO: locate player's pos */
    int maxpoint;

    bool host;

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

    void modifiedstart();
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
    void n_show_card_ontable();
    void n_current_player();
    void n_not_current_player();
    void n_play();
    void n_update_gui();
    void n_preNetwork_start(bool server);

    QFrame *getCurrentPlayerFrame() const;
    QFrame *getPlayerFrame(int pos) const;

private slots:
    void updateRecords(const QList<AvahiRecord> &);
    void on_buttonConnect_clicked();
    void on_buttonCreateServer_clicked();
    void on_buttonToggle_toggled(bool checked);
    void on_buttonMultiplayer_clicked();
    void on_styletoolMulti_clicked();
    void on_styletoolSingle_clicked();
    void on_pushButton_clicked();
    void cardClicked(QObject *obj);
    void n_cardClicked(QObject *obj);
    void processMessage(QTcpSocket*);
    void slotPrepareNetworkUI(int n);
    void prepareNetworkUI();

    void SCardClicked(QObject *obj);
    void SNetworkStart();
    void connectToServer(const QHostInfo &hostinfo, quint16 port);
};

#endif // WIDGET_H
