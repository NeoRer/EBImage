#ifndef _COMMON_H_LOCAL
#define _COMMON_H_LOCAL
/* -------------------------------------------------------------------------

Common definitions for the 'EBImage' project

Copyright (c) 2005 Oleg Sklyar

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2.1
of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU Lesser General Public License for more details.
LGPL license wording: http://www.gnu.org/licenses/lgpl.html

------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* imagemagick includes */
#include <magick/ImageMagick.h>

/* R includes */
#include <R.h>
#include <Rdefines.h>
#include <R_ext/Error.h>

/* GTK+ includes */
#ifdef USE_GTK
#   include <glib.h>
#   include <glib-object.h>
#   include <gdk/gdk.h>
#   include <gdk-pixbuf/gdk-pixbuf.h>
#   include <gtk/gtk.h>
#   ifdef WIN32
        typedef unsigned long ulong;
        extern  __declspec(dllimport) void (* R_tcldo) ();
#       include <sys/types.h>
// FIXME: what is the next line doing?
#       include <gdk/gdkwin32.h>
#   else
#       include "R_ext/eventloop.h"
#       include <gdk/gdkx.h>
#   endif
#   ifdef GLIB_GETTEXT
#       define GETTEXT_PACKAGE "gtk20"
#       include <glib/gi18n-lib.h>
#   endif
#endif

#define MAX_MODE  1
#define MODE_GRAY 0
#define MODE_RGB  1

typedef struct {
    int x, y;
} PointXY;

#ifdef __cplusplus
extern "C" {
#endif

/* R-lib exports to use with .Call */
SEXP         lib_ (SEXP);                                           /* tools.c, _() for R    */
SEXP         lib_readImages (SEXP, SEXP);                           /* io.c                  */
SEXP         lib_writeImages (SEXP, SEXP, SEXP);                    /* -"-                   */
SEXP         lib_chooseImages ();                                   /* -"-                   */
SEXP         lib_display (SEXP, SEXP);                              /* display.c             */
SEXP         lib_animate (SEXP);                                    /* -"-                   */
SEXP         lib_channel (SEXP, SEXP);                              /* colors.c              */
SEXP         lib_filterMagick (SEXP, SEXP, SEXP);                   /* filters_magick.c      */
SEXP         lib_filterFill (SEXP, SEXP, SEXP, SEXP, SEXP);         /* -"-                   */
SEXP         lib_erode_dilate (SEXP, SEXP, SEXP, SEXP);             /* filters_morph.c       */
SEXP         lib_filterThresh (SEXP, SEXP);                         /* filters_thresh.c      */
SEXP         lib_distMap (SEXP, SEXP, SEXP, SEXP);                  /* filters_distmap.c     */
SEXP         lib_filterInvWS (SEXP, SEXP, SEXP, SEXP);              /* filters_watershed.c   */
SEXP         lib_paintFeatures (SEXP, SEXP, SEXP, SEXP);            /* object_counting.c     */
SEXP         lib_combineFeatures (SEXP, SEXP, SEXP, SEXP);          /* -"-                   */
SEXP         lib_matchFeatures (SEXP, SEXP);                        /* -"-                   */
SEXP         lib_getFeatures (SEXP, SEXP);                          /* -"-                   */
SEXP         lib_deleteFeatures (SEXP, SEXP, SEXP);                 /* -"-                   */

/* library exports and internal functions */
Image *      sexp2Magick (SEXP);                                    /* conversions.c         */
SEXP         magick2SEXP (Image *, int);                            /* -"-                   */
int          isImage (SEXP);                                        /* tools.c               */
double       distanceXY (const PointXY, const PointXY);             /* -"-                   */
double       distancexy (int, int, int, int);                       /* -"-                   */
PointXY      pointFromIndex (const int, const int);                 /* -"-                   */
int          indexFromPoint (const PointXY, const int);             /* -"-                   */
int          indexFromXY (const int, const int, const int);         /* -"-                   */
Image *      int2image1D (int *, int);                              /* colors.c              */
Image *      double2image1D (double *, int);                        /* -"-                   */
void         image1D2double (Image *, double *, int);               /* -"-                   */
void         image1D2int (Image *, int *, int);                     /* -"-                   */
Image *      vector2image1D (SEXP);                                 /* -"-                   */
SEXP         get_features (SEXP);                                   /* object_counting.c     */
SEXP         get_all_features (SEXP, SEXP);                         /* -"-                   */

#ifdef USE_GTK
    /* global vars needed to initialise GTK, local vars were used before, caused
      memory problems because they were freed before the function returned */
    char ** argv;
    int argc;
    int GTK_OK;
    void     _doIter (void *);                                      /* tools.c               */
    GdkPixbuf * newPixbufFromImages (Image *, int);                 /* conversions.c         */
#   ifdef WIN32
    void     _doIterWin32 ();                                       /* tools.c               */
#   else
    InputHandler * hdlr;
#   endif
#endif

/* will be substituted by gettext internationalisation */
#ifndef GLIB_GETTEXT
    char *   _(char *);
    char *   N_(char *);
#endif

/*
    void R_init_EBImage(DllInfo *); and void R_unload_EBImage(DllInfo *);
    are exported in init.c
*/

#ifdef __cplusplus
};
#endif

/* _COMMON_H_LOCAL */
#endif
