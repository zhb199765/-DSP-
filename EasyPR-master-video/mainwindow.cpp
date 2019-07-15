#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <include/easypr.h>
#include <ctime>
#include <fstream>
#include <list>
#include <memory>
#include <numeric>
#include <unordered_map>
#include "E:/Qt_test/EasyPR-master/EasyPR-master/include/easypr/core/core_func.h"
#include "E:/Qt_test/EasyPR-master/EasyPR-master/include/easypr/util/switch.hpp"
#include "thirdparty/xmlParser/xmlParser.h"
#include "E:/Qt_test/EasyPR-master/EasyPR-master/include/easypr/core/params.h"
#include "test/config.hpp"
#include "test/result.hpp"
#include "test/plate.hpp"
#include <QPushButton>
#include <QDebug>
#include <QString>
#include <string>
using namespace easypr;
using namespace cv;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("视频播放简单示例");
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(ReadFrame()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(OpenCameraClicked()));//打开摄像头
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(CloseCameraClicked()));//关闭摄像头
//    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(on_pushButton_3_clicked()));//打开图片
//    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(on_pushButton_9_clicked()));
//    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(on_pushButton_8_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReadFrame()
{
    //获取图像帧
    capture>>frame;
/*
    //将抓取到的帧,转换为QImage格式,QImage::Format_RGB888使用24位RGB格式（8-8-8）存储图像
    //此时没有使用rgbSwapped()交换所有像素的红色和蓝色分量的值，底色偏蓝
    QImage image = QImage((const uchar*)frame.data,frame.cols, frame.rows,QImage::Format_RGB888);
*/
    //将视频显示到label上
    QImage image = QImage((const uchar*)frame.data,frame.cols,frame.rows,QImage::Format_RGB888).rgbSwapped();
    image = image.scaled(ui->label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(QPixmap::fromImage(image));
    cv::Mat src = frame;
//读取视频
    CPlateRecognize pr;
      pr.setLifemode(true);
      pr.setDebug(false);
      pr.setMaxPlates(1);
      //pr.setDetectType(PR_DETECT_COLOR | PR_DETECT_SOBEL);
      pr.setDetectType(easypr::PR_DETECT_CMSER);

//      vector<string> plateVec;
      vector<CPlate> plateVec;

      int result = pr.plateRecognize(src, plateVec);
//      int result = pr.plateRecognizeAsText(src, plateVec);
      cout <<"kkkkkk"<< endl;
      if (result == 0) {
        size_t num = plateVec.size();
        for (size_t j = 0; j < num; j++) {
          cv::String stt=plateVec[j].getPlateStr();
          cout << "plateRecognize: " << plateVec[j].getPlateStr() << endl;
          std::string str = stt;
          QString qstring;
          qstring = QString(QString::fromLocal8Bit(str.c_str()));//从std::string 到QString
          ui->label_2->setText(qstring);
        }
      }
}
void MainWindow::DisplayMat(cv::Mat image)
{
    cv::Mat rgb;
    QImage img;
    if(image.channels() == 3)
    {
        cvtColor(image,rgb,CV_BGR2RGB);
        img = QImage((const unsigned char*)(rgb.data),
                     rgb.cols,rgb.rows,rgb.cols*rgb.channels(),//rgb.cols*rgb.channels()可以替换为image.step
                     QImage::Format_RGB888);
    }
    else
    {
        img = QImage((const unsigned char*)(image.data),
                     image.cols,image.rows,rgb.cols*image.channels(),
                     QImage::Format_RGB888);
    }
    ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size()));//setPixelmap(QPixmap::fromImage(img));
    ui->label->resize(ui->label->pixmap()->size());//resize(ui->label->pixmap()->size());
}

//打开摄像头
void MainWindow::OpenCameraClicked()
{
    capture.open(0);//打开摄像头
    timer->start(10);//开启定时器，一次25ms
}

//关闭摄像头
void MainWindow::CloseCameraClicked()
{
    timer->stop();//关闭定时器
    capture.release();//释放图像
}

