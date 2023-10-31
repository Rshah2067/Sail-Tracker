#include <math.h>
class heaversine {
   private: 
        // these cordinates define the 0 for the system and all later x and y measurements are relative to this 0 point
        //these values should be set awhen the 
        double initialLat = 0;
        double initialLong =0;
        //note this is a nominal radius, due to geological things this is an approximation
        int r = 6371;
        double havsin(double theta){
            return square(sin(theta/2));
        }
        double havcsin(double theta){
            return square(cos(theta/2));
        }
    public:
        heaversine(){

        }
        heaversine(double initlat, double initlong){
            initialLat = initlat;
            initialLong = initlong;
        }
        //method to set initial position if a reset is needed
        void setInitial(double initlat, double initlong){
            initialLat = initlat;
            initialLong = initlong;
        }
        //calculate the distance from a lat and long to the intial lat long
        //based on haversine formula where phi is lat and lambda is long
        double distance(double lng, double lat){
            //distance in meters
            double dist = 2*r*asin(sqrt(havsin(initialLat-lat)+cos(initialLat)*cos(lat)*havcsin(initialLong-lng)))*1000;
        return dist;
        }
        //Calculate the x displacement from initial position in meters
        // double deltaX (double dist){
        //     double x = arcsin;
        //     return x;
        // }
        // double deltaY (double dist){
        //     double y;
        //     return y;
        // }



    

};