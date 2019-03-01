#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#define MAX_THRUST  127
#define MIN_THRUST -128
#define MAX_YAW     127
#define MIN_YAW    -128
#define MAX_PITCH   127
#define MIN_PITCH  -128
#define MAX_ROLL    127
#define MIN_ROLL   -128

#include <QObject>
#include <QVector>
#include <map>
#include <tuple>
#include <complex>
#include "datamodels.h"

using namespace model;

class DataController : public QObject
{
  Q_OBJECT
  explicit DataController(QObject *parent = nullptr);
private:
  axis* getAxis(AXIS a);
  channel* getChannel(AXIS a);
  void recalculateCurve(int p, QVector<double> &yData);

  std::map<AXIS,std::tuple<axis*, channel*>> map;
  axis m_thrust;
  axis m_yaw;
  axis m_pitch;
  axis m_roll;
  axis m_aux1;
  axis m_aux2;
  axis m_aux3;
  axis m_aux4;

  channel m_ch1;
  channel m_ch2;
  channel m_ch3;
  channel m_ch4;
  channel m_ch5;
  channel m_ch6;
  channel m_ch7;
  channel m_ch8;

  QVector<double> m_xData;
  QVector<double> m_thrustCurveYData;
  QVector<double> m_yawCurveYData;
  QVector<double> m_pitchCurveYData;
  QVector<double> m_rollCurveYData;

public:
  static DataController& getInstance(QObject* parent = nullptr);
  //setters
  void expoChanged(AXIS a, int p);
  void axisValueChanged(AXIS a, int16_t value);
  void trimValueChanged(AXIS a, int16_t trim);
  void invertChannel(CHANNELS c, bool invert);

  //getters
  const QVector<double>& getCurveXData();
  const QVector<double>& getCurveData(AXIS a);
  int16_t getAxisValue(AXIS a);
  float getAxisPercentage(AXIS a);
  float getChannelValue(CHANNELS c);
  float getChannelPercentage(CHANNELS c);
  int16_t getRawAxisValue(AXIS a);
  uint16_t getRawChannelValue(CHANNELS c);

  DataController(DataController const&)  = delete; //delete copyconstructor
  void operator=(DataController const&)  = delete; //delete assignmentoperator

signals:

public slots:
};

#endif // DATACONTROLLER_H
