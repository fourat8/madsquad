#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "rdv.h"
#include <QMainWindow>
#include <Qsound>

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
    void on_pb_modifier_clicked();
    //void on_pb_supprimer_2_clicked();
    void on_recherche_patient_clicked();
    void on_rechercher_medecin_clicked();
    //void on_chambre_recherche_clicked();

    void on_patient_recherche_returnPressed();

    void on_medecin_recherche_returnPressed();

private:
    Ui::MainWindow *ui;
    rdv tmprdv;
    QSound *son;
};

#endif // MAINWINDOW_H





