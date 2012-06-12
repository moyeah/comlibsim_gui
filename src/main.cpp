/*
 *  main.cpp
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

/* Include config file */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* Include files */
#include "mainwindow.h"
#include <gtkmm/main.h>

/* Main function */
int main (int argc, char *argv[])
{
  Gtk::Main kit (argc, argv);

  ComLibSim::MainWindow mainwindow;

  Gtk::Main::run (mainwindow);

  return EXIT_SUCCESS;
}
