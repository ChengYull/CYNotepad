#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 虽然上一行代码进行了Widget和ui的关联，但是当窗口大小发生变化时，里面的布局不会随之变化
    // 通过显式设置布局，使窗口变化时，布局及其子控件随之调整
    this->setLayout(ui->verticalLayout);
    ui->widgetBottom->setLayout(ui->horizontalLayout);
}

Widget::~Widget()
{
    delete ui;
}
