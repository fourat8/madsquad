#include "confirmer_ajout.h"
#include "ui_confirmer_ajout.h"

Confirmer_ajout::Confirmer_ajout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Confirmer_ajout)
{
    ui->setupUi(this);
}

Confirmer_ajout::~Confirmer_ajout()
{
    delete ui;
}

void Confirmer_ajout::on_pushButton_2_clicked()
{
    hide();
}

void Confirmer_ajout::on_pushButton_clicked()
{
    int id = ui->lineEdit_ref->text().toInt();
    QString nom= ui->lineEdit_nom->text();
    QString prenom= ui->lineEdit_prenom->text();
    Etudiant e(id,nom,prenom);
    bool test=e.ajouter();
    if(test)
    {ui->tabetudiant->setModel(tmpetudiant.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Ajouter un étudiant"),
                  QObject::tr("Etudiant ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un étudiant"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
