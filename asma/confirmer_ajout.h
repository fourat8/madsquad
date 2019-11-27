#ifndef CONFIRMER_AJOUT_H
#define CONFIRMER_AJOUT_H

#include <QDialog>

namespace Ui {
class Confirmer_ajout;
}

class Confirmer_ajout : public QDialog
{
    Q_OBJECT

public:
    explicit Confirmer_ajout(QWidget *parent = nullptr);
    ~Confirmer_ajout();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Confirmer_ajout *ui;
};

#endif // CONFIRMER_AJOUT_H
