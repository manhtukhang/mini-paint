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


#include "interfaces.h"
#include "plugindialog.h"

#include <QPluginLoader>
#include <QStringList>
#include <QDir>

#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QHeaderView>

PluginDialog::PluginDialog(const QString &path, const QStringList &fileNames,
                           QWidget *parent) :
    QDialog(parent),
    label(new QLabel),
    treeWidget(new QTreeWidget),
    okButton(new QPushButton(tr("OK")))
{
    treeWidget->setAlternatingRowColors(false);
    treeWidget->setSelectionMode(QAbstractItemView::NoSelection);
    treeWidget->setColumnCount(1);
    treeWidget->header()->hide();

    okButton->setDefault(true);

    connect(okButton, SIGNAL(clicked()), this, SLOT(close()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(2, 1);
    mainLayout->addWidget(label, 0, 0, 1, 3);
    mainLayout->addWidget(treeWidget, 1, 0, 1, 3);
    mainLayout->addWidget(okButton, 2, 1);
    setLayout(mainLayout);

    interfaceIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirOpenIcon),
                            QIcon::Normal, QIcon::On);
    interfaceIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirClosedIcon),
                            QIcon::Normal, QIcon::Off);
    featureIcon.addPixmap(style()->standardPixmap(QStyle::SP_FileIcon));

    setWindowTitle(tr("Thông tin plugin"));
    findPlugins(path, fileNames);
}

void PluginDialog::findPlugins(const QString &path,
                               const QStringList &fileNames)
{
    label->setText(tr("Mini Paint tìm thấy các plugin sau\n"
                      "(tìm trong %1):")
                   .arg(QDir::toNativeSeparators(path)));

    const QDir dir(path);

    foreach (QObject * plugin, QPluginLoader::staticInstances())
    populateTreeWidget(plugin, tr("%1 (Plugin tĩnh)")
                       .arg(plugin->metaObject()->className()));

    foreach (QString fileName, fileNames) {
        QPluginLoader loader(dir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin) {
            populateTreeWidget(plugin, fileName);
        }
    }
}

void PluginDialog::populateTreeWidget(QObject *plugin, const QString &text)
{
    QTreeWidgetItem *pluginItem = new QTreeWidgetItem(treeWidget);
    pluginItem->setText(0, text);
    treeWidget->setItemExpanded(pluginItem, true);

    QFont boldFont = pluginItem->font(0);
    boldFont.setBold(true);
    pluginItem->setFont(0, boldFont);

    if (plugin) {
        BrushInterface *iBrush = qobject_cast<BrushInterface *>(plugin);
        if (iBrush) {
            addItems(pluginItem, "Cọ vẽ", iBrush->brushes());
        }

        ShapeInterface *iShape = qobject_cast<ShapeInterface *>(plugin);
        if (iShape) {
            addItems(pluginItem, "Hình khối", iShape->shapes());
        }

        FilterInterface *iFilter =
            qobject_cast<FilterInterface *>(plugin);
        if (iFilter) {
            addItems(pluginItem, "Các bộ lọc", iFilter->filters());
        }
    }
}

void PluginDialog::addItems(QTreeWidgetItem *pluginItem,
                            const char *interfaceName,
                            const QStringList &features)
{
    QTreeWidgetItem *interfaceItem = new QTreeWidgetItem(pluginItem);
    interfaceItem->setText(0, interfaceName);
    interfaceItem->setIcon(0, interfaceIcon);

    foreach (QString feature, features) {
        if (feature.endsWith("...")) {
            feature.chop(3);
        }
        QTreeWidgetItem *featureItem = new QTreeWidgetItem(interfaceItem);
        featureItem->setText(0, feature);
        featureItem->setIcon(0, featureIcon);
    }
}
