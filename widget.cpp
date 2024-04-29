#include "widget.h"
#include "ui_widget.h"
//#include <QHostAddress>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //TCP
    QObject::connect(&tcp_socket_, &QAbstractSocket::connected, this, &Widget::doConnected);
    QObject::connect(&tcp_socket_, &QAbstractSocket::disconnected, this, &Widget::doDisconnected);
    QObject::connect(&tcp_socket_, &QAbstractSocket::readyRead, this, &Widget::doReadyRead);

    //SSL
    QObject::connect(&ssl_socket_, &QAbstractSocket::connected, this, &Widget::doConnected);
    QObject::connect(&ssl_socket_, &QAbstractSocket::disconnected, this, &Widget::doDisconnected);
    QObject::connect(&ssl_socket_, &QAbstractSocket::readyRead, this, &Widget::doReadyRead);

    ui->cb_tcp->setChecked(1);
    select_tcp = true;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setActivation(bool act){
    ui->pbConnect->setEnabled(act);
    ui->pbDisConnect->setEnabled(!act);
    ui->leHost->setEnabled(act);
    ui->lePort->setEnabled(act);
    ui->cb_tcp->setEnabled(act);
    ui->cb_ssl->setEnabled(act);
}

void Widget::doConnected(){
    ui->pteMessage->insertPlainText("Connected \r\n");
}

void Widget::doDisconnected(){
    ui->pteMessage->insertPlainText("Disconnected \r\n");
}

void Widget::doReadyRead(){
    QByteArray ba = tcp_socket_.readAll();
    ui->pteMessage->insertPlainText(ba);
}

void Widget::on_pbConnect_clicked()
{
    if(select_ssl == true)
        ssl_socket_.connectToHostEncrypted(ui->leHost->text(),ui->lePort->text().toUShort());
    if(select_tcp == true)
        tcp_socket_.connectToHost(ui->leHost->text(), ui->lePort->text().toUShort());

    setActivation(false);
}

void Widget::on_pbDisConnect_clicked()
{
    tcp_socket_.close();
    ssl_socket_.close();

    setActivation(true);
}

void Widget::on_pbSend_clicked()
{
    tcp_socket_.write(ui->pteSend->toPlainText().toUtf8());
}

void Widget::on_pbClear_clicked()
{
    ui->pteMessage->clear();
}

void Widget::on_cb_tcp_clicked()
{
    select_tcp = ui->cb_tcp->isChecked();
    ui->cb_ssl->setChecked(0);
    select_ssl = false;

    ui->lePort->setText("80");
}

void Widget::on_cb_ssl_clicked()
{
    select_ssl = ui->cb_ssl->isChecked();
    ui->cb_tcp->setChecked(0);
    select_tcp = false;

    ui->lePort->setText("443");
}

