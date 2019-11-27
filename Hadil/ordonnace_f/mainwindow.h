#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ordo.h"
#include <QMainWindow>
#include <QWidget>
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




   void on_numm_textChanged(const QString &arg1);

   void on_numm_returnPressed();

   void on_pdf_clicked();

private:
    Ui::MainWindow *ui;
 ordo tmpordo;
};

#endif // MAINWINDOW_H

