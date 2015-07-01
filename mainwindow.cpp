#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Sets fixed size
    QWidget::setFixedSize(this->size());
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
    // creates dialog that gets the name/location of  where the file is
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "Text files (*.txt)");

    // returns if no name chosen
    if(fileName.isEmpty())
    {
        return;
    }

    // creates file object checks that it has text and reads it into robot weights
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
    // Checks if text is in the robot weights, no text no need to run the function
    if(ui->robotWeightText->toPlainText() == "")
    {
        QMessageBox msgBox;
        msgBox.setText("You need to have text in the left window first.");
        msgBox.exec();
        return;
    }

    // Get profile name from user
    QString requiredElems[4] = {"(","Pawn:", "v1:"};
    profileName = QInputDialog::getText(this, tr("Profile Name"), tr("Name:"));
    QString finishedString;
    QString startingString;
    QStringList weightList;

    if(profileName.isEmpty())
    {
        return;
    }

    // Adding require elems
    for(int i = 0; i < 3; i++)
    {
        finishedWeightList.push_back(requiredElems[i]);
    }
    finishedWeightList.push_back("\"" + profileName + "\":");

    // Setting up startingString and getting rid of spaces
    startingString = ui->robotWeightText->toPlainText();
    weightList = startingString.split("\n");


    // clearing the set bonus weights from the list
    // while spliting the name and values of the weights
    // into seperate vectors
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
    // Translates needed names from robot to pawn
    // then creates the finalized vector formated
    // in pawn lingo to be pushed to the string
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

    // Print loop (Bad name)
    // Added final needed elem
    // and pushes finalized vector to a string
    finishedWeightList.push_back(")");
    for(int i = 0; i < finishedWeightList.length(); i++)
    {
        if (i == finishedWeightList.length() - 1)
        {
           finishedString += finishedWeightList.at(i);
           break;
        }
        finishedString += finishedWeightList.at(i) + " ";
    }

    // pushses finished string to ui
    ui->pawnWeightText->setPlainText(finishedString);

    // clears needed vars to if you hit
    // convert again you wont get double
    // what you want
    weightValues.clear();
    weightNames.clear();
    finishedWeightList.clear();
    profileName.clear();
}

QString MainWindow::AttributeTranslate(QString attribute)
{
    // Translates Robot to Pawn strings
    // I really wish I could use switchs
    // here
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
    // Wont trigger save if pawn weights are empty
    if(ui->pawnWeightText->toPlainText() == "")
    {
        return;
    }

    // I kinda have an idea how this works
    // gets the save name/location you want
    QString fn = QFileDialog::getSaveFileName(this, tr("Save as..."), QString(), tr("Text Files (*.txt)"));

    // If empty returns
    if (fn.isEmpty())
    {
        return;
    }

    // If your being dumb and you didn't add .txt we add it for you
    if (!fn.endsWith(".txt", Qt::CaseInsensitive))
    {
        fn += ".txt";
    }

    // Creates writer then shoves our file into it
    QTextDocumentWriter writer(fn);

    writer.write(ui->pawnWeightText->document());
    ui->pawnWeightText->document()->setModified(false);
}

void MainWindow::on_actionSave_triggered()
{
    on_saveWeights_clicked();
}
