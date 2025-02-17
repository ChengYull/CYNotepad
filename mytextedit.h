#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QTextEdit>
#include <QWheelEvent>
class MyTextEdit : public QTextEdit
{
public:
    MyTextEdit(QWidget *parent);

protected:
    void wheelEvent(QWheelEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
private:
    bool ctrlPressed = false;
};

#endif // MYTEXTEDIT_H
