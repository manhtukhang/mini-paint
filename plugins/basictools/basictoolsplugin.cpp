/******************************************************************************
 * Mini Paint                                                                 *
 * Copyleft (Ɔ) 2014 - Mini Paint                                             *
 * https://github.com/manhtuvjp/mini-paint                                    *
 *                                                                            *
 ******************************************************************************
 * Cung cấp các công cụ đơn giản như:                                         *
 *  - Bút vẽ                                                                  *
 *  - Công cụ phun màu dạng sương mù                                          *
 *  - Chèn vào 1 chữ cái ngẫu nhiên trong bảng chữ cái Alphabet               *
 *  - Các hình cơ bản như: hình tròn, ngôi sao, văn bản                       *
 ******************************************************************************/


#include <QtWidgets>

#include <math.h>
#include <stdlib.h>

#include "basictoolsplugin.h"

// Khai báo và định nghĩa hằng số Pi
const float Pi = 3.14159f;


/*** Thực hiện giao diện cọ vẽ ***/

// Hàm trả về danh sách các cọ vẽ có trong plugin.
QStringList BasicToolsPlugin::brushes() const
{
    return QStringList() << tr("Bút chì") << tr("Phun sương")
           << tr("Chữ cái ngẫu nhiên");
}


// Hàm dùng để vẽ khi xảy ra sự kiện bấm chuột bằng cách gọi hàm
// BasicToolsPlugin::mouseMove(...)
QRect BasicToolsPlugin::mousePress(const QString &brush, QPainter &painter,
                                   const QPoint &pos)
{
    return mouseMove(brush, painter, pos, pos);
}

// Hàm dùng để vẽ bằng cọ vẽ cung cấp trong plugin
QRect BasicToolsPlugin::mouseMove(const QString &brush, QPainter &painter,
                                  const QPoint &oldPos, const QPoint &newPos)
{
    // Lưu trạng thái của Qpainter và tính toán một số biến cần thiết
    painter.save();

    int rad = painter.pen().width() / 2;
    QRect boundingRect = QRect(oldPos, newPos).normalized()
                         .adjusted(-rad, -rad, +rad, +rad);
    QColor color = painter.pen().color();
    int thickness = painter.pen().width();
    QColor transparentColor(color.red(), color.green(), color.blue(), 0);


    // Lựa chọn loại cọ vẽ từ QString &brush để có hành động thích hợp.
    if (brush == tr("Bút chì")) {
        // Nếu cọ vẽ là "Bút chì" ta chỉ cần gọi Qpainter::drawLine() với Qpen
        // hiện tại
        painter.drawLine(oldPos, newPos);
    } else if (brush == tr("Phun sương")) {
        // Nếu cọ vẽ là "Phun sương" ta thiết lập QBrush của painter về
        // Q::Dense6Pattern để được các chấm.
        int numSteps = 2 + (newPos - oldPos).manhattanLength() / 2;

        painter.setBrush(QBrush(color, Qt::Dense6Pattern));
        painter.setPen(Qt::NoPen);

        // Ta vẽ một vòng tròn đầy bằng nhều lần QBrush, để có cảm giác như
        // một đường sương.
        for (int i = 0; i < numSteps; ++i) {
            int x = oldPos.x() + i * (newPos.x() - oldPos.x()) / (numSteps - 1);
            int y = oldPos.y() + i * (newPos.y() - oldPos.y()) / (numSteps - 1);

            painter.drawEllipse(x - (thickness / 2), y - (thickness / 2),
                                thickness, thickness);
        }
    } else if (brush == tr("Chữ cái ngẫu nhiên")) {
        // Nếu cọ vẽ là một "Chữ ngẫu nhiên" ta sẽ chọn một kí tự ngẫu nhiên
        // từ A đến Z
        QChar ch('A' + (qrand() % 26));

        // Cài đặt phông chữ đậm và lớn hơn so với phông chữ mặc định
        QFont biggerFont = painter.font();
        biggerFont.setBold(true);
        biggerFont.setPointSize(biggerFont.pointSize() + thickness);
        painter.setFont(biggerFont);

        painter.drawText(newPos, QString(ch));

        // Xác định một QRect ranh giới thích hợp
        QFontMetrics metrics(painter.font());
        boundingRect = metrics.boundingRect(ch);
        boundingRect.translate(newPos);
        boundingRect.adjust(-10, -10, +10, +10);
    }
    painter.restore();
    return boundingRect;
}

// Hàm trả về một hình QRect rỗng khi người dùng thả chuột
QRect BasicToolsPlugin::mouseRelease(const QString & /* brush */,
                                     QPainter & /* painter */,
                                     const QPoint & /* pos */)
{
    return QRect(0, 0, 0, 0);
}


/*** Thực hiện giao diện hình cơ bản ***/

// Hàm trả về các hình cơ bản trong plugin
QStringList BasicToolsPlugin::shapes() const
{
    return QStringList() << tr("Hình tròn") << tr("Ngôi sao") << tr("Văn bản...");
}

// Hàm dùng để vẽ các hình cơ bản trong plugin
QPainterPath BasicToolsPlugin::generateShape(const QString &shape,
        QWidget *parent)
{
    // QPainterPath sẽ nhận một hình dạng xác định để được vẽ
    QPainterPath path;

    if (shape == tr("Hình tròn")) {
        // Nếu là "Hình tròn" thì ta sẽ bật một QInputDialog lên để người dùng
        // nhập vào bán kính
        double r = QInputDialog::getDouble(parent, tr("Bán kính"),
                                           tr("Nhập bán kính:"),
                                           QLineEdit::Normal, 10);
        // Vẽ hình tròn với bán kính bằng r vừa nhập
        path.addEllipse(0, 0, r, r);
    } else if (shape == tr("Ngôi sao")) {
        // Di chuyển đến vị trí (90, 50)
        path.moveTo(90, 50);
        // Vẽ 5 cánh của ngôi sao bằng các vẽ từng cánh một
        for (int i = 1; i < 5; ++i) {
            // Vẽ một đoạn thẳng từ vị trí hiênh tại đến vị trí (x, y) và cập
            // nhật vị trí hiện tại thành (x, y)
            path.lineTo(50 + 40 * cos(0.8 * i * Pi),
                        50 + 40 * sin(0.8 * i * Pi));
        }
        path.closeSubpath();
    } else if (shape == tr("Văn bản...")) {
        // Nếu là "Văn bản..." thì ta sẽ bật một QInputDialog lên để người
        // dùng nhập vào văn bản cần chèn
        QString text = QInputDialog::getText(parent, tr("Văn bản"),
                                             tr("Nhập văn bản:"),
                                             QLineEdit::Normal, tr("Mini-Paint"));
        // Thiết lập font, kích thước, bao khung và chèn văn bản
        if (!text.isEmpty()) {
            QFont timesFont("Times", 50);
            timesFont.setStyleStrategy(QFont::ForceOutline);
            path.addText(0, 0, timesFont, text);
        }
    }

    return path;
}
