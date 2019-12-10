#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "traitement.h"
#include <QMainWindow>
#include <QSound>
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



    void on_rech_returnPressed();

    //void on_rechercher_2_clicked();

    void on_rech_textChanged(const QString &arg1);

    void on_rech2_textChanged(const QString &arg1);


    void on_modif_2_clicked();

    void on_pb_supprimer_2_clicked();

private:
    Ui::MainWindow *ui;
    traitement tmptraitement;
    QSound *son;
};

#endif // MAINWINDOW_H
