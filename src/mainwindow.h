/*
 *  mainwindow.h
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
#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

/* Include files */
#include "modelcolumns.h"
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/widget.h>
#include <gtkmm/menubar.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/actiongroup.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treeselection.h>

/* Namespace */
namespace ComLibSim
{

/* Class MainWindow */
class MainWindow : public Gtk::Window
{
public:
  MainWindow ();
  virtual ~MainWindow ();

protected:
  /* Window contents */
  void init_bars       ();
  void init_sensorsmap ();
// TODO
//  void init_statusbar  ();

  /* Signal handlers */
  virtual bool on_delete_event      (GdkEventAny* event);
  void         on_menu_pl_cluster   ();
  void         on_menu_quit         ();
  void         on_menu_about        ();
  void         on_selection_changed ();
  void         on_sensors_add       ();
  void         on_sensors_del       ();
  void         on_sensors_import    ();
  void         on_sensors_export    ();
  void         on_file_error        (const Glib::ustring& filename);
  
  /* Child widgets */
  Gtk::Box                               m_VBoxMain,
                                         m_HBoxToolBar,
                                         m_HBoxCluster,
                                         m_VBoxSensors;
  Gtk::Widget                           *m_pMenuBar,
                                        *m_pToolBar;
  Glib::RefPtr<Gtk::UIManager>           m_refUIManager;
  Glib::RefPtr<Gtk::ActionGroup>         m_refActionGroup;
  Gtk::Frame                             m_FrameCluster;
  Gtk::Label                             m_ClusterLabel;
  Gtk::Entry                             m_ClusterName;
  ModelColumns                           m_Columns;
  Gtk::ScrolledWindow                    m_ScrolledWindow;
  Gtk::TreeView                          m_TreeView;
  Glib::RefPtr<Gtk::ListStore>           m_refTreeModel;
  Gtk::TreeModel::Row                    m_row;
  Glib::RefPtr<Gtk::TreeView::Selection> m_refTreeSelection;
};

} /* namespace */

#endif /* __MAINWINDOW_H__ */
