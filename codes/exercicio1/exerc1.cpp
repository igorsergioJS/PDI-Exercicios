#include <iostream>
#include <opencv2/opencv.hpp>
const int MAX = 100;

int main(int, char**){
  cv::Mat image;
  cv::Vec3b val;
  char nome_img[MAX] = "biel.png"; // Definir inicialmente o nome do arquivo a ser editado.

  int x1, x2, y1, y2;

  std:: cout << "Inserir x1, x2, y1, y2:" << std::endl;
  std:: cin >> x1 >> x2 >> y1 >> y2;

  image= cv::imread(nome_img,cv::IMREAD_GRAYSCALE);
  if(!image.data)
    std::cout << "nao abriu" << nome_img << std::endl;

  cv::namedWindow("janela", cv::WINDOW_AUTOSIZE);

  for(int i=x1;i<x2;i++){ // 200 to 210
    for(int j=y1;j<y2;j++){ // 10 to 200
      image.at<uchar>(i,j)= 255 - image.at<uchar>(i,j);
    }
  }

  cv::imshow("janela", image);
  cv::imwrite("negativo.png", image);
  cv::waitKey();


  return 0;
}

