#include <iostream>
#include <opencv2/opencv.hpp>
const int MAX = 100;

int main(int, char**){
  cv::Mat image, img_clone;

  int largura, altura;

  char nome_img[MAX] = "biel.png"; // Definir inicialmente o nome do arquivo a ser editado.


  image= cv::imread(nome_img,cv::IMREAD_GRAYSCALE);
  if(!image.data)
    std::cout << "nao abriu" << nome_img << std::endl;

  cv::namedWindow("janela", cv::WINDOW_AUTOSIZE);

      largura = image.size().width;
      altura = image.size().height;

   // Primeiro quadrante
    img_clone = image.clone();

    for(int i=0;i<altura/2;i++){
    for(int j=0;j<largura/2;j++){
      img_clone.at<uchar>(i,j) = image.at<uchar>(i+altura/2,j+largura/2);
      img_clone.at<uchar>(i+altura/2,j+largura/2) = image.at<uchar>(i,j);
      img_clone.at<uchar>(i+altura/2,j) = image.at<uchar>(i,j+largura/2);
      img_clone.at<uchar>(i,j+largura/2) = image.at<uchar>(i+altura/2,j);
    }
  }


  cv::imshow("janela", img_clone);
  imwrite("Troca.png", img_clone);
  cv::waitKey();


  return 0;
}

