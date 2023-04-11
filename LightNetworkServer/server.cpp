#include "server.h"

Server::Server()
{
    if (this->listen(QHostAddress::Any, 6666))
    {
        qDebug() << "Listen...";
    }
    else
    {
        qDebug() << "Error";
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket* socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    _sockets.push_back(socket);

    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, [this, socket, socketDescriptor](){
        qDebug() << "Client disconnected" << socketDescriptor;
        _sockets.removeOne(socket);
        socket->deleteLater();
        qDebug() << "Current connections:" << _sockets.size();
    });

    qDebug() << "Client connected" << socketDescriptor;
    qDebug() << "Current connections:" << _sockets.size();
}

void Server::slotReadyRead()
{
    QTcpSocket* socket = (QTcpSocket*)sender();

    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_1);

    if (in.status() == QDataStream::Ok)
    {
        qDebug() << "Read...";

//        quint32 blockSize;
        QByteArray message;
        in >> message;

        qDebug() << "Connection" << socket->socketDescriptor() << "message:" << QString(message);
        sendToClient(message);
    }
}

void Server::sendToClient(QByteArray message)
{
    _data.clear();
    QDataStream out(&_data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_1);
    out << message;

    for (auto & iter : _sockets)
    {
        iter->write(_data);
    }
}
