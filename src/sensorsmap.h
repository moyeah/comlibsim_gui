/*
 *  sensorsmap.h
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
#ifndef __SENSORSMAP_H__
#define __SENSORSMAP_H__

/* Include files */
#include <gtkmm/drawingarea.h>

/* Namespace */
namespace ComLibSim
{

/* Class SensorsMap */
class SensorsMap : public Gtk::DrawingArea
{
public:
  /* Constructor and destructor */
  SensorsMap () {}
  virtual ~SensorsMap () {}

protected:
  /* Signal handlers */
  virtual bool on_draw (const Cairo::RefPtr<Cairo::Context>& cr);
};

}

#endif /* __SENSORSMAP_H__ */
