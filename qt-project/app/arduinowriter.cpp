#include "arduinowriter.h"
#include <iostream>

ArduinoWriter::ArduinoWriter()
{
  m_timer.setInterval(100);
  m_timer.setSingleShot(false);
  connect(&m_timer, &QTimer::timeout, this, &ArduinoWriter::transmitData);
}

void ArduinoWriter::start()
{
  m_timer.start();
}

void ArduinoWriter::transmitData()
{
  std::cout << "transmit data" << std::endl;
  emit dataTransmitted();
}
