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
                         public ShapeInterface
{
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

#endif
