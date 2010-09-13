#include "card.h"

Card::Card(int ct, int cn) :
        type(ct), cardNumber(cn)
{
    switch (type) {
    case 0:
        cardType = KUPA;
        break;

    case 1:
        cardType = KARO;
        break;

    case 2:
        cardType = SINEK;
        break;

    case 3:
        cardType = MACA;
        break;

    default:
        qDebug() << "Wrong card type";
    }

    cardName = this->toString();
    cardImageName = "./graphics/" + cardName.toLower();
    buttonPtr = (void *) getButton();
}

QString Card::toString()
{
    QString retVal;

    switch (cardType) {
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

    switch (cardNumber) {
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
        retVal += QString::number(cardNumber);
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

bool Card::operator ==(const Card &other) const {
    if (this->cardNumber == other.cardNumber)
        return true;

    return false;
}

bool Card::equals(Card *c)
{
    return (this->cardNumber == c->cardNumber);
}

QWidget* Card::getButton()
{
    toolButton = new QToolButton;
    toolButton->setMinimumSize(QSize(50, 50));
    toolButton->setStyleSheet(QString("border-image: url(%1);").arg(this->cardImageName));
    // buttonPtr = toolButton;

    return toolButton;
}
