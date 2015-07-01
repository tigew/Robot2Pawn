#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QVector>
#include <QInputDialog>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString AttributeTranslate(QString attribute);

private slots:
    void on_actionExit_triggered();

    void on_actionUsage_triggered();

    void on_actionAbout_triggered();

    void on_openRobotWeightsMain_clicked();

    void on_actionOpen_triggered();

    void on_convertButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<QString> finishedWeightList;
    QVector<QString> weightNames;
    QVector<QString> weightValues;
};

#endif // MAINWINDOW_H
