#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSettings>
#include <QDialog>
#include <QString>
#include<QFontDialog>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();










    void on_actionBackgroung_triggered();

    void on_actionFont_triggered();

private:
    Ui::MainWindow *ui;
    QSettings* settings;



};
#endif // MAINWINDOW_H
