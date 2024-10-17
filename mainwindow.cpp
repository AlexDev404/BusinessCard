#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void openFile(Ui::MainWindow *ui, QString fileName){
    // Open up a file picker to read some JSON and print the data to the console
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Could not open file";
        return;
    }
    QTextStream in(&file);
    QString json = in.readAll();
    file.close(); // We have no use for this again, after reading it. So we'll dispose of it.

    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject data = doc.object();
    qDebug() << data; // Debug

    // Set the data in the UI
    ui->company_name->setText(data["company_name"].toString());
    ui->name->setText(data["name"].toString());
    ui->position->setText(data["position"].toString());
    ui->phone->setText(data["phone"].toString());
    ui->fax->setText(data["fax"].toString());
    ui->email->setText(data["email"].toString());
    ui->website->setText(data["website"].toString());
    ui->address->setText(data["address"].toString());
}

void MainWindow::on_openFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("JSON/Text Files (*.json; *.txt)"));
    openFile(ui, fileName);
}


void MainWindow::on_actionOpen_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("JSON/Text Files (*.json; *.txt)"));
    openFile(ui, fileName);
}


void MainWindow::on_actionClose_File_triggered()
{
    // Set the data in the UI
    ui->company_name->setText("Open a file to begin..");
    ui->name->setText("Open a file to begin..");
    ui->position->setText("Open a file to begin..");
    ui->phone->setText("Open a file to begin..");
    ui->fax->setText("Open a file to begin..");
    ui->email->setText("Open a file to begin..");
    ui->website->setText("Open a file to begin..");
    ui->address->setText("Open a file to begin..");
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit(); // Exit
}

