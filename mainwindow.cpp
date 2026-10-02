#include "mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>

MyWindow::MyWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Моё Главное Окно");

    centralWidget = new QWidget(this);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    textEdit = new QTextEdit(centralWidget);
    layout->addWidget(textEdit);

    setCentralWidget(centralWidget);
}
