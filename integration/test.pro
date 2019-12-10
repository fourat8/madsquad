QT       += core gui sql
QT       += network
QT      += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    amedicament.cpp \
    commande.cpp \
    commande1.cpp \
    compte.cpp \
    connexion.cpp \
    creer_compte.cpp \
    crud_materiel.cpp \
    login.cpp \
    main.cpp \
    materiel.cpp \
    medicament.cpp \
    modification.cpp \
    patient.cpp \
    rdv.cpp \
    secretaire.cpp

HEADERS += \
    admin.h \
    amedicament.h \
    commande.h \
    commande1.h \
    compte.h \
    connexion.h \
    creer_compte.h \
    crud_materiel.h \
    login.h \
    materiel.h \
    medicament.h \
    modification.h \
    patient.h \
    rdv.h \
    secretaire.h

FORMS += \
    admin.ui \
    amedicament.ui \
    commande.ui \
    creer_compte.ui \
    crud_materiel.ui \
    login.ui \
    modification.ui \
    secretaire.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

  //RC_ICONS = logo.ico
RC_ICONS = logo.ico

RESOURCES += \
    ressource.qrc

DISTFILES +=
