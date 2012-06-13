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
#include <glibmm.h>
#include <libxml++/parsers/domparser.h>
#include <libxml++/nodes/node.h>
#include <libxml++/nodes/element.h>
#include <libxml++/document.h>
#include <iomanip>
#include <iostream>

/* Namespace */
namespace ComLibSim
{

/* Method XML_to_TreeModel */
bool ClusterSettings::XML_to_TreeModel (const Glib::ustring& filename,
                             Glib::RefPtr<Gtk::ListStore> sensors_store)
{
  /* Create parser */
// TODO validate xml file
  try
  {
    xmlpp::DomParser parser (filename, false);
    if (parser)
    {
      /* Get root node */
      const xmlpp::Node *root_node = parser.get_document ()->
                                                       get_root_node ();

      /* Get cluster node and cluster name */
      xmlpp::Node::NodeList cluster_list =
                            root_node->get_children ("Cluster");
      xmlpp::Node::NodeList::iterator cluster_iter = 
                                                  cluster_list.begin ();
      const xmlpp::Element *cluster_node =
                    dynamic_cast<const xmlpp::Element*> (*cluster_iter);
      set_name (cluster_node->get_attribute_value ("name"));

      /* Get sensors */
      xmlpp::Node::NodeList sensors_list =
                                  cluster_node->get_children ("Sensor");
      xmlpp::Node::NodeList::iterator sensor_iter;
      Gtk::TreeModel::Row row;
      sensors_store->clear ();
      for (sensor_iter = sensors_list.begin ();
           sensor_iter != sensors_list.end ();
           sensor_iter++)
      {
        const xmlpp::Element *sensor_element =
                     dynamic_cast<const xmlpp::Element*> (*sensor_iter);
        row = *(sensors_store->append ());
        row[m_Columns.m_col_x] =
                      Glib::Ascii::strtod (
                      sensor_element->get_attribute_value ("x"));
        row[m_Columns.m_col_y] =
                      Glib::Ascii::strtod (
                      sensor_element->get_attribute_value ("y"));
        row[m_Columns.m_col_max_rate] =
                      Glib::Ascii::strtod (
                      sensor_element->get_attribute_value ("max_rate"));
        row[m_Columns.m_col_data] =
                      Glib::Ascii::strtod (
                      sensor_element->get_attribute_value ("data"));
      }
    }
  }
  catch (const std::exception& ex)
  {
    std::cout << "Exception caught: " << ex.what () << std::endl;
    return false;
  }

  /* Return success */
  return true;
}

/* Method TreeModel_to_XML */
void ClusterSettings::TreeModel_to_XML (const Glib::ustring& filename,
                              Glib::RefPtr<Gtk::ListStore> sensors_list)
{
  /* Get ListStore contents */
  sensors_list->foreach_iter (sigc::mem_fun (*this,
                             &ClusterSettings::on_foreach_iter));

  /* Create xml document */
  xmlpp::Document doc;

  /* Create root node */
  xmlpp::Element *root_node =
                        doc.create_root_node ("SensorsClusterSettings");

  /* Add root comment */
  Glib::ustring message;
  message.assign ("File created by ComLibSim at [");
  message.append (filename);
  message.append ("]");
  root_node->add_child_comment (message);

  /* Create and set cluster node */
  xmlpp::Element *cluster_node = root_node->add_child ("Cluster");
  cluster_node->set_attribute ("name", m_Name);

  /* Create and set sensor elements */
  std::list<SensorSettings>::iterator iter;
  for (iter=m_Sensors.begin (); iter != m_Sensors.end (); iter++)
  {
    const SensorSettings& sensor_iter = *iter;

    /* Sensor element */
    xmlpp::Element *sensor_element = cluster_node->add_child ("Sensor");

    /* Set sensor attributes */
    Glib::ustring tmp;
    tmp = Glib::ustring::format (std::fixed, std::setprecision (6),
                                 iter->get_x ());
    sensor_element->set_attribute ("x", tmp);
    tmp = Glib::ustring::format (std::fixed, std::setprecision (6),
                                 iter->get_y ());
    sensor_element->set_attribute ("y", tmp);
    tmp = Glib::ustring::format (std::fixed, std::setprecision (6),
                                 iter->get_max_rate ());
    sensor_element->set_attribute ("max_rate", tmp);
    tmp = Glib::ustring::format (std::fixed, std::setprecision (6),
                                 iter->get_data ());
    sensor_element->set_attribute ("data", tmp);
  }

  /* Save to xml file */
  doc.write_to_file (filename);
}

/* Callback on_foreach_iter */
bool ClusterSettings::on_foreach_iter (
                                   const Gtk::TreeModel::iterator& iter)
{
  Gtk::TreeModel::Row row = *iter;
  m_Sensors.push_back (SensorSettings (row[m_Columns.m_col_x],
                                       row[m_Columns.m_col_y],
                                       row[m_Columns.m_col_max_rate],
                                       row[m_Columns.m_col_data]));
  return false;
}

} /* namespace */
