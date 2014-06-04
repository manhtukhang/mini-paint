/******************************************************************************
 * Mini Paint                                                                 *
 * Copyleft (Ɔ) 2014 - Mini Paint                                             *
 * https://github.com/manhtuvjp/mini-paint                                    *
 ******************************************************************************
 * Tạo ra cửa sổ chính của chuơng trình bao gồm:                              *
 *  - Vùng vẽ ảnh                                                             *
 *  - Menu và các mục con của mỗi menu                                        *
 *  - Thông tin về chương trình và các plugin                                 *
 *  - Nạp plugin đồng thời tạo ra các menu con tương ứng                      *
 ******************************************************************************/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QMainWindow>
#include <QStringList>

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QMenu;
class QScrollArea;
QT_END_NAMESPACE
class PaintArea;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

private slots:
    void open();           // Mở hình
    bool saveAs();         // Lưu hình
    void undo();           // Hủy thao tác
    void brushColor();     // Thay đổi màu cọ vẽ
    void brushWidth();     // Thay đổi kích thước cọ vẽ
    void changeBrush();    // Thay đổi loại cọ vẽ
    void insertShape();    // Chèn hình
    void applyFilter();    // Áp dụng thay đổi từ các bộ lọc
    void about();          // Hiển thị thông tin về chương trình
    void aboutPlugins();   // Hỉên thị thông tin về các plugin

private:
    void createMenus();    // Tạo menu
    void createActions();  // Tạo ra hành động tương ứng khi nhấn vào menu

    void loadPlugins();                  // Nạp các plugin
    void populateMenus(QObject *plugin); // Định miền gt cho các thể hiện plugin
    void addToMenu(QObject *plugin, const QStringList &texts, QMenu *menu,
                   const char *member, QActionGroup *actionGroup = 0);
private:
    PaintArea *paintArea;        // Vùng hiển thị ảnh
    QScrollArea *scrollArea;     // Vùng cuộn (tùy kích thước khung hình)
    QDir pluginsDir;             // Thư mục plugin
    QStringList pluginFileNames; // Tên plugin

    // Các Menu đổ xuống
    QMenu *fileMenu;             // Menu Tệp
    QMenu *editMenu;             // Menu Biên tập
    QMenu *brushMenu;            // Menu Cọ vẽ
    QMenu *shapesMenu;           // Menu Hình
    QMenu *filterMenu;           // Menu Bộ lọc
    QMenu *helpMenu;             // Menu Thông tin

    // Các hành động tương ứng khi được chọn trong menu
    QAction *openAct;            // Mở tệp hình ảnh
    QAction *saveAsAct;          // Lưu hình ảnh ra tệp
    QAction *exitAct;            // Thoát khỏi chương trình
    QAction *undoAct;            // Hủy bỏ các thao tác vừa làm
    QAction *brushWidthAct;      // Thay đổi màu cọ vẽ
    QAction *brushColorAct;      // Thay đổi kích thước cọ vẽ
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *aboutPluginsAct;

    // Nhóm menu này được tạo ra hay không tùy thuộc vào plugin 
    QActionGroup *brushActionGroup;
};

#endif
