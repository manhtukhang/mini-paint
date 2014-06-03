#ifndef EXTRAFILTERSPLUGIN_H
#define EXTRAFILTERSPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QStringList>
#include <QImage>

#include <interfaces.h>

class ExtraFiltersPlugin : public QObject, public FilterInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt.Mini-Paint.FilterInterface")
    Q_INTERFACES(FilterInterface)

public:
    QStringList filters() const;
    QImage filterImage(const QString &filter, const QImage &image,
                       QWidget *parent);
};

#endif
