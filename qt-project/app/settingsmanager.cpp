#include "settingsmanager.h"

SettingsManager::SettingsManager(QObject *parent) : QObject(parent),
  m_thrustExpo(0),
  m_yawExpo(0),
  m_pitchExpo(0),
  m_rollExpo(0)
{

}

SettingsManager& SettingsManager::getInstance(QObject* parent)
{
  static SettingsManager instance(parent);
  return instance;
}

void SettingsManager::setExpo(model::AXIS axis, uint8_t val)
{
  switch(axis)
  {
    case model::AXIS::THRUST:
      {
        m_thrustExpo = val;
        break;
      }
    case model::AXIS::YAW:
      {
        m_yawExpo = val;
        break;
      }
    case model::AXIS::PITCH:
      {
        m_pitchExpo = val;
        break;
      }
    case model::AXIS::ROLL:
      {
        m_rollExpo = val;
        break;
      }
    default:
      {
        return;
      }
  }
}

uint8_t SettingsManager::getExpoValue(model::AXIS axis)
{
  switch(axis)
  {
    case model::AXIS::THRUST: return m_thrustExpo;
    case model::AXIS::YAW: return m_yawExpo;
    case model::AXIS::PITCH: return m_pitchExpo;
    case model::AXIS::ROLL: return m_rollExpo;
    default: return 0;
  }
}
