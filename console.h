#ifndef CONSOLE_H
#define CONSOLE_H
#include <QPlainTextEdit>

class Console : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit Console(QWidget *parent = 0);
    ~Console();

signals:
    void getData(const QByteArray &data);
    void getEnter();

private:
    bool localEchoEnabled;

public:
    Q_INVOKABLE void printData(QString text);
    void putData(const QByteArray &data);
    void setLocalEchoEnabled(bool set);

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void contextMenuEvent(QContextMenuEvent *e);
};

#endif // CONSOLE_H
