#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv){
  Mat image, hist0, hist1, cinza;
  int width, height;
  cv::VideoCapture cap;
  std::vector<cv::Mat> planes;
  int nbins = 64;
  float range[] = {0, 256};
  double comparar;
  int cont = 0;
  double limiar = 0.99;
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;
  int key;

	cap.open(1);

  if(!cap.isOpened()){
    std::cout << "cameras indisponiveis";
    return -1;
  }

  cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
  width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
  height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

  std::cout << "largura = " << width << std::endl;
  std::cout << "altura  = " << height << std::endl;

    calcHist(&cinza, 1, 0, Mat(), hist0, 1, &nbins, &histrange, uniform, acummulate);

  while(1){
    //captura a imagem
    cap >> image;

    cvtColor( image, cinza, CV_BGR2GRAY );

    calcHist(&cinza, 1, 0, Mat(), hist1, 1, &nbins, &histrange, uniform, acummulate);

    comparar = compareHist(hist0, hist1, CV_COMP_CORREL);

    if(comparar < limiar)
    {
        std::cout << "Movimento Detectado" << "(" << cont << ")" << "!!! \n ";
        cont++;
    }
    imshow("image", image);

    calcHist(&cinza, 1, 0, Mat(), hist0, 1, &nbins, &histrange, uniform, acummulate);

    key = cv::waitKey(30);
    if(key == 27) break;
  }
  return 0;
}
