#include <gtk/gtk.h>
#include "Pokemon.h"
#include <string>
using namespace std;
int count = 0;
GtkWidget *txt;

void end_program(GtkWidget *wid, gpointer ptr)
{
    gtk_main_quit();
}
void test_button(GtkWidget *wid, gpointer ptr)
{
    GtkWidget *newWin = (GtkWidget *)ptr;
    gtk_widget_show_all(newWin);
}
void hide(GtkWidget *wid, gpointer ptr)
{
    GtkWidget *newWin = (GtkWidget *)ptr;
    gtk_widget_hide(newWin);
}

GtkWidget* getWidgetByName(GSList *objectList, gchar *name)
{
    GSList *iterator = objectList;
    while (iterator != NULL)
    {
         if(GTK_IS_WIDGET((GtkWidget*)iterator->data))
         {
            
            if (strcmp(name, gtk_widget_get_name((GtkWidget*)iterator)))
            {
                return (GtkWidget*)iterator;
            }
        }  else {
            iterator = iterator->next;
        }
    } 
}
int main(int argc, char *argv[])
{

    gtk_init(&argc, &argv);
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "mylayout.glade", NULL);
    GSList *list = gtk_builder_get_objects(builder);
    gchar* window1 = "window1";
    GtkWidget *win2 = getWidgetByName(list,window1);
    GtkWidget *win = (GtkWidget *)gtk_builder_get_object(builder, "window1");
    GtkWidget *newWin = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon");
    GtkWidget *moveWin = (GtkWidget *)gtk_builder_get_object(builder, "new_move");
    GtkWidget *newBtn = (GtkWidget *)gtk_builder_get_object(builder, "new_button");
    GtkWidget *createBtn = (GtkWidget *)gtk_builder_get_object(builder, "create_button");
    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);
    g_signal_connect(newWin, "delete_event", G_CALLBACK(end_program), newWin);
    g_signal_connect(createBtn, "clicked", G_CALLBACK(hide), newWin);
    g_signal_connect(newBtn, "clicked", G_CALLBACK(test_button), newWin);
    gtk_widget_show_all(win);
    gtk_main();
    return 0;
}
