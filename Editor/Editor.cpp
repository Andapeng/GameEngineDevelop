#include "Editor.h"
#include <qqmlapplicationengine.h>
#include <QtQuickWidgets/QtQuickWidgets>
#include <QVBoxLayout>

Editor::Editor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QQuickWidget* quickWidget = new QQuickWidget(this);
    quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    quickWidget->setSource(QUrl("qrc:/QML/main.qml")); // 使用资源文件路径
    
    ui.centralWidget->setLayout(new QVBoxLayout());
    ui.centralWidget->layout()->addWidget(quickWidget);
}

Editor::~Editor()
{}
