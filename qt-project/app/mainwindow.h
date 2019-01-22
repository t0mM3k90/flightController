#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datacontroller.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
private:
  void updateValueWidgets();
public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_action_Exit_triggered();
  void on_trim_thrust_valueChanged(double value);
  void on_trim_yaw_valueChanged(double value);
  void on_trim_pitch_valueChanged(double value);
  void on_trim_roll_valueChanged(double value);
  void on_action_Clear_Trims_triggered();

  void on_invertChannel1_stateChanged(int state);
  void on_invertChannel2_stateChanged(int state);
  void on_invertChannel3_stateChanged(int state);
  void on_invertChannel4_stateChanged(int state);
  void on_invertChannel5_stateChanged(int state);
  void on_invertChannel6_stateChanged(int state);
  void on_invertChannel7_stateChanged(int state);
  void on_invertChannel8_stateChanged(int state);

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
