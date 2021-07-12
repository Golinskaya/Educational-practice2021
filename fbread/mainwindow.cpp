#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QFile>
#include<QMessageBox>
#include<QTextStream>



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


void MainWindow::on_pushButton_clicked()
{

    QString file_name = QFileDialog ::getOpenFileName(this,"open a file","D://");
    QFile file(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"title","file not open");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setHtml(text);

    file.close();



}

