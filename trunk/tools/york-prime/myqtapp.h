#ifndef MYQTAPP_H
#define MYQTAPP_H

#include "ui_widget.h"

class myQtApp : public QWidget, private Ui::myQtAppDLG {
    Q_OBJECT

public:
    myQtApp(QWidget *parent = 0);

public slots:
    void doSomething();
    void clear();
};

#endif