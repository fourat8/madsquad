#ifndef ORDONANCE_H
#define ORDONANCE_H
#include "ordo.h"
#include <QDialog>
#include <QSound>

namespace Ui {
class ordonance;
}

class ordonance : public QDialog
{
    Q_OBJECT

public:
    explicit ordonance(QWidget *parent = nullptr);
    ~ordonance();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_pdf_clicked();

    void on_pb_deconnexion_clicked();


    void on_pb_chercher_clicked();

private:
    Ui::ordonance *ui;
    ordo tmpordo;
    QSound *son;
};

#endif // ORDONANCE_H
