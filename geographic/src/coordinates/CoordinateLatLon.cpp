#include "CoordinateLatLon.h"

using namespace cv;
using namespace std;

/**
 * Default constructor for Lat Lon Coordinate
*/
CoordinateLatLon::CoordinateLatLon(){
    lat = 0;
    lon = 0;
}

CoordinateLatLon::CoordinateLatLon( const double& latDD, const double& lonDD ){

    lat = latDD;
    lon = lonDD;

}


CoordinateLatLon::CoordinateLatLon( const Point2f& coord ){

    lat = coord.y;
    lon = coord.x;
}

CoordinateLatLon::CoordinateLatLon( const int& latDeg, const double& latMin, 
                                    const int& lonDeg, const double& lonMin){
        
    throw string("ERROR: Not Implemented");
}

CoordinateLatLon::CoordinateLatLon( const int& latDeg, const int&    latMin, const double& latSec
                                    const int& lonDeg, const int&    lonMin, const double& lonSec ){

    throw string("ERROR: Not Implemented");
}


private:

double lat; /*< Latitude  */
double lon; /*< Longitude */

};

#endif


#endif