 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/core/core.hpp"
 #include "opencv2/imgproc/imgproc.hpp"
 #include "lbp.hpp"
 #include "histogram.hpp"

 #include <iostream>
 #include <cstdio>
 #include <vector>

 using namespace std;
 using namespace cv;
 using namespace lbp;

 int block = 5;

  int main(int argc, char** argv)
 {
     //ear2-4 7-9 png is from yogi
     //ear5-6 png is from lan
     Mat image_original = imread(argc == 2 ? argv[1] : "ear1.png", 1);
     // change input training picture
     Mat image_train = imread(argc == 2 ? argv[1] : "./ears/ear-train2-left.png", CV_LOAD_IMAGE_GRAYSCALE);
     Mat image_adam = imread(argc == 2 ? argv[1] : "./moreears/ear-adamb-left.png", CV_LOAD_IMAGE_GRAYSCALE);
     Mat image_yogi = imread(argc == 2 ? argv[1] : "./moreears/ear-yogib-left.png", CV_LOAD_IMAGE_GRAYSCALE);
     Mat image_lan = imread(argc == 2 ? argv[1] : "./moreears/ear-lanb-left.png", CV_LOAD_IMAGE_GRAYSCALE);

     Mat lbp_train = ELBP(image_train,2,16);
     Mat lbp_adam = ELBP(image_adam,2,16);
     Mat lbp_yogi = ELBP(image_yogi,2,16);
     Mat lbp_lan = ELBP(image_lan,2,16);

    Mat stats_train = spatial_histogram(lbp_train, 65536);
    Mat stats_adam = spatial_histogram(lbp_adam, 65536);
    Mat stats_yogi = spatial_histogram(lbp_yogi, 65536);
    Mat stats_lan = spatial_histogram(lbp_lan, 65536);

    double result_adam = chi_square_<unsigned short>(stats_train,stats_adam);
    printf("adam: %f\n",result_adam);
    double result_yogi = chi_square_<unsigned short>(stats_train,stats_yogi);
    printf("yogi: %f\n",result_yogi);
    double result_lan = chi_square_<unsigned short>(stats_train,stats_lan);
    printf("lan: %f\n",result_lan);

     waitKey(0);
     return 0;

     //imshow("image", image_original);

     //Mat image_lbp = ELBP(image_gray,2,16);
     //imshow("image", image_lbp);

     /*int rows = image_gray.rows;
     int cols = image_gray.cols;

     printf("%d %d", rows, cols);
     printf("%d",rows%block);


     vector<Mat> segment;
     Mat region_frame;

     int width = cols/block;
     int height = rows/block;



     for(int i=0;i<block;i++)
     {
        for(int j=0;j<block;j++)
        {
            int x_start = (cols/block)*i;
            int y_start = (rows/block)*j;
            Rect region = Rect(x_start, y_start,width,height);
            region_frame = image_gray(region);
            segment.push_back(ELBP(region_frame,2,16));

        }
     }*/

    //printf("%d %d", cols/block, rows/block);
    //imshow("segment0",segment[0]);
    //cout<<segment[10].type()<<endl;



 }


