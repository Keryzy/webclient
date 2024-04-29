#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QSslSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QTcpSocket tcp_socket_;
    QSslSocket ssl_socket_;
    bool select_tcp;
    bool select_ssl;

public slots:
    void doConnected();

    void doDisconnected();

    void doReadyRead();

    void setActivation(bool act);

private slots:
    void on_pbConnect_clicked();

    void on_pbDisConnect_clicked();

    void on_pbSend_clicked();

    void on_pbClear_clicked();

    void on_cb_tcp_clicked();

    void on_cb_ssl_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
