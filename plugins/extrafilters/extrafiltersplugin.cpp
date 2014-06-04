#include <QtWidgets>

#include <math.h>
#include <stdlib.h>

#include "extrafiltersplugin.h"

QStringList ExtraFiltersPlugin::filters() const {
    return QStringList() << tr("Lật dọc")
           << tr("Lật ngang")
           << tr("Làm mờ")
           << tr("Chia ngưỡng")
           << tr("Ảnh nhị phân")
           << tr("Đảo ngược pixel")
           << tr("Đảo màu (RGB->BGR)")
           << tr("Đa mức xám")
           << tr("Độ sáng")
           << tr("Làm ấm")
           << tr("Làm mát")
           << tr("Bão hòa");
}


QImage ExtraFiltersPlugin::filterImage(const QString &filter,
                                       const QImage &image, QWidget *parent) {
    QImage original = image.convertToFormat(QImage::Format_RGB32);
    QImage result = original;

    if (filter == tr("Lật dọc")) {
        for (int y = 0; y < original.height(); ++y) {
            for (int x = 0; x < original.width(); ++x) {
                int pixel = original.pixel(original.width() - x - 1, y);
                result.setPixel(x, y, pixel);
            }
        }
    } else if (filter == tr("Lật ngang")) {
        for (int y = 0; y < original.height(); ++y) {
            for (int x = 0; x < original.width(); ++x) {
                int pixel = original.pixel(x, original.height() - y - 1);
                result.setPixel(x, y, pixel);
            }
        }
    } else if (filter == tr("Làm mờ")) {
        bool ok;
        int numIters = QInputDialog::getInt(parent, tr("Làm mờ ảnh"),
                                            tr("Nhập giá trị:"),
                                            5, 1, 20, 1, &ok);
        if (ok) {
            for (int i = 0; i < numIters; ++i) {
                for (int y = 1; y < original.height() - 1; ++y) {
                    for (int x = 1; x < original.width() - 1; ++x) {
                        int p1 = original.pixel(x, y);
                        int p2 = original.pixel(x, y + 1);
                        int p3 = original.pixel(x, y - 1);
                        int p4 = original.pixel(x + 1, y);
                        int p5 = original.pixel(x - 1, y);

                        int red = (qRed(p1) + qRed(p2) + qRed(p3) + qRed(p4)
                                   + qRed(p5)) / 5;
                        int green = (qGreen(p1) + qGreen(p2) + qGreen(p3)
                                     + qGreen(p4) + qGreen(p5)) / 5;
                        int blue = (qBlue(p1) + qBlue(p2) + qBlue(p3)
                                    + qBlue(p4) + qBlue(p5)) / 5;
                        int alpha = (qAlpha(p1) + qAlpha(p2) + qAlpha(p3)
                                     + qAlpha(p4) + qAlpha(p5)) / 5;

                        result.setPixel(x, y, qRgba(red, green, blue, alpha));
                    }
                }
            }
        }
    } else if (filter == tr("Chia ngưỡng")) {
        bool ok;
        int threshold = QInputDialog::getInt(parent, tr("Chia ngưỡng"),
                                             tr("Nhập ngưỡng:"),
                                             10, 1, 256, 1, &ok);
        if (ok) {
            int factor = 256 / threshold;
            for (int y = 0; y < original.height(); ++y) {
                for (int x = 0; x < original.width(); ++x) {
                    int pixel = original.pixel(x, y);
                    result.setPixel(x, y, qRgba(qRed(pixel) / factor * factor,
                                                qGreen(pixel) / factor * factor,
                                                qBlue(pixel) / factor * factor,
                                                qAlpha(pixel)));
                }
            }
        }
    } else if (filter == tr("Ảnh nhị phân")) {
        {
            for (int y = 0; y < original.height(); ++y) {
                for (int x = 0; x < original.width(); ++x) {
                    int pixel = original.pixel(x, y);
                    int r = static_cast<int>(qRed(pixel));
                    if (r >= 200) {
                        r = 0;
                    } else if (r >= 100 && r < 200) {
                        r = 255;
                    } else {
                        r = 0;
                    }
                    pixel = qRgb(r, r, r);
                    result.setPixel(x, y, pixel);
                }
            }
        }
    } else if (filter == tr("Đảo ngược pixel")) {
        result.invertPixels();
    } else if (filter == tr("Đảo màu (RGB->BGR)")) {
        result = result.rgbSwapped();
    } else if (filter == tr("Đa mức xám")) {
        for (int y = 0; y < result.height(); ++y) {
            for (int x = 0; x < result.width(); ++x) {
                int pixel = result.pixel(x, y);
                int gray = qGray(pixel);
                int alpha = qAlpha(pixel);
                result.setPixel(x, y, qRgba(gray, gray, gray, alpha));
            }
        }
    } else if(filter == tr("Độ sáng")) {
        bool ok;
        int brighness = QInputDialog::getInt(parent, tr("Độ sáng"),
                                                 tr("Nhập độ sáng:"),
                                                 10, 1, 256, 1, &ok);
        if(ok) {
            for(int y = 0; y < original.height(); ++y) {
                for(int x = 0; x < original.width(); ++x) {
                    int pixel = original.pixel(x, y);
                    result.setPixel(x, y, qRgba(qRed(pixel) + brighness,
                                                qGreen(pixel) + brighness,
                                                qBlue(pixel) + brighness,
                                                qAlpha(pixel)));
                }
            }
        }
    } else if(filter == tr("Làm ấm")) {
        bool ok;
        int delta = QInputDialog::getInt(parent, tr("Lầm ấm"),
                                                 tr("Nhập mức độ ấm:"),
                                                 10, 1, 256, 1, &ok);
        if(ok) {
            for(int y = 0; y < original.height(); ++y) {
                for(int x = 0; x < original.width(); ++x) {
                    int pixel = original.pixel(x, y);
                    result.setPixel(x, y, qRgba(qRed(pixel) + delta,
                                                qGreen(pixel) + delta,
                                                qBlue(pixel),
                                                qAlpha(pixel)));
                }
            }
        }
    } else if(filter == tr("Làm mát")) {
        bool ok;
        int delta = QInputDialog::getInt(parent, tr("Lầm mát"),
                                                 tr("Nhập mức độ mát:"),
                                                 10, 1, 256, 1, &ok);
        if(ok) {
            for(int y = 0; y < original.height(); ++y) {
                for(int x = 0; x < original.width(); ++x) {
                    int pixel = original.pixel(x, y);
                    result.setPixel(x, y, qRgba(qRed(pixel),
                                                qGreen(pixel),
                                                qBlue(pixel) + delta,
                                                qAlpha(pixel)));
                }
            }
        }
    } else if(filter == tr("Bão hòa")) {
        bool ok;
        int delta = QInputDialog::getInt(parent, tr("Bão hòa"),
                                                 tr("Nhập độ bão hòa:"),
                                                 10, 1, 256, 1, &ok);
        QColor newClolor;
        QColor oldColor;
        int h, s, l;
        if(ok) {
            for(int y = 0; y < original.height(); ++y) {
                for(int x = 0; x < original.width(); ++x) {

                    oldColor = QColor(original.pixel(x, y));
                    newClolor = oldColor.toHsl();

                    h = newClolor.hue();
                    s = newClolor.saturation() + delta;
                    l = newClolor.lightness();

                    newClolor.setHsl(h, s, l);

                    result.setPixel(x, y, qRgba(newClolor.red(),
                                                newClolor.green(),
                                                newClolor.blue(),
                                                newClolor.alpha()));
                }
            }
        }
    }
    return result;
}
