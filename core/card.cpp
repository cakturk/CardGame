#include "card.h"

Card::Card(int ct, int cn) :
        type(ct), value(cn)
{
    switch (type) {
    case 0:
        suit = KUPA;
        break;

    case 1:
        suit = KARO;
        break;

    case 2:
        suit = SINEK;
        break;

    case 3:
        suit = MACA;
        break;

    default:
        qDebug() << "Wrong card type";
    }

    cardName = this->toString();
    cardImageName = "./graphics/" + cardName.toLower();
    cardImageName.append(".png");

    QToolButton *foo = new QToolButton;
    foo->setMinimumSize(QSize(50, 60));
    foo->setStyleSheet(QString("border-image: url(%1)").arg(this->cardImageName));

    this->buttonPtr = static_cast<void *>(foo);

    //buttonPtr = (void *) getButton();
}

Card::~Card()
{
    delete static_cast<QToolButton *>(buttonPtr);
}

QString Card::toString()
{
    QString retVal;

    switch (suit) {
    case KARO:
        retVal = "Karo";
        break;
    case KUPA:
        retVal = "Kupa";
        break;
    case SINEK:
        retVal = "Sinek";
        break;
    case MACA:
        retVal = "Maca";
        break;
    }

    switch (value) {
    case 1:
        retVal += "As";
        break;
    case 11:
        retVal += "Vale";
        break;
    case 12:
        retVal += "Kiz";
        break;
    case 13:
        retVal += "Papaz";
        break;
    default:
        retVal += QString::number(value);
    }

    return retVal;
}

void Card::shuffleList(QList<Card *> &p)
{
    qsrand( QTime(0,0,0).secsTo(QTime::currentTime()) );

    for( int i = p.count() - 1 ; i > 0 ; --i )
    {
        int random = qrand() % p.count();
        Card *str = p[i];
        p[i] = p[random];
        p[random] = str;
    }
}

bool Card::operator ==(const Card &other) const
{
    if (this->value == other.value)
        return true;

    return false;
}

bool Card::operator <(const Card &rhs) const
{
    if (this->compareTo(&rhs) == -1)
        return true;
    else
        return false;
}

bool Card::equals(Card *other)
{
    return (this->value == other->value);
}

QWidget* Card::getButton()
{
    toolButton = new QToolButton;
    toolButton->setMinimumSize(QSize(50, 50));
    toolButton->setStyleSheet(QString("border-image: url(%1)").arg(this->cardImageName));

    /* refresh button */
    // delete (QToolButton *) buttonPtr;

    QToolButton *old = (QToolButton *) buttonPtr;
    buttonPtr = static_cast<void *>(toolButton);

    qDebug() << "getButton()";

    return old;
}

int Card::compareTo(const Card *rhs) const
{
    /* special case, we found ace */
    if (value == 1)
        return 1;
    else if (rhs->value == 1)
        return -1;

    if (value == rhs->value)
        return 0;
    else if (value > rhs->value)
        return 1;
    else
        return -1;
}
