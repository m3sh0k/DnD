#include "mapwidget.h"
#include <QPainter>
#include <QWheelEvent>
#include <QMouseEvent>

MapWidget::MapWidget(QWidget *parent)
    : QWidget(parent),
    scaleFactor(1.0),  // Начальный масштаб
    isDragging(false),  // Карта не перетаскивается по умолчанию
    offset(0, 0)  // Начальное смещение
{
    setMouseTracking(true);
}

MapWidget::~MapWidget()
{
}

void MapWidget::setImage(const QImage &image)
{
    mapImage = image;
    update();  // Перерисовываем виджет
}

void MapWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Масштабируем картинку
    painter.scale(scaleFactor, scaleFactor);

    // Применяем смещение, чтобы перемещать карту
    painter.translate(offset);

    // Рисуем карту
    painter.drawImage(0, 0, mapImage);

    // Рисуем сетку
    drawGrid(painter);
}

void MapWidget::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0)
        zoomIn();
    else
        zoomOut();
}

void MapWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging) {
        // Вычисляем разницу в положении мыши и обновляем смещение карты
        QPoint delta = event->pos() - lastMousePos;
        offset += delta;
        update();  // Перерисовываем виджет, чтобы отобразить перемещённую карту
    }
    lastMousePos = event->pos();
}

void MapWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        lastMousePos = event->pos();
    }
}

void MapWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
    }
}

void MapWidget::drawGrid(QPainter &painter)
{
    int gridSize = 50;  // Размер ячейки сетки
    painter.setPen(QPen(Qt::black, 1, Qt::DotLine));

    // Рисуем вертикальные линии
    for (int x = 0; x < mapImage.width(); x += gridSize) {
        painter.drawLine(x, 0, x, mapImage.height());
    }

    // Рисуем горизонтальные линии
    for (int y = 0; y < mapImage.height(); y += gridSize) {
        painter.drawLine(0, y, mapImage.width(), y);
    }
}

void MapWidget::updateScale(double scale)
{
    scaleFactor = scale;
    update();
}

void MapWidget::zoomIn()
{
    updateScale(scaleFactor * 1.1);
}

void MapWidget::zoomOut()
{
    updateScale(scaleFactor / 1.1);
}
