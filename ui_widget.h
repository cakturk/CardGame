/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Mon Sep 20 17:00:29 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *page_2;
    QGridLayout *gridLayout;
    QFrame *westHand;
    QFrame *southHand;
    QFrame *eastHand;
    QFrame *tableEast;
    QFrame *tableCenter;
    QFrame *tableWest;
    QFrame *tableNorth;
    QFrame *tableSouth;
    QFrame *northHand;
    QPushButton *pushButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(635, 548);
        Widget->setAutoFillBackground(false);
        Widget->setStyleSheet(QString::fromUtf8("background-color: rgb(54, 111, 195);"));
        gridLayout_2 = new QGridLayout(Widget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        stackedWidget = new QStackedWidget(Widget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        gridLayout = new QGridLayout(page_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        westHand = new QFrame(page_2);
        westHand->setObjectName(QString::fromUtf8("westHand"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(westHand->sizePolicy().hasHeightForWidth());
        westHand->setSizePolicy(sizePolicy);
        westHand->setFrameShape(QFrame::NoFrame);
        westHand->setFrameShadow(QFrame::Raised);
        westHand->setLineWidth(1);

        gridLayout->addWidget(westHand, 0, 0, 4, 1);

        southHand = new QFrame(page_2);
        southHand->setObjectName(QString::fromUtf8("southHand"));
        southHand->setMinimumSize(QSize(50, 50));
        southHand->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(southHand, 4, 0, 1, 5);

        eastHand = new QFrame(page_2);
        eastHand->setObjectName(QString::fromUtf8("eastHand"));
        eastHand->setFrameShape(QFrame::NoFrame);
        eastHand->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(eastHand, 0, 4, 4, 1);

        tableEast = new QFrame(page_2);
        tableEast->setObjectName(QString::fromUtf8("tableEast"));
        tableEast->setFrameShape(QFrame::NoFrame);
        tableEast->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(tableEast, 2, 3, 1, 1);

        tableCenter = new QFrame(page_2);
        tableCenter->setObjectName(QString::fromUtf8("tableCenter"));
        tableCenter->setFrameShape(QFrame::NoFrame);
        tableCenter->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(tableCenter, 2, 2, 1, 1);

        tableWest = new QFrame(page_2);
        tableWest->setObjectName(QString::fromUtf8("tableWest"));
        tableWest->setFrameShape(QFrame::NoFrame);
        tableWest->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(tableWest, 2, 1, 1, 1);

        tableNorth = new QFrame(page_2);
        tableNorth->setObjectName(QString::fromUtf8("tableNorth"));
        tableNorth->setFrameShape(QFrame::NoFrame);
        tableNorth->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(tableNorth, 1, 2, 1, 1);

        tableSouth = new QFrame(page_2);
        tableSouth->setObjectName(QString::fromUtf8("tableSouth"));
        tableSouth->setFrameShape(QFrame::NoFrame);
        tableSouth->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(tableSouth, 3, 2, 1, 1);

        northHand = new QFrame(page_2);
        northHand->setObjectName(QString::fromUtf8("northHand"));
        northHand->setFrameShape(QFrame::NoFrame);
        northHand->setFrameShadow(QFrame::Raised);
        northHand->setLineWidth(1);

        gridLayout->addWidget(northHand, 0, 1, 1, 3);

        stackedWidget->addWidget(page_2);

        gridLayout_2->addWidget(stackedWidget, 1, 0, 1, 1);

        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton->setStyleSheet(QString::fromUtf8("color: rgb(222, 222, 222);\n"
"font: 75 10pt \"DejaVu Sans Mono\";\n"
"\n"
""));
        pushButton->setCheckable(false);
        pushButton->setFlat(true);

        gridLayout_2->addWidget(pushButton, 0, 0, 1, 1);


        retranslateUi(Widget);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushButton->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        pushButton->setText(QApplication::translate("Widget", "Restart Game", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
