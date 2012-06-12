/*
 *  clustersettings.h
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
#ifndef __CLUSTERSETTINGS_H__
#define __CLUSTERSETTINGS_H__

/* Include files */
#include "sensorsettings.h"
#include "modelcolumns.h"
#include <glibmm/ustring.h>
#include <gtkmm/liststore.h>

/* Namespace */
namespace ComLibSim
{

/* Class ClusterSettings */
class ClusterSettings
{
public:
  /* Constructor and destructor */
  ClusterSettings () {}
  ClusterSettings (const Glib::ustring& name) { m_Name = name; }
  virtual ~ClusterSettings () {}

  /* Get methods */
  const std::string& get_name ()                 { return m_Name.raw (); }
  const std::list<SensorSettings> get_sensors () { return m_Sensors; }

  /* Set methods */
  void set_name (const Glib::ustring& name) { m_Name = name; }
/*  void set_sensors (Glib::RefPtr<Gtk::ListStore> sensors)
  {
    m_sensors = sensors;
  }
*/

  /* Other methods */
  bool XML_to_TreeModel (const Glib::ustring& filename,
                         Glib::RefPtr<Gtk::ListStore> sensors_list);
  void TreeModel_to_XML (const Glib::ustring& filename,
                         Glib::RefPtr<Gtk::ListStore> sensors_list);

protected:
  /* Variables */
  Glib::ustring             m_Name;
  std::list<SensorSettings> m_Sensors;
  ModelColumns              m_Columns;

  /* Signal handlers */
  bool on_foreach_iter (const Gtk::TreeModel::iterator& iter);
};

} /* namespace */

#endif /* __CLUSTERSETTINGS_H__ */
