#ifndef DATAMODELS_H
#define DATAMODELS_H

#define MAX_CHANNEL_VALUE 255

#include <cstdint>

namespace model{

  enum CHANNELS
  {
    CH1,
    CH2,
    CH3,
    CH4,
    CH5,
    CH6,
    CH7,
    CH8
  };

  enum AXIS
  {
    THRUST,
    YAW,
    PITCH,
    ROLL,
    AUX1,
    AUX2,
    AUX3,
    AUX4
  };

  class axis
  {
    int16_t m_maxThreshold, m_minThreshold;
  public:
    explicit axis(int16_t min, int16_t max);
    int16_t m_value=0, m_trim=0;
    int16_t value();
    float percentage();
  };


  class channel
  {
    float m_percentage=0;
    uint16_t m_value=0;
    bool m_inverted=false;
  public:
    channel();
    void invert(bool i);
    void percentage(float perc);
    float percentage();
    uint16_t value();
  };
}
#endif // DATAMODELS_H
