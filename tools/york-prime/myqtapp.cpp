#include <sstream>
#include <QtGui>
#include "myqtapp.h"

myQtApp::myQtApp(QWidget *parent) {
    setupUi(this); // this sets up GUI

    connect( pushButton_do, SIGNAL( clicked() ), this, SLOT( doSomething() ) );
    connect( pushButton_clear, SIGNAL( clicked() ), this, SLOT( clear() ) );
}

bool is_prime(long long n) {
    if (n % 2 == 0) {
        return n == 2;
    }
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

long long get_max_prime(long long n) {
    if (n < 2) {
        return -1;
    }
    while (1) {
        if (is_prime(n)) {
            return n;
        }
        n--;
    }
}

void myQtApp::doSomething() {
    long long n;
    std::stringstream ss(lineEdit->text().toStdString());
    if (ss >> n) {
        long long prime = get_max_prime(n);
        if (prime < 0) {
            QMessageBox::about(this, "...", "no solution for given number");
        } else {
            textEdit->append( QString::number(n) + " : " + QString::number(prime) );
        }

    } else {
        QMessageBox::about(this, "input is invalid", "check if it fits 64-bit integer");
    }
}

void myQtApp::clear() {
    textEdit->clear();
}
