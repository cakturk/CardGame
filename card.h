#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QDebug>
#include <QToolButton>
#include <QTime>

class Card : public QObject
{
public:
    Card(int cardType, int cardNumber);

    QString toString();
    static void shuffleList(QList<Card *> &p);
    bool operator ==(const Card &other) const;
    bool equals(Card *c);
    QWidget* getButton();

    enum card_type {
        KUPA,
        KARO,
        SINEK,
        MACA
    };

    /* 0 -> KUPA, 1 -> KARO, 2-> SINEK, 3-> MACA */
    int type;
    card_type cardType;
    int cardNumber;
    QString cardName;
    QString cardImageName;
    void *buttonPtr;

    QWidget *toolButton;

private:
};

#endif // CARD_H
