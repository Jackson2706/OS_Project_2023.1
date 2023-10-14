#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QListWidget>
#include <QStandardItemModel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    connect(ui->btnSync, SIGNAL(clicked()), this, SLOT(on_btnSync_clicked()));
    connect(ui->bntConnect, SIGNAL(clicked()), this, SLOT(on_bntConnect_clicked()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(onDataReceived()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSync_clicked()
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        QByteArray dataToSend = "Hello, I want to connect server";
        socket->write(dataToSend);
        socket->flush();
    } else {
        qDebug() << "Không kết nối hoặc kết nối đã bị ngắt.";
        // Xử lý trường hợp kết nối chưa được thiết lập hoặc đã bị ngắt
    }
}

void MainWindow::newConnection()
{
    qDebug() << "Connect server complete";
}

void MainWindow::connectionError(QAbstractSocket::SocketError error) {
    qDebug() << "Error connect: " << socket->errorString();
}

void MainWindow::on_bntConnect_clicked()
{
    QString localHost = ui->lineLocal->text();
    int port = ui -> linePort -> text().toInt();

    socket->connectToHost(localHost,port);
    connect(socket, SIGNAL(connected()), this, SLOT(newConnection()));
    connect(socket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(connectionError(QAbstractSocket::SocketError)));
}
void MainWindow::onDataReceived() {
    // Đọc dữ liệu từ máy chủ khi sự kiện readyRead được kích hoạt
    if (socket->state() == QAbstractSocket::ConnectedState) {
        QByteArray data = socket->readAll(); // Đọc toàn bộ dữ liệu có sẵn
        QStandardItemModel *model = dynamic_cast<QStandardItemModel*>(ui->listView->model());
         if (!model) {
            model = new QStandardItemModel();
            ui->listView->setModel(model);
         }

        QStandardItem *item = new QStandardItem(data);
        model->appendRow(item);
        qDebug() << "Dữ liệu từ máy chủ: " << data;

        // Xử lý dữ liệu theo nhu cầu của bạn
    }
}
