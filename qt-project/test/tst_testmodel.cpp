#include <QtTest>
#include <iostream>
#include "datamodels.h"

// add necessary includes here

class TestModel : public QObject
{
  Q_OBJECT

public:
  TestModel();
  ~TestModel();

private slots:
  void test_axisPercentage();

};

TestModel::TestModel()
{

}

TestModel::~TestModel()
{

}

void TestModel::test_axisPercentage()
{
  model::axis axis(-100, 100);
  axis.m_value = -96;
  QVERIFY(axis.percentage() == float(0.02));
  axis.m_value = 0;
  QVERIFY(axis.percentage() == float(0.5));
  axis.m_value = 73;
  QVERIFY(axis.percentage() == float(0.865));
}

QTEST_APPLESS_MAIN(TestModel)
#include "tst_testmodel.moc"
