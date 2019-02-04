#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include "datamodels.h"

class SettingsManager : public QObject
{
  Q_OBJECT
  explicit SettingsManager(QObject *parent = nullptr);
private:
  uint8_t m_thrustExpo, m_yawExpo, m_pitchExpo, m_rollExpo;
public:
  static SettingsManager& getInstance(QObject* parent = nullptr);

  SettingsManager(SettingsManager const&)  = delete; //delete copyconstructor
  void operator=(SettingsManager const&)  = delete; //delete = operator

  void setExpo(model::AXIS axis, uint8_t val);
  uint8_t getExpoValue(model::AXIS axis);

signals:

public slots:
};

#endif // SETTINGSMANAGER_H
