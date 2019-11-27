 #include "amedicament.h"
#include "ui_amedicament.h"
#include "medicament.h"
#include "QMessageBox"
#include "QDebug"
#include "QSqlError"
Amedicament::Amedicament(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Amedicament)
{
    ui->setupUi(this);
     ui->tablemedicament->setModel(tmpmedicament.afficher());
}

Amedicament::~Amedicament()
{
    delete ui;
}

void Amedicament::on_pushButton_ok_clicked()
{
    player->setMedia(QUrl::fromLocalFile("C:/Users/asus/Documents/medicaments/medicament/click.mp3"));
    player->play();
    qDebug()<<player->errorString();
    QThread::sleep(1);
    int ref = ui->lineEdit_ref->text().toInt();
    QString nomProduit= ui->lineEdit_nomP->text();
    int nbrMed= ui->lineEdit_nb->text().toInt();
    if(nbrMed<=20){
        QMessageBox::critical(nullptr, QObject::tr("ALERT!!"),
                                         QObject::tr("veuillez recharger le stocke de ce médicament à nouveau.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);
    }
    medicament m (ref,nomProduit,nbrMed);
    bool test=m.ajouter();
    if(test)
    {
        ui->tablemedicament->setModel(tmpmedicament.afficher());
    QMessageBox::information(nullptr, QObject::tr("Ajouter un médicament"),
                  QObject::tr("médicament ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
            ui->lineEdit_ref->clear();
            ui->lineEdit_nomP->clear();
            ui->lineEdit_nb->clear();

    }
    else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un médicament"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void Amedicament::on_pushButton_modifier_clicked()
{
    player->setMedia(QUrl::fromLocalFile("C:/Users/asus/Documents/medicaments/medicament/click.mp3"));
    player->play();
    qDebug()<<player->errorString();
    QThread::sleep(1);

    int ref = ui->lineEdit_ref_2->text().toInt();
    QString nomProduit= ui->lineEdit_nomP_2->text();
    int nbrMed= ui->lineEdit_nb_2->text().toInt();
    if(nbrMed<=20){
        QMessageBox::critical(nullptr, QObject::tr("ALERT!!"),
                                         QObject::tr("veuillez recharger le stocke de ce médicament à nouveau!.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);
    }
    medicament m (ref,nomProduit,nbrMed);
    bool test=m.modifier(ref,nomProduit,nbrMed);
    if(test)
    { ui->tablemedicament->setModel(tmpmedicament.afficher());

            QMessageBox::information(nullptr, QObject::tr("Modifier un médicament"),
                  QObject::tr("médicament modifié.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
            ui->lineEdit_ref_2->clear();
            ui->lineEdit_nomP_2->clear();
            ui->lineEdit_nb_2->clear();
    }
    else
      QMessageBox::critical(nullptr, QObject::tr("Modifier un étudiant"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}



void Amedicament::on_pushButton_supp_clicked()
{
    player->setMedia(QUrl::fromLocalFile("C:/Users/asus/Documents/medicaments/medicament/click.mp3"));
    player->play();
    qDebug()<<player->errorString();
    QThread::sleep(1);

    medicament m;
        int ref = ui->lineEdit_ref_3->text().toInt();
        bool test=m.supprimer(ref);
        if(test)
        { ui->tablemedicament->setModel(tmpmedicament.afficher());
            QMessageBox::information(nullptr, QObject::tr("Supprimer un médicament"),
                        QObject::tr("Médicament supprimé.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
               ui->lineEdit_ref_3->clear();
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer un médicament"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
     QSqlQueryModel *   model=m.afficher();
}

void Amedicament::on_pushButton_chercherP_clicked()
{
    player->setMedia(QUrl::fromLocalFile("C:/Users/asus/Documents/medicaments/medicament/click.mp3"));
    player->play();
    qDebug()<<player->errorString();
    QThread::sleep(1);

    QString nomProduit= ui->lineEdit_nomP_2->text();
     qDebug()<< nomProduit << endl;
            QSqlQuery query;
            query.first();
            query.prepare("SELECT * from TABMED where NOMPRODUIT= '"+nomProduit+"'");
            if(query.exec())

            {
                while(query.next())
                {

                    ui->lineEdit_ref_2->setText(query.value(0).toString());//Ref
                    ui->lineEdit_nomP_2->setText(query.value(1).toString());//nomProduit
                    ui->lineEdit_nb_2->setText(query.value(2).toString());//nbrmed


                }
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Chercher médicament!"),
                                      QObject::tr("Erreur!.\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);
            }
}

void Amedicament::on_pushButton_rechercher_clicked()
{
    player->setMedia(QUrl::fromLocalFile("C:/Users/asus/Documents/medicaments/medicament/click.mp3"));
    player->play();
    qDebug()<<player->errorString();
    QThread::sleep(1);

    QSqlQuery query;
         QString nomProduit= ui->lineEdit_nomP_3->text();
        nomProduit=nomProduit+"%";
        qDebug()<<nomProduit;
        query.prepare("SELECT * from TABMED where(NOMPRODUIT LIKE :nomProduit)");
        query.bindValue(":nomProduit",nomProduit);
        if(!query.exec())
        {
            qDebug()<<query.lastError();
        }
        QSqlQueryModel * modal= new QSqlQueryModel();
        modal->setQuery(query);
        qDebug()<<modal->rowCount();
        ui->tablemedicament_2->setModel(modal);
}



void Amedicament::on_pushButton_tri_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        QSqlQuery qry;
        qry.prepare("select * from TABMED");
        qry.exec();
        model->setQuery(qry);

        QSortFilterProxyModel *m=new QSortFilterProxyModel(this);
        m->setDynamicSortFilter(true);
        m->setSourceModel(model);
        ui->tablemedicament->setModel(m);
        ui->tablemedicament->setSortingEnabled(true);
}
