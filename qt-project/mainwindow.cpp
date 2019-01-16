#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->left_plot->enableAxis(QwtPlot::xBottom, false);
  ui->left_plot->enableAxis(QwtPlot::yLeft, false);
  ui->right_plot->enableAxis(QwtPlot::xBottom, false);
  ui->right_plot->enableAxis(QwtPlot::yLeft, false);
  ui->left_plot->setCanvasBackground(QBrush(QColor(26,158,178)));
  ui->right_plot->setCanvasBackground(QBrush(QColor(26,158,178)));

  QwtPlotGrid *grid1 = new QwtPlotGrid();
  QwtPlotGrid *grid2 = new QwtPlotGrid();
  grid1->setPen(Qt::lightGray,1.0,Qt::PenStyle::DotLine);
  grid2->setPen(Qt::lightGray,1.0,Qt::PenStyle::DotLine);
  grid1->attach(ui->left_plot);
  grid2->attach(ui->right_plot);

  ui->statusBar->addWidget(new QLabel("(0,0,0,0,0,0,0,0)",this));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::updateValueWidgets()
{
  DataController *dataCtrl = &DataController::getInstance();
  ui->thrust_slide->setValue(static_cast<double>(dataCtrl->getAxisValue(DataController::AXIS::THRUST)));
  ui->yaw_slide->setValue(static_cast<double>(dataCtrl->getAxisValue(DataController::AXIS::YAW)));
  ui->pitch_slide->setValue(static_cast<double>(dataCtrl->getAxisValue(DataController::AXIS::PITCH)));
  ui->roll_slide->setValue(static_cast<double>(dataCtrl->getAxisValue(DataController::AXIS::ROLL)));
}

// ************************** GUI SLOTS **************************

void MainWindow::on_action_Exit_triggered()
{
  std::exit(0);
}

void MainWindow::on_trim_thrust_valueChanged(double value)
{
  ui->lbl_trimThrus->setText(QString::number(static_cast<int>(value)));
  DataController::getInstance().trimValueChanged(DataController::AXIS::THRUST, static_cast<int8_t>(value));
  updateValueWidgets();
}

void MainWindow::on_trim_yaw_valueChanged(double value)
{
  ui->lbl_trimYaw->setText(QString::number(static_cast<int>(value)));
  DataController::getInstance().trimValueChanged(DataController::AXIS::YAW, static_cast<int8_t>(value));
  updateValueWidgets();
}

void MainWindow::on_trim_pitch_valueChanged(double value)
{
  ui->lbl_trimPitch->setText(QString::number(static_cast<int>(value)));
  DataController::getInstance().trimValueChanged(DataController::AXIS::PITCH, static_cast<int8_t>(value));
  updateValueWidgets();
}

void MainWindow::on_trim_roll_valueChanged(double value)
{
  ui->lbl_trimRoll->setText(QString::number(static_cast<int>(value)));
  DataController::getInstance().trimValueChanged(DataController::AXIS::ROLL, static_cast<int8_t>(value));
  updateValueWidgets();
}

void MainWindow::on_action_Clear_Trims_triggered()
{
  ui->trim_thrust->setValue(0);
  ui->trim_yaw->setValue(0);
  ui->trim_pitch->setValue(0);
  ui->trim_roll->setValue(0);
  DataController::getInstance().trimValueChanged(DataController::AXIS::THRUST, 0);
  DataController::getInstance().trimValueChanged(DataController::AXIS::YAW, 0);
  DataController::getInstance().trimValueChanged(DataController::AXIS::PITCH, 0);
  DataController::getInstance().trimValueChanged(DataController::AXIS::ROLL, 0);
  updateValueWidgets();
}
