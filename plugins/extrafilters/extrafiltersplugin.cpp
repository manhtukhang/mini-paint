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


#include <QtWidgets>

#include <math.h>
#include <stdlib.h>

#include "extrafiltersplugin.h"


/*** FilterInterface ***/

// Hàm trả về danh sách các bộ lọc có trong plugin
QStringList ExtraFiltersPlugin::filters() const
{
    return QStringList() << tr("Lật dọc")
           << tr("Lật ngang")
           << tr("Làm mờ")
           << tr("Đa mức xám")
           << tr("Ảnh nhị phân")
           << tr("Ảnh âm bản")
           << tr("Đảo màu (RGB->BGR)")
           << tr("Độ sáng")
           << tr("Độ bão hòa")
           << tr("Làm ấm")
           << tr("Làm mát...");
}


// Hàm dùng lọc ảnh bằng các filter tương ứng
QImage ExtraFiltersPlugin::filterImage(const QString &filter,
                                       const QImage &image, QWidget *parent)
{
    // Chuyển đổi định dạng ảnh sang RGB 32-bit để các hàm làm việc như mong
    // đợi
    QImage original = image.convertToFormat(QImage::Format_RGB32);
    QImage result = original;

    if (filter == tr("Lật ngang")) {
        // Nếu filter là "Lật ngang" thì hoán đổi các pixel của ảnh theo chiều
        // ngang của ảnh
        for (int y = 0; y < original.height(); ++y) {
            for (int x = 0; x < original.width(); ++x) {
                int pixel = original.pixel(original.width() - x - 1, y);
                result.setPixel(x, y, pixel);
            }
        }
    } else if (filter == tr("Lật dọc")) {
        // Nếu filter là "Lật dọc" thì hoán đổi các pixel của ảnh theo chiều
        // dọc của ảnh
        for (int y = 0; y < original.height(); ++y) {
            for (int x = 0; x < original.width(); ++x) {
                int pixel = original.pixel(x, original.height() - y - 1);
                result.setPixel(x, y, pixel);
            }
        }
    } else if (filter == tr("Làm mờ")) {
        // Nếu filter là "Làm mờ" thì bật QInputDialog lên cho người dùng nhập
        // vào giá trị làm mờ, giá trị này trong khoảng 1 đến 20
        bool ok;  // Kiểm tra giá trị nhập
        int numIters = QInputDialog::getInt(parent, tr("Làm mờ ảnh"),
                                            tr("Nhập giá trị:"),
                                            5, 1, 20, 1, &ok);
        // Thực hiện làm mờ bằng cách set các giá trị của pixel bằng giá trị
        // trung bình của nó với 4 pixel xung quanh.
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
    } else if (filter == tr("Ảnh nhị phân")) {
        // Nếu filter là "Ảnh nhị phân" thì bật QInputDialog lên cho người dùng
        // nhập vào giá trị ngưỡng, nằm trong khoảng 0 đến 255
        bool ok; // Kiểm tra giá trị nhập
        int threshold = QInputDialog::getInt(parent, tr("Chia ngưỡng"),
                                             tr("Nhập ngưỡng:"),
                                             85, 0, 255, 1, &ok);
        // Đầu tiên ta chuyển ảnh về ảnh đa mức xám rồi so sánh từng pixel của
        // ảnh với giá trị ngưỡng.
        if (ok) {
            for (int y = 0; y < original.height(); ++y) {
                for (int x = 0; x < original.width(); ++x) {
                    int pixel = original.pixel(x, y);
                    int gray = qGray(pixel);
                    gray = gray > threshold ? 255 : 0;
                    pixel = qRgb(gray, gray, gray);
                    result.setPixel(x, y, pixel);
                }
            }
        }
    } else if (filter == tr("Ảnh âm bản")) {
        // Dùng hàm invertPixels() để đảo ngược các pixel.
        result.invertPixels();
    } else if (filter == tr("Đảo màu (RGB->BGR)")) {
        // Dùng hàm rgbSwapped() để chuyển kênh màu của ảnh từ RGB sang BGR
        result = result.rgbSwapped();
    } else if (filter == tr("Đa mức xám")) {
        //
        for (int y = 0; y < result.height(); ++y) {
            for (int x = 0; x < result.width(); ++x) {
                int pixel = result.pixel(x, y);
                int gray = qGray(pixel);
                int alpha = qAlpha(pixel);
                result.setPixel(x, y, qRgba(gray, gray, gray, alpha));
            }
        }
    } else if (filter == tr("Độ sáng")) {
        // Nếu filter là "Độ sáng" thì bật QInputDialog lên cho người dùng
        // nhập vào giá trị ngưỡng, giá trị này trong khoảng -255 đến 255
        bool ok;  // Kiểm tra giá trị nhập
        int brighness = QInputDialog::getInt(parent, tr("Độ sáng"),
                                             tr("Nhập độ sáng:"),
                                             10, -255, 255, 1, &ok);
        // Ta tăng hoặc giảm giá trị các màu của từng pixel
        if (ok) {
            int r, g, b;

            for (int x = 0; x < original.width(); x++) {
                for (int y = 0; y < original.height(); y++) {

                    int pixel = original.pixel(x, y);

                    r = qRed(pixel) + brighness;
                    g = qGreen(pixel) + brighness;
                    b = qBlue(pixel) + brighness;

                    //Ta kiểm tra các giá trị mới trong khoảng cho phép.
                    r = qBound(0, r, 255);
                    g = qBound(0, g, 255);
                    b = qBound(0, b, 255);

                    result.setPixel(x, y, qRgba(r, g, b, qAlpha(pixel)));
                }
            }
        }
    } else if (filter == tr("Làm ấm")) {
        // Nếu filter là "Làm ấm" thì bật QInputDialog lên cho người dùng
        // nhập vào giá trị, giá trị này trong khoảng 1 đến 255
        bool ok;  // Kiểm tra giá trị nhập
        int delta = QInputDialog::getInt(parent, tr("Lầm ấm"),
                                         tr("Nhập mức độ ấm:"),
                                         10, 1, 255, 1, &ok);
        // Hình sẽ trong ấm hơn nếu ta tăng độ vàng của ảnh, và màu vàng được
        // tổng hợp từ màu đỏ và xanh lục trong kênh màu RGB
        if (ok) {
            int r, g, b;

            for (int x = 0; x < original.width(); x++) {
                for (int y = 0; y < original.height(); y++) {

                    int pixel = original.pixel(x, y);

                    r = qRed(pixel) + delta;
                    g = qGreen(pixel) + delta;
                    b = qBlue(pixel);

                    //Ta kiểm tra các giá trị mới trong khoảng cho phép.
                    r = qBound(0, r, 255);
                    g = qBound(0, g, 255);

                    result.setPixel(x, y, qRgba(r, g, b, qAlpha(pixel)));
                }
            }
        }
    } else if (filter == tr("Làm mát...")) {
        // Nếu filter là "Làm mát" thì bật QInputDialog lên cho người dùng
        // nhập vào giá trị, giá trị này trong khoảng 1 đến 255
        bool ok;  // Kiểm tra giá trị nhập
        int delta = QInputDialog::getInt(parent, tr("Lầm mát"),
                                         tr("Nhập mức độ mát:"),
                                         10, 1, 256, 1, &ok);
        // Hình sẽ có cảm giác mát hơn khi ta tăng giá trị kênh màu xanh lam
        if (ok) {
            int r, g, b;

            for (int x = 0; x < original.width(); x++) {
                for (int y = 0; y < original.height(); y++) {

                    int pixel = original.pixel(x, y);

                    r = qRed(pixel);
                    g = qGreen(pixel);
                    b = qBlue(pixel) + delta;

                    //Ta kiểm tra giá trị mới trong khoảng cho phép.
                    b = qBound(0, b, 255);

                    result.setPixel(x, y, qRgba(r, g, b, qAlpha(pixel)));
                }
            }
        }
    } else if (filter == tr("Độ bão hòa")) {
        // Nếu filter là "Độ bão hòa" thì bật QInputDialog lên cho người dùng
        // nhập vào giá trị, giá trị này trong khoảng -255 đến 255
        bool ok; // Kiểm tra giá trị nhập vào
        int delta = QInputDialog::getInt(parent, tr("Độ bão hòa"),
                                         tr("Nhập độ bão hòa:"),
                                         10, -255, 255, 1, &ok);
        QColor newClolor;
        QColor oldColor;
        int h, s, l;

        // Ta chuyển hình về kênh màu HSL rồi sau đó tăng hoặc giảm kênh
        // saturation để tăng hoặc giảm độ bão hòa sau đó lại chuyển ảnh về RGB
        if (ok) {
            for (int y = 0; y < original.height(); ++y) {
                for (int x = 0; x < original.width(); ++x) {

                    oldColor = QColor(original.pixel(x, y));
                    newClolor = oldColor.toHsl();

                    h = newClolor.hue();
                    s = newClolor.saturation() + delta;
                    l = newClolor.lightness();

                    // Ta kiểm tra giá trị mới trong khoảng cho phép
                    s = qBound(0, s, 255);

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
