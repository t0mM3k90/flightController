#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#define MAX_THRUST 255
#define MIN_THRUST   0
#define MAX_YAW    127
#define MIN_YAW   -128
#define MAX_PITCH  127
#define MIN_PITCH -128
#define MAX_ROLL   127
#define MIN_ROLL  -128

#include <QObject>
#include <map>
#include <tuple>
#include "datamodels.h"

using namespace model;

class DataController : public QObject
{
  Q_OBJECT
  explicit DataController(QObject *parent = nullptr);
private:
  std::map<AXIS,std::tuple<axis*, channel*>> map;
  axis m_thrust, m_yaw, m_pitch, m_roll, m_aux1, m_aux2, m_aux3, m_aux4;
  channel m_ch1, m_ch2, m_ch3, m_ch4, m_ch5, m_ch6, m_ch7, m_ch8;

  axis* getAxis(AXIS a);
  channel* getChannel(AXIS a);
public:

  static DataController& getInstance(QObject* parent = nullptr);
  void trimValueChanged(AXIS a, int16_t trim);
  int16_t getRawAxisValue(AXIS a);
  int16_t getAxisValue(AXIS a);
  float getAxisPercentage(AXIS a);
  void invertChannel(CHANNELS c, bool invert);
  uint16_t getRawChannelValue(CHANNELS c);
  float getChannelValue(CHANNELS c);


  DataController(DataController const&)  = delete; //delete copyconstructor
  void operator=(DataController const&)  = delete; //delete = operator

signals:

public slots:
};

#endif // DATACONTROLLER_H
