/********************************************************************************
** Form generated from reading UI file 'download.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOAD_H
#define UI_DOWNLOAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Download
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label;
    QTextEdit *request;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QComboBox *requestTypes;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLineEdit *url;
    QTextEdit *response;
    QTableWidget *vars;
    QPushButton *downloadButton;

    void setupUi(QWidget *Download)
    {
        if (Download->objectName().isEmpty())
            Download->setObjectName(QStringLiteral("Download"));
        Download->resize(600, 500);
        verticalLayout = new QVBoxLayout(Download);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new QLabel(Download);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 7, 0, 1, 1);

        label = new QLabel(Download);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 9, 0, 1, 1);

        request = new QTextEdit(Download);
        request->setObjectName(QStringLiteral("request"));

        gridLayout->addWidget(request, 10, 0, 1, 1);

        label_2 = new QLabel(Download);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 7, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_4 = new QLabel(Download);
        label_4->setObjectName(QStringLiteral("label_4"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_4);

        requestTypes = new QComboBox(Download);
        requestTypes->setObjectName(QStringLiteral("requestTypes"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(requestTypes->sizePolicy().hasHeightForWidth());
        requestTypes->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(requestTypes);


        gridLayout->addLayout(horizontalLayout, 5, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_5 = new QLabel(Download);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_2->addWidget(label_5);

        url = new QLineEdit(Download);
        url->setObjectName(QStringLiteral("url"));

        horizontalLayout_2->addWidget(url);


        gridLayout->addLayout(horizontalLayout_2, 5, 2, 1, 1);

        response = new QTextEdit(Download);
        response->setObjectName(QStringLiteral("response"));

        gridLayout->addWidget(response, 8, 2, 3, 1);

        vars = new QTableWidget(Download);
        vars->setObjectName(QStringLiteral("vars"));

        gridLayout->addWidget(vars, 8, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        downloadButton = new QPushButton(Download);
        downloadButton->setObjectName(QStringLiteral("downloadButton"));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        downloadButton->setFont(font);
        downloadButton->setStyleSheet(QStringLiteral("padding-top: 1em; padding-bottom: 1em"));

        verticalLayout->addWidget(downloadButton);


        retranslateUi(Download);

        QMetaObject::connectSlotsByName(Download);
    } // setupUi

    void retranslateUi(QWidget *Download)
    {
        Download->setWindowTitle(QApplication::translate("Download", "Form", nullptr));
        label_3->setText(QApplication::translate("Download", "Request Variables", nullptr));
        label->setText(QApplication::translate("Download", "Request", nullptr));
        label_2->setText(QApplication::translate("Download", "Response", nullptr));
        label_4->setText(QApplication::translate("Download", "Request Type:", nullptr));
        label_5->setText(QApplication::translate("Download", "URL:", nullptr));
        downloadButton->setText(QApplication::translate("Download", "Download OFX", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Download: public Ui_Download {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOAD_H
