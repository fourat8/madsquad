#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "docteur.h"
#include <QMainWindow>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();



    void on_supprimer_clicked();







   void on_pushButton_clicked();




   void on_lineEdit_textChanged(const QString &arg1);

   void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    docteur tmpdocteur;
};

#endif // MAINWINDOW_H
