#include "mytextedit.h"
#include <QDebug>
#include <QGuiApplication>
MyTextEdit::MyTextEdit(QWidget *parent) : QTextEdit(parent) {
    // 安装过滤器
    this->installEventFilter(this);
}

void MyTextEdit::wheelEvent(QWheelEvent *e)
{
    int flag = e->angleDelta().y();
    if(ctrlPressed){
        if(flag > 0)    zoomIn();
        else    zoomOut();
        e->accept();
    }
    return QTextEdit::wheelEvent(e);
}

void MyTextEdit::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Control){
        ctrlPressed = true;
    }
    return QTextEdit::keyPressEvent(e);
}

void MyTextEdit::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Control){
        ctrlPressed = false;
    }
    return QTextEdit::keyPressEvent(e);
}

bool MyTextEdit::eventFilter(QObject *watched, QEvent *event)
{
    // 测试事件过滤器
    if(event->type() == QEvent::Wheel){
        if(QGuiApplication::keyboardModifiers() == Qt::ControlModifier){
            qDebug() << "Ctrl + wheel";
        }

        //return true;
    }
    // if(event->type() == QEvent::KeyPress){
    //     qDebug() << "key";
    //     QKeyEvent *ke = static_cast<QKeyEvent*>(event);
    //     qDebug() << ke->key();
    //     return true;
    // }
    return false;
}
