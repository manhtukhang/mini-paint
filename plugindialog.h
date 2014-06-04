/******************************************************************************
 * Mini Paint                                                                 *
 * Copyleft (Ɔ) 2014 - Mini Paint                                             *
 * https://github.com/manhtuvjp/mini-paint                                    *
 *                                                                            *
 ******************************************************************************
 * Hộp thoại hỉên thị các công cụ, bộ lọc được nạp từ plugin                  *
 * Gồm có 2 loại:                                                             *
 *  - Plugin tĩnh, được biên dịch và liên kết trực tíêp vào chương trình      *
 *  - Plugin động, dạng thư viện chia sẻ dùng chung liên kết động             *
 * Loại thứ 2 sẽ được nạp khi chương trình thực thi                           *
 ******************************************************************************/


#ifndef PLUGINDIALOG_H
#define PLUGINDIALOG_H

#include <QDialog>
#include <QIcon>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QStringList;
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE

class PluginDialog : public QDialog {
    Q_OBJECT

public:
    PluginDialog(const QString &path, const QStringList &fileNames,
                 QWidget *parent = 0);

private:
    void findPlugins(const QString &path, const QStringList &fileNames);
    void populateTreeWidget(QObject *plugin, const QString &text);
    void addItems(QTreeWidgetItem *pluginItem, const char *interfaceName,
                  const QStringList &features);

    QLabel *label;
    QTreeWidget *treeWidget;
    QPushButton *okButton;
    QIcon interfaceIcon;
    QIcon featureIcon;
};

#endif
