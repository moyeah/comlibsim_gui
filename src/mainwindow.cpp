/*
 *  mainwindow.cpp
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
#include "mainwindow.h"
#include "sensorsmap.h"
#include "clustersettings.h"
#include <gtkmm/stock.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/filechooserdialog.h>
#include <iostream>

/* Namespace */
namespace ComLibSim
{

/* MainWindow */
MainWindow::MainWindow () :
  m_VBoxMain (Gtk::ORIENTATION_VERTICAL),
  m_HBoxToolBar (Gtk::ORIENTATION_HORIZONTAL),
  m_VBoxSensors (Gtk::ORIENTATION_VERTICAL),
  m_HBoxCluster (Gtk::ORIENTATION_HORIZONTAL),
  m_ClusterLabel ("Cluster _name:", true)
{
  /* Main window proprieties */
  set_title ("Communication Library Simulator");
  set_border_width (10);
  set_default_size (800, 600);
  set_position (Gtk::WIN_POS_CENTER);
  
  /* Add main box */
  add (m_VBoxMain);

  /* Create and pack bars (menubar and toolbar) */
  init_bars ();
  if (m_pMenuBar)
    m_VBoxMain.pack_start (*m_pMenuBar, Gtk::PACK_SHRINK);
  if (m_pToolBar)
    m_VBoxMain.pack_start (*m_pToolBar, Gtk::PACK_SHRINK);

  /* Create and pack sensors map */
  init_sensorsmap ();
  m_VBoxMain.pack_start (m_FrameCluster);
  
  /* Show all widgets */
  show_all_children ();
}

/* MainWindow destructor*/
MainWindow::~MainWindow ()
{
}

/* Create menubar and toolbar */
void MainWindow::init_bars ()
{
  /* Create actions for menus and toolbars */
  m_refActionGroup = Gtk::ActionGroup::create ();

  /* ComLibSim menu */
  m_refActionGroup->add (Gtk::Action::create (
                         "ComLibSimMenu", "_ComLibSim"));
  m_refActionGroup->add (Gtk::Action::create (
                         "PlotCluster", "_Plot cluster"),
                         sigc::mem_fun (*this,
                                        &MainWindow::on_menu_pl_cluster));
  m_refActionGroup->add (Gtk::Action::create (
                         "Quit", Gtk::Stock::QUIT),
                         sigc::mem_fun (*this,
                                        &MainWindow::on_menu_quit));

  /* Sensors menu */
  m_refActionGroup->add (Gtk::Action::create (
                         "SensorsMenu", "S_ensors"));
  m_refActionGroup->add (Gtk::Action::create (
                         "SensorAdd", Gtk::Stock::ADD, "A_dd Sensor"),
                         sigc::mem_fun (*this,
                                        &MainWindow::on_sensors_add));
  m_refActionGroup->add (Gtk::Action::create (
                         "SensorDel", Gtk::Stock::DELETE, "_Delete Sensor"),
                         sigc::mem_fun (*this,
                                        &MainWindow::on_sensors_del));
  m_refActionGroup->add (Gtk::Action::create (
                         "SensorImport", Gtk::Stock::OPEN),
                         sigc::mem_fun (*this,
                                        &MainWindow::on_sensors_import));
  m_refActionGroup->add (Gtk::Action::create (
                         "SensorExport", Gtk::Stock::SAVE),
                         sigc::mem_fun (*this,
                                        &MainWindow::on_sensors_export));

  /* Help menu */
  m_refActionGroup->add (Gtk::Action::create (
                         "HelpMenu", "_Help"));
  m_refActionGroup->add (Gtk::Action::create (
                         "HelpAbout", Gtk::Stock::ABOUT),
                         sigc::mem_fun (*this,
                                        &MainWindow::on_menu_about));

  /* Create UIManager and add ActionGroup and AccelGroup */
  m_refUIManager = Gtk::UIManager::create ();
  m_refUIManager->insert_action_group (m_refActionGroup);
  add_accel_group (m_refUIManager->get_accel_group ());
  try
  {
// TODO
// The xml file should be load into the build
    m_refUIManager->add_ui_from_file ("./xml/ui_info.xml");
  }
  catch (const Glib::Error& ex)
  {
    std::cerr << "Building menus failed: " << ex.what ();
  }

  /* Get MenuBar widget */
  m_pMenuBar = m_refUIManager->get_widget ("/MenuBar");

  /* Get ToolBar widget */
  m_pToolBar = m_refUIManager->get_widget ("/ToolBar");

  /* Disable widgets */
  m_refUIManager->get_widget ("/MenuBar/SensorsMenu/SensorDel")->
                                                 set_sensitive (false);
  m_refUIManager->get_widget ("/ToolBar/SensorDel")->
                                                 set_sensitive (false);
}

/* Create sensors map */
void MainWindow::init_sensorsmap ()
{
  /* Set and create frame */
  m_FrameCluster.set_label ("Sensors cluster:");
  m_FrameCluster.add (m_VBoxSensors);

  /* Set and pack cluster name */
  m_ClusterLabel.set_mnemonic_widget (m_ClusterName);
  m_ClusterName.set_text ("Cluster XPTO");
  m_HBoxCluster.pack_start (m_ClusterLabel, Gtk::PACK_SHRINK, 10);
  m_HBoxCluster.pack_start (m_ClusterName, Gtk::PACK_EXPAND_WIDGET, 10);
  m_VBoxSensors.pack_start (m_HBoxCluster, Gtk::PACK_SHRINK, 10);

  /* Set and pack ScrolledWindow */
  m_ScrolledWindow.set_policy (Gtk::POLICY_AUTOMATIC,
                               Gtk::POLICY_AUTOMATIC);
  m_ScrolledWindow.set_border_width (5);
  m_VBoxSensors.pack_start (m_ScrolledWindow);

  /* Create TreeModel, TreeView and TreeSelection */
  m_refTreeModel = Gtk::ListStore::create (m_Columns);
  m_TreeView.set_model (m_refTreeModel);
  m_refTreeSelection = m_TreeView.get_selection ();

  /* Add TreeView */
  m_ScrolledWindow.add (m_TreeView);

  /* Add TreeView columns */
  m_TreeView.append_column_editable ("X coordinate",
                                     m_Columns.m_col_x);
  m_TreeView.append_column_editable ("Y coordinate",
                                     m_Columns.m_col_y);
  m_TreeView.append_column_editable ("Max ComRate",
                                     m_Columns.m_col_max_rate);
  m_TreeView.append_column_editable ("Data to collect (Kb)",
                                     m_Columns.m_col_data);
  
  /* Fill 1st TreeView row*/
  MainWindow::on_sensors_add ();

  /* Connect signals */
  m_refTreeSelection->signal_changed ().connect (sigc::mem_fun (*this,
                     &MainWindow::on_selection_changed));
}

/* Callback on_delete_event */
bool MainWindow::on_delete_event (GdkEventAny* event)
{
  Gtk::MessageDialog dialog (*this, "Exit application...",
                             false /* use_markup */,
                             Gtk::MESSAGE_QUESTION,
                             Gtk::BUTTONS_YES_NO);

  Glib::ustring message;
  message.assign ("You are about to exit the application\n");
  message.append ("Do you want to close it?");

  dialog.set_secondary_text (message);

  int result = dialog.run ();

  if (result == Gtk::RESPONSE_YES)
    hide ();
  else
    return true;
}

/* Callback on_menu_pl_cluster */
void MainWindow::on_menu_pl_cluster ()
{
  /* Dialog title */
  Glib::ustring title ("Plot cluster - ");
  title.append (m_ClusterName.get_text ());

  /* Create and set dialog */
  Gtk::Dialog dialog (title, *this, true);
  dialog.set_default_size (600, 400);
  dialog.set_position (Gtk::WIN_POS_CENTER);

  /* Get dialog content area */
  Gtk::Box *vbox = dialog.get_vbox ();

  /* Create and sensors map */
  SensorsMap sensors_map;
  vbox->pack_start (sensors_map, true, true, 0);
  sensors_map.show ();

  /* Add response buttons */
  dialog.add_button (Gtk::Stock::CLOSE, Gtk::RESPONSE_CANCEL);

  /* Show dialog */
  dialog.run ();
}

/* Callback on_menu_quit */
void MainWindow::on_menu_quit ()
{
  on_delete_event (NULL);
}

/* Callback on_menu_about */
void MainWindow::on_menu_about ()
{
  /* Create AboutDialog */
  Gtk::AboutDialog dialog;

  /* Fill AboutDialog */
  dialog.set_program_name ("Communication Library Simulator");
  dialog.set_version ("version 0.0");
  dialog.set_copyright ("Copyright (C) 2011-2012  Daniel Sousa");
// TODO
//  dialog.set_authors ("Daniel Sousa <da.arada@gmail.com>");
//  dialog.set_logo ();

  /* Show AboutDialog */
  dialog.run ();
}

/* Callback on_selection_changed */
void MainWindow::on_selection_changed ()
{
  if (m_refTreeSelection->count_selected_rows () > 0)
  {
    m_refUIManager->get_widget ("/MenuBar/SensorsMenu/SensorDel")->
                                                   set_sensitive (true);
    m_refUIManager->get_widget ("/ToolBar/SensorDel")->
                                                   set_sensitive (true);
  }
  else
  {
    m_refUIManager->get_widget ("/MenuBar/SensorsMenu/SensorDel")->
                                                  set_sensitive (false);
    m_refUIManager->get_widget ("/ToolBar/SensorDel")->
                                                  set_sensitive (false);
  }
}

/* Callback on_sensors_add */
void MainWindow::on_sensors_add ()
{
  /* Add template row */
  m_row = *(m_refTreeModel->append ());
  m_row[m_Columns.m_col_x] = 1.0;
  m_row[m_Columns.m_col_y] = 2.0;
  m_row[m_Columns.m_col_max_rate] = 100.0;
  m_row[m_Columns.m_col_data] = 50;

  /* Enable widgets */
  m_refUIManager->get_widget ("/MenuBar/SensorsMenu/SensorExport")->
                                                   set_sensitive (true);
  m_refUIManager->get_widget ("/ToolBar/SensorExport")->
                                                   set_sensitive (true);
}

/* Callback on_sensors_del */
void MainWindow::on_sensors_del ()
{
  Gtk::TreeModel::iterator iter = m_refTreeSelection->get_selected ();
  if (iter)
  {
    m_refTreeModel->erase (iter);
  }
}

/* Callback on_sensors_import */
void MainWindow::on_sensors_import ()
{
  /* Create dialog to import */
  Gtk::FileChooserDialog dialog (*this, "Import from..",
                                 Gtk::FILE_CHOOSER_ACTION_OPEN);
// TODO
  dialog.set_transient_for (*this);
  dialog.set_modal (true);
// END TODO

  /* Add response buttons */
  dialog.add_button (Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button (Gtk::Stock::OPEN, Gtk::RESPONSE_ACCEPT);

  /* Add file filters */
  Glib::RefPtr<Gtk::FileFilter> filter_xml = Gtk::FileFilter::create ();
  filter_xml->set_name ("Sensors map");
  filter_xml->add_mime_type ("application/xml");
  dialog.add_filter (filter_xml);

  /* Create dialog all files filter */
  Glib::RefPtr<Gtk::FileFilter> filter_all = Gtk::FileFilter::create ();
  filter_all->set_name ("All files");
  filter_all->add_pattern ("*");
  dialog.add_filter (filter_all);

  /* Set default path */
  dialog.set_current_folder ("./config/");

  /* Run dialog and wait for response */
  int response = dialog.run ();

  /* Handle dialog response */
  if (response == Gtk::RESPONSE_ACCEPT)
  {
    /* Create cluster settings */
// TODO
    ClusterSettings cluster_settings;

    /* Save cluster settings */
    cluster_settings.XML_to_TreeModel (dialog.get_filename (), m_refTreeModel);

    /* Set cluster name */
    m_ClusterName.set_text (cluster_settings.get_name ());
  }
}

/* Callback on_sensors_export */
void MainWindow::on_sensors_export ()
{
  /* Create dialog to export */
  Gtk::FileChooserDialog dialog (*this, "Export to..",
                                 Gtk::FILE_CHOOSER_ACTION_SAVE);
// TODO
  dialog.set_transient_for (*this);
  dialog.set_modal (true);
// END TODO
  dialog.set_do_overwrite_confirmation (true);

  /* Add response buttons */
  dialog.add_button (Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button (Gtk::Stock::SAVE, Gtk::RESPONSE_ACCEPT);

  /* Add file filters */
  Glib::RefPtr<Gtk::FileFilter> filter_xml = Gtk::FileFilter::create ();
  filter_xml->set_name ("Sensors map");
  filter_xml->add_mime_type ("application/xml");
  dialog.add_filter (filter_xml);

  /* Create dialog all files filter */
  Glib::RefPtr<Gtk::FileFilter> filter_all = Gtk::FileFilter::create ();
  filter_all->set_name ("All files");
  filter_all->add_pattern ("*");
  dialog.add_filter (filter_all);

  /* Set default path and filename */
  dialog.set_current_folder ("./config/");
  dialog.set_current_name ("map.xml");

  /* Run dialog and wait for response */
  int response = dialog.run ();

  /* Handle dialog response */
  if (response == Gtk::RESPONSE_ACCEPT)
  {
    /* Create cluster settings */
    ClusterSettings cluster_settings (m_ClusterName.get_text ());

    /* Save cluster settings */
    cluster_settings.TreeModel_to_XML (dialog.get_filename (),
                                       m_refTreeModel);
  }
}

/* Callback on_file_error */
void MainWindow::on_file_error (const Glib::ustring& filename)
{
    Gtk::MessageDialog dialog (*this, "ERROR!...",
                               false /* use_markup */,
                               Gtk::MESSAGE_ERROR,
                               Gtk::BUTTONS_OK,
                               true /* modal */);

    Glib::ustring err_msg;
    err_msg.assign ("Error importing file:");
    err_msg.append ("[" + filename + "]");
    dialog.set_secondary_text (err_msg);

    dialog.run ();
}

} /* namespace */
