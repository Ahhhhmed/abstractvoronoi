#include <QString>
#include <QtTest>
#include <descriptor.h>

class TestTest : public QObject
{
    Q_OBJECT

public:
    TestTest();

private Q_SLOTS:
    void desctiptorTest();
};

TestTest::TestTest()
{
}

void TestTest::desctiptorTest()
{
    QVERIFY(Descriptor(std::make_tuple(1,2,3,4),std::make_tuple(2,4,1,6)).set() == std::set<int>({1,2,3,4,6}));
}

QTEST_APPLESS_MAIN(TestTest)

#include "tst_testtest.moc"
