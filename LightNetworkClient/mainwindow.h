#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonConnect_clicked();
    void on_buttonSend_clicked();
    void on_editMessage_returnPressed();
    void slotReadyRead();
    void sendToServer();

private:
    Ui::MainWindow *ui;
    QTcpSocket* _socket;
    QByteArray _data;
};
#endif // MAINWINDOW_H
