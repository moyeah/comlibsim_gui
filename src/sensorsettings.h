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
  SensorSettings (const Glib::ustring& tag,
                  bool                 online,
                  const gdouble        x,
                  const gdouble        y,
                  const guint          adata,
                  const Glib::ustring& type)
  {
    m_Tag = tag;
    m_Online = online;
    m_X = x;
    m_Y = y;
    m_Adata = adata;
    m_Type = type;
  }
  virtual ~SensorSettings () {}

  /* Get methods */
  const std::string& get_tag ()    const { return m_Tag.raw (); }
  bool               get_online () const { return m_Online; }
  double             get_x ()      const { return m_X; }
  double             get_y ()      const { return m_Y; }
  unsigned int       get_adata ()  const { return m_Adata; }
  const std::string& get_type ()   const { return m_Type.raw (); }

  /* Set methods */
  void set_tag    (const Glib::ustring& tag)  { m_Tag = tag; }
  void set_online (bool online)               { m_Online = online; }
  void set_x      (const gdouble x)           { m_X = x; }
  void set_y      (const gdouble y)           { m_Y = y; }
  void set_adata  (const guint adata)         { m_Adata = adata; }
  void set_type   (const Glib::ustring& type) { m_Type = type; }

  /* Other methods */
  const std::string get_online_as_string () const
  {
    return m_Online ? "true" : "false";
  }

protected:
  /* Variables */
  Glib::ustring m_Tag,
                m_Type;
  bool          m_Online;
  gdouble       m_X,
                m_Y;
  guint         m_Adata;
};
  
} /* namespace */

#endif /* __SENSORSETTINGS_H__ */
