#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsView>
#include <qwt/qwt_plot_curve.h>
#include <qwt/qwt_plot_marker.h>
#include <qwt/qwt_symbol.h>
#include "datacontroller.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
private:
  void updateValueWidgets();
  void refreshJoystick();
  void refreshArduino();

  QwtPlotCurve m_thrustCurve;
  QwtPlotCurve m_yawCurve;
  QwtPlotCurve m_pitchCurve;
  QwtPlotCurve m_rollCurve;

  QwtPlotMarker *m_thrustMarker;
  QwtPlotMarker *m_yawMarker;
  QwtPlotMarker *m_pitchMarker;
  QwtPlotMarker *m_rollMarker;

  QwtSymbol *m_thrustMarkerSymbol;
  QwtSymbol *m_yawMarkerSymbol;
  QwtSymbol *m_pitchMarkerSymbol;
  QwtSymbol *m_rollMarkerSymbol;

  QGraphicsView *m_joystickView;
  QGraphicsView *m_arduinoView;
  QGraphicsScene *m_joystickScene;
  QGraphicsScene *m_arduinoScene;
  bool m_joystickActive=false;
  bool m_arduinoActive=false;
  QPixmap *m_joystickGreen;
  QPixmap *m_joystickRed;
  QPixmap *m_arduinoGreen;
  QPixmap *m_arduinoRed;
  QTimer *m_joystickTimer;
  QTimer *m_arduinoTimer;

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

  void on_action_Settings_triggered();

public slots:
  void onThrustExpoChanged(int value);
  void onYawExpoChanged(int value);
  void onPitchExpoChanged(int value);
  void onRollExpoChanged(int value);

  void joyStickTriggered();
  void arduinoTriggered();

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
