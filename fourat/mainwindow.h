#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "patient.h"
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


    void on_modif_clicked();


    void on_rechercher_clicked();

    void on_rech_returnPressed();

    void on_rechercher_2_clicked();

private:
    Ui::MainWindow *ui;
    patient tmppatient;
};

#endif // MAINWINDOW_H
