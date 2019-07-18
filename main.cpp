#include "Pokemon.h"
#include <cstring>
#include <fstream>
#include <gtk/gtk.h>
#include <map>
#include <queue>
#include <string>
using namespace std;
map<string, Pokemon> pokemans;

// misc functions
void end_program(GtkWidget *wid, gpointer ptr) { gtk_main_quit(); }
void updateDisplay(gpointer ptr) {
    GtkBuilder *builder = (GtkBuilder *)ptr;
    GtkWidget *comboBoxText = (GtkWidget *)gtk_builder_get_object(builder, "profiles_combo_box");
    Pokemon tempPoke = pokemans.at(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBoxText)));

    // set name
    GtkWidget *singleWorker = (GtkWidget *)gtk_builder_get_object(builder, "name");
    gtk_label_set_text(GTK_LABEL(singleWorker), tempPoke.name.c_str());
    singleWorker = (GtkWidget *)gtk_builder_get_object(builder, "nature_stat");
    gtk_label_set_text(GTK_LABEL(singleWorker), tempPoke.nature.c_str());
    singleWorker = (GtkWidget *)gtk_builder_get_object(builder, "current_level");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(singleWorker), tempPoke.currentLevel);

    // get and set current stats
    GtkWidget *statWorker = (GtkWidget *)gtk_builder_get_object(builder, "hp_stat");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.hp.current).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "att_stat");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.att.current).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "def_stat");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.def.current).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "spec_att_stat");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.spec_attack.current).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "spec_def_stat");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.spec_def.current).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "speed_stat");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.speed.current).c_str());

    // get base stats labels
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "hp_base");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.hp.base).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "att_base");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.att.base).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "def_base");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.def.base).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "spec_att_base");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.spec_attack.base).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "spec_def_base");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.spec_def.base).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "speed_base");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.speed.base).c_str());

    // get and set current stat entry boxes
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "hp_base");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.hp.base).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "att_base");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.att.base).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "def_base");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.def.base).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "spec_att_base");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.spec_attack.base).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "spec_def_base");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.spec_def.base).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "speed_base");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.speed.base).c_str());

    // get and set iv ranges
    string output;
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "hp_iv");
    output = to_string(tempPoke.hp.bottomIV) + "-" + to_string(tempPoke.hp.topIV);
    gtk_label_set_text(GTK_LABEL(statWorker), output.c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "att_iv");
    output = to_string(tempPoke.att.bottomIV) + "-" + to_string(tempPoke.att.bottomIV);
    gtk_label_set_text(GTK_LABEL(statWorker), output.c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "def_iv");
    output = to_string(tempPoke.def.bottomIV) + "-" + to_string(tempPoke.def.bottomIV);
    gtk_label_set_text(GTK_LABEL(statWorker), output.c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "spec_att_iv");
    output = to_string(tempPoke.spec_attack.bottomIV) + "-" + to_string(tempPoke.spec_attack.bottomIV);
    gtk_label_set_text(GTK_LABEL(statWorker), output.c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "spec_def_iv");
    output = to_string(tempPoke.spec_def.bottomIV) + "-" + to_string(tempPoke.spec_def.bottomIV);
    gtk_label_set_text(GTK_LABEL(statWorker), output.c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "speed_iv");
    output = to_string(tempPoke.speed.bottomIV) + "-" + to_string(tempPoke.speed.bottomIV);
    gtk_label_set_text(GTK_LABEL(statWorker), output.c_str());

    // get and set current evs
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "hp_ev_entry");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(statWorker), tempPoke.hp.EV);
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "att_ev_entry");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(statWorker), tempPoke.att.EV);
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "def_ev_entry");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(statWorker), tempPoke.def.EV);
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "spec_att_ev_entry");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(statWorker), tempPoke.spec_attack.EV);
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "spec_def_ev_entry");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(statWorker), tempPoke.spec_def.EV);
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "speed_ev_entry");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(statWorker), tempPoke.speed.EV);

    // get and set move names
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "move_1_name");
    gtk_label_set_text(GTK_LABEL(statWorker), tempPoke.move1.name.c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "move_2_name");
    gtk_label_set_text(GTK_LABEL(statWorker), tempPoke.move2.name.c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "move_3_name");
    gtk_label_set_text(GTK_LABEL(statWorker), tempPoke.move3.name.c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "move_4_name");
    gtk_label_set_text(GTK_LABEL(statWorker), tempPoke.move4.name.c_str());

    // get and set move damage
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "move_1_damage");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.move1.power).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "move_2_damage");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.move2.power).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "move_3_damage");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.move3.power).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "move_4_damage");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.move4.power).c_str());
}

