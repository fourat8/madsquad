#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlDatabase>


class connexion
{

public:
    QSqlDatabase db;
    connexion();
    bool ouvrirconnexion();
    void fermerconnexion();
};

#endif // CONNEXION_H


