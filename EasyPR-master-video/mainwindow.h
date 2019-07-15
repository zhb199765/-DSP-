#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextCodec>
#include <QMessageBox>
#include "QTimer"
#include "QImage"
#include "opencv2/opencv.hpp"
#include <QString>
#include <vector>
#include <iostream>
#include <string>
using namespace std;
QString s2q(const string &s);
string q2s(const QString &s);

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ReadFrame();
    void OpenCameraClicked();
    void CloseCameraClicked();
    void DisplayMat(cv::Mat image);
    void on_pushButton_3_clicked();
    void on_pushButton_9_clicked();

private slots:
    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::MainWindow *ui;
    VideoCapture capture;
    QTimer *timer;
    Mat frame;
    cv::Mat image;
};

#endif // MAINWINDOW_H