// main window button handlers
void update_button_handler(GtkWidget *wid, gpointer ptr) {
    GtkBuilder *builder = (GtkBuilder *)ptr;
    // TODO
}
void level_change_handler(GtkWidget *wid, gpointer ptr) {
    GtkBuilder *builder = (GtkBuilder *)ptr;
    GtkWidget *worker = (GtkWidget *)gtk_builder_get_object(builder, "profiles_combo_box");
    Pokemon currentProfile = pokemans.at(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(worker)));
    currentProfile.update_IVs();
    // TODO
}
void new_pokemon_window_handler(GtkWidget *wid, gpointer ptr) {
    GtkBuilder *builder = (GtkBuilder *)ptr;
    GtkWidget *newWin = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon");
    gtk_widget_show_all(newWin);
}
void new_move_handler(GtkWidget *wid, gpointer ptr) {
    GtkBuilder *builder = (GtkBuilder *)ptr;
    GtkWidget *newWin = (GtkWidget *)gtk_builder_get_object(builder, "new_move");
    gtk_widget_show_all(newWin);
}
void calculate_move_damage_handler(GtkWidget *wid, gpointer ptr) {
    // TODO
}
void profile_changed_handler(GtkWidget *wid, gpointer ptr) {
    updateDisplay(ptr);
    // TODO
}
void load_button_handler(GtkWidget *wid, gpointer ptr) {

    GtkBuilder *builder = (GtkBuilder *)ptr;
    GtkWidget *comboBox = (GtkWidget *)gtk_builder_get_object(builder, "profiles_combo_box");
    GtkWidget *load_button = (GtkWidget *)gtk_builder_get_object(builder, "load_button");
    ifstream fin;
    const char *loadFile;
    loadFile = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(load_button));
    char *output;
    string temp;
    string str;
    queue<string> pokemon;

    // read file to a string
    fin.open(loadFile);
    while (!fin.eof()) {
        getline(fin, temp);
        str += temp;
    }
    char input[str.length()];
    strcpy(input, str.c_str());
    output = strtok(input, "*");
    pokemon.push(output);
    while (true) {
        output = strtok(NULL, "*");
        if (output != NULL) {
            pokemon.push(output);
        } else {
            break;
        }
    }
    int runs = pokemon.size();
    for (int i = 0; i < runs; i++) {
        Pokemon poke(pokemon.front());
        pokemon.pop();
        pokemans[poke.name] = poke;
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox), poke.name.c_str());
    }
    // TODO
}
void save_button_handler(GtkWidget *wid, gpointer ptr) {

    // TODO
}

// new pokemon window button handlers
void new_pokemon_ok_handler(GtkWidget *wid, gpointer ptr) {
    GtkBuilder *builder = (GtkBuilder *)ptr;
    string baseName;
    // combo box for adding pokes
    GtkWidget *comboBox = (GtkWidget *)gtk_builder_get_object(builder, "profiles_combo_box");
    // name
    GtkWidget *nameField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_name_entry");
    string name = gtk_entry_get_text(GTK_ENTRY(nameField));
    // nature
    GtkWidget *natureField = (GtkWidget *)gtk_builder_get_object(builder, "new_natures");
    string nature = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(natureField));
    // stats
    GtkWidget *hpField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_hp_entry");
    GtkWidget *attField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_att_entry");
    GtkWidget *defField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_defense_entry");
    GtkWidget *specAttField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_spec_att_entry");
    GtkWidget *specDefField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_spec_def_entry");
    GtkWidget *speedField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_speed_entry");
    // level
    GtkWidget *levelField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_level_entry");

    // generate object

    // make sure name is unique
    baseName = name;
    int i = 1;
    while (pokemans.find(name) != pokemans.end()) {
        name = baseName + "(" + to_string(i) + ")";
    }
    // clang-format off
  pokemans.insert(pair<string, Pokemon>(name, Pokemon(name, 
                    atoi(gtk_entry_get_text(GTK_ENTRY(hpField))), 
                    atoi(gtk_entry_get_text(GTK_ENTRY(attField))),
                    atoi(gtk_entry_get_text(GTK_ENTRY(defField))), 
                    atoi(gtk_entry_get_text(GTK_ENTRY(specAttField))),
                    atoi(gtk_entry_get_text(GTK_ENTRY(specDefField))), 
                    atoi(gtk_entry_get_text(GTK_ENTRY(speedField))),
                    nature, 
                    atoi(gtk_entry_get_text(GTK_ENTRY(levelField))))));
    // clang-format on
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

