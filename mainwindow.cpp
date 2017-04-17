#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   //To define the size of the pixel block that will be pixelizing rendered
   size = 50;
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
    //pimg = new QImage (myimagelink);

    ui->FilePathLabel->setText(myimagelink);

    pixmap = new QPixmap(myimagelink);

    pimg = pixmap->toImage();

    //Setting the picture to display the required size of the image

    int w, h;
    w=ui->DrawingLabel->width();
    h=ui->DrawingLabel->height();

    ui->DrawingLabel->setPixmap(pixmap->scaled(w,h, Qt::KeepAspectRatio));
    
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

    pimg.save(" ");
}

//Having assitance from Khoi I was able to find the average of the picture and extract its color to replace it with new color.
void MainWindow::on_pushButton_3_clicked()
{
    //Loop to divide the image into smaller region.
    for(int i = 0; i < pimg.width(); i += size)
        for(int j = 0; j < pimg.height(); j += size){

            int r=0,g=0,b=0,a=0;

            //A loop to go through every pixels of the each cube
            for(int k = 0; k < size; ++k)
                for(int l = 0; l < size; ++l){

           // stopping criterion
                    if (i+k < pimg.width() && j+l <pimg.height()) {

                        // Converting the QRgb to QColor
                        QColor color(pimg.pixel(i+k,j+l));

                        // extracting color channels using QColor built-in functions
                        r += color.red();
                        g += color.green();
                        b += color.blue();
                        a += color.alpha();



                    }
                }

            // calculate the mean color value of every channels
            r /= size*size; g /= size*size; b /= size*size; a /= size*size;

            // combine 4 channels into QRgb data type
            QRgb meanColor = qRgba(r,g,b,a);

            // replacing the pixel of the cube by the new color extracted
            for(int k = 0; k < size; ++k)
                for(int l = 0; l < size; ++l)

                    // same stopping criterion as above
                    if (i+k < pimg.width() && j+l <pimg.height())
                        pimg.setPixel(i+k, j+l, meanColor);

        }


    //Displayin the pixelised image.
    *pixmap = QPixmap::fromImage(pimg);

    //Setting the picture to display the required size of the image
    int w,h;
    w=ui->DrawingLabel->width();
    h=ui->DrawingLabel->height();

    ui->DrawingLabel->setPixmap(pixmap->scaled(w,h, Qt::KeepAspectRatio));
}
