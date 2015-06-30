#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionUsage_triggered();

    void on_actionAbout_triggered();

    void on_openRobotWeightsMain_clicked();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
