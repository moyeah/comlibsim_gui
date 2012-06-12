/*
 *  sensor.cpp
 *
 *  Copyright (C) 2011-2012  Daniel Sousa   <da.arada@gmail.com>
 *  Copyright (C) 2011-2012  Jorge Estrela  <jes@isep.ipp.pt>
 *
 *  Autor:
 *    Daniel Sousa  <da.arada@gmail.com>
 *
 *  Orientador:
 *    Jorge Estrela  <jes@isep.ipp.pt>
 */

/* Include files */
#include "sensor.h"
#include <cmath>

/* Namespace */
namespace ComLibSim
{

/* Method get_distance */
const double Sensor::get_distance (const double x,
                                   const double y)
{
  return sqrt(pow (x-m_x, 2) + pow (y-m_y, 2));
}

/* Method get_com_rate */
const double Sensor::get_com_rate (const double x,
                                   const double y)
{
  double distance = get_distance (x, y);
  if (distance < 20.0)
    return 4;
  if (distance < 80.0)
    return 12 * pow (10, -0.024*distance);
  return 0;
}

} /* namespace */
