#include <unistd.h>

//#####################
// TODO:
// query error codes
//#####################

#include "Iota300Fake.h"

///
///
///
Iota300Fake::Iota300Fake( const ioport_t ioPort )
    :VIota300(ioPort)
{
  circulatorStatus_ = 0;
  flow_ = 20;
}

///
/// returns success flag
///
bool Iota300Fake::SetFlow( const float flow ) const {

  if( flow > __IOTA300_UPPER_FLOW_LIMIT || flow < __IOTA300_LOWER_FLOW_LIMIT ) {
    std::cerr << " [Iota300Fake::SetFlow] ** ERROR: Flow Q="
	      << flow << " exceeds soft limits." << std::endl;
    std::cerr << "  > (s. Iota300Fake class definition)" << std::endl;
    return false;
  }

  std::cout << " [Iota300Fake::SetFlow] -- FAKE: Setting Flow = " 
	    << flow << "." << std::endl;

  flow_ = flow;

  return true;

}

///
/// returns success flag
///
bool Iota300Fake::SetPressure( const float pressure ) const {

  if( pressure > __IOTA300_UPPER_PRESSURE_LIMIT || pressure < __IOTA300_LOWER_PRESSURE_LIMIT ) {
    std::cerr << " [Iota300Fake::SetPressure] ** ERROR: p="
	      << pressure << " exceeds soft limits." << std::endl;
    std::cerr << "  > (s. Iota300Fake class definition)" << std::endl;
    return false;
  }

  std::cout << " [Iota300Fake::SetPressure] -- FAKE: Setting p = " 
	    << pressure << "." << std::endl;

  pressure_ = pressure;

  return true;

}
///
/// returns success flag
///
bool Iota300Fake::SetStatus( const float status ) const {

  if( status > __IOTA300_UPPER_STATUS_LIMIT || status < __IOTA300_LOWER_STATUS_LIMIT ) {
    std::cerr << " [Iota300Fake::SetStatus] ** ERROR: Status ="
	      << status << " exceeds soft limits." << std::endl;
    std::cerr << "  > (s. Iota300Fake class definition)" << std::endl;
    return false;
  }

  std::cout << " [Iota300Fake::SetStatus] -- FAKE: Setting Status = " 
	    << status << "." << std::endl;

  status_ = status;

  return true;

}


///
///
///
float Iota300Fake::GetFlow( void ) const
{
  std::cout << " [Iota300Fake::GetFlow] -- FAKE: Returning Q = "
	    << flow_ << std::endl;
  usleep( 10000 );
  return flow_ + (double)rand() / RAND_MAX;
}

///
///
///
float Iota300Fake::GetPressure( void ) const
{
  std::cout << " [Iota300Fake::GetPressure] -- FAKE: Returning Q = "
	    << pressure_ << std::endl;
  usleep( 10000 );
  return pressure_;
}

///
///
///
float Iota300Fake::GetStatus( void ) const
{
  std::cout << " [Iota300Fake::GetStatus] -- FAKE: Returning Status = "
	    << status_ << std::endl;
  usleep( 10000 );
  return status_;
}

///
///
///
void Iota300Fake::Device_Init( void ) {

  
}