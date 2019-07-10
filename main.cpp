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
void test_button(GtkWidget *wid, gpointer ptr) {
    int temp = 0;
    GtkBuilder * builder = (GtkBuilder *) ptr;
    GtkWidget *name = (GtkWidget *) gtk_builder_get_object(builder,"name");
    gtk_label_set_text (GTK_LABEL (name), "charboi");
}
int main(int argc, char *argv[])
{

    gtk_init(&argc, &argv);
    GtkBuilder * builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "mylayout.glade", NULL);
    GtkWidget *win = (GtkWidget *) gtk_builder_get_object(builder, "window1");
    g_signal_connect(win, "delete_event", G_CALLBACK (end_program), NULL);
    GtkWidget *newBtn = (GtkWidget *) gtk_builder_get_object(builder, "new_button");
    g_signal_connect(newBtn, "clicked", G_CALLBACK (test_button), builder);
    gtk_widget_show_all (win);
    gtk_main();
    return 0;
}