/*
 *  sensorsettings.h
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
#ifndef __SENSORSETTINGS_H__
#define __SENSORSETTINGS_H__

/* Include files */
#include <glibmm/ustring.h>

/* Namespace */
namespace ComLibSim
{

/* Class SensorSettings */
class SensorSettings
{
public:
  /* Constructor and destructor */
  SensorSettings () {}
  SensorSettings (const gdouble x,
                  const gdouble y,
                  const gdouble max_rate,
                  const gdouble data)
  {
    m_X = x;
    m_Y = y;
    m_MaxRate = max_rate;
    m_Data = data;
  }
  virtual ~SensorSettings () {}

  /* Get methods */
  double get_x        () const { return m_X; }
  double get_y        () const { return m_Y; }
  double get_max_rate () const { return m_MaxRate; }
  double get_data     () const { return m_Data; }

  /* Set methods */
  void set_x        (const gdouble x)        { m_X = x; }
  void set_y        (const gdouble y)        { m_Y = y; }
  void ser_max_rate (const gdouble max_rate) { m_MaxRate = max_rate; }
  void set_data     (const gdouble data)     { m_Data = data; }

protected:
  /* Variables */
  gdouble m_X,
          m_Y,
          m_MaxRate,
          m_Data;
};
  
} /* namespace */

#endif /* __SENSORSETTINGS_H__ */
