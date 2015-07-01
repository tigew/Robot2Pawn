#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionUsage_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Enter your text on the left and hit 'Convert'.\nButtons beyond that are self explanitory.");
    msgBox.exec();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Made using Qt and love.\nPlease Mr.Robot add this feature!");
    msgBox.exec();
}

void MainWindow::on_openRobotWeightsMain_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "Text files (*.txt)");

    if(fileName.isEmpty())
    {
        return;
    }

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream in(&file);

    while (!in.atEnd())
    {
       QString line = in.readLine();
       ui->robotWeightText->appendPlainText(line);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    on_openRobotWeightsMain_clicked();
}

void MainWindow::on_convertButton_clicked()
{
    // Get profile name from user
    QString requiredElems[4] = {"(","Pawn:", "v1:"};
    QString profileName = QInputDialog::getText(this, tr("Profile Name"), tr("Name:"));
    QString finishedString;
    QString startingString;
    QStringList weightList;

    // Adding require elems
    for(int i = 0; i < 3; i++)
    {
        weightVector.push_back(requiredElems[i]);
    }
    weightVector.push_back("\"" + profileName + "\"");

    // Setting up startingString and getting rid of spaces
    startingString = ui->robotWeightText->toPlainText();
    weightList = startingString.split("\n");



    // Meat


    // Print loop
    weightVector.push_back(")");
    for(int i = 0; i < weightVector.length(); i++)
    {
        finishedString += weightVector.at(i) + " ";
    }

    ui->pawnWeightText->setPlainText(finishedString);
}

QString MainWindow::AttributeTranslate(QString attribute)
{
    QString translated;

    return translated;
}
