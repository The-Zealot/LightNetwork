#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _socket = new QTcpSocket(this);
    connect(_socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(_socket, &QTcpSocket::disconnected, _socket, &QTcpSocket::deleteLater);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonConnect_clicked()
{
    _socket->connectToHost(ui->editHost->text(), 6666);
}

void MainWindow::on_buttonSend_clicked()
{
    sendToServer();
}

void MainWindow::on_editMessage_returnPressed()
{
    sendToServer();
}

void MainWindow::slotReadyRead()
{
    QDataStream in(_socket);
    in.setVersion(QDataStream::Qt_6_1);

    if (in.status() == QDataStream::Ok)
    {
        QByteArray message;
        in >> message;
        ui->textBrowserHistory->append(message);
    }
}

void MainWindow::sendToServer()
{
    _data.clear();
    QByteArray message;
    QDataStream out(&_data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_1);
    message = ui->editMessage->text().toUtf8();
    out << message;
    _socket->write(_data);
}


