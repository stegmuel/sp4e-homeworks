#include "material_point.hh"

/* -------------------------------------------------------------------------- */
void MaterialPoint::printself(std::ostream& stream) const {
  Particle::printself(stream);
  stream << " " << temperature << " " << heat_rate;
}

/* -------------------------------------------------------------------------- */

void MaterialPoint::initself(std::istream& sstr) {
  Particle::initself(sstr);
  sstr >> temperature  >> heat_rate;;
}

void MaterialPoint::setHeatRate(Real heat_rate){
  this->heat_rate = heat_rate;
}


void MaterialPoint::setTemperature(Real temperature){
  this->temperature = temperature;
}