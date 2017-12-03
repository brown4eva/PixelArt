#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();   //load picture

    void on_pushButton_2_clicked(); //save picture

    void on_pushButton_3_clicked(); //pixelize picture

    void on_pushButton_4_clicked(); //load multiple images

    void on_pushButton_5_clicked(); //transform art image

private:
    Ui::MainWindow *ui;
    QImage pimg;
    QPixmap *pixmap;
    int size;
    QVector<QImage> sampleimages; //I store multiple images here.
    QVector<int> samplecolors; //I store mean colors here
};

#endif // MAINWINDOW_H
