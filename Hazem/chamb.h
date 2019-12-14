#ifndef CHAMB_H
#define CHAMB_H
#include "chambre.h"
#include <QDialog>
#include <QMediaPlayer>
#include <QThread>
#include <QSortFilterProxyModel>

namespace Ui {
class Chamb;
}

class Chamb : public QDialog
{
    Q_OBJECT

public:
    explicit Chamb(QWidget *parent = nullptr);
    ~Chamb();
    private slots:

    void on_pb_ajouter_clicked();
    void on_pb_supprimer_clicked();
    void on_pb_modifier_clicked();

    void on_pb_chercher_clicked();

    void on_pb_imprimer_clicked();

    void on_pb_chercherNum_clicked();

private:
    Ui::Chamb *ui;
    chambre tmp;
};

#endif // CHAMB_H
