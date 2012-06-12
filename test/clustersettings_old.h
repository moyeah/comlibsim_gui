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
#include "modelcolumns.h"
#include <glibmm/ustring.h>
#include <glibmm/refptr.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/window.h>
#include <string>
#include <list>

/* Namespace */
namespace ComLibSim
{

/* Class SensorSettings */
class SensorSettings
{
public:
  /* Constructor and destructor */
  SensorSettings ();
  SensorSettings (const Glib::ustring& tag,
                  bool                online,
                  const gdouble       x,
                  const gdouble       y,
                  const guint         adata,
                  const Glib::ustring& type);
  virtual ~SensorSettings ();

  /* Set methods */
  void set_tag               (const Glib::ustring& tag);
  void set_online            (bool online);
  void set_x_coord           (const gdouble x);
  void set_y_coord           (const gdouble y);
  void set_amount_data       (const guint adata);
  void set_type              (const Glib::ustring& type);
// TODO
//  void set_from_TreeModelRow ();
//  void set_to_TreeModelRow ();

  /* Set methods */
  Glib::ustring get_tag         ();
  bool          get_online      ();
  gdouble       get_x_coord     ();
  gdouble       get_y_coord     ();
  guint         get_amount_data ();
  Glib::ustring get_type        ();

protected:
  /* Variables */
  Glib::ustring m_Tag,
                m_Type;
  bool          m_Online;
  gdouble       m_Xcoord,
                m_Ycoord;
  guint         m_Adata;
};

/* Class ClusterSettings */
class ClusterSettings
{
public:
  /* Constructor and destructor */
  ClusterSettings ();
  ClusterSettings (const std::string& name);
  virtual ~ClusterSettings ();

  /* Set methods */
  void set_name           (const std::string& name);
  void set_from_TreeModel (Glib::RefPtr<Gtk::ListStore> list_store);

  /* Get methods */
  std::string get_name ();

  /* Other methods */
  void          save_xml         (const Glib::ustring& filename);
  bool          load_xml         (const Glib::ustring& filename);
  Glib::ustring to_TreeModel     (Glib::RefPtr<Gtk::ListStore> list_store);
  bool          TreeModel_to_XML (Glib::RefPtr<Gtk::ListStore> list_store,
                                  const Glib::ustring& filename);

protected:
  /* Variables */
  std::string               m_Name;
  std::list<SensorSettings> m_Sensors;
  ModelColumns              m_Columns;

  /* Signal handlers */
  bool on_foreach_iter (const Gtk::TreeModel::iterator& iter);
};

} /* namespace */

#endif /* __CLUSTERSETTINGS_H__ */
