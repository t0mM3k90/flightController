#ifndef ARDUINOWRITER_H
#define ARDUINOWRITER_H

#include <QObject>
#include <QTimer>
//#include <QSerialPort>

class ArduinoWriter: public QObject
{
  Q_OBJECT
private:
  QTimer m_timer;
  void transmitData();
public:
  ArduinoWriter();
  void start();

signals:
  void dataTransmitted();
};

#endif // ARDUINOWRITER_H
