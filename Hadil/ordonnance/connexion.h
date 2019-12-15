#ifndef CONNEXION_H
#define CONNEXION_H
#include<QSqlQuery>
#include<QSqlError>
#include<QSqlDatabase>
#include <QDialog>
#include <QSqlError>

namespace Ui {
class connexion;
}

class connexion : public QDialog
{
    Q_OBJECT

public:
    explicit connexion(QWidget *parent = nullptr);
    ~connexion();

private:
    Ui::connexion *ui;
};
class connection
{
 public:
    connection();
    bool creatconnect();
};


#endif // CONNEXION_H
