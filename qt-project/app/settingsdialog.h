#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
  class SettingsDialog;
}

class SettingsDialog : public QDialog
{
  Q_OBJECT
  uint8_t m_oldThrustExpo, m_oldYawExpo, m_oldPitchExpo, m_oldRollExpo;

public:
  explicit SettingsDialog(QWidget *parent = nullptr);
  ~SettingsDialog();

private slots:
  void on_buttonBox_rejected();

  void on_buttonBox_accepted();

private:
  Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
