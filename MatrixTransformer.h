//
// Created by Gabriel Spranger Rojas on 6/28/20.
//

#ifndef PROYECTO_MATRIXTRANSFORMER_H
#define PROYECTO_MATRIXTRANSFORMER_H

#include <vector>
#include <cinttypes>
#include <ctime>
#include <cstdlib>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

enum method {
    _601,
    _709,
    _240
};

static size_t instance_number = 0;

class MatrixTransformer {

private:
    method _method;
    Mat img;
    float umbral;
    vector<vector<int>> transformed_img = {};

public:
    MatrixTransformer() { ++instance_number; }
    MatrixTransformer(const string& imgpath, method _method, float umbral): _method{_method}, umbral{umbral} {
        ++instance_number;
        this->img = imread(imgpath, IMREAD_COLOR);
    }
    void setMethod(method method) {
        _method = method;
    }

private:
    vector<vector<int>> apply_transformation(const float coefficients[3]) {
        vector<vector<int>> matrix = {};
        float luma;
        for (int r = 0; r < img.rows; ++r) {
            vector<int> fila = {};
            luma = 0.0f;
            for (int c = 0; c < img.cols; ++c) {
                // [0] blue channel, [1] green channel, [2] red channel
                // luma = brightness
                luma += float(img.at<cv::Vec3b>(r, c)[0]) * coefficients[0];
                luma += float(img.at<cv::Vec3b>(r, c)[1]) * coefficients[1];
                luma += float(img.at<cv::Vec3b>(r, c)[2]) * coefficients[2];
                // si luma < umbral, push 1, sino, push 0
                //fila.push_back(luma < umbral);
                if (luma < umbral)
                    fila.push_back(1);
                else
                    fila.push_back(0);
                luma = 0.0f;
            }
            matrix.push_back(fila);
        }
        return matrix;
    }

public:
    // funcion que transforma una imagen a 0s y 1s
    vector<vector<int>> transform() {
        switch (_method) {
            case _601: {
                const float __601[3] = {0.114f, 0.587f, 0.299f};
                transformed_img = apply_transformation(__601);
                return transformed_img;
            }
            case _709: {
                const float __709[3] = {0.0722f, 0.7152f, 0.2126f};
                transformed_img = apply_transformation(__709);
                return transformed_img;
            }
            case _240: {
                const float __240[3] = {0.087f, 0.701f, 0.212f};
                transformed_img = apply_transformation(__240);
                return transformed_img;
            }
            default: {
                printf("Error en transformar la imagen a una matriz de 0s y 1s.\n");
                return {};
            }
        }
    }

    void print_transformed_img() {
        for (int i = 0; i < transformed_img.size(); ++i) {
            for (int j = 0; j < transformed_img[i].size(); ++j) {
                if (transformed_img[i][j]) {
                    cout << '\'' << " ";
                } else {
                    cout << '*' << " ";
                }
            }
            cout << endl;
        }
    }

    void show_image() {
        string win_name = "Imagen ";
        ///Hack para tener varias ventanas
        win_name += to_string(rand()%1000);
        imshow(win_name, img);
    }

    ~MatrixTransformer() {
        --instance_number;
    }
};

#endif //PROYECTO_MATRIXTRANSFORMER_H
