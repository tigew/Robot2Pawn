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
    weightValues.clear();
    weightNames.clear();
    finishedWeightList.clear();
    QString requiredElems[4] = {"(","Pawn:", "v1:"};
    profileName = QInputDialog::getText(this, tr("Profile Name"), tr("Name:"));
    QString finishedString;
    QString startingString;
    QStringList weightList;

    // Adding require elems
    for(int i = 0; i < 3; i++)
    {
        finishedWeightList.push_back(requiredElems[i]);
    }
    finishedWeightList.push_back("\"" + profileName + "\":");

    // Setting up startingString and getting rid of spaces
    startingString = ui->robotWeightText->toPlainText();
    weightList = startingString.split("\n");


    for(int i = 0; i < weightList.length(); i ++)
    {
        if(weightList.at(i).contains("set"))
        {
            continue;
        }

        QStringList temp = weightList.at(i).split(" ");
        weightNames.push_back(temp.at(0));

        for(int j = 0; j < temp.length(); j++)
        {
            if(temp.at(j).contains("."))
            {
                weightValues.push_back(temp.at(j));
            }
        }
    }


    // Meat
    for(int i = 0; i < weightNames.length(); i++)
    {
        if (weightNames.at(i) == "Haste" || weightNames.at(i) == "Mastery"|| weightNames.at(i) == "CriticalStrike" ||
            weightNames.at(i) == "AttackPower")
        {
            weightNames[i] = AttributeTranslate(weightNames.at(i));
        }

        if (i == weightNames.length() - 1)
        {
           finishedWeightList.push_back(weightNames.at(i) + "=" + weightValues.at(i));
           break;
        }
        finishedWeightList.push_back(weightNames.at(i) + "=" + weightValues.at(i) + ",");
    }

    // Print loop
    finishedWeightList.push_back(")");
    for(int i = 0; i < finishedWeightList.length(); i++)
    {
        finishedString += finishedWeightList.at(i) + " ";
    }

    ui->pawnWeightText->setPlainText(finishedString);
}

QString MainWindow::AttributeTranslate(QString attribute)
{
    QString translated;

    if(attribute == "Haste") {
        translated = "HasteRating";
    } else if (attribute == "Mastery") {
        translated = "MasteryRating";
    } else if (attribute == "CriticalStrike") {
        translated = "CritRating";
    } else if (attribute == "AttackPower") {
        translated = "Ap";
    } else {
        translated = "NO EXIST";
    }

    return translated;
}

void MainWindow::on_saveWeights_clicked()
{
    // I kinda have an idea how this works
    QString fn = QFileDialog::getSaveFileName(this, tr("Save as..."), QString(), tr("Text Files (*.txt)"));
    if (fn.isEmpty())
    {
        return;
    }

    if (!fn.endsWith(".txt", Qt::CaseInsensitive))
    {
        fn += ".txt";
    }
    QTextDocumentWriter writer(fn);

    writer.write(ui->pawnWeightText->document());
    ui->pawnWeightText->document()->setModified(false);
}

void MainWindow::on_actionSave_triggered()
{
    on_saveWeights_clicked();
}
