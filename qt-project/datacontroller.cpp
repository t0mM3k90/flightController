#include "datacontroller.h"

DataController::DataController(QObject *parent) : QObject(parent)
{

}

DataController& DataController::getInstance(QObject* parent)
{
  static DataController instance(parent);
  return instance;
}

void DataController::trimValueChanged(AXIS t, int8_t val)
{
  switch(t)
  {
    case AXIS::THRUST:
      {
        m_trimThrust = val;
        break;
      }
    case AXIS::YAW:
      {
        m_trimYaw = val;
        break;
      }
    case AXIS::PITCH:
      {
        m_trimPitch = val;
        break;
      }
    case AXIS::ROLL:
      {
        m_trimRoll = val;
        break;
      }
  }

}

int8_t DataController::getAxisValue(AXIS a)
{
  switch(a)
  {
    case AXIS::THRUST: return m_axisThrust + m_trimThrust;
    case AXIS::YAW: return m_axisYaw + m_trimYaw;
    case AXIS::PITCH: return m_axisPitch + m_trimPitch;
    case AXIS::ROLL: return m_axisRoll + m_trimRoll;
  }
  return 0;
}
