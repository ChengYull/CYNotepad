#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QList>
#include <QShortcut>
#include <QKeySequence>
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
    QString m_code = "UTF-8";
    QPoint m_pos;
private slots:
    void on_btnOpen_clicked();

    void on_btnSave_clicked();

    void on_btnClose_clicked();

    void on_comboBox_changed();

    void on_cursor_changed();

    void on_zoom_in();

    void on_zoom_out();
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
