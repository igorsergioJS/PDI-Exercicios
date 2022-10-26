#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv) {
  cv::Mat image, realce;
  int width, height;
  int nobjects, nholes;

  cv::Point p;
  image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

  if (!image.data) {
    std::cout << "imagem nao carregou corretamente\n";
    return (-1);
  }

  width = image.cols;
  height = image.rows;
  std::cout << width << "x" << height << std::endl;

  p.x = 0;
  p.y = 0;

  //Remover objetos dos cantos
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (image.at<uchar>(i, j) == 255 && (i == 0 || i == width - 1 || j == 0 || j == height - 1)) {
        p.x = j;
        p.y = i;
        cv::floodFill(image, p, 0);
      }
    }
  }
  cv::imwrite("cantos.png", image);

  //Pintar o fundo de outro tom de cinza
  p.x = 0;
  p.y = 0;
  cv::floodFill(image, p, 100);
   cv::imwrite("fundocinza.png", image);


  // busca objetos presentes
  nobjects = 0;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (image.at<uchar>(i, j) == 255) {
        // achou um objeto
        nobjects++;
        // para o floodfill as coordenadas
        // x e y sao trocadas.
        p.x = j;
        p.y = i;
        // preenche o objeto com o contador
        cv::floodFill(image, p, nobjects);
      }
    }
  }

  cv::imwrite("contagemTotal.png", image);

    nholes = 0;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (image.at<uchar>(i, j) == 0) {
        nholes++;
        p.x = j;
        p.y = i;
        cv::floodFill(image, p, nholes);
      }
    }
  }


  cv::imwrite("contagemBuracos.png", image);


  std::cout << "a figura tem: " << nobjects << " objetos, sendo: \n"<< nobjects - nholes << " bolhas completas e " << nholes << " buracos. \n";

  return 0;
}
