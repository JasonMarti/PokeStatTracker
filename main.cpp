#include <gtk/gtk.h>
#include <string>
#include "Pokemon.h"
using namespace std;
int count = 0;
GtkWidget *txt;

Pokemon createNewPokemonObject (GtkBuilder *builder) {
    
}
void end_program(GtkWidget *wid, gpointer ptr) { gtk_main_quit(); }
void test_button(GtkWidget *wid, gpointer ptr) {
  GtkBuilder *builder = (GtkBuilder *)ptr;
  GtkWidget *newWin =
      (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon");

  gtk_widget_show_all(newWin);
}
void hide(GtkWidget *wid, gpointer ptr) {
  GtkBuilder *builder = (GtkBuilder *)ptr;
  GtkWidget *newWin =
      (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon");
  gtk_widget_hide(newWin);
}



int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);
  GtkBuilder *builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "mylayout.glade", NULL);
  GtkWidget *win = (GtkWidget *)gtk_builder_get_object(builder, "window1");
  GtkWidget *newWin =
      (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon");
  GtkWidget *moveWin = (GtkWidget *)gtk_builder_get_object(builder, "new_move");
  GtkWidget *newBtn =
      (GtkWidget *)gtk_builder_get_object(builder, "new_button");
  GtkWidget *createBtn =
      (GtkWidget *)gtk_builder_get_object(builder, "create_button");
  g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);
  g_signal_connect(newWin, "delete_event", G_CALLBACK(end_program), newWin);
  g_signal_connect(createBtn, "clicked", G_CALLBACK(hide), builder);
  g_signal_connect(newBtn, "clicked", G_CALLBACK(test_button), builder);
  gtk_widget_show_all(win);
  gtk_main();
  return 0;
}
