#include <QString>
#include <QtTest>
#include <descriptor.h>
#include <historygraphnode.h>

class TestTest : public QObject
{
    Q_OBJECT

public:
    TestTest();
private:
    Descriptor sampleDescriptor;

private Q_SLOTS:
    void desctiptorTest();
    void historyGraphNodeTest();
};

TestTest::TestTest()
    :sampleDescriptor(Descriptor(std::make_tuple(1,2,3,4),std::make_tuple(2,4,1,6)))
{

}

void TestTest::desctiptorTest()
{
    QVERIFY(sampleDescriptor.set() == std::set<int>({1,2,3,4,6}));
}

void TestTest::historyGraphNodeTest()
{
    auto h = HistoryGraphNode(sampleDescriptor);
    QVERIFY(h.descriptor().set() == sampleDescriptor.set());
    QVERIFY(h.children_number() == 0);
}

QTEST_APPLESS_MAIN(TestTest)

#include "tst_testtest.moc"
