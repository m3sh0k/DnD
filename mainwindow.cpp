#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    mapWidget(new MapWidget(this)) // Создаем виджет карты
{
    setCentralWidget(mapWidget);  // Устанавливаем карту как центральный виджет
    setWindowTitle("DnD Map Assistant");
}

MainWindow::~MainWindow()
{
}
