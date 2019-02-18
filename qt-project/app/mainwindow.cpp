#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qwt/qwt_plot_grid.h"
#include "settingsdialog.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  //initialize the vectors for the curves
  for(int x=-100;x<=100;++x)
  {
    m_xData.append(x);
    m_thrustCurveYData.append(x);
    m_yawCurveYData.append(x);
    m_pitchCurveYData.append(x);
    m_rollCurveYData.append(x);
  }
  m_thrustCurve.setSamples(m_xData, m_thrustCurveYData);
  m_yawCurve.setSamples(m_xData, m_yawCurveYData);
  m_pitchCurve.setSamples(m_xData, m_pitchCurveYData);
  m_rollCurve.setSamples(m_xData, m_rollCurveYData);

  //setting colors for the curves
  m_thrustCurve.setPen(Qt::black, 1.0);
  m_yawCurve.setPen(Qt::red, 1.0);
  m_pitchCurve.setPen(Qt::blue, 1.0);
  m_rollCurve.setPen(Qt::yellow, 1.0);

  m_thrustCurve.attach(ui->left_plot);
  m_yawCurve.attach(ui->left_plot);
  m_pitchCurve.attach(ui->right_plot);
  m_rollCurve.attach(ui->right_plot);

  //set constraints for the trim-wheels
  ui->trim_thrust->setRange(MIN_THRUST, MAX_THRUST);
  ui->trim_yaw->setRange(MIN_YAW, MAX_YAW);
  ui->trim_pitch->setRange(MIN_PITCH, MAX_PITCH);
  ui->trim_roll->setRange(MIN_ROLL, MAX_ROLL);

  //draw grids into plot windows
  ui->left_plot->enableAxis(QwtPlot::xBottom, false);
  ui->left_plot->enableAxis(QwtPlot::yLeft, false);
  ui->right_plot->enableAxis(QwtPlot::xBottom, false);
  ui->right_plot->enableAxis(QwtPlot::yLeft, false);
  ui->left_plot->setCanvasBackground(QBrush(QColor(26,158,178)));
  ui->right_plot->setCanvasBackground(QBrush(QColor(26,158,178)));

  QwtPlotGrid *grid1 = new QwtPlotGrid();
  QwtPlotGrid *grid2 = new QwtPlotGrid();
  grid1->setMajorPen(Qt::black,1.0,Qt::PenStyle::SolidLine);
  grid1->setMinorPen(Qt::lightGray,1.0,Qt::PenStyle::DotLine);
  grid2->setMajorPen(Qt::black,1.0,Qt::PenStyle::SolidLine);
  grid2->setMinorPen(Qt::lightGray,1.0,Qt::PenStyle::DotLine);

  grid1->enableXMin(true);
  grid1->enableYMin(true);
  grid2->enableXMin(true);
  grid2->enableYMin(true);

  QwtScaleDiv div(-100,100);
  QList<double> ticks[3];
  ticks[QwtScaleDiv::MajorTick] << 0;
  ticks[QwtScaleDiv::MediumTick] << -100 << -80 << -60 << -40 << -20 << 20 << 40 << 60 << 80 << 100;
  ticks[QwtScaleDiv::MinorTick] << -90 << -70 << -50 << -30 << -10 << 10 << 30 << 50 << 70 << 90 ;
  div.setTicks(QwtScaleDiv::MajorTick,ticks[QwtScaleDiv::MajorTick]);
  div.setTicks(QwtScaleDiv::MediumTick,ticks[QwtScaleDiv::MediumTick]);
  div.setTicks(QwtScaleDiv::MinorTick,ticks[QwtScaleDiv::MinorTick]);
  ui->left_plot->setAxisScaleDiv(QwtPlot::xBottom, div);
  ui->left_plot->setAxisScaleDiv(QwtPlot::yLeft, div);
  ui->right_plot->setAxisScaleDiv(QwtPlot::xBottom, div);
  ui->right_plot->setAxisScaleDiv(QwtPlot::yLeft, div);
  grid1->attach(ui->left_plot);
  grid2->attach(ui->right_plot);

  //draw markers into the grids
  m_thrustMarker = new QwtPlotMarker();
  m_yawMarker = new QwtPlotMarker();
  m_pitchMarker = new QwtPlotMarker();
  m_rollMarker = new QwtPlotMarker();

  m_thrustMarkerSymbol = new QwtSymbol(QwtSymbol::Style::Ellipse);
  m_yawMarkerSymbol = new QwtSymbol(QwtSymbol::Style::Ellipse);
  m_pitchMarkerSymbol = new QwtSymbol(QwtSymbol::Style::Ellipse);
  m_rollMarkerSymbol = new QwtSymbol(QwtSymbol::Style::Ellipse);

  m_thrustMarkerSymbol->setSize(5,5);
  m_thrustMarkerSymbol->setPen(Qt::black);
  m_thrustMarkerSymbol->setBrush(Qt::black);
  m_yawMarkerSymbol->setSize(5,5);
  m_yawMarkerSymbol->setPen(Qt::red);
  m_yawMarkerSymbol->setBrush(Qt::red);
  m_pitchMarkerSymbol->setSize(5,5);
  m_pitchMarkerSymbol->setPen(Qt::blue);
  m_pitchMarkerSymbol->setBrush(Qt::blue);
  m_rollMarkerSymbol->setSize(5,5);
  m_rollMarkerSymbol->setPen(Qt::yellow);
  m_rollMarkerSymbol->setBrush(Qt::yellow);

  m_thrustMarker->setSymbol(m_thrustMarkerSymbol);
  m_thrustMarker->attach(ui->left_plot);
  m_yawMarker->setSymbol(m_yawMarkerSymbol);
  m_yawMarker->attach(ui->left_plot);
  m_pitchMarker->setSymbol(m_pitchMarkerSymbol);
  m_pitchMarker->attach(ui->right_plot);
  m_rollMarker->setSymbol(m_rollMarkerSymbol);
  m_rollMarker->attach(ui->right_plot);

  //(better viewability on ASUS-Netbook)
  this->setGeometry(0,60,1018,682);

  //statusbar
  m_joystickView = new QGraphicsView(this);
  m_arduinoView = new QGraphicsView(this);
  m_joystickScene = new QGraphicsScene(this);
  m_arduinoScene = new QGraphicsScene(this);
  m_joystickGreen = new QPixmap(":images/resources/joystick_green_96.png");
  m_joystickRed = new QPixmap(":images/resources/joystick_red_96.png");
  m_arduinoGreen = new QPixmap(":images/resources/arduino_green_96.png");
  m_arduinoRed = new QPixmap(":images/resources/arduino_red_96.png");
  m_joystickView->setMaximumSize(30,30);
  m_arduinoView->setMaximumSize(30,30);
  m_joystickScene->addPixmap(m_joystickRed->scaled(29,29));
  m_arduinoScene->addPixmap(m_arduinoRed->scaled(29,29));
  m_joystickView->setScene(m_joystickScene);
  m_arduinoView->setScene(m_arduinoScene);
  m_joystickTimer = new QTimer(this);
  m_arduinoTimer = new QTimer(this);
  m_joystickTimer->setSingleShot(false);
  m_joystickTimer->setInterval(50);
  m_arduinoTimer->setSingleShot(false);
  m_arduinoTimer->setInterval(50);

  ui->statusBar->addPermanentWidget(m_joystickView);
  ui->statusBar->addPermanentWidget(m_arduinoView);
  ui->statusBar->addPermanentWidget(new QLabel(), 1); //spacer only

  connect(m_joystickTimer, &QTimer::timeout, [this](){this->m_joystickActive = !this->m_joystickActive; this->refreshJoystick();});
  connect(m_arduinoTimer, &QTimer::timeout, [this](){this->m_arduinoActive = !this->m_arduinoActive; this->refreshArduino();});

  on_action_Clear_Trims_triggered();
}

