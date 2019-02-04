#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "mainwindow.h"
#include "settingsmanager.h"

#include <iostream>

SettingsDialog::SettingsDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SettingsDialog)
{
  ui->setupUi(this);
  //visualize change on GUI (FIXME: maybe GUI shall be connected to SettingsManager instead?!)
  connect(ui->set_thrustExpo, &QScrollBar::valueChanged, static_cast<MainWindow*>(parent), &MainWindow::onThrustExpoChanged);
  connect(ui->set_yawExpo, &QScrollBar::valueChanged, static_cast<MainWindow*>(parent), &MainWindow::onYawExpoChanged);
  connect(ui->set_pitchExpo, &QScrollBar::valueChanged, static_cast<MainWindow*>(parent), &MainWindow::onPitchExpoChanged);
  connect(ui->set_rollExpo, &QScrollBar::valueChanged, static_cast<MainWindow*>(parent), &MainWindow::onRollExpoChanged);

  //remember old settings
  m_oldThrustExpo = SettingsManager::getInstance().getExpoValue(model::AXIS::THRUST);
  m_oldYawExpo = SettingsManager::getInstance().getExpoValue(model::AXIS::YAW);
  m_oldPitchExpo = SettingsManager::getInstance().getExpoValue(model::AXIS::PITCH);
  m_oldRollExpo = SettingsManager::getInstance().getExpoValue(model::AXIS::ROLL);

  ui->set_thrustExpo->setValue(m_oldThrustExpo);
  ui->set_yawExpo->setValue(m_oldYawExpo);
  ui->set_pitchExpo->setValue(m_oldPitchExpo);
  ui->set_rollExpo->setValue(m_oldRollExpo);

  //write the expos directly into the settings
  connect(ui->set_thrustExpo, &QScrollBar::valueChanged, [](int val){SettingsManager::getInstance().setExpo(model::AXIS::THRUST, static_cast<uint8_t>(val));});
  connect(ui->set_yawExpo, &QScrollBar::valueChanged, [](int val){SettingsManager::getInstance().setExpo(model::AXIS::YAW, static_cast<uint8_t>(val));});
  connect(ui->set_pitchExpo, &QScrollBar::valueChanged, [](int val){SettingsManager::getInstance().setExpo(model::AXIS::PITCH, static_cast<uint8_t>(val));});
  connect(ui->set_rollExpo, &QScrollBar::valueChanged, [](int val){SettingsManager::getInstance().setExpo(model::AXIS::ROLL, static_cast<uint8_t>(val));});
}

SettingsDialog::~SettingsDialog()
{
  delete ui;
}


void SettingsDialog::on_buttonBox_rejected()
{
  //set back old settings
  SettingsManager::getInstance().setExpo(model::AXIS::THRUST, m_oldThrustExpo);
  SettingsManager::getInstance().setExpo(model::AXIS::YAW, m_oldYawExpo);
  SettingsManager::getInstance().setExpo(model::AXIS::PITCH, m_oldPitchExpo);
  SettingsManager::getInstance().setExpo(model::AXIS::ROLL, m_oldRollExpo);

  //setting back the scrollbars, to notify the GUI (they are connected(
  ui->set_thrustExpo->setValue(m_oldThrustExpo);
  ui->set_yawExpo->setValue(m_oldYawExpo);
  ui->set_pitchExpo->setValue(m_oldPitchExpo);
  ui->set_rollExpo->setValue(m_oldRollExpo);

  this->close();
}

void SettingsDialog::on_buttonBox_accepted()
{
  this->close();
}
