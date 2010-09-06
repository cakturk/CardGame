/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Mon Sep 6 12:07:25 2010
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
#include <QtGui/QHeaderView>
#include <QtGui/QStackedWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page_2;
    QFrame *southHand;
    QFrame *westHand;
    QFrame *northHand;
    QFrame *table;
    QFrame *eastHand;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(576, 410);
        Widget->setAutoFillBackground(false);
        stackedWidget = new QStackedWidget(Widget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(20, 30, 537, 351));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        southHand = new QFrame(page_2);
        southHand->setObjectName(QString::fromUtf8("southHand"));
        southHand->setGeometry(QRect(0, 270, 531, 81));
        southHand->setMinimumSize(QSize(50, 50));
        southHand->setFrameShape(QFrame::StyledPanel);
        southHand->setFrameShadow(QFrame::Raised);
        westHand = new QFrame(page_2);
        westHand->setObjectName(QString::fromUtf8("westHand"));
        westHand->setGeometry(QRect(0, 10, 121, 251));
        westHand->setFrameShape(QFrame::StyledPanel);
        westHand->setFrameShadow(QFrame::Raised);
        northHand = new QFrame(page_2);
        northHand->setObjectName(QString::fromUtf8("northHand"));
        northHand->setGeometry(QRect(130, 10, 281, 71));
        northHand->setFrameShape(QFrame::StyledPanel);
        northHand->setFrameShadow(QFrame::Raised);
        northHand->setLineWidth(1);
        table = new QFrame(page_2);
        table->setObjectName(QString::fromUtf8("table"));
        table->setGeometry(QRect(130, 90, 281, 171));
        table->setFrameShape(QFrame::StyledPanel);
        table->setFrameShadow(QFrame::Raised);
        eastHand = new QFrame(page_2);
        eastHand->setObjectName(QString::fromUtf8("eastHand"));
        eastHand->setGeometry(QRect(420, 10, 111, 251));
        eastHand->setFrameShape(QFrame::StyledPanel);
        eastHand->setFrameShadow(QFrame::Raised);
        stackedWidget->addWidget(page_2);

        retranslateUi(Widget);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
