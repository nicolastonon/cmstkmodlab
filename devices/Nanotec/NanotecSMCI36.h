#ifndef __NANOTECSMCI36_H
#define __NANOTECSMCI36_H

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <utility>
#include <fstream>
#include <cmath>

#include "VNanotecSMCI36.h"
#include "NanotecComHandler.h"

class NanotecSMCI36 : public VNanotecSMCI36
{
 public:

  NanotecSMCI36( const ioport_t );
  ~NanotecSMCI36();

 public:

  bool DeviceAvailable() const;

  std::string GetFirmwareVersion() const;

 private:

  void StripBuffer( char* ) const;
  void DeviceInit();

  NanotecComHandler* comHandler_;
  bool isDeviceAvailable_;
};

#endif
