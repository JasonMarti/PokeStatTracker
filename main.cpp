#include <gtk/gtk.h>
#include <string>
#include <cstring>
#include "Pokemon.h"
#include <vector>
#include <map>
using namespace std;
map<string, Pokemon> pokemans;

//misc functions
void end_program(GtkWidget *wid, gpointer ptr) { gtk_main_quit(); }
void updateDisplay(gpointer ptr)
{
    GtkBuilder *builder = (GtkBuilder *)ptr;
    GtkWidget *comboBoxText = (GtkWidget *)gtk_builder_get_object(builder, "profiles_combo_box");
    Pokemon tempPoke = pokemans.at(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBoxText)));
}

//main window button handlers
void update_button_handler(GtkWidget *wid, gpointer ptr)
{
    GtkBuilder *builder = (GtkBuilder *)ptr;
    //INPROGRESS
}
void new_pokemon_window_handler(GtkWidget *wid, gpointer ptr)
{
    GtkBuilder *builder = (GtkBuilder *)ptr;
    GtkWidget *newWin =
        (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon");

    gtk_widget_show_all(newWin);
}
void new_move_handler(GtkWidget *wid, gpointer ptr)
{
    //TODO
}
void calculate_move_damage_handler(GtkWidget *wid, gpointer ptr)
{
    //TODO
}
void profile_changed_handler(GtkWidget *wid, gpointer ptr)
{
    updateDisplay(ptr);
    //TODO
}
void save_button_handler(GtkWidget *wid, gpointer ptr)
{
    //TODO
}
void load_button_handler(GtkWidget *wid, gpointer ptr)
{
    //TODO
}

//new pokemon window button handlers
void new_pokemon_ok_handler(GtkWidget *wid, gpointer ptr)
{
    GtkBuilder *builder = (GtkBuilder *)ptr;
    string baseName;
    //combo box for adding pokes
    GtkWidget *comboBox = (GtkWidget *)gtk_builder_get_object(builder, "profiles_combo_box");
    //name
    GtkWidget *nameField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_name_entry");
    string name = gtk_entry_get_text(GTK_ENTRY(nameField));
    //nature
    GtkWidget *natureField = (GtkWidget *)gtk_builder_get_object(builder, "new_natures");
    string nature = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(natureField));
    //stats
    GtkWidget *hpField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_hp_entry");
    GtkWidget *attField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_att_entry");
    GtkWidget *defField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_defense_entry");
    GtkWidget *specAttField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_spec_att_entry");
    GtkWidget *specDefField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_spec_def_entry");
    GtkWidget *speedField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_speed_entry");
    //level
    GtkWidget *levelField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_level_entry");

    //generate object

    //make sure name is unique
    baseName = name;
    int i = 1;
    while (pokemans.find(name) != pokemans.end())
    {
        name = baseName + "(" + to_string(i) + ")";
    }
    pokemans.insert(pair<string, Pokemon>(name, Pokemon(
                                                    name,
                                                    atoi(gtk_entry_get_text(GTK_ENTRY(hpField))),
                                                    atoi(gtk_entry_get_text(GTK_ENTRY(attField))),
                                                    atoi(gtk_entry_get_text(GTK_ENTRY(defField))),
                                                    atoi(gtk_entry_get_text(GTK_ENTRY(specAttField))),
                                                    atoi(gtk_entry_get_text(GTK_ENTRY(specDefField))),
                                                    atoi(gtk_entry_get_text(GTK_ENTRY(speedField))),
                                                    nature,
                                                    atoi(gtk_entry_get_text(GTK_ENTRY(levelField))))));
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox), name.c_str());
    gtk_entry_set_text(GTK_ENTRY(levelField), "");
    gtk_entry_set_text(GTK_ENTRY(nameField), "");
    gtk_entry_set_text(GTK_ENTRY(hpField), "");
    gtk_entry_set_text(GTK_ENTRY(attField), "");
    gtk_entry_set_text(GTK_ENTRY(defField), "");
    gtk_entry_set_text(GTK_ENTRY(specAttField), "");
    gtk_entry_set_text(GTK_ENTRY(specDefField), "");
    gtk_entry_set_text(GTK_ENTRY(speedField), "");

    GtkWidget *newWin = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon");
    gtk_widget_hide(newWin);
}