void new_pokemon_no_handler(GtkWidget *wid, gpointer ptr) {
    GtkBuilder *builder = (GtkBuilder *)ptr;
    // name
    GtkWidget *nameField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_name_entry");
    string name = gtk_entry_get_text(GTK_ENTRY(nameField));
    // nature
    GtkWidget *natureField = (GtkWidget *)gtk_builder_get_object(builder, "new_natures");
    string nature = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(natureField));
    // stats
    GtkWidget *hpField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_hp_entry");
    GtkWidget *attField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_att_entry");
    GtkWidget *defField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_defense_entry");
    GtkWidget *specAttField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_spec_att_entry");
    GtkWidget *specDefField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_spec_def_entry");
    GtkWidget *speedField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_speed_entry");
    // level
    GtkWidget *levelField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_level_entry");
    // generate object
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
// new move button

void new_move_ok_handler(GtkWidget *wid, gpointer ptr) {
    GtkBuilder *builder = (GtkBuilder *)ptr;
    // name
    GtkWidget *nameField = (GtkWidget *)gtk_builder_get_object(builder, "new_move_name_entry");
    string name = gtk_entry_get_text(GTK_ENTRY(nameField));
    // nature
    GtkWidget *natureField = (GtkWidget *)gtk_builder_get_object(builder, "new_natures");
    string nature = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(natureField));
    // stats
    GtkWidget *hpField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_hp_entry");
    GtkWidget *attField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_att_entry");
    GtkWidget *defField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_defense_entry");
    GtkWidget *specAttField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_spec_att_entry");
    GtkWidget *specDefField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_spec_def_entry");
    GtkWidget *speedField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_speed_entry");
    // level
    GtkWidget *levelField = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_level_entry");
    // generate object
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
    if (pokemans.size() > 0) {
    }
}
void new_move_no_handler(GtkWidget *wid, gpointer ptr) {}

int main(int argc, char *argv[]) {
    // clang-format off
    gtk_init(&argc, &argv);
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "mylayout.glade", NULL);
    //main window and buttons
    GtkWidget *mainWindow = (GtkWidget *)gtk_builder_get_object(builder, "window1");
    GtkWidget *updateButton = (GtkWidget *)gtk_builder_get_object(builder, "update_button");
    GtkWidget *currentLevelSpinBox = (GtkWidget *)gtk_builder_get_object(builder, "current_level");
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
    g_signal_connect(currentLevelSpinBox, "value-changed", G_CALLBACK(level_change_handler), builder);
    g_signal_connect(newPokemonButton, "clicked", G_CALLBACK(new_pokemon_window_handler), builder);
    g_signal_connect(newMoveButton, "clicked", G_CALLBACK(new_move_handler), builder);
    g_signal_connect(calculateMoveButton, "clicked", G_CALLBACK(calculate_move_damage_handler), builder);
    g_signal_connect(profilesComboBox, "changed", G_CALLBACK(profile_changed_handler), builder);
    g_signal_connect(saveButton, "clicked", G_CALLBACK(save_button_handler), builder);
    g_signal_connect(loadButton, "file-set", G_CALLBACK(load_button_handler), builder);

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
