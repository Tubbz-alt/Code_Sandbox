#include <iostream>

#include <GeoImage.h>

using namespace cv;
using namespace std;

int main( int argc, char* argv[] ){


    cout << "usage: ./hello_geoworld   <Image Name>" << endl;
    if( argc < 2 )
        return 0;
    
    //create a GeoImage using the input filename
    GEO::GeoImage geoimg( argv[1], true );

    //pull out the OpenCV Mat Object
    Mat img = geoimg.get_image();
    
    if( img.type() == CV_16UC1 )
        cout << "CV_16UC1" << endl;
    if( img.type() == CV_16SC1 )
        cout << "CV_16US1" << endl;
    
    imwrite("out1.jpg", img);
    for( int i=0; i<img.rows; i++)
    for( int j=0; j<img.cols; j++)
        img.at<ushort>(j,i) = abs(img.at<ushort>(j,i) - 255*255);

    
    imwrite("out2.jpg", img);

    //create an output filename
    string output_filename = "result.ntf";

    //lets pretend you want to write a new image, but want to reuse the 
    // input image's header data
    GEO::GeoHeader_Info* header_info = geoimg.get_header();
   
    //lets change some header info
    header_info->set_header_item("NITF_ISORCE","HELLO");
    header_info->set_header_item("NITF_ISREL","WORLD");

    //write header back to file
    GEO::GDAL_Data::write( output_filename, img, header_info );


    return 0;
}
