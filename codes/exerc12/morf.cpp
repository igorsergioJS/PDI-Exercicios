#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
  cv::Mat image, erosao, dilatacao, abertura, fechamento, abertfecha;
  cv::Mat str;
  cv::Mat img1, img2;

  if (argc != 2) {
    std::cout << "morfologia entrada saida\n";
  }

  image = cv::imread(argv[1], cv::IMREAD_UNCHANGED);


  if(image.empty()) {
    std::cout << "Erro ao carregar a imagem: " << argv[1] << std::endl;
    return -1;
  }

  // elemento estruturante
  str = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));


  cv::dilate(image, img1, str);
  str = cv::getStructuringElement(cv::MORPH_ELLIPSE , cv::Size(2, 2));
  cv::dilate(img1,img2,str);
  cv::dilate(img2, img1, str);
  cv::dilate(img1,img2,str);

  str = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
  cv::erode(img2, img1, str);
  cv::erode(img1, img2, str);
  cv::erode(img2, img1, str);
  cv::erode(img1, img2, str);
  cv::erode(img2, img1, str);
  cv::erode(img1, img2, str);
  cv::erode(img2, img1, str);
  str = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));
  cv::erode(img1, img2, str);

  str = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

  cv::dilate(img2, img1, str);
  cv::dilate(img1,img2,str);
  cv::dilate(img2, img1, str);
  cv::dilate(img1,img2,str);
  cv::dilate(img2, img1, str);
  cv::dilate(img1,img2,str);
  cv::dilate(img2, img1, str);

  str = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
  cv::erode(img1, img2, str);
  cv::erode(img2, img1, str);
  cv::erode(img1, img2, str);
  cv::erode(img1, img2, str);
  cv::erode(img2, img1, str);


  cv::Mat matArray[] = {image, img1, img2};
  cv::hconcat(matArray, 3, image);

  cv::imshow("morfologia", image);
  cv::imwrite("clock_morf.png",img1);

  cv::waitKey();
  return 0;
}
