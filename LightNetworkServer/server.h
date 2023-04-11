#ifndef SERVER_H
#define SERVER_H

#include <QTcpSocket>
#include <QTcpServer>
#include <QVector>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();

public slots:
    void incomingConnection(qintptr socketDescriptor) override;
    void slotReadyRead();
    void sendToClient(QByteArray message);

private:
    QVector<QTcpSocket*> _sockets;
    QByteArray _data;
};

#endif // SERVER_H