void MainWindow::refreshJoystick()
{
  if(m_joystickActive)
  {
    m_joystickScene->addPixmap(m_joystickGreen->scaled(29,29));
  } else
  {
    m_joystickScene->addPixmap(m_joystickRed->scaled(29,29));
    m_joystickTimer->stop();
  }
}

void MainWindow::refreshArduino()
{
  if(m_arduinoActive)
  {
    m_arduinoScene->addPixmap(m_arduinoGreen->scaled(29,29));
  } else
  {
    m_arduinoScene->addPixmap(m_arduinoRed->scaled(29,29));
    m_arduinoTimer->stop();
  }
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::updateValueWidgets()
{
  DataController *dataCtrl = &DataController::getInstance();
  ui->thrust_slide->setValue(static_cast<double>(dataCtrl->getAxisPercentage(model::AXIS::THRUST)*100));
  ui->yaw_slide->setValue((static_cast<double>(dataCtrl->getAxisPercentage(model::AXIS::YAW))*100));
  ui->pitch_slide->setValue((static_cast<double>(dataCtrl->getAxisPercentage(model::AXIS::PITCH))*100));
  ui->roll_slide->setValue((static_cast<double>(dataCtrl->getAxisPercentage(model::AXIS::ROLL))*100));

  ui->channel1->setValue(static_cast<int>(dataCtrl->getChannelValue(model::CHANNELS::CH1)*100));
  ui->channel2->setValue(static_cast<int>(dataCtrl->getChannelValue(model::CHANNELS::CH2)*100));
  ui->channel3->setValue(static_cast<int>(dataCtrl->getChannelValue(model::CHANNELS::CH3)*100));
  ui->channel4->setValue(static_cast<int>(dataCtrl->getChannelValue(model::CHANNELS::CH4)*100));
  ui->channel5->setValue(static_cast<int>(dataCtrl->getChannelValue(model::CHANNELS::CH5)*100));
  ui->channel6->setValue(static_cast<int>(dataCtrl->getChannelValue(model::CHANNELS::CH6)*100));
  ui->channel7->setValue(static_cast<int>(dataCtrl->getChannelValue(model::CHANNELS::CH7)*100));
  ui->channel8->setValue(static_cast<int>(dataCtrl->getChannelValue(model::CHANNELS::CH8)*100));

  //draw markers on plotlines (FIXME: values do not show +/- 100% yet which makes drawing shitty
  int thrust_x, yaw_x, pitch_x, roll_x;
  thrust_x = static_cast<int>(dataCtrl->getAxisPercentage(model::AXIS::THRUST)*100);
  m_thrustMarker->setValue(thrust_x, m_thrustCurveYData[thrust_x+100]);
  yaw_x = static_cast<int>(dataCtrl->getAxisPercentage(model::AXIS::YAW)*100);
  m_yawMarker->setValue(yaw_x, m_yawCurveYData[yaw_x+100]);
  pitch_x = static_cast<int>(dataCtrl->getAxisPercentage(model::AXIS::PITCH)*100);
  m_pitchMarker->setValue(pitch_x, m_pitchCurveYData[pitch_x+100]);
  roll_x = static_cast<int>(dataCtrl->getAxisPercentage(model::AXIS::ROLL)*100);
  m_rollMarker->setValue(roll_x, m_rollCurveYData[roll_x+100]);
  ui->left_plot->replot();
  ui->right_plot->replot();

}

// ************************** GUI SLOTS **************************

void MainWindow::joyStickTriggered()
{
  if(!m_joystickTimer->isActive())
    m_joystickTimer->start();  //start the timer, that toggles the JOYSTICK_INDICATOR from red to green
}

void MainWindow::arduinoTriggered()
{
  if(!m_arduinoTimer->isActive())
    m_arduinoTimer->start(); //start the timer, that toggles the ARDUINO_INDICATOR from red to green
}

void MainWindow::on_action_Exit_triggered()
{
  std::exit(0);
}

void MainWindow::on_trim_thrust_valueChanged(double value)
{
  ui->lbl_trimThrus->setText(QString::number(static_cast<int>(value)));
  DataController::getInstance().trimValueChanged(model::AXIS::THRUST, static_cast<int16_t>(value));
  updateValueWidgets();
}

void MainWindow::on_trim_yaw_valueChanged(double value)
{
  ui->lbl_trimYaw->setText(QString::number(static_cast<int>(value)));
  DataController::getInstance().trimValueChanged(model::AXIS::YAW, static_cast<int16_t>(value));
  updateValueWidgets();
}

void MainWindow::on_trim_pitch_valueChanged(double value)
{
  ui->lbl_trimPitch->setText(QString::number(static_cast<int>(value)));
  DataController::getInstance().trimValueChanged(model::AXIS::PITCH, static_cast<int16_t>(value));
  updateValueWidgets();
}

void MainWindow::on_trim_roll_valueChanged(double value)
{
  ui->lbl_trimRoll->setText(QString::number(static_cast<int>(value)));
  DataController::getInstance().trimValueChanged(model::AXIS::ROLL, static_cast<int16_t>(value));
  updateValueWidgets();
}

void MainWindow::on_action_Clear_Trims_triggered()
{
  DataController* dataCtrl = &DataController::getInstance();
  ui->trim_thrust->setValue(0);
  ui->trim_yaw->setValue(0);
  ui->trim_pitch->setValue(0);
  ui->trim_roll->setValue(0);
  dataCtrl->trimValueChanged(model::AXIS::THRUST, 0);
  dataCtrl->trimValueChanged(model::AXIS::YAW, 0);
  dataCtrl->trimValueChanged(model::AXIS::PITCH, 0);
  dataCtrl->trimValueChanged(model::AXIS::ROLL, 0);
  updateValueWidgets();
}

void MainWindow::on_invertChannel1_stateChanged(int state)
{
  DataController::getInstance().invertChannel(model::CHANNELS::CH1, static_cast<bool>(state));
  ui->channel1->setValue(static_cast<int>(DataController::getInstance().getChannelValue(model::CHANNELS::CH1)*100));
}

void MainWindow::on_invertChannel2_stateChanged(int state)
{
  DataController::getInstance().invertChannel(model::CHANNELS::CH2, static_cast<bool>(state));
  ui->channel2->setValue(static_cast<int>(DataController::getInstance().getChannelValue(model::CHANNELS::CH2)*100));
}

void MainWindow::on_invertChannel3_stateChanged(int state)
{
  DataController::getInstance().invertChannel(model::CHANNELS::CH3, static_cast<bool>(state));
  ui->channel3->setValue(static_cast<int>(DataController::getInstance().getChannelValue(model::CHANNELS::CH3)*100));
}

void MainWindow::on_invertChannel4_stateChanged(int state)
{
  DataController::getInstance().invertChannel(model::CHANNELS::CH4, static_cast<bool>(state));
  ui->channel4->setValue(static_cast<int>(DataController::getInstance().getChannelValue(model::CHANNELS::CH4)*100));
}

void MainWindow::on_invertChannel5_stateChanged(int state)
{
  DataController::getInstance().invertChannel(model::CHANNELS::CH5, static_cast<bool>(state));
  ui->channel5->setValue(static_cast<int>(DataController::getInstance().getChannelValue(model::CHANNELS::CH5)*100));
}

void MainWindow::on_invertChannel6_stateChanged(int state)
{
  DataController::getInstance().invertChannel(model::CHANNELS::CH6, static_cast<bool>(state));
  ui->channel6->setValue(static_cast<int>(DataController::getInstance().getChannelValue(model::CHANNELS::CH6)*100));
}

void MainWindow::on_invertChannel7_stateChanged(int state)
{
  DataController::getInstance().invertChannel(model::CHANNELS::CH7, static_cast<bool>(state));
  ui->channel7->setValue(static_cast<int>(DataController::getInstance().getChannelValue(model::CHANNELS::CH7)*100));
}

void MainWindow::on_invertChannel8_stateChanged(int state)
{
  DataController::getInstance().invertChannel(model::CHANNELS::CH8, static_cast<bool>(state));
  ui->channel8->setValue(static_cast<int>(DataController::getInstance().getChannelValue(model::CHANNELS::CH8)*100));
}

void MainWindow::onThrustExpoChanged(int value)
{
  recalculateCurve(value, m_thrustCurveYData);
  m_thrustCurve.setSamples(m_xData, m_thrustCurveYData);
  ui->left_plot->replot();
}

void MainWindow::onYawExpoChanged(int value)
{
  recalculateCurve(value, m_yawCurveYData);
  m_yawCurve.setSamples(m_xData, m_yawCurveYData);
  ui->left_plot->replot();
}

void MainWindow::onPitchExpoChanged(int value)
{
  recalculateCurve(value, m_pitchCurveYData);
  m_pitchCurve.setSamples(m_xData, m_pitchCurveYData);
  ui->right_plot->replot();
}

void MainWindow::onRollExpoChanged(int value)
{
  recalculateCurve(value, m_rollCurveYData);
  m_rollCurve.setSamples(m_xData, m_rollCurveYData);
  ui->right_plot->replot();
}

void MainWindow::on_action_Settings_triggered()
{
    SettingsDialog *dialog = new SettingsDialog(this);
    dialog->show();
}

// ************************** PRIVATE GUI FUNCTIONS **************************

void MainWindow::recalculateCurve(int p, QVector<double> &yData)
{
  auto f1 = [](double x){return x;};
  auto f2 = [](double x){return 100*std::pow(x/100.0, 3);};
  auto sig = [](int p){return 2/(1 + std::exp(-1*p/30.0))-1;};

  yData.clear();
  for(int x=-100; x<=100; ++x)
  {
    double y = f1(x) + (f2(x) - f1(x))*sig(p);
    yData.append(y);
  }
}
