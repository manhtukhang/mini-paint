#include "interfaces.h"
#include "mainwindow.h"
#include "paintarea.h"
#include "plugindialog.h"

#include <QPluginLoader>
#include <QTimer>

#include <QScrollArea>
#include <QMessageBox>
#include <QActionGroup>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QColorDialog>
#include <QInputDialog>
#include <QApplication>

// Constructor
MainWindow::MainWindow() :
    paintArea(new PaintArea),
    scrollArea(new QScrollArea)
{
//    undoStack = new QUndoStack(this);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(paintArea);
    setCentralWidget(scrollArea);

    createActions();
    createMenus();
    loadPlugins();

    setWindowTitle(tr("Mini Paint"));

    if (!brushActionGroup->actions().isEmpty())
        brushActionGroup->actions().first()->trigger();

    QTimer::singleShot(500, this, SLOT(aboutPlugins()));
}


// Mở hình ảnh
void MainWindow::open()
{
    const QString fileName = QFileDialog::getOpenFileName(this,
                                                          tr("Mở tệp"),
                                                          QDir::currentPath());
    if (!fileName.isEmpty()) {
        if (!paintArea->openImage(fileName)) {
            QMessageBox::information(this, tr("Mini Paint"),
                                     tr("Không thể mở %1.").arg(fileName));
            return;
        }
        paintArea->adjustSize();
    }
}


// Lưu hình ảnh với tên mới
bool MainWindow::saveAs()
{
    const QString initialPath = QDir::currentPath() + "/untitled.png";
	
	// Hộp thoại chọn nơi lưu tệp
    const QString fileName = QFileDialog::getSaveFileName(this, tr("Lưu"),
                                                          initialPath);
    if (fileName.isEmpty()) {
        return false;
    } else {
        return paintArea->saveImage(fileName, "png");
    }
}


// Hủy bỏ thao tác trước đó
void MainWindow::undo()
{

}


// Làm lại thao tác vừa hủy bỏ
void MainWindow::redo()
{

}


// Thay đổi màu cọ vẽ
void MainWindow::brushColor()
{
	// Hiển thị bảng chọn màu
    const QColor newColor = QColorDialog::getColor(paintArea->brushColor());
    if (newColor.isValid())
        paintArea->setBrushColor(newColor);
}


// Thay đổi kích thước cọ vẽ
void MainWindow::brushWidth()
{
    bool ok;
    // Hiển thị hộp thoại chọn kích thước cọ vẽ
    const int newWidth = QInputDialog::getInt(this, tr("Mini Paint"),
                                              tr("Kích thước cọ vẽ:"),
                                              paintArea->brushWidth(),
                                              1, 50, 1, &ok);
    if (ok)
        paintArea->setBrushWidth(newWidth);
}


// Thay đổi cọ vẽ
void MainWindow::changeBrush()
{
    QAction *action = qobject_cast<QAction *>(sender());
    BrushInterface *iBrush = qobject_cast<BrushInterface *>(action->parent());
    const QString brush = action->text();

    paintArea->setBrush(iBrush, brush);
}


// Thêm hình, tùy thuộc vào hình được chọn
void MainWindow::insertShape()
{
    QAction *action = qobject_cast<QAction *>(sender());
    ShapeInterface *iShape = qobject_cast<ShapeInterface *>(action->parent());

    const QPainterPath path = iShape->generateShape(action->text(), this);
    if (!path.isEmpty())
        paintArea->insertShape(path);
}


// Áp dụng kết quả sau khi chọn bộ lọc vào vùng làm việc
void MainWindow::applyFilter()
{
    QAction *action = qobject_cast<QAction *>(sender());
    FilterInterface *iFilter =
            qobject_cast<FilterInterface *>(action->parent());

    const QImage image = iFilter->filterImage(action->text(), paintArea->image(),
                                              this);
    paintArea->setImage(image);
}


// Hộp thoại hiển thị thông tin chương trình
void MainWindow::about()
{
   QMessageBox::about(this, tr("Thông tin về Mini Paint"),
            tr("<b>Mini Paint</b> là chương trình biên tập hình ảnh đơn giản. "
               "Có sử dụng các plugin ở dạng modul rời"));
}


