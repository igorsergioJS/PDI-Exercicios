#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char**argv) {
  cv::Mat imagemPortadora, imagemEscondida, imagemFinal;
  cv::Vec3b valPortadora, valEscondida, valFinal;
  int nbits = 3;

  imagemPortadora = cv::imread(argv[1], cv::IMREAD_COLOR);
  //imagemEscondida = cv::imread(argv[2], cv::IMREAD_COLOR);


  /*
  if (imagemPortadora.rows != imagemEscondida.rows ||
      imagemPortadora.cols != imagemEscondida.cols) {
    std::cout << "imagens devem ter o mesmo tamanho" << std::endl;
    return (-1);
  }
  */

  //imagemFinal = imagemPortadora.clone();

  for (int i = 0; i < imagemPortadora.rows; i++) {
    for (int j = 0; j < imagemPortadora.cols; j++) {
      valPortadora = imagemPortadora.at<cv::Vec3b>(i, j);
      valEscondida = imagemEscondida.at<cv::Vec3b>(i, j);
      valPortadora[0] = valPortadora[0] >> nbits << nbits;
      valPortadora[1] = valPortadora[1] >> nbits << nbits;
      valPortadora[2] = valPortadora[2] >> nbits << nbits;
      valEscondida[0] = valEscondida[0] >> (8-nbits);
      valEscondida[1] = valEscondida[1] >> (8-nbits);
      valEscondida[2] = valEscondida[2] >> (8-nbits);
    }
  }
  imwrite("esteganografia.png", imagemEscondida);
  return 0;
}
