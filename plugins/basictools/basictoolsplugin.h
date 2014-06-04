/******************************************************************************
 * Mini Paint                                                                 *
 * Copyleft (Ɔ) 2014 - Mini Paint                                             *
 * https://github.com/manhtuvjp/mini-paint                                    *
 *                                                                            *
 ******************************************************************************
 * Cung cấp các công cụ đơn giản như:                                         *
 *  - Bút vẽ                                                                  *
 *  - Công cụ phun màu dạng sương mụ                                          *
 *  - Chèn vào 1 chữ cái ngẫu nhiên trong bảng chữ cái Alphabet               *
 *  - Các hình cơ bản như: hình tròn, ngôi sao, văn bản                       *
 ******************************************************************************/

#ifndef BASICTOOLSPLUGIN_H
#define BASICTOOLSPLUGIN_H

#include <QRect>
#include <QObject>
#include <QtPlugin>
#include <QStringList>
#include <QPainterPath>
#include <QImage>

#include <interfaces.h>

class BasicToolsPlugin : public QObject,
    public BrushInterface,
    public ShapeInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt.Mini-Paint.BrushInterface")
    Q_INTERFACES(BrushInterface ShapeInterface)

public:
    // BrushInterface
    QStringList brushes() const;
    QRect mousePress(const QString &brush, QPainter &painter,
                     const QPoint &pos);
    QRect mouseMove(const QString &brush, QPainter &painter,
                    const QPoint &oldPos, const QPoint &newPos);
    QRect mouseRelease(const QString &brush, QPainter &painter,
                       const QPoint &pos);

    // ShapeInterface
    QStringList shapes() const;
    QPainterPath generateShape(const QString &shape, QWidget *parent);

};

#endif  // BASICTOOLSPLUGIN_H
