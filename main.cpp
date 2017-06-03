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
     Mat image_original = imread(argc == 2 ? argv[1] : "ear.jpg", 1);
     Mat image_gray = imread(argc == 2 ? argv[1] : "ear.jpg", CV_LOAD_IMAGE_GRAYSCALE);

     //imshow("image", image_original);

     Mat image_lbp = ELBP(image_gray,2,16);
     imshow("image", image_lbp);

     int rows = image_gray.rows;
     int cols = image_gray.cols;

     //printf("%d %d", rows, cols);
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
     }

    //printf("%d %d", cols/block, rows/block);



     waitKey(0);
     return 0;
 }
