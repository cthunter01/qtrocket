#include "SphericalGravityModel.h"

#include "utils/math/Constants.h"

#include <cmath>
#include <tuple>

namespace sim
{

SphericalGravityModel::SphericalGravityModel()
{

}

SphericalGravityModel::~SphericalGravityModel()
{

}

std::tuple<double, double, double> SphericalGravityModel::getAccel(double x, double y, double z)
{
   // Convert x, y, z from meters to km. This is to avoid potential precision losses
   // with using the earth's gravitation parameter in meters (14 digit number).
   // GM in kilometers is much more manageable.
   // An alternative is to use quadruple precision, but that may
   // take a lot more computation time and I think this will be fine.
   double x_km = x / 1000.0;
   double y_km = y / 1000.0;
   double z_km = z / 1000.0;

   double r_km = std::sqrt(x_km * x_km + y_km * y_km + z_km * z_km);
   
   double accelFactor = - utils::math::Constants::earthGM_km / std::sqrt(r_km * r_km * r_km);
   double ax = accelFactor * x_km * 1000.0;
   double ay = accelFactor * y_km * 1000.0;
   double az = accelFactor * z_km * 1000.0;

   return std::make_tuple(ax, ay, az);
}


}