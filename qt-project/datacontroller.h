#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#include <QObject>

class DataController : public QObject
{
  Q_OBJECT
  explicit DataController(QObject *parent = nullptr);
private:
  int8_t m_trimThrust, m_trimYaw, m_trimPitch, m_trimRoll;
  int8_t m_axisThrust, m_axisYaw, m_axisPitch, m_axisRoll;
public:
  enum AXIS
  {
    THRUST,
    YAW,
    PITCH,
    ROLL
  };

  static DataController& getInstance(QObject* parent = nullptr);
  void trimValueChanged(AXIS t, int8_t val);
  int8_t getAxisValue(AXIS a);

  DataController(DataController const&)  = delete; //delete copyconstructor
  void operator=(DataController const&)  = delete; //delete = operator

signals:

public slots:
};

#endif // DATACONTROLLER_H
