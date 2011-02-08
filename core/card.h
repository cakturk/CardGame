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
    ~Card();

    QString toString();
    static void shuffleList(QList<Card *> &p);
    bool operator==(const Card &other) const;
    bool operator <(const Card &rhs) const;
    bool equals(Card *c);
    QWidget* getButton();

    enum Suit {
        MACA = 4,
        KARO = 3,
        SINEK = 2,
        KUPA = 1,
    };

    int type;
    Suit suit;
    int value;
    QString cardName;
    QString cardImageName;
    void *buttonPtr;

    QWidget *toolButton;

private:
    int compareTo(const Card *rhs) const;

private slots:

};

#endif // CARD_H
