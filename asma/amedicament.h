#ifndef AMEDICAMENT_H
#define AMEDICAMENT_H
#include "medicament.h"
#include <QDialog>
#include <QMediaPlayer>
#include <QThread>
#include <QSortFilterProxyModel>

namespace Ui {
class Amedicament;
}

class Amedicament : public QDialog
{
    Q_OBJECT

public:
    explicit Amedicament(QWidget *parent = nullptr);
    ~Amedicament();
     QMediaPlayer* player= new QMediaPlayer;
private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_supp_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_rechercher_clicked();
    void on_pushButton_chercherP_clicked();

    void on_pushButton_tri_clicked();



private:
    Ui::Amedicament *ui;
    medicament tmpmedicament;

};

#endif // AMEDICAMENT_H