// Hộp thoại hiển thị thông tin các plugin
void MainWindow::aboutPlugins()
{
    PluginDialog dialog(pluginsDir.path(), pluginFileNames, this);
    dialog.exec();
}


// Tạo ra các mục chọn, tương ứng với một hành động
// Tạo cơ chế kết nối các mục tương ứng và hành động
void MainWindow::createActions()
{
    openAct = new QAction(tr("&Mở..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAsAct = new QAction(tr("&Lưu..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    undoAct = new QAction(tr("Hủy thao tác"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    redoAct = new QAction(tr("Làm lại"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));


    exitAct = new QAction(tr("&Thoát"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    brushColorAct = new QAction(tr("Mà&u cọ vẽ..."), this);
    connect(brushColorAct, SIGNAL(triggered()), this, SLOT(brushColor()));

    brushWidthAct = new QAction(tr("&Kích thước cọ vẽ..."), this);
    connect(brushWidthAct, SIGNAL(triggered()), this, SLOT(brushWidth()));

    brushActionGroup = new QActionGroup(this);

    aboutAct = new QAction(tr("&Về Mini Paint"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("Về &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    aboutPluginsAct = new QAction(tr("Về các &Plugin"), this);
    connect(aboutPluginsAct, SIGNAL(triggered()), this, SLOT(aboutPlugins()));
}


// Tạo ra Menu và thêm các mục con cho mỗi Menu tương ứng
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Tệp"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Biên tập"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);


    brushMenu = menuBar()->addMenu(tr("&Cọ vẽ"));
    brushMenu->addAction(brushColorAct);
    brushMenu->addAction(brushWidthAct);
    brushMenu->addSeparator();

    shapesMenu = menuBar()->addMenu(tr("&Hình"));

    filterMenu = menuBar()->addMenu(tr("Bộ &lọc"));

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Giúp đỡ"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
    helpMenu->addAction(aboutPluginsAct);
}


// Nạp các plugin dưới dạng thư viện liên kết động đã biên dịch
// Tìm trong thư mực hiện tại, nếu tìm thấy sẽ nạp vào các thể hiện sẵn có
void MainWindow::loadPlugins()
{
    foreach (QObject *plugin, QPluginLoader::staticInstances())
        populateMenus(plugin);

    pluginsDir = QDir(qApp->applicationDirPath());

#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    // pluginsDir.cd("plugins");

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin) {
            populateMenus(plugin);
            pluginFileNames += fileName;
        }
    }

    brushMenu->setEnabled(!brushActionGroup->actions().isEmpty());
    shapesMenu->setEnabled(!shapesMenu->actions().isEmpty());
    filterMenu->setEnabled(!filterMenu->actions().isEmpty());
}


// Nạp tiêu đề của các bộ lọc từ plugin vào menu
void MainWindow::populateMenus(QObject *plugin)
{
    BrushInterface *iBrush = qobject_cast<BrushInterface *>(plugin);
    if (iBrush)
        addToMenu(plugin, iBrush->brushes(), brushMenu, SLOT(changeBrush()),
                  brushActionGroup);

    ShapeInterface *iShape = qobject_cast<ShapeInterface *>(plugin);
    if (iShape)
        addToMenu(plugin, iShape->shapes(), shapesMenu, SLOT(insertShape()));

    FilterInterface *iFilter = qobject_cast<FilterInterface *>(plugin);
    if (iFilter)
        addToMenu(plugin, iFilter->filters(), filterMenu, SLOT(applyFilter()));
}


// Thêm các Menu con vào thanh Menu
void MainWindow::addToMenu(QObject *plugin, const QStringList &texts,
                           QMenu *menu, const char *member,
                           QActionGroup *actionGroup)
{
    foreach (QString text, texts) {
        QAction *action = new QAction(text, plugin);
        connect(action, SIGNAL(triggered()), this, member);
        menu->addAction(action);

        if (actionGroup) {
            action->setCheckable(true);
            actionGroup->addAction(action);
        }
    }
}
