/******************************************************************************
** Lớp giao diện cho các plugin
** Đây là lớp trừu tượng, dùng để kế thừa, tránh nhầm lẫn với giao diện
** tương tác (GUI, CLI, API)
** 
** Bao gồm các lớp sau:
**  - BrushInterface
**  - ShapeInterface
**  - FilterInterface
** Thể hiện của những lớp trên sẽ được cụ thể hóa ở các lớp kế thừa sau này
*/

#ifndef INTERFACES_H
#define INTERFACES_H

#include <QtPlugin>

QT_BEGIN_NAMESPACE
class QImage;
class QPainter;
class QWidget;
class QPainterPath;
class QPoint;
class QRect;
class QString;
class QStringList;
QT_END_NAMESPACE

class BrushInterface
{
public:
    virtual ~BrushInterface() {}

    virtual QStringList brushes() const = 0;
    virtual QRect mousePress(const QString &brush, QPainter &painter,
                             const QPoint &pos) = 0;
    virtual QRect mouseMove(const QString &brush, QPainter &painter,
                            const QPoint &oldPos, const QPoint &newPos) = 0;
    virtual QRect mouseRelease(const QString &brush, QPainter &painter,
                               const QPoint &pos) = 0;
};

class ShapeInterface
{
public:
    virtual ~ShapeInterface() {}

    virtual QStringList shapes() const = 0;
    virtual QPainterPath generateShape(const QString &shape,
                                       QWidget *parent) = 0;
};

class FilterInterface
{
public:
    virtual ~FilterInterface() {}

    virtual QStringList filters() const = 0;
    virtual QImage filterImage(const QString &filter, const QImage &image,
                               QWidget *parent) = 0;
};


/*
Phần này hết sức quan trọng
Là tên để nhận diện các plugin trong chương trình chính khi nạp các plugin
*/
QT_BEGIN_NAMESPACE

#define BrushInterface_iid "org.qt.Mini-Paint.BrushInterface"
Q_DECLARE_INTERFACE(BrushInterface, BrushInterface_iid)
#define ShapeInterface_iid  "org.qt.Mini-Paint.ShapeInterface"
Q_DECLARE_INTERFACE(ShapeInterface, ShapeInterface_iid)
#define FilterInterface_iid "org.qt.Mini-Paint.FilterInterface"
Q_DECLARE_INTERFACE(FilterInterface, FilterInterface_iid)

QT_END_NAMESPACE

#endif
