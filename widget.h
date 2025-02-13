#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QString m_filePath = "";
    QFile m_file;
    QString m_text = "";
    QFileInfo m_fileInfo;
private slots:
    void on_btnOpen_clicked();

    void on_btnSave_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
