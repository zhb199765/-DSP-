#ifndef EASYPR_PLATE_HPP
#define EASYPR_PLATE_HPP
#include <include/easypr.h>
#include <ctime>
#include <fstream>
#include <list>
#include <memory>
#include <numeric>
#include <unordered_map>
#include "E:/Qt_test/EasyPR-master/EasyPR-master/include/easypr/core/core_func.h"
#include "E:/Qt_test/EasyPR-master/EasyPR-master/include/easypr/util/util.h"
#include "thirdparty/xmlParser/xmlParser.h"
#include "E:/Qt_test/EasyPR-master/EasyPR-master/include/easypr/core/params.h"
#include "config.hpp"
#include "result.hpp"
namespace easypr {

namespace demo {

using namespace cv;
using namespace std;

int test_plate_locate() {
  cout << "test_plate_locate" << endl;

  //const string file = "resources/video/1.jpg";
  VideoCapture cap(0);
  VideoCapture video_capture;
  video_capture.set(CV_CAP_PROP_FPS, 12);
  video_capture.set(CV_CAP_PROP_EXPOSURE, -12.0);
  video_capture.open(0);
  video_capture.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
  Mat frame;
  Mat edges;
  Mat src;
  while (1)
  {
      cap >> frame;
      src = frame;
      cvtColor(frame, edges, 0);
      imshow("a", edges);
      vector<cv::Mat> resultVec;
      CPlateLocate plate;
  //plate.setDebug(0);
  //plate.setLifemode(true);
      int result = plate.plateLocate(src, resultVec);
      if (result == 0) {
          size_t num = resultVec.size();
          for (size_t j = 0; j < num; j++) {
              cv::Mat resultMat = resultVec[j];
              imshow("plate_locate", resultMat);
          }
          return 0;
      }
      destroyWindow("plate_locate");
      return result;
  }
}

int test_plate_judge() {
  cout << "test_plate_judge" << endl;

  cv::Mat src = imread("E:\\Qt_test\\EasyPR-master\\EasyPR-master\\resources\\image\\video\\2.jpg");

  vector<cv::Mat> matVec;
  vector<cv::Mat> resultVec;

  CPlateLocate lo;
  lo.setDebug(1);
  lo.setLifemode(true);

  int resultLo = lo.plateLocate(src, matVec);

  if (0 != resultLo) return -1;

  cout << "plate_locate_img" << endl;
  size_t num = matVec.size();
  for (size_t j = 0; j < num; j++) {
    Mat resultMat = matVec[j];
    imshow("plate_judge", resultMat);
    waitKey(0);
  }
  destroyWindow("plate_judge");

  int resultJu = PlateJudge::instance()->plateJudge(matVec, resultVec);

  if (0 != resultJu) return -1;

  cout << "plate_judge_img" << endl;
  num = resultVec.size();
  for (size_t j = 0; j < num; j++) {
    Mat resultMat = resultVec[j];
    imshow("plate_judge", resultMat);
    waitKey(0);
  }
  destroyWindow("plate_judge");

  return resultJu;
}

int test_plate_detect() {
  cout << "test_plate_detect" << endl;

  cv::Mat src = imread("resources/video/3.jpg");

  vector<CPlate> resultVec;
  CPlateDetect pd;
  pd.setPDLifemode(true);

  int result = pd.plateDetect(src, resultVec);
  if (result == 0) {
    size_t num = resultVec.size();
    for (size_t j = 0; j < num; j++) {
      CPlate resultMat = resultVec[j];

      imshow("plate_detect", resultMat.getPlateMat());
      waitKey(0);
    }
    destroyWindow("plate_detect");
  }

  return result;
}

int test_plate_recognize() {

      cout << "test_plate_recognize" << endl;

  //Mat src = imread("resources/video/7.jpg");
  VideoCapture cap(0);
  VideoCapture video_capture;
  video_capture.set(CV_CAP_PROP_FPS, 12);
  video_capture.set(CV_CAP_PROP_EXPOSURE, -12.0);
  video_capture.open(0);
  video_capture.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
  Mat frame;
  Mat edges;
  Mat src;

      cap >> frame;
      src = frame;
      CPlateRecognize pr;
      pr.setLifemode(true);
      pr.setDebug(false);
      pr.setMaxPlates(1);
      //pr.setDetectType(PR_DETECT_COLOR | PR_DETECT_SOBEL);
      pr.setDetectType(easypr::PR_DETECT_CMSER);

      //vector<string> plateVec;
      vector<CPlate> plateVec;

      int result = pr.plateRecognize(src, plateVec);
      //int result = pr.plateRecognizeAsText(src, plateVec);
      if (result == 0) {
          size_t num = plateVec.size();
          for (size_t j = 0; j < num; j++) {
              cout << "plateRecognize: " << plateVec[j].getPlateStr() << endl;

          }
      }
      if (result != 0)
          cout << "result:" << result << endl;

      return result;

}
}
}

#endif  // EASYPR_PLATE_HPP
