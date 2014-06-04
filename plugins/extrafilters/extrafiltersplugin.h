/******************************************************************************
 * Mini Paint                                                                 *
 * Copyleft (Ɔ) 2014 - Mini Paint                                             *
 * https://github.com/manhtuvjp/mini-paint                                    *
 *                                                                            *
 ******************************************************************************
 * Cung cấp các bộ lọc ảnh đơn giản như:                                      *
 *  - Lật dọc ảnh                                                             *
 *  - Lật ngang ảnh                                                           *
 *  - Làm mờ ảnh                                                              *
 *  - Chuyển thành ảnh đa mức xám                                             *
 *  - Chuyển thành ảnh nhị phân                                               *
 *  - Chuyển thành ảnh âm bản                                                 *
 *  - Đảo kênh màu từ RGB thành BGR                                           *
 *  - Thay đổi độ sáng của ảnh                                                *
 *  - Thay đổi độ bão hòa của ảnh                                             *
 *  - Làm ấm màu sắc ảnh                                                      *
 *  - Làm mát màu sắc ảnh                                                     *
 ******************************************************************************/


#ifndef EXTRAFILTERSPLUGIN_H
#define EXTRAFILTERSPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QStringList>
#include <QImage>

#include <interfaces.h>

class ExtraFiltersPlugin : public QObject, public FilterInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt.Mini-Paint.FilterInterface")
    Q_INTERFACES(FilterInterface)

public:
    QStringList filters() const;
    QImage filterImage(const QString &filter, const QImage &image,
                       QWidget *parent);
};

#endif
