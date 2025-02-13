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

    // 链接字符选择下拉列表变化时的槽函数
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &Widget::on_comboBox_changed);
    // 连接光标变化时更新右下角光标位置
    connect(ui->textEdit, &QTextEdit::cursorPositionChanged, this, &Widget::on_cursor_changed);
}

Widget::~Widget()
{
    delete ui;
}



void Widget::on_btnOpen_clicked()
{
    m_filePath = QFileDialog::getOpenFileName(this,
                                            "请选择文件",
                                            "",
                                            "Text Files (*.txt);");
    if(m_filePath.isEmpty())
        return;
    m_file.setFileName(m_filePath);
    if(!m_file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "文件打开失败";
        QMessageBox::critical(nullptr, "错误", "文件打开失败!");
        return;
    }
    // this->setWindowTitle(m_file.fileName());
    // 直接通过m_file.file.fileName() 获取到的是完整路径 而非单文件名
    // 通过QFileInfo 可以简便地获取到文件名
    m_fileInfo.setFile(m_file);
    this->setWindowTitle(m_fileInfo.fileName());

    /*m_text = m_file.readAll();
    m_file.close();
    ui->textEdit->setText(m_text);*/

    // 逐行读取优化
    ui->textEdit->clear();  // 清空原本区域
    QTextStream in(&m_file);
    in.setCodec(m_code.toStdString().c_str());
    while(!in.atEnd()){
        QString context = in.readLine();
        ui->textEdit->append(context);  // 添加文本至输入区
    }
    m_file.close();

    // QFile 语法学习
    /*QFile file(":/test.txt");  // 路径可以是绝对路径或资源文件路径（qrc）
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        while(!in.atEnd()){
            QString line = in.readLine(); // 逐行读取
            qDebug() << line;
        }
        file.close();
    }else{
        qDebug() << "Error opening file: " << file.errorString();
    }*/


}


void Widget::on_btnSave_clicked()
{
    // 如果文件为空
    if(m_file.fileName().isEmpty()){
        m_filePath = QFileDialog::getSaveFileName(this,
                                                  "请选择保存位置",
                                                  "*.txt",
                                                  "Text Files (*.txt);");
        if(m_filePath.isEmpty())
            return;
        m_file.setFileName(m_filePath);
        //this->setWindowTitle(m_file.fileName());
        m_fileInfo.setFile(m_file);
        this->setWindowTitle(m_fileInfo.fileName());
    }
    // 写入文件
    if(!m_file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "文件打开失败";
        QMessageBox::critical(nullptr, "错误", "文件打开失败!");
        return;
    }
    m_text = ui->textEdit->toPlainText();
    QTextStream out(&m_file);
    out.setCodec(m_code.toStdString().c_str());
    out << m_text;
    m_file.close();

    QMessageBox::information(nullptr, "提示", "保存成功！");

}

void Widget::on_btnClose_clicked()
{
    ui->textEdit->clear();
}

void Widget::on_comboBox_changed(){
    m_code = ui->comboBox->currentText();
    qDebug() << m_pos;
    if(m_file.fileName().isEmpty())
        return;
    // 当前文件打开时刷新显示
    if(!m_file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "文件打开失败";
        QMessageBox::critical(nullptr, "错误", "文件打开失败!");
        return;
    }
    ui->textEdit->clear();  // 清空原本区域
    QTextStream in(&m_file);
    in.setCodec(m_code.toStdString().c_str());
    while(!in.atEnd()){
        QString context = in.readLine();
        ui->textEdit->append(context);  // 添加文本至输入区
    }
    m_file.close();
}

void Widget::on_cursor_changed(){
    // 获取当前的文本光标
    QTextCursor cursor = ui->textEdit->textCursor();
    int row = cursor.blockNumber() + 1;
    int col = cursor.positionInBlock() + 1;
    QString posInfo = "第" + QString::fromStdString(std::to_string(row))
                      + "行,第" + QString::fromStdString(std::to_string(col)) + "列";
    ui->posLabel->setText(posInfo);
}

