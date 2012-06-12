/*
 *  sensor.h
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

/* Include guard */
#ifndef __SENSOR_H__
#define __SENSOR_H__

/* Namespace */
namespace ComLibSim
{

/* Class Sensor */
class Sensor
{
public:
  /* Constructor and destructor */
  Sensor () {}
  Sensor (const double x,
          const double y,
          const double adata = 20.0)
  {
    m_x = x;
    m_y = y;
    m_adata = adata;
    m_rdata = adata;
  }
  virtual ~Sensor () {}

  /* Get methods */
  const double get_x     () const { return m_x; }
  const double get_y     () const { return m_y; }
  const double get_adata () const { return m_adata; }
  const double get_rdata () const { return m_rdata; }

  const double get_distance (const double x,
                             const double y);
  const double get_com_rate (const double x,
                             const double y);

protected:
  /* Variables */
  double m_x,
         m_y,
         m_adata,
         m_rdata;
};

} /* namespace */

#endif /* __SENSOR_H__ */
