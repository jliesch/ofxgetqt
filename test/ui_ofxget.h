/********************************************************************************
** Form generated from reading UI file 'ofxget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OFXGET_H
#define UI_OFXGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OfxGet
{
public:
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QLabel *OFXGetLabel;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QLabel *institutionNameLabel;
    QLineEdit *institutionNameSearch;
    QHBoxLayout *horizontalLayout;
    QListWidget *institutionList;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLineEdit *failureLabel;
    QLineEdit *fidLabel;
    QLabel *label_9;
    QLabel *label_8;
    QLineEdit *orgLabel;
    QLabel *label_5;
    QLineEdit *bankIdLabel;
    QSpacerItem *verticalSpacer_3;
    QLineEdit *brokerIdLabel;
    QLabel *label_2;
    QLineEdit *urlLabel;
    QLabel *label_3;
    QLabel *label_6;
    QLineEdit *notesLabel;
    QLabel *label_4;
    QLineEdit *nameLabel;
    QLabel *label_7;
    QTextEdit *profileLabel;
    QLabel *label_10;
    QPushButton *query;
    QCheckBox *statusLabel;

    void setupUi(QWidget *OfxGet)
    {
        if (OfxGet->objectName().isEmpty())
            OfxGet->setObjectName(QStringLiteral("OfxGet"));
        OfxGet->setWindowModality(Qt::NonModal);
        OfxGet->resize(600, 600);
        verticalLayout_2 = new QVBoxLayout(OfxGet);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        OFXGetLabel = new QLabel(OfxGet);
        OFXGetLabel->setObjectName(QStringLiteral("OFXGetLabel"));
        QFont font;
        font.setFamily(QStringLiteral("Hoefler Text"));
        font.setPointSize(36);
        font.setBold(true);
        font.setWeight(75);
        OFXGetLabel->setFont(font);
        OFXGetLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(OFXGetLabel);

        label = new QLabel(OfxGet);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        institutionNameLabel = new QLabel(OfxGet);
        institutionNameLabel->setObjectName(QStringLiteral("institutionNameLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(institutionNameLabel->sizePolicy().hasHeightForWidth());
        institutionNameLabel->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(institutionNameLabel);

        institutionNameSearch = new QLineEdit(OfxGet);
        institutionNameSearch->setObjectName(QStringLiteral("institutionNameSearch"));

        verticalLayout_2->addWidget(institutionNameSearch);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        institutionList = new QListWidget(OfxGet);
        institutionList->setObjectName(QStringLiteral("institutionList"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(institutionList->sizePolicy().hasHeightForWidth());
        institutionList->setSizePolicy(sizePolicy1);
        institutionList->setAlternatingRowColors(false);

        horizontalLayout->addWidget(institutionList);

        scrollArea = new QScrollArea(OfxGet);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 265, 353));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy2);
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        failureLabel = new QLineEdit(scrollAreaWidgetContents);
        failureLabel->setObjectName(QStringLiteral("failureLabel"));
        failureLabel->setReadOnly(true);

        gridLayout->addWidget(failureLabel, 6, 1, 1, 1);

        fidLabel = new QLineEdit(scrollAreaWidgetContents);
        fidLabel->setObjectName(QStringLiteral("fidLabel"));
        fidLabel->setReadOnly(true);

        gridLayout->addWidget(fidLabel, 2, 1, 1, 1);

        label_9 = new QLabel(scrollAreaWidgetContents);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 7, 0, 1, 1);

        label_8 = new QLabel(scrollAreaWidgetContents);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 6, 0, 1, 1);

        orgLabel = new QLineEdit(scrollAreaWidgetContents);
        orgLabel->setObjectName(QStringLiteral("orgLabel"));
        orgLabel->setReadOnly(true);

        gridLayout->addWidget(orgLabel, 3, 1, 1, 1);

        label_5 = new QLabel(scrollAreaWidgetContents);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        bankIdLabel = new QLineEdit(scrollAreaWidgetContents);
        bankIdLabel->setObjectName(QStringLiteral("bankIdLabel"));
        bankIdLabel->setReadOnly(true);

        gridLayout->addWidget(bankIdLabel, 5, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 10, 1, 1, 1);

        brokerIdLabel = new QLineEdit(scrollAreaWidgetContents);
        brokerIdLabel->setObjectName(QStringLiteral("brokerIdLabel"));
        brokerIdLabel->setReadOnly(true);

        gridLayout->addWidget(brokerIdLabel, 4, 1, 1, 1);

        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        urlLabel = new QLineEdit(scrollAreaWidgetContents);
        urlLabel->setObjectName(QStringLiteral("urlLabel"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(urlLabel->sizePolicy().hasHeightForWidth());
        urlLabel->setSizePolicy(sizePolicy4);
        urlLabel->setReadOnly(true);

        gridLayout->addWidget(urlLabel, 1, 1, 1, 1);

        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy3.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_6 = new QLabel(scrollAreaWidgetContents);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        notesLabel = new QLineEdit(scrollAreaWidgetContents);
        notesLabel->setObjectName(QStringLiteral("notesLabel"));
        notesLabel->setReadOnly(true);

        gridLayout->addWidget(notesLabel, 7, 1, 1, 1);

        label_4 = new QLabel(scrollAreaWidgetContents);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        nameLabel = new QLineEdit(scrollAreaWidgetContents);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        sizePolicy4.setHeightForWidth(nameLabel->sizePolicy().hasHeightForWidth());
        nameLabel->setSizePolicy(sizePolicy4);
        nameLabel->setReadOnly(true);

        gridLayout->addWidget(nameLabel, 0, 1, 1, 1);

        label_7 = new QLabel(scrollAreaWidgetContents);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 5, 0, 1, 1);

        profileLabel = new QTextEdit(scrollAreaWidgetContents);
        profileLabel->setObjectName(QStringLiteral("profileLabel"));
        profileLabel->setReadOnly(true);

        gridLayout->addWidget(profileLabel, 9, 1, 1, 1);

        label_10 = new QLabel(scrollAreaWidgetContents);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 9, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);


        verticalLayout_2->addLayout(horizontalLayout);

        query = new QPushButton(OfxGet);
        query->setObjectName(QStringLiteral("query"));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setWeight(75);
        query->setFont(font1);
        query->setStyleSheet(QStringLiteral("padding-top: 1em; padding-bottom: 1em"));

        verticalLayout_2->addWidget(query);

        statusLabel = new QCheckBox(OfxGet);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        statusLabel->setChecked(true);

        verticalLayout_2->addWidget(statusLabel);


        retranslateUi(OfxGet);

        QMetaObject::connectSlotsByName(OfxGet);
    } // setupUi

    void retranslateUi(QWidget *OfxGet)
    {
        OfxGet->setWindowTitle(QApplication::translate("OfxGet", "OfxGet", nullptr));
        OFXGetLabel->setText(QApplication::translate("OfxGet", "OFX Get", nullptr));
        label->setText(QApplication::translate("OfxGet", "A service from <a href=\"http://www.ofxhome.com\">www.ofxhome.com</a>", nullptr));
        institutionNameLabel->setText(QApplication::translate("OfxGet", "Search Institution Name:", nullptr));
        label_9->setText(QApplication::translate("OfxGet", "Notes", nullptr));
        label_8->setText(QApplication::translate("OfxGet", "Failure", nullptr));
        label_5->setText(QApplication::translate("OfxGet", "ORG", nullptr));
        label_2->setText(QApplication::translate("OfxGet", "Name", nullptr));
        label_3->setText(QApplication::translate("OfxGet", "URL", nullptr));
        label_6->setText(QApplication::translate("OfxGet", "BROKERID", nullptr));
        label_4->setText(QApplication::translate("OfxGet", "FID", nullptr));
        label_7->setText(QApplication::translate("OfxGet", "BANKID", nullptr));
        label_10->setText(QApplication::translate("OfxGet", "Profile", nullptr));
        query->setText(QApplication::translate("OfxGet", "Build Query", nullptr));
        statusLabel->setText(QApplication::translate("OfxGet", "Send institution status to OFX Home", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OfxGet: public Ui_OfxGet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OFXGET_H
