#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QListWidget>
#include <QStandardItemModel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSync_clicked()
{
    QString text = ui->lineEdit->text();

    QStandardItemModel *model = dynamic_cast<QStandardItemModel*>(ui->listView->model());
    if (!model) {
        model = new QStandardItemModel();
        ui->listView->setModel(model);
    }

    // Tạo một mục dữ liệu (item) mới và thêm nó vào mô hình dữ liệu
    QStandardItem *item = new QStandardItem(text);
    model->appendRow(item);

}

