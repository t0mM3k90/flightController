#include <QApplication>

#include "mainwindow.h"
#include "datacontroller.h"
#include "arduinowriter.h"
#include "settingsmanager.h"
#include <QThread>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QThread arduinoThread(&a);
  DataController::getInstance(); //initialize DataController
  SettingsManager::getInstance(); //initialize SettingsManager
  ArduinoWriter aw;
  MainWindow w;

  arduinoThread.start();
  aw.moveToThread(&arduinoThread);
  aw.start();
  w.show();

  a.connect(&aw, &ArduinoWriter::dataTransmitted, &w, &MainWindow::arduinoTriggered);

  return a.exec();
}
