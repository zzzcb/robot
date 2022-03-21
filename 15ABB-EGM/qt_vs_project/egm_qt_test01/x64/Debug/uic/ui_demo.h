/********************************************************************************
** Form generated from reading UI file 'demo.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEMO_H
#define UI_DEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DemoClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit;
    QGridLayout *gridLayout_6;
    QLabel *label_8;
    QLineEdit *j1;
    QLabel *label_15;
    QLineEdit *j2;
    QLabel *label_14;
    QLineEdit *j3;
    QLabel *label_13;
    QLineEdit *j4;
    QLabel *label_16;
    QLineEdit *j5;
    QLabel *label_17;
    QLineEdit *j6;
    QFrame *line;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_4;
    QLabel *label_4;
    QLineEdit *rx;
    QLabel *label_5;
    QLineEdit *ry;
    QLabel *label_6;
    QLineEdit *rz;
    QGridLayout *gridLayout_2;
    QLineEdit *x;
    QLineEdit *z;
    QLineEdit *y;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label;
    QFrame *line_3;
    QGridLayout *gridLayout;
    QLineEdit *q2;
    QLineEdit *q3;
    QLabel *label_7;
    QLineEdit *q1;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLineEdit *q4;
    QFrame *line_2;
    QFrame *line_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QWidget *widget;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DemoClass)
    {
        if (DemoClass->objectName().isEmpty())
            DemoClass->setObjectName(QString::fromUtf8("DemoClass"));
        DemoClass->resize(963, 589);
        centralWidget = new QWidget(DemoClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        plainTextEdit = new QPlainTextEdit(groupBox);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setEnabled(false);

        verticalLayout->addWidget(plainTextEdit);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_6->addWidget(label_8, 0, 0, 1, 1);

        j1 = new QLineEdit(groupBox);
        j1->setObjectName(QString::fromUtf8("j1"));
        j1->setEnabled(false);

        gridLayout_6->addWidget(j1, 0, 1, 1, 1);

        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_6->addWidget(label_15, 1, 0, 1, 1);

        j2 = new QLineEdit(groupBox);
        j2->setObjectName(QString::fromUtf8("j2"));
        j2->setEnabled(false);

        gridLayout_6->addWidget(j2, 1, 1, 1, 1);

        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_6->addWidget(label_14, 2, 0, 1, 1);

        j3 = new QLineEdit(groupBox);
        j3->setObjectName(QString::fromUtf8("j3"));
        j3->setEnabled(false);

        gridLayout_6->addWidget(j3, 2, 1, 1, 1);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_6->addWidget(label_13, 3, 0, 1, 1);

        j4 = new QLineEdit(groupBox);
        j4->setObjectName(QString::fromUtf8("j4"));
        j4->setEnabled(false);

        gridLayout_6->addWidget(j4, 3, 1, 1, 1);

        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_6->addWidget(label_16, 4, 0, 1, 1);

        j5 = new QLineEdit(groupBox);
        j5->setObjectName(QString::fromUtf8("j5"));
        j5->setEnabled(false);

        gridLayout_6->addWidget(j5, 4, 1, 1, 1);

        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_6->addWidget(label_17, 5, 0, 1, 1);

        j6 = new QLineEdit(groupBox);
        j6->setObjectName(QString::fromUtf8("j6"));
        j6->setEnabled(false);

        gridLayout_6->addWidget(j6, 5, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_6);

        line = new QFrame(groupBox);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 0, 0, 1, 1);

        rx = new QLineEdit(groupBox);
        rx->setObjectName(QString::fromUtf8("rx"));
        rx->setEnabled(false);

        gridLayout_4->addWidget(rx, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_4->addWidget(label_5, 1, 0, 1, 1);

        ry = new QLineEdit(groupBox);
        ry->setObjectName(QString::fromUtf8("ry"));
        ry->setEnabled(false);

        gridLayout_4->addWidget(ry, 1, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_4->addWidget(label_6, 2, 0, 1, 1);

        rz = new QLineEdit(groupBox);
        rz->setObjectName(QString::fromUtf8("rz"));
        rz->setEnabled(false);

        gridLayout_4->addWidget(rz, 2, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 1, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        x = new QLineEdit(groupBox);
        x->setObjectName(QString::fromUtf8("x"));
        x->setEnabled(false);

        gridLayout_2->addWidget(x, 0, 1, 1, 1);

        z = new QLineEdit(groupBox);
        z->setObjectName(QString::fromUtf8("z"));
        z->setEnabled(false);

        gridLayout_2->addWidget(z, 2, 1, 1, 1);

        y = new QLineEdit(groupBox);
        y->setObjectName(QString::fromUtf8("y"));
        y->setEnabled(false);

        gridLayout_2->addWidget(y, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        line_3 = new QFrame(groupBox);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_3, 3, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_2, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        q2 = new QLineEdit(groupBox);
        q2->setObjectName(QString::fromUtf8("q2"));
        q2->setEnabled(false);

        gridLayout->addWidget(q2, 1, 1, 1, 1);

        q3 = new QLineEdit(groupBox);
        q3->setObjectName(QString::fromUtf8("q3"));
        q3->setEnabled(false);

        gridLayout->addWidget(q3, 2, 1, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 0, 0, 1, 1);

        q1 = new QLineEdit(groupBox);
        q1->setObjectName(QString::fromUtf8("q1"));
        q1->setEnabled(false);

        gridLayout->addWidget(q1, 0, 1, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 3, 0, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 2, 0, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 1, 0, 1, 1);

        q4 = new QLineEdit(groupBox);
        q4->setObjectName(QString::fromUtf8("q4"));
        q4->setEnabled(false);

        gridLayout->addWidget(q4, 3, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout, 0, 2, 2, 1);

        line_2 = new QFrame(groupBox);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line_2, 0, 1, 1, 1);

        line_4 = new QFrame(groupBox);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line_4, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_5);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        widget = new QWidget(groupBox_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(400, 400));
        widget->setMaximumSize(QSize(400, 400));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(244, 240, 255);"));

        gridLayout_3->addWidget(widget, 0, 0, 1, 2);

        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout_3->addWidget(pushButton_2, 1, 0, 1, 1);

        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_3->addWidget(pushButton, 1, 1, 1, 1);


        horizontalLayout->addWidget(groupBox_2);

        DemoClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DemoClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 963, 23));
        DemoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DemoClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        DemoClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DemoClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        DemoClass->setStatusBar(statusBar);

        retranslateUi(DemoClass);

        QMetaObject::connectSlotsByName(DemoClass);
    } // setupUi

    void retranslateUi(QMainWindow *DemoClass)
    {
        DemoClass->setWindowTitle(QCoreApplication::translate("DemoClass", "Demo", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DemoClass", "\346\234\272\346\242\260\350\207\202\345\275\223\345\211\215\347\232\204\344\275\215\345\247\277", nullptr));
        label_8->setText(QCoreApplication::translate("DemoClass", "j1 ", nullptr));
        label_15->setText(QCoreApplication::translate("DemoClass", "j2", nullptr));
        label_14->setText(QCoreApplication::translate("DemoClass", "j3", nullptr));
        label_13->setText(QCoreApplication::translate("DemoClass", "j4", nullptr));
        label_16->setText(QCoreApplication::translate("DemoClass", "j5", nullptr));
        label_17->setText(QCoreApplication::translate("DemoClass", "j6", nullptr));
        label_4->setText(QCoreApplication::translate("DemoClass", "Rx ", nullptr));
        label_5->setText(QCoreApplication::translate("DemoClass", "Ry", nullptr));
        label_6->setText(QCoreApplication::translate("DemoClass", "Rz", nullptr));
        label_3->setText(QCoreApplication::translate("DemoClass", "Z", nullptr));
        label_2->setText(QCoreApplication::translate("DemoClass", "Y ", nullptr));
        label->setText(QCoreApplication::translate("DemoClass", "X", nullptr));
        label_7->setText(QCoreApplication::translate("DemoClass", "q1 ", nullptr));
        label_10->setText(QCoreApplication::translate("DemoClass", "q4", nullptr));
        label_11->setText(QCoreApplication::translate("DemoClass", "q3", nullptr));
        label_12->setText(QCoreApplication::translate("DemoClass", "q2", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("DemoClass", "\347\247\273\345\212\250\351\274\240\346\240\207\347\273\230\345\210\266\346\234\272\345\231\250\344\272\272\350\277\220\345\212\250\350\275\250\350\277\271", nullptr));
        pushButton_2->setText(QCoreApplication::translate("DemoClass", "\345\260\206\351\274\240\346\240\207\350\275\250\350\277\271\345\217\221\351\200\201\350\207\263\346\234\272\345\231\250\344\272\272", nullptr));
        pushButton->setText(QCoreApplication::translate("DemoClass", "\346\270\205\347\251\272\347\224\273\345\270\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DemoClass: public Ui_DemoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMO_H
