#include <QString>
#include <QtTest>
#include <descriptor.h>
#include <historygraphnode.h>
#include <abstractvoronoidiagram.h>
#include <basicoperationprovider.h>

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
    void abstractVoronoiDiagramTest();
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

class DummyProvider : public BasicOperationProvider{


    // BasicOperationProvider interface
public:
    BasicOperationOutput basic_operation(int, int, int, int, int){
        return intersection_empty;
    }

    int number_of_sites(){return 4;}
};

void TestTest::abstractVoronoiDiagramTest()
{
    AbstractVoronoiDiagram instance;
    instance.initialize(new DummyProvider());
    QVERIFY(instance.getDiagram().edges.size() == 6);
    QVERIFY(instance.getDiagram().vertices.size() == 2);
}

QTEST_APPLESS_MAIN(TestTest)

#include "tst_testtest.moc"
