#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //To define the size of the pixel block that will be pixelizing rendered
    size = 20;
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Loading and Displaying function
void MainWindow::on_pushButton_clicked()
{
    QString myimagelink = QFileDialog::getOpenFileName(
                this,
                "Open a file",
                "",
                "Images (*.png *.gif *.jpeg *.jpg)");

    //Shows the path of my loaded image.
    ui->FilePathLabel->setText(myimagelink);

    // create a pixmap using image url above
    pixmap = new QPixmap(myimagelink);

    // I worked on this part with my classmate Selma Boudissa
    // convert QPixmap to QImage
    pimg = pixmap->toImage();

    //Setting the picture to display the required size of the image
    int w, h;
    w = ui->DrawingLabel->width();
    h = ui->DrawingLabel->height();

    //Scale the picture and load it on the drawinglabel
    ui->DrawingLabel->setPixmap(pixmap->scaled(w,h, Qt::KeepAspectRatio));
    
}

//Saving an image
void MainWindow::on_pushButton_2_clicked()
{
    // get the url of the file and folder when user click save in QFileDialog and use it to save the image
    QString saveurl = QFileDialog::getSaveFileName(this, tr(""),"",tr("Images (*.png *.jpeg *.jpg)"));
    pimg.save(saveurl);
}

//Finding the average of the picture and extract its color to replace it with new color.
void MainWindow::on_pushButton_3_clicked()
{
    //Loop to divide the image into smaller region.
    for(int i = 0; i < pimg.width(); i += size)             // this loop will shift the window vertically
        for(int j = 0; j < pimg.height(); j += size){       // this loop will shift the window horizontally

            int r=0,g=0,b=0,a=0;

            //A loop to go through every pixels of the each window
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

            // replacing the pixel of the window by the new color extracted
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

    //scale the picture and load it on the drawinglabel
    ui->DrawingLabel->setPixmap(pixmap->scaled(w,h, Qt::KeepAspectRatio));
}

//load multiple sample images funciton
void MainWindow::on_pushButton_4_clicked()
{
    QStringList myimagelinks = QFileDialog::getOpenFileNames(
                this,
                "Open a file",
                "",
                "Images (*.png *.gif *.jpeg *.jpg)");


    //store sample images in sampleimages attribute
    for(int i=0; i<myimagelinks.length(); i++){
        QImage tempimage(myimagelinks[i]);

        sampleimages.append(tempimage);   // store the created image in the vector to use in next function
    }

    //loop through sample image list and calculate mean colors
    //it will be the same like I did with pixel blocks on previous function
    QVector<QImage>::iterator it;
    for(it = sampleimages.begin(); it != sampleimages.end(); ++it){

        int r=0,g=0,b=0,a=0,sumcolor;

        for(int k = 0; k < it->width(); ++k)
            for(int l = 0; l < it->height(); ++l){
                // Converting the QRgb to QColor
                QColor color(it->pixel(k,l));
                // extracting color channels using QColor built-in functions
                r += color.red();
                g += color.green();
                b += color.blue();
                a += color.alpha();

            }
        // calculate the mean color value of every channels
        r /= it->width()*it->height();
        g /= it->width()*it->height();
        b /= it->width()*it->height();
        a /= it->width()*it->height();

        //sum the color to store in samplecolors list for value comparision in next function
        sumcolor = r + g + b + a;
        samplecolors.append(sumcolor);
    }

}

//Art transform function
void MainWindow::on_pushButton_5_clicked()
{
    //here I reuse the same function as I created to do pixelizing
    //since I have to loop through this process again to get the mean color
    //of every pixel blocks and so I can do color comparision with sample colors

    //Loop to divide the image into smaller region.
    for(int i = 0; i < pimg.width(); i += size)
        for(int j = 0; j < pimg.height(); j += size){

            int r=0,g=0,b=0,a=0,sumcolor;

            //A loop to go through every pixels of the each window
            for(int k = 0; k < size; ++k)
                for(int l = 0; l < size; ++l){
                    //stopping criterion
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
            //calculate the mean color value of every channels
            r /= size*size; g /= size*size; b /= size*size; a /= size*size;


            //sum color to do color comparision below
            sumcolor = r+g+b+a;

            //variables to store temporary best values
            //bestColorIndex will be used to get the best matched image
            int bestcolorindex, initoffset = 10000;

            //loop through sample color to find best match color
            QVector<int>::iterator it;
            for(it = samplecolors.begin(); it != samplecolors.end(); ++it){
                //color value comparision to choose best match color
                if(abs(sumcolor-*it) < initoffset){
                    initoffset = abs(sumcolor-*it);     //i used abs to neglect the minus number cases
                    bestcolorindex = it-samplecolors.begin();   // get the position of the best color
                }
            }

            QLabel *pixelimage = new QLabel(this);

            //create label to store this matched picture, on the same
            //location of the pixel block
            pixelimage->setGeometry(QRect(i,j,size,size)); // The label to be in the right place.
            pixelimage->setPixmap(QPixmap::fromImage(sampleimages[bestcolorindex]).scaled(QSize(size,size)));
            pixelimage->show();

        }

}
