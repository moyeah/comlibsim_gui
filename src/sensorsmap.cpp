/*
 *  sensorsmap.cpp
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
#include "sensorsmap.h"
#include <cairomm/context.h>

/* Namespace */
namespace ComLibSim
{

/* Callback on_draw */
bool SensorsMap::on_draw (const Cairo::RefPtr<Cairo::Context>& cr)
{
  /* Get window allocation */
  Gtk::Allocation allocation = get_allocation ();
  const int width = allocation.get_width ();
  const int height = allocation.get_height ();

  /* Get center of the window */
  int xc, yc;
  xc = width / 2;
  yc = height / 2;

// DEBUG
cr->set_line_width(10.0);

// draw red lines out from the center of the window
cr->set_source_rgb(0.8, 0.0, 0.0);
cr->move_to(0, 0);
cr->line_to(xc, yc);
cr->line_to(0, height);
cr->move_to(xc, yc);
cr->line_to(width, yc);
cr->stroke();
// END DEBUG

  /* Return success */
  return true;
}

} /* namespace */
