#include <QtTest/QtTest>

#include "../download.h"

class Download_test: public QObject
{
    Q_OBJECT
private slots:
    // Test response formatting
    void formatHello();
    void formatSgml();
    void formatXml();

    // Test request sanitizing
    void sanitizeHello();
    void sanitizeUserid1();
    void sanitizeUserid2();
    void sanitizeUserid3();
    void sanitizeUserid4();
    void sanitizeUserpass1();
    void sanitizeAcctid1();
    void sanitizeMultiple1();
};

void Download_test::formatHello()
{
    QString str = "Hello";
    QCOMPARE(Download::FormatResponse(str), QString("Hello"));
}

void Download_test::formatSgml()
{
    QString str = "OFXHEADER\n\n<open>text<open2>test2</open2>";
    QCOMPARE(Download::FormatResponse(str), QString("OFXHEADER\n\n<open>text\n<open2>test2\n</open2>"));
}

void Download_test::formatXml()
{
    QString str = "<?xml?><?OFX?>\n\n<open>text<open2>test2</open2></open>";
    QCOMPARE(Download::FormatResponse(str), QString("<?xml?>\n<?OFX?>\n\n<open>text\n<open2>test2\n</open2>\n</open>"));
}

void Download_test::sanitizeHello()
{
    QString str = "Hello";
    QCOMPARE(Download::SanitizeRequest(str), QString("Hello"));
}

void Download_test::sanitizeUserid1()
{
    QString str = "<USERID>ABCD";
    QCOMPARE(Download::SanitizeRequest(str), QString("<USERID>XXXXX"));
}

void Download_test::sanitizeUserid2()
{
    QString str = "<USERID>ABCD<OTHER>";
    QCOMPARE(Download::SanitizeRequest(str), QString("<USERID>XXXXX<OTHER>"));
}

void Download_test::sanitizeUserid3()
{
    QString str = "<USERID>ABCD\n  \n<OTHER>ABCD";
    QCOMPARE(Download::SanitizeRequest(str), QString("<USERID>XXXXX\n  \n<OTHER>XXXXX"));
}

void Download_test::sanitizeUserid4()
{
    QString str = "<userid>ABCD";
    QCOMPARE(Download::SanitizeRequest(str), QString("<userid>XXXXX"));
}

void Download_test::sanitizeUserpass1()
{
    QString str = "<USERPASS>secret";
    QCOMPARE(Download::SanitizeRequest(str), QString("<USERPASS>XXXXX"));
}

void Download_test::sanitizeAcctid1()
{
    QString str = "<ACCTID>secret";
    QCOMPARE(Download::SanitizeRequest(str), QString("<ACCTID>XXXXX"));
}

void Download_test::sanitizeMultiple1()
{
    QString str = "<USERID>user\n<USERPASS>pass<ACCTID>12345";
    QCOMPARE(Download::SanitizeRequest(str), QString("<USERID>XXXXX\n<USERPASS>XXXXX<ACCTID>XXXXX"));
}

QTEST_MAIN(Download_test)
#include "download_test.moc"
