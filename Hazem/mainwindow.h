#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "chambre.h"
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

    void on_pb_supprimer_clicked();


    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Chambre tmp;
};

#endif // MAINWINDOW_H
