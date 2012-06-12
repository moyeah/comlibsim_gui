/*
 *  clustersettings.cpp
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
#include "clustersettings.h"
#include "./tinyxml/tinyxml.h"
#include "./tinyxml/tinystr.h"
#include <gtkmm/messagedialog.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <iostream>

/* Namespace */
namespace ComLibSim
{

/* SensorSettings */
SensorSettings::SensorSettings () :
  m_Tag ("UntitledSensor"),
  m_Online (true),
  m_Xcoord (0.0),
  m_Ycoord (0.0),
  m_Adata (0),
  m_Type ("NoType")
{
}

/* SensorSettings with arguments */
SensorSettings::SensorSettings (const Glib::ustring& tag,
                                bool online,
                                const gdouble x,
                                const gdouble y,
                                const guint adata,
                                const Glib::ustring& type)
{
  set_tag (tag);
  set_online (online);
  set_x_coord (x);
  set_y_coord (y);
  set_amount_data (adata);
  set_type (type);
}

/* SensorSettings destructor*/
SensorSettings::~SensorSettings ()
{
}

/* Method set_tag */
void SensorSettings::set_tag (const Glib::ustring& tag)
{
  m_Tag = tag;
}

/* Method set_online */
void SensorSettings::set_online (bool online)
{
  m_Online = online;
}

/* Method set_x_coord */
void SensorSettings::set_x_coord (const gdouble x)
{
  m_Xcoord = x;
}

/* Method set_y_coord */
void SensorSettings::set_y_coord (const gdouble y)
{
  m_Ycoord = y;
}

/* Method set_amount_data */
void SensorSettings::set_amount_data (const guint adata)
{
  m_Adata = adata;
}

/* Method set_type */
void SensorSettings::set_type (const Glib::ustring& type)
{
  m_Type = type;
}

/* Method get_tag */
Glib::ustring SensorSettings::get_tag ()
{
  return m_Tag;
}

/* Method get_online */
bool SensorSettings::get_online ()
{
  return m_Online;
}

/* Method get_x_coord */
gdouble SensorSettings::get_x_coord ()
{
  return m_Xcoord;
}

/* Method get_y_coord */
gdouble SensorSettings::get_y_coord ()
{
  return m_Ycoord;
}

/* Method get_amount_data */
guint SensorSettings::get_amount_data ()
{
  return m_Adata;
}

/* Method get_type */
Glib::ustring SensorSettings::get_type ()
{
  return m_Type;
}

/* ClusterSettings */
ClusterSettings::ClusterSettings () :
  m_Name ("UntitledCluster")
{
}

/* ClusterSettings with name */
ClusterSettings::ClusterSettings (const std::string& name)
{
  set_name (name);
}

/* ClusterSettings destructor*/
ClusterSettings::~ClusterSettings ()
{
}

/* Method set_name */
void ClusterSettings::set_name (const std::string& name)
{
  m_Name = name;
}

/* Method set_from_TreeModel */
void ClusterSettings::set_from_TreeModel (Glib::RefPtr<Gtk::ListStore> 
                                          list_store)
{
  /* Get list store contents */
  list_store->foreach_iter (sigc::mem_fun (*this,
                             &ClusterSettings::on_foreach_iter));
}

/* Method get_name */
std::string ClusterSettings::get_name ()
{
  return m_Name;
}

/* Method save_xml */
void ClusterSettings::save_xml (const Glib::ustring& filename)
{
  /* Create xml document */
  TiXmlDocument doc;

  /* XML Declaration */
  TiXmlDeclaration *decl = new TiXmlDeclaration ("0.0", "", "");
  doc.LinkEndChild (decl);

  /* Root element */
  TiXmlElement *root = new TiXmlElement ("SensorsClusterSettings");
  doc.LinkEndChild (root);

  /* Comment */
  Glib::ustring message;
  message.assign (" File created by ComLibSim at [");
  message.append (filename);
  message.append ("] ");
  TiXmlComment *comment = new TiXmlComment ();
  comment->SetValue (message.c_str ());
  root->LinkEndChild (comment);

  /* Cluster element */
  TiXmlElement *cluster = new TiXmlElement ("Cluster");
  root->LinkEndChild (cluster);

  /* Set cluster attribute */
  cluster->SetAttribute ("name", m_Name.c_str ());

  /* Sensors element */
  TiXmlElement *sensorsNode = new TiXmlElement ("Sensors");
  root->LinkEndChild (sensorsNode);

  /* Set sensor element and attributes */
  std::list<SensorSettings>::iterator iter;
  for (iter=m_Sensors.begin (); iter != m_Sensors.end (); iter++)
  {
    const SensorSettings& sensor_iter = *iter;

    /* Sensor element */
    TiXmlElement *sensor = new TiXmlElement ("Sensor");
    sensorsNode->LinkEndChild (sensor);

    /* Set sensor attributes */
    sensor->SetAttribute ("tag", iter->get_tag ().c_str ());
    sensor->SetAttribute ("online", iter->get_online ());
    sensor->SetDoubleAttribute ("x", iter->get_x_coord ());
    sensor->SetDoubleAttribute ("y", iter->get_y_coord ());
    sensor->SetAttribute ("adata", iter->get_amount_data ());
    sensor->SetAttribute ("type", iter->get_type ().c_str ());
  }

  /* Save xml to file */
  doc.SaveFile (filename.c_str ());
}

/* Method load_xml */
bool ClusterSettings::load_xml (const Glib::ustring& filename)
{
  /* Create xml document */
  TiXmlDocument doc (filename.c_str ());

  /* Test xml file */
  if (!doc.LoadFile ())
    return false;

  /* XML handles */
  TiXmlHandle hdoc (&doc);
  TiXmlHandle hroot (0);

  /* Root element */
  TiXmlElement *root = hdoc.FirstChildElement ().ToElement ();
  Glib::ustring check_xml;
  check_xml.assign (root->Value ());
  if (!root && !check_xml.compare ("SensorsClusterSettings"))
    return false;
  hroot = TiXmlHandle (root);

  /* Cluster element */
  TiXmlElement *cluster = hroot.FirstChildElement ("Cluster").ToElement ();
  if (!cluster)
    return false;

  /* Get cluster attribute */
  set_name (cluster->Attribute ("name"));

  /* Sensors element */
  TiXmlElement *sensorsNode = hroot.FirstChildElement ("Sensors").ToElement ();
  if (!sensorsNode)
    return false;

  /* Get sensors and attributes */
  TiXmlElement *sensor;
  sensor = hroot.FirstChildElement ("Sensors").FirstChild ("Sensor").ToElement ();
  if (!sensor)
    return false;
  for (sensor; sensor; sensor = sensor->NextSiblingElement ())
  {
    std::string sensor_tag,
                sensor_type;
    int sensor_online,
        sensor_adata;
    double sensor_x_coord,
           sensor_y_coord;
    SensorSettings sensor_settings;

    sensor_tag.assign (sensor->Attribute ("tag"));
    if (sensor_tag.empty ())
      return false;
    if (sensor->QueryIntAttribute ("online", &sensor_online) != TIXML_SUCCESS)
      return false;
    if (sensor->QueryDoubleAttribute ("x", &sensor_x_coord) != TIXML_SUCCESS)
      return false;
    if (sensor->QueryDoubleAttribute ("y", &sensor_y_coord) != TIXML_SUCCESS)
      return false;
    if (sensor->QueryIntAttribute ("adata", &sensor_adata) != TIXML_SUCCESS)
      return false;
    sensor_type.assign (sensor->Attribute ("type"));
    if (sensor_type.empty ())
      return false;
    m_Sensors.push_back (SensorSettings (sensor_tag,
                                         sensor_online,
                                         sensor_x_coord,
                                         sensor_y_coord,
                                         sensor_adata,
                                         sensor_type));
  }
  return true;
}

/* Method to_TreeModel */
Glib::ustring ClusterSettings::to_TreeModel (
                               Glib::RefPtr<Gtk::ListStore> list_store)
{
}

/* Callback on_foreach_iter */
bool ClusterSettings::on_foreach_iter (const Gtk::TreeModel::iterator& iter)
{
  Gtk::TreeModel::Row row = *iter;
  m_Sensors.push_back (SensorSettings (row[m_Columns.m_col_tag],
                                       row[m_Columns.m_col_online],
                                       row[m_Columns.m_col_x],
                                       row[m_Columns.m_col_y],
                                       row[m_Columns.m_col_adata],
                                       row[m_Columns.m_col_type]));
  return false;
}

} /* namespace */
