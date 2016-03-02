#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "yantranslate.h"

class UnitTest : public QObject
{
    Q_OBJECT

public:
    UnitTest();

private Q_SLOTS:
    void testCase1_data();
    void testCase1();
};

UnitTest::UnitTest()
{
}

void UnitTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::addColumn<QString>("translation");
    QTest::newRow("test0") << "мама" << "mom";
    QTest::newRow("test01") << "папа" << "dad";
    QTest::newRow("test02") << "" << "";
}

void UnitTest::testCase1()
{
    YanTranslate yt;

    QFETCH(QString, data);
    QFETCH(QString, translation);

    yt.setText(data);
    yt.setLang("ru-en");
    QString actual = yt.yantranslate();
    QCOMPARE (actual, translation);
    //QVERIFY2(true, "Failure");
}

QTEST_MAIN(UnitTest)

#include "tst_unittest.moc"
