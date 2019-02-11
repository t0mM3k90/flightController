#include "datacontroller.h"

DataController::DataController(QObject *parent) : QObject(parent),
  m_thrust(MIN_THRUST,MAX_THRUST),
  m_yaw(MIN_YAW,MAX_YAW),
  m_pitch(MIN_PITCH,MAX_PITCH),
  m_roll(MIN_ROLL,MAX_ROLL),
  m_aux1(0,1),
  m_aux2(0,1),
  m_aux3(0,1),
  m_aux4(0,1)
{
  map.emplace(AXIS::THRUST, std::make_tuple(&m_thrust,&m_ch1));
  map.emplace(AXIS::YAW,    std::make_tuple(&m_yaw,&m_ch2));
  map.emplace(AXIS::PITCH,  std::make_tuple(&m_pitch,&m_ch3));
  map.emplace(AXIS::ROLL,   std::make_tuple(&m_roll,&m_ch4));
  map.emplace(AXIS::AUX1,   std::make_tuple(&m_aux1,&m_ch5));
  map.emplace(AXIS::AUX2,   std::make_tuple(&m_aux2,&m_ch6));
  map.emplace(AXIS::AUX3,   std::make_tuple(&m_aux3,&m_ch7));
  map.emplace(AXIS::AUX4,   std::make_tuple(&m_aux4,&m_ch8));
}

DataController& DataController::getInstance(QObject* parent)
{
  static DataController instance(parent);
  return instance;
}

void DataController::trimValueChanged(AXIS a, int16_t trim)
{
  axis* ax = getAxis(a);
  ax->m_trim = trim;
  float perc = ax->percentage();
  getChannel(a)->percentage(0.5f + 0.5f*perc);
}

int16_t DataController::getRawAxisValue(AXIS a)
{
  return getAxis(a)->m_value;
}

int16_t DataController::getAxisValue(AXIS a)
{
  return getAxis(a)->value();
}

float DataController::getAxisPercentage(AXIS a)
{
  return getAxis(a)->percentage();
}

void DataController::invertChannel(CHANNELS c, bool invert)
{
  switch(c)
    {
    case CHANNELS::CH1: m_ch1.invert(invert); break;
    case CHANNELS::CH2: m_ch2.invert(invert); break;
    case CHANNELS::CH3: m_ch3.invert(invert); break;
    case CHANNELS::CH4: m_ch4.invert(invert); break;
    case CHANNELS::CH5: m_ch5.invert(invert); break;
    case CHANNELS::CH6: m_ch6.invert(invert); break;
    case CHANNELS::CH7: m_ch7.invert(invert); break;
    case CHANNELS::CH8: m_ch8.invert(invert); break;
    }
}

uint16_t DataController::getRawChannelValue(CHANNELS c)
{
  switch(c)
    {
    case CHANNELS::CH1: return m_ch1.value();
    case CHANNELS::CH2: return m_ch2.value();
    case CHANNELS::CH3: return m_ch3.value();
    case CHANNELS::CH4: return m_ch4.value();
    case CHANNELS::CH5: return m_ch5.value();
    case CHANNELS::CH6: return m_ch6.value();
    case CHANNELS::CH7: return m_ch7.value();
    case CHANNELS::CH8: return m_ch8.value();
    }
}

float DataController::getChannelValue(CHANNELS c)
{
  switch(c)
    {
    case CHANNELS::CH1: return m_ch1.percentage();
    case CHANNELS::CH2: return m_ch2.percentage();
    case CHANNELS::CH3: return m_ch3.percentage();
    case CHANNELS::CH4: return m_ch4.percentage();
    case CHANNELS::CH5: return m_ch5.percentage();
    case CHANNELS::CH6: return m_ch6.percentage();
    case CHANNELS::CH7: return m_ch7.percentage();
    case CHANNELS::CH8: return m_ch8.percentage();
    }
}

axis* DataController::getAxis(AXIS a)
{
  axis* ax = static_cast<axis*>(std::get<0>(map.at(a)));
  return ax;
}

channel* DataController::getChannel(AXIS a)
{
  channel* ch = static_cast<channel*>(std::get<1>(map.at(a)));
  return ch;
}