void MainWindow::on_pushButton_3_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
                       tr("Open Image"),".",tr("Image File (*.jpg *.png *.bmp)"));
    QTextCodec *code = QTextCodec::codecForName("gb18030");
    std::string name = code->fromUnicode(filename).data();//filename.toAscii().data()
    image = cv::imread(name);
    if(!image.data)
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Image Data Is Null"));
        msgBox.exec();
    }
    else {
       DisplayMat(image);
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    //demo::test_plate_recognize();
    cout << "test_plate_recognize" << endl;

 // Mat src = imread("resources/image/test.jpg");
//    QString filename = QFileDialog::getOpenFileName(this,
//                       tr("Open Image"),".",tr("Image File (*.jpg *.png *.bmp)"));
//    QTextCodec *code = QTextCodec::codecForName("gb18030");
//    std::string name = code->fromUnicode(filename).data();//filename.toAscii().data()
//    cv::Mat src = cv::imread(name);
//    DisplayMat(src);
//读取图片中的车牌
    capture.open(0);//打开摄像头
    capture>>frame;
    QImage image = QImage((const uchar*)frame.data,frame.cols,frame.rows,QImage::Format_RGB888).rgbSwapped();
    image = image.scaled(ui->label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    ui->label->setPixmap(QPixmap::fromImage(image));
    cv::Mat src = frame;
//读取视频
    CPlateRecognize pr;
      pr.setLifemode(true);
      pr.setDebug(false);
      pr.setMaxPlates(1);
      //pr.setDetectType(PR_DETECT_COLOR | PR_DETECT_SOBEL);
      pr.setDetectType(easypr::PR_DETECT_CMSER);

//      vector<string> plateVec;
      vector<CPlate> plateVec;

      int result = pr.plateRecognize(src, plateVec);
//      int result = pr.plateRecognizeAsText(src, plateVec);
      cout <<"kkkkkk"<< endl;
      if (result == 0) {
        size_t num = plateVec.size();
        for (size_t j = 0; j < num; j++) {
          cv::String stt=plateVec[j].getPlateStr();
          cout << "plateRecognize: " << plateVec[j].getPlateStr() << endl;
          std::string str = stt;
          QString qstring;
          //从std::string 到QString
          qstring = QString(QString::fromLocal8Bit(str.c_str()));
          ui->label_2->setText(qstring);
//          cv::Mat mat2(1, str.size(), CV_8U, (char*)str.data());
//          cv::Mat dst = cv::imdecode(mat2, CV_LOAD_IMAGE_COLOR);
//          QImage image = QImage((const uchar*)dst.data,dst.cols,dst.rows,QImage::Format_RGB888).rgbSwapped();
//          image = image.scaled(ui->label_2->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
//          ui->label_2->setPixmap(QPixmap::fromImage(image));
//用cv::String提取识别值，然后转为std::string,再转为Mat就可以显示了
        }
      }

      if (result != 0)
          cout << "result:" << result << endl;
}

void MainWindow::on_pushButton_8_clicked()
{
//    demo::test_plate_judge();
    cout << "test_plate_judge" << endl;

  //  cv::Mat src = imread("E:\\Qt_test\\EasyPR-master\\EasyPR-master\\resources\\image\\video\\2.jpg");
    QString filename = QFileDialog::getOpenFileName(this,
                       tr("Open Image"),".",tr("Image File (*.jpg *.png *.bmp)"));
    QTextCodec *code = QTextCodec::codecForName("gb18030");
    std::string name = code->fromUnicode(filename).data();//filename.toAscii().data()
    cv::Mat src = cv::imread(name);
    DisplayMat(src);
    vector<cv::Mat> matVec;
    vector<cv::Mat> resultVec;

    CPlateLocate lo;
    lo.setDebug(1);
    lo.setLifemode(true);

    int resultLo = lo.plateLocate(src, matVec);



    cout << "plate_locate_img" << endl;
    size_t num = matVec.size();
    for (size_t j = 0; j < num; j++) {
      Mat resultMat = matVec[j];
      QImage image = QImage((const uchar*)resultMat.data,resultMat.cols,resultMat.rows,QImage::Format_RGB888).rgbSwapped();
      image = image.scaled(ui->label_3->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
      ui->label_3->setPixmap(QPixmap::fromImage(image));
    }
}

void MainWindow::on_pushButton_10_clicked()
{
    //cv::Mat src = imread("E:\\Qt_test\\EasyPR-master\\EasyPR-master\\resources\\image\\video\\2.jpg");
    QString filename = QFileDialog::getOpenFileName(this,
                       tr("Open Image"),".",tr("Image File (*.jpg *.png *.bmp)"));
    QTextCodec *code = QTextCodec::codecForName("gb18030");
    std::string name = code->fromUnicode(filename).data();//filename.toAscii().data()
    cv::Mat src = cv::imread(name);
    DisplayMat(src);
    vector<cv::Mat> matVec;
    vector<cv::Mat> resultVec;

    CPlateLocate lo;
    lo.setDebug(1);
    lo.setLifemode(true);

    int resultLo = lo.plateLocate(src, matVec);

//    if (0 != resultLo) return -1;

    cout << "plate_locate_img" << endl;
    size_t num = matVec.size();
    for (size_t j = 0; j < num; j++) {
      Mat resultMt = matVec[j];
      QImage image = QImage((const uchar*)resultMt.data,resultMt.cols,resultMt.rows,QImage::Format_RGB888).rgbSwapped();
      image = image.scaled(ui->label_4->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
      ui->label_4->setPixmap(QPixmap::fromImage(image));
    }
    //destroyWindow("plate_judge");

    int resultJu = PlateJudge::instance()->plateJudge(matVec, resultVec);

//    if (0 != resultJu)


    cout << "plate_judge_img" << endl;
    num = resultVec.size();
    for (size_t j = 0; j < num; j++) {
      Mat resultMa = resultVec[j];
      QImage image = QImage((const uchar*)resultMa.data,resultMa.cols,resultMa.rows,QImage::Format_RGB888).rgbSwapped();
      image = image.scaled(ui->label_5->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
      ui->label_5->setPixmap(QPixmap::fromImage(image));
    }
}
