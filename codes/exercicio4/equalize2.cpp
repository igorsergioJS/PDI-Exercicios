#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv){
  cv::Mat image, cinza, saida, histG, histE;
  int width, height;
  cv::VideoCapture cap;
  std::vector<cv::Mat> planes;
  int nbins = 64;
  float range[] = {0, 255};
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

  int histw = nbins, histh = nbins/2;
  cv::Mat histGimg(histh, histw, CV_BGR2GRAY, Scalar(0));
  cv::Mat histEimg(histh, histw, CV_BGR2GRAY, Scalar(0));


  while(1){
    //captura a imagem
    cap >> image;
    //transforma para escala de cinza
    cvtColor( image, cinza, CV_BGR2GRAY );
    //equaliza o histograma
    equalizeHist( cinza, saida );

    calcHist(&cinza, 1, 0, Mat(), histG, 1, &nbins, &histrange, uniform, acummulate);

    calcHist(&saida, 1, 0, Mat(), histE, 1, &nbins, &histrange, uniform, acummulate);

    normalize(histG, histG, 0, histGimg.rows, NORM_MINMAX, -1, Mat());
    normalize(histE, histE, 0, histEimg.rows, NORM_MINMAX, -1, Mat());

    histGimg.setTo(Scalar(0));
    histEimg.setTo(Scalar(0));

    for(int i=0; i<nbins; i++){
      line(histGimg,
           Point(i, histh),
           Point(i, histh-cvRound(histG.at<float>(i))),
           Scalar(255), 1, 8, 0);
      line(histEimg,
           Point(i, histh),
           Point(i, histh-cvRound(histE.at<float>(i))),
           Scalar(255), 1, 8, 0);
    }

    histGimg.copyTo(cinza(cv::Rect(0, 0,nbins, histh)));
    histEimg.copyTo(saida(cv::Rect(0, 0,nbins, histh)));

    imshow("Original", saida);
    imshow("cinza", cinza);

    key = cv::waitKey(30);
    if(key == 27) break;
  }
  return 0;
}

