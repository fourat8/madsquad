#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "rdv.h"
#include <QMainWindow>
#include "patient.h"
#include <QSound>

namespace Ui {
class secretaire;
}

class secretaire : public QMainWindow
{
    Q_OBJECT

public:
    explicit secretaire(QWidget *parent = nullptr);
    ~secretaire();

private slots:
    void on_pb_ajouter_clicked();
    void on_pb_supprimer_clicked();
    void on_pb_modifier_clicked();
    //void on_pb_supprimer_2_clicked();
    void on_recherche_patient_clicked();
   // void on_rechercher_medecin_clicked();
    //void on_chambre_recherche_clicked();

    void on_patient_recherche_returnPressed();

    void on_pushButton_clicked();

    void on_pb_ajouter_3_clicked();

    void on_pb_supprimer_3_clicked();

    void on_modif_2_clicked();

    void on_rech_2_returnPressed();

    void on_rech_2_textChanged(const QString &arg1);

    void on_rech2_2_textChanged(const QString &arg1);

private:
    Ui::secretaire *ui;
    rdv tmprdv;
    patient tmppatient;
    QSound *son;


};

#endif // MAINWINDOW_H