void new_pokemon_no_handler(GtkWidget *wid, gpointer ptr)
{
    GtkBuilder *builder = (GtkBuilder *)ptr;
    //name
    GtkWidget *nameField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_name_entry");
    string name = gtk_entry_get_text(GTK_ENTRY(nameField));
    //nature
    GtkWidget *natureField = (GtkWidget *)gtk_builder_get_object(builder, "new_natures");
    string nature = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(natureField));
    //stats
    GtkWidget *hpField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_hp_entry");
    GtkWidget *attField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_att_entry");
    GtkWidget *defField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_defense_entry");
    GtkWidget *specAttField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_spec_att_entry");
    GtkWidget *specDefField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_spec_def_entry");
    GtkWidget *speedField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_speed_entry");
    //level
    GtkWidget *levelField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_level_entry");
    //generate object
    gtk_entry_set_text(GTK_ENTRY(levelField), "");
    gtk_entry_set_text(GTK_ENTRY(nameField), "");
    gtk_entry_set_text(GTK_ENTRY(hpField), "");
    gtk_entry_set_text(GTK_ENTRY(attField), "");
    gtk_entry_set_text(GTK_ENTRY(defField), "");
    gtk_entry_set_text(GTK_ENTRY(specAttField), "");
    gtk_entry_set_text(GTK_ENTRY(specDefField), "");
    gtk_entry_set_text(GTK_ENTRY(speedField), "");

    GtkWidget *newWin = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon");
    gtk_widget_hide(newWin);
}
//new move button

void new_move_ok_handler(GtkWidget *wid, gpointer ptr)
{
}
void new_move_no_handler(GtkWidget *wid, gpointer ptr)
{
}

int main(int argc, char *argv[])
{
    // clang-format off
    gtk_init(&argc, &argv);
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "mylayout.glade", NULL);
    //main window and buttons
    GtkWidget *mainWindow = (GtkWidget *)gtk_builder_get_object(builder, "window1");
    GtkWidget *updateButton = (GtkWidget *)gtk_builder_get_object(builder, "update_button");
    GtkWidget *newPokemonButton = (GtkWidget *)gtk_builder_get_object(builder, "new_button");
    GtkWidget *newMoveButton = (GtkWidget *)gtk_builder_get_object(builder, "new_move_button");
    GtkWidget *calculateMoveButton = (GtkWidget *)gtk_builder_get_object(builder, "calculate_move_damage_button");
    GtkWidget *profilesComboBox  = (GtkWidget *)gtk_builder_get_object(builder, "profiles_combo_box");
    GtkWidget *saveButton = (GtkWidget *)gtk_builder_get_object(builder, "save_button");
    GtkWidget *loadButton = (GtkWidget *)gtk_builder_get_object(builder, "load_button");

    //new Pokemon window and buttons
    GtkWidget *newPokemonWindow = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon");
    GtkWidget *newPokemonCreateButton = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_ok_button");
    GtkWidget *newPokemonCancelButton = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_no_button");

    //new move window and buttons
    GtkWidget *newMoveWin = (GtkWidget *)gtk_builder_get_object(builder, "new_move");
    GtkWidget *newMoveCreateButton = (GtkWidget *)gtk_builder_get_object(builder, "new_move_ok_button");
    GtkWidget *newMoveCancelButton = (GtkWidget *)gtk_builder_get_object(builder, "new_move_no_button");

    //main window handler mapping
    g_signal_connect(mainWindow, "delete_event", G_CALLBACK(end_program), NULL);
    g_signal_connect(updateButton, "clicked", G_CALLBACK(update_button_handler), builder);
    g_signal_connect(newPokemonButton, "clicked", G_CALLBACK(new_pokemon_window_handler), builder);
    g_signal_connect(newMoveButton, "clicked", G_CALLBACK(new_move_handler), builder);
    g_signal_connect(calculateMoveButton, "clicked", G_CALLBACK(calculate_move_damage_handler), builder);
    g_signal_connect(profilesComboBox, "changed", G_CALLBACK(profile_changed_handler), builder);
    //g_signal_connect(saveButton, "clicked", G_CALLBACK(save_button_handler), builder);
    //g_signal_connect(loadButton, "clicked", G_CALLBACK(load_button_handler), builder);

    //new Pokemon window handler mapping
    g_signal_connect(mainWindow, "delete_event", G_CALLBACK(end_program), NULL);
    g_signal_connect(newPokemonCreateButton, "clicked", G_CALLBACK(new_pokemon_ok_handler), builder);
    g_signal_connect(newPokemonCancelButton, "clicked", G_CALLBACK(new_pokemon_no_handler), builder);

    //new move window handler mapping
    g_signal_connect(mainWindow, "delete_event", G_CALLBACK(end_program), NULL);
    g_signal_connect(newMoveCreateButton, "clicked", G_CALLBACK(new_move_ok_handler), builder);
    g_signal_connect(newMoveCancelButton, "clicked", G_CALLBACK(new_move_no_handler), builder);

    gtk_widget_show_all(mainWindow);
    // clang-format on
    gtk_main();
    return 0;
}
