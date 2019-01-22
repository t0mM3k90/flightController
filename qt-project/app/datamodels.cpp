#include "datamodels.h"
#include <cstdlib>

using namespace model;

axis::axis(int16_t min, int16_t max):
  m_maxThreshold(max),
  m_minThreshold(min)
{
}

int16_t axis::value()
{
  int val = m_value + m_trim;
  if(val > m_maxThreshold)
    val = m_maxThreshold;
  else if (val < m_minThreshold)
    val = m_minThreshold;

  return static_cast<int16_t>(val);
}

float axis::percentage(){
  int range = std::abs(m_minThreshold) + std::abs(m_maxThreshold);
  int offset = (m_value+m_trim) - m_minThreshold;
  return static_cast<float>(offset) / range;
}


channel::channel()
{

}

void channel::percentage(float perc)
{
  uint16_t tmp = static_cast<uint16_t>(perc * MAX_CHANNEL_VALUE);
  if (m_inverted)
  {
    m_value = MAX_CHANNEL_VALUE - tmp;
    m_percentage = 1 - perc;
  }
  else
  {
    m_value = tmp;
    m_percentage = perc;
  }
}

float channel::percentage()
{
  return m_percentage;
}

uint16_t channel::value()
{
  return m_value;
}

void channel::invert(bool i)
{
  uint16_t tmp = m_value;
  if (m_inverted != i)
  {
    m_value = MAX_CHANNEL_VALUE - tmp;
  }
  else
  {
    m_value = tmp;
  }
  m_percentage = static_cast<float>(m_value) / MAX_CHANNEL_VALUE;
  m_inverted = i;
}
