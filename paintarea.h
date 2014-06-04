/******************************************************************************
 * Mini Paint                                                                 *
 * Copyleft (Ɔ) 2014 - Mini Paint                                             *
 * https://github.com/manhtuvjp/mini-paint                                    *
 ******************************************************************************
 * Vùng làm việc chính, bao gồm các hoạt động sau:                            *
 *  - Khởi tạo các thông số mặc định                                          *
 *  - Mở hình ảnh từ tệp                                                      *
 *  - Lưu hình ảnh ra tệp                                                     *
 *  - Chèn các hình cơ bản do người dùng chọn                                 *
 *  - Bắt các sự kiện chuột như: nhấn, di chuyển                              *
 ******************************************************************************/


#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QColor>
#include <QImage>
#include <QPainterPath>
#include <QWidget>

class BrushInterface;

class PaintArea : public QWidget {
    Q_OBJECT

public:
    PaintArea(QWidget *parent = 0);

    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setImage(const QImage &image);
    void insertShape(const QPainterPath &path);
    void setBrushColor(const QColor &color);
    void setBrushWidth(int width);
    void setBrush(BrushInterface *brushInterface, const QString &brush);

    QImage image() const {
        return theImage;
    }
    QColor brushColor() const {
        return color;
    }
    int brushWidth() const {
        return thickness;
    }
    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void setupPainter(QPainter &painter);

    QImage theImage;
    QColor color;
    int thickness;

    BrushInterface *brushInterface;
    QString brush;
    QPoint lastPos;

    QPainterPath pendingPath;
};

#endif
