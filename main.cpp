#include "mainwindow.h"
#include <QApplication>
#include <QImage>
#include <QFileDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    // Загружаем карту с диска с помощью диалога выбора файла
    QString fileName = QFileDialog::getOpenFileName(&w, "Select Map Image", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (!fileName.isEmpty()) {
        QImage mapImage(fileName);
        if (!mapImage.isNull()) {
            w.findChild<MapWidget *>()->setImage(mapImage);  // Устанавливаем картинку на карту
        } else {
            // Если изображение не загрузилось
            qWarning("Failed to load the map image.");
        }
    }

    return a.exec();
}
