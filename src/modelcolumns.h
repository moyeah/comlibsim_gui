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
#ifndef __MODELCOLUMNS_H__
#define __MODELCOLUMNS_H__

/* Include files */
#include <gtkmm/treemodel.h>

/* Namespace */
namespace ComLibSim
{

/* Tree model columns */
class ModelColumns : public Gtk::TreeModel::ColumnRecord
{
public:
  ModelColumns ()
  {
    add (m_col_x);
    add (m_col_y);
    add (m_col_max_rate);
    add (m_col_data);
  }

  /* Child widgets */
  Gtk::TreeModelColumn<gdouble> m_col_x;
  Gtk::TreeModelColumn<gdouble> m_col_y;
  Gtk::TreeModelColumn<gdouble> m_col_max_rate;
  Gtk::TreeModelColumn<gdouble> m_col_data;
};

} /* namespace */

#endif /* __MODELCOLUMNS_H__ */
