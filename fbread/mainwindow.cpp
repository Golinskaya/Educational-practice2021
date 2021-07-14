#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QFile>
#include<QMessageBox>
#include<QTextStream>
#include<QXmlStreamReader>
#include<QDebug>
#include<QFontDialog>
#include<QColorDialog>




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
        QString book;
        QString imgId;
        QString imgType;
        QStringList thisToken;
        QXmlStreamReader xml(&file);
        while (!xml.atEnd()) {
             switch(xml.readNext())
             {
             case QXmlStreamReader::NoToken:
                 qDebug()<<"QXmlStreamReader::NoToken";
                 break;
             case QXmlStreamReader::StartDocument:
                 book="<!DOCTYPE HTML><html><body style=\"font-size:16px\">";
                 break;
             case QXmlStreamReader::EndDocument:
                 book.append("</body></html>");
                 break;
             case QXmlStreamReader::StartElement:
                  thisToken.append( xml.name().toString() );
                  if( xml.name().toString() == "image" )
                {
                    if(xml.attributes().count() > 0)
                    book.append("<p align=\"center\">"+xml.attributes().at(0).value().toString()+"</p>");
                }
                   if(xml.name() == "binary")
                {
                   imgId = xml.attributes().at(0).value().toString();
                  imgType = xml.attributes().at(1).value().toString();
                 }
                   break;
              case QXmlStreamReader::EndElement:
                 if( thisToken.last() == xml.name().toString() )
                    thisToken.removeLast();
                 else
                    qDebug() << "error token";
                   break;
             case QXmlStreamReader::Characters:
             if( xml.text().toString().contains( QRegExp("[A-Z]|[a-z]|[А-Я]|[а-я]") ))
                {
                  if(thisToken.contains("description"))
                    {
                      break;
                    }
                     if(thisToken.contains("div"))
                        break;
                     if(!thisToken.contains( "binary" ))
                       book.append("<p>" + xml.text().toString() + "</p>");
                       }
                     if(thisToken.contains( "binary" ) )
                      {
                        QString image = "<img src=\"data:"
                               + imgType +";base64,"
                               + xml.text().toString()
                               + "\"/>";
                        book.replace("#"+imgId, image);
                       }
                       break;


  }
        }
  file.close();
  ui->textBrowser->setHtml(book);
}























void MainWindow::on_actionBackgroung_triggered()
{

    QColor color = QColorDialog::getColor(Qt::white,this,"Choose Color");
    if(color.isValid())
    {
        ui->textBrowser->setTextBackgroundColor(color);
     }

}




void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);
    if (ok)
    {
        ui->textBrowser->setFont(font);
    }
}

