#include<gtk/gtk.h>
#include<gdk/gdk.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

static GdkPixmap *pixmap = NULL;

static gint configure_event (GtkWidget *widget, GdkEventConfigure *event)
{
   
    if (pixmap) {
        gdk_pixmap_unref (pixmap);
    }
   
    pixmap = gdk_pixmap_new (widget->window,
                widget->allocation.width,
                widget->allocation.height,
                -1);
    /*   */            
    gdk_draw_rectangle (pixmap,
		      widget->style->white_gc,
		      TRUE,
		      0, 0,
		      widget->allocation.width,
		      widget->allocation.height);
		      
	/**/

    return TRUE;
}

gint expose_event (GtkWidget *widget, GdkEventExpose *event)
{
   
    gdk_draw_pixmap (widget->window,
          widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
          pixmap,
          event->area.x, event->area.y,
          event->area.x, event->area.y,
          event->area.width, event->area.height);
    return FALSE;
}

void quit ()
{
    gtk_exit (0);
}

int main (int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *drawing_area;
    GtkWidget *vbox;
    
    gtk_init (&argc, &argv);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    vbox = gtk_hbox_new (FALSE, 0);
    
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);
    
    gtk_signal_connect (GTK_OBJECT (window), "destroy",
                GTK_SIGNAL_FUNC (quit), NULL);
   
   
    drawing_area = gtk_drawing_area_new ();
    gtk_drawing_area_size (GTK_DRAWING_AREA (drawing_area), 200, 200);
    
    gtk_box_pack_start (GTK_BOX (vbox), drawing_area, TRUE, TRUE, 0);
    
   /* 
    gtk_signal_connect (GTK_OBJECT (drawing_area), "expose_event",
                (GtkSignalFunc) expose_event, NULL);
    gtk_signal_connect (GTK_OBJECT(drawing_area),"configure_event",
                (GtkSignalFunc) configure_event, NULL);
                
    /*   */ 
	
	
	
	/* */
    
    gtk_signal_connect (GTK_OBJECT(drawing_area),"configure_event",
                (GtkSignalFunc) configure_event, NULL);
    gtk_signal_connect (GTK_OBJECT (drawing_area), "expose_event",
                (GtkSignalFunc) expose_event, NULL);
                
    /*   */       
	
	
	           
    gtk_widget_show (drawing_area);
                
    /**/
   
    /*  */   
	gtk_widget_show (window);
	/*       */
   
    gdk_draw_line (pixmap, drawing_area->style->black_gc,0,100,100,0);
    gdk_draw_point(pixmap, drawing_area->style->black_gc,120,100);
    
   
   
    gtk_main ();
    return 0;
}
