#include <QtWidgets>

#include <math.h>
#include <stdlib.h>

#include "basictoolsplugin.h"

const float Pi = 3.14159f;


QStringList BasicToolsPlugin::brushes() const
{
    return QStringList() << tr("Bút chì") << tr("Phun sương")
                         << tr("Chữ ngẫu nhiên");
}


QRect BasicToolsPlugin::mousePress(const QString &brush, QPainter &painter,
                                   const QPoint &pos)
{
    return mouseMove(brush, painter, pos, pos);
}


QRect BasicToolsPlugin::mouseMove(const QString &brush, QPainter &painter,
                                  const QPoint &oldPos, const QPoint &newPos)
{
    painter.save();

    int rad = painter.pen().width() / 2;
    QRect boundingRect = QRect(oldPos, newPos).normalized()
                                              .adjusted(-rad, -rad, +rad, +rad);
    QColor color = painter.pen().color();
    int thickness = painter.pen().width();
    QColor transparentColor(color.red(), color.green(), color.blue(), 0);

    if (brush == tr("Bút chì")) {
        painter.drawLine(oldPos, newPos);
    } else if (brush == tr("Phun sương")) {
        int numSteps = 2 + (newPos - oldPos).manhattanLength() / 2;

        painter.setBrush(QBrush(color, Qt::Dense6Pattern));
        painter.setPen(Qt::NoPen);

        for (int i = 0; i < numSteps; ++i) {
            int x = oldPos.x() + i * (newPos.x() - oldPos.x()) / (numSteps - 1);
            int y = oldPos.y() + i * (newPos.y() - oldPos.y()) / (numSteps - 1);

            painter.drawEllipse(x - (thickness / 2), y - (thickness / 2),
                                thickness, thickness);
        }
    } else if (brush == tr("Chữ ngẫu nhiên")) {
        QChar ch('A' + (qrand() % 26));

        QFont biggerFont = painter.font();
        biggerFont.setBold(true);
        biggerFont.setPointSize(biggerFont.pointSize() + thickness);
        painter.setFont(biggerFont);

        painter.drawText(newPos, QString(ch));

        QFontMetrics metrics(painter.font());
        boundingRect = metrics.boundingRect(ch);
        boundingRect.translate(newPos);
        boundingRect.adjust(-10, -10, +10, +10);
    }
    painter.restore();
    return boundingRect;
}


QRect BasicToolsPlugin::mouseRelease(const QString & /* brush */,
                                     QPainter & /* painter */,
                                     const QPoint & /* pos */)
{
    return QRect(0, 0, 0, 0);
}


QStringList BasicToolsPlugin::shapes() const
{
    return QStringList() << tr("Hình tròn") << tr("Ngôi sao") << tr("Văn bản...");
}


QPainterPath BasicToolsPlugin::generateShape(const QString &shape,
                                             QWidget *parent)
{
    QPainterPath path;

    if (shape == tr("Hình tròn")) {
        double r = QInputDialog::getDouble(parent, tr("BK"),
                                             tr("Nhập BK:"),
                                             QLineEdit::Normal, 10);
        path.addEllipse(0, 0, r, r);
    } else if (shape == tr("Ngôi sao")) {
        path.moveTo(90, 50);
        for (int i = 1; i < 5; ++i) {
            path.lineTo(50 + 40 * cos(0.8 * i * Pi),
                        50 + 40 * sin(0.8 * i * Pi));
        }
        path.closeSubpath();
    } else if (shape == tr("Văn bản...")) {
        QString text = QInputDialog::getText(parent, tr("Văn bản"),
                                             tr("Nhập văn bản:"),
                                             QLineEdit::Normal, tr("Mini-Paint"));
        if (!text.isEmpty()) {
            QFont timesFont("Times", 50);
            timesFont.setStyleStrategy(QFont::ForceOutline);
            path.addText(0, 0, timesFont, text);
        }
    }

    return path;
}


QStringList BasicToolsPlugin::filters() const
{
    return QStringList() << tr("Đảo ngược pixel") << tr("Đảo màu (RGB->BGR)")
                         << tr("Màu xám");
}


QImage BasicToolsPlugin::filterImage(const QString &filter, const QImage &image,
                                     QWidget * /* parent */)
{
    QImage result = image.convertToFormat(QImage::Format_RGB32);

    if (filter == tr("Đảo ngược pixel")) {
        result.invertPixels();
    } else if (filter == tr("Đảo màu (RGB->BGR)")) {
        result = result.rgbSwapped();
    } else if (filter == tr("Màu xám")) {
        for (int y = 0; y < result.height(); ++y) {
            for (int x = 0; x < result.width(); ++x) {
                int pixel = result.pixel(x, y);
                int gray = qGray(pixel);
                int alpha = qAlpha(pixel);
                result.setPixel(x, y, qRgba(gray, gray, gray, alpha));
            }
        }
    }
    return result;
}
