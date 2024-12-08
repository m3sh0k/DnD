#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QWheelEvent>
#include <QMouseEvent>

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapWidget(QWidget *parent = nullptr);
    ~MapWidget();

    void setImage(const QImage &image);

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QImage mapImage;  // Изображение карты
    double scaleFactor;  // Масштаб
    QPoint lastMousePos;  // Последняя позиция мыши
    bool isDragging;  // Флаг, указывающий на то, что карта перетаскивается
    QPoint offset;  // Смещение карты

    void drawGrid(QPainter &painter);  // Рисуем сетку
    void updateScale(double scale);  // Обновление масштаба
    void zoomIn();  // Увеличение масштаба
    void zoomOut();  // Уменьшение масштаба
};

#endif // MAPWIDGET_H
