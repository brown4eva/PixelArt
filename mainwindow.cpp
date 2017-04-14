#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString myimagelink = QFileDialog::getOpenFileName(
                this,
                "Open a file",
                QString(),
                "Images (*.png *.gif *.jpeg *.jpg)");

    //Save
    pimg = new QImage (myimagelink);

    ui->FilePathLabel->setText(myimagelink);

    QPixmap pixmap (myimagelink);

    //Resizing

    int w, h;
    w=ui->DrawingLabel->width();
    h=ui->DrawingLabel->height();

    ui->DrawingLabel->setPixmap(pixmap.scaled(w,h, Qt::KeepAspectRatio));
    
}

void MainWindow::on_pushButton_2_clicked()
{
    /*QString myimagelink = QFileDialog::getSaveFileName(
                this,
                "Open a file",
                QString(),
                "Images (*.png *.gif *.jpeg *.jpg)");

    ui->FilePathLabel->setText(myimagelink);

    QPixmap newpic (myimagelink);

    ui->DrawingLabel->setPixmap(newpic);*/

    pimg->save(" ");
}

