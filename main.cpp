#include "Pokemon.h"
#include <cstring>
#include <fstream>
#include <gtk/gtk.h>
#include <map>
#include <queue>
#include <string>
using namespace std;
map<string, Pokemon> pokemans;

//*************************
// helper and misc handlers
//*************************

void end_program(GtkWidget *wid, gpointer ptr) { gtk_main_quit(); }

char print_nature(float input) {
    if (input > 1.01) {
        return 'u';

    } else if (input < 0.99) {
        return 'd';
    } else {
        return 'n';
    }
}

void get_and_set_evs(Pokemon &poke, gpointer ptr) {
    GtkBuilder *builder = (GtkBuilder *)ptr;
    GtkWidget *statWorker = (GtkWidget *)gtk_builder_get_object(builder, "hp_ev_entry");
    poke.hp.EV = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(statWorker));
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "att_ev_entry");
    poke.att.EV = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(statWorker));
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "def_ev_entry");
    poke.def.EV = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(statWorker));
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "spec_att_ev_entry");
    poke.spec_attack.EV = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(statWorker));
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "spec_def_ev_entry");
    poke.spec_def.EV = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(statWorker));
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "speed_ev_entry");
    poke.speed.EV = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(statWorker));
}

void collect_and_update_entry_stats(gpointer ptr) {

    GtkBuilder *builder = (GtkBuilder *)ptr;
    GtkWidget *comboBox = (GtkWidget *)gtk_builder_get_object(builder, "profiles_combo_box");

    Pokemon poke = pokemans[gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBox))];

    GtkWidget *statWorker = (GtkWidget *)gtk_builder_get_object(builder, "hp_stat_entry");
    poke.hp.current = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(statWorker));
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "att_stat_entry");
    poke.att.current = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(statWorker));
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "def_stat_entry");
    poke.def.current = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(statWorker));
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "spec_att_stat_entry");
    poke.spec_attack.current = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(statWorker));
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "spec_def_stat_entry");
    poke.spec_def.current = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(statWorker));
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "speed_stat_entry");
    poke.speed.current = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(statWorker));

    pokemans[gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBox))] = poke;
}
float calculate_move_damage(gpointer ptr, int moveIndex) {
    int power = 0;
    int defense = 50;
    bool special = false;
    float damageMod = 0.0;

    GtkBuilder *builder = (GtkBuilder *)ptr;
    GtkWidget *worker = (GtkWidget *)gtk_builder_get_object(builder, "profiles_combo_box");
    Pokemon poke = pokemans[gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(worker))];
    // get pokemon move power
    switch (moveIndex) {
    case 1:
        power = poke.move1.power;
        if (poke.move1.stab)
            power += power / 2;
        special = poke.move1.type;
        worker = (GtkWidget *)gtk_builder_get_object(builder, "move_1_effectivity");
        damageMod = gtk_spin_button_get_value(GTK_SPIN_BUTTON(worker));
        break;
    case 2:
        power = poke.move2.power;
        if (poke.move2.stab)
            power += power / 2;
        special = poke.move2.type;
        worker = (GtkWidget *)gtk_builder_get_object(builder, "move_2_effectivity");
        damageMod = gtk_spin_button_get_value(GTK_SPIN_BUTTON(worker));
        break;
    case 3:
        power = poke.move3.power;
        if (poke.move3.stab)
            power += power / 2;
        special = poke.move3.type;
        worker = (GtkWidget *)gtk_builder_get_object(builder, "move_3_effectivity");
        damageMod = gtk_spin_button_get_value(GTK_SPIN_BUTTON(worker));
        break;
    case 4:
        power = poke.move4.power;
        if (poke.move4.stab)
            power += power / 2;
        special = poke.move4.type;
        worker = (GtkWidget *)gtk_builder_get_object(builder, "move_4_effectivity");
        damageMod = gtk_spin_button_get_value(GTK_SPIN_BUTTON(worker));
        break;
    };

    // get defense based on move type, if 0 do 50 for default
    if (special) {
        worker = (GtkWidget *)gtk_builder_get_object(builder, "opponent_spec_def_entry");
        defense = atoi(gtk_entry_get_text(GTK_ENTRY(worker)));
        if (defense < 1) {
            defense = 50;
        }

        return (((((((2 * poke.currentLevel) / 5 + 2) * power) * poke.spec_attack.current) / (float)defense) / 50) + 2) *
               damageMod;
    } else {
        worker = (GtkWidget *)gtk_builder_get_object(builder, "opponent_def_entry");
        defense = atoi(gtk_entry_get_text(GTK_ENTRY(worker)));
        if (defense < 1) {
            defense = 50;
        }

        return (((((((2 * poke.currentLevel) / 5 + 2) * power) * poke.att.current) / (float)defense) / 50) + 2) * damageMod;
    }

    // plug in damage to formula
    // return value
}

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

    // get and set current stats entry box
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "hp_stat_entry");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(statWorker), tempPoke.hp.current);
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "att_stat_entry");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(statWorker), tempPoke.att.current);
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "def_stat_entry");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(statWorker), tempPoke.def.current);
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "spec_att_stat_entry");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(statWorker), tempPoke.spec_attack.current);
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "spec_def_stat_entry");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(statWorker), tempPoke.spec_def.current);
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "speed_stat_entry");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(statWorker), tempPoke.speed.current);

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
    output = to_string(tempPoke.att.bottomIV) + "-" + to_string(tempPoke.att.topIV);
    gtk_label_set_text(GTK_LABEL(statWorker), output.c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "def_iv");
    output = to_string(tempPoke.def.bottomIV) + "-" + to_string(tempPoke.def.topIV);
    gtk_label_set_text(GTK_LABEL(statWorker), output.c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "spec_att_iv");
    output = to_string(tempPoke.spec_attack.bottomIV) + "-" + to_string(tempPoke.spec_attack.topIV);
    gtk_label_set_text(GTK_LABEL(statWorker), output.c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "spec_def_iv");
    output = to_string(tempPoke.spec_def.bottomIV) + "-" + to_string(tempPoke.spec_def.topIV);
    gtk_label_set_text(GTK_LABEL(statWorker), output.c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "speed_iv");
    output = to_string(tempPoke.speed.bottomIV) + "-" + to_string(tempPoke.speed.topIV);
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
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "move_1_power");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.move1.power).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "move_2_power");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.move2.power).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "move_3_power");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.move3.power).c_str());
    statWorker = (GtkWidget *)gtk_builder_get_object(builder, "move_4_power");
    gtk_label_set_text(GTK_LABEL(statWorker), to_string(tempPoke.move4.power).c_str());
}

//****************************
// main window button handlers
//****************************

void update_button_handler(GtkWidget *wid, gpointer ptr) {
    // get builder and current pokemon object
    GtkBuilder *builder = (GtkBuilder *)ptr;
    GtkWidget *comboBox = (GtkWidget *)gtk_builder_get_object(builder, "profiles_combo_box");
    GtkWidget *worker = (GtkWidget *)gtk_builder_get_object(builder, "current_level");
    Pokemon poke = pokemans[gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBox))];
    poke.currentLevel = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(worker));
    // recalculate stats with current IVs save it and update
    get_and_set_evs(poke, ptr);
    poke.recalculate_stats();
    pokemans[gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBox))] = poke;
    updateDisplay(ptr);
}

void update_iv_button_handler(GtkWidget *wid, gpointer ptr) {
    // get builder and current pokemon object
    // pull stat changes if any from entry box
    GtkBuilder *builder = (GtkBuilder *)ptr;
    collect_and_update_entry_stats(ptr);
    GtkWidget *comboBox = (GtkWidget *)gtk_builder_get_object(builder, "profiles_combo_box");
    Pokemon poke = pokemans[gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBox))];

    // pull stat changes if any from entry box
    poke.update_IVs();
    pokemans[gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBox))] = poke;
    updateDisplay(ptr);
}

void new_pokemon_window_handler(GtkWidget *wid, gpointer ptr) {
    GtkBuilder *builder = (GtkBuilder *)ptr;
    GtkWidget *newWin = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon");
    gtk_widget_show_all(newWin);
}

void delete_pokemon_handler(GtkWidget *wid, gpointer ptr) {
    return;
    GtkBuilder *builder = (GtkBuilder *)ptr;
    GtkWidget *worker = (GtkWidget *)gtk_builder_get_object(builder, "profiles_combo_box");
    gtk_combo_box_text_remove(GTK_COMBO_BOX_TEXT(worker), 0);
    gchar * profile = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(worker));
    pokemans.erase(profile);
    //gint temp = gtk_combo_box_get_active(GTK_COMBO_BOX(worker));
   
}
void new_move_handler(GtkWidget *wid, gpointer ptr) {
    GtkBuilder *builder = (GtkBuilder *)ptr;
    GtkWidget *newWin = (GtkWidget *)gtk_builder_get_object(builder, "new_move");
    gtk_widget_show_all(newWin);
}
void calculate_move_damage_handler(GtkWidget *wid, gpointer ptr) {
    GtkBuilder *builder = (GtkBuilder *)ptr;
    GtkWidget *worker = (GtkWidget *)gtk_builder_get_object(builder, "move_1_damage");
    gtk_label_set_text(GTK_LABEL(worker), to_string(calculate_move_damage(ptr, 1)).c_str());
    worker = (GtkWidget *)gtk_builder_get_object(builder, "move_2_damage");
    gtk_label_set_text(GTK_LABEL(worker), to_string(calculate_move_damage(ptr, 2)).c_str());
    worker = (GtkWidget *)gtk_builder_get_object(builder, "move_3_damage");
    gtk_label_set_text(GTK_LABEL(worker), to_string(calculate_move_damage(ptr, 3)).c_str());
    worker = (GtkWidget *)gtk_builder_get_object(builder, "move_4_damage");
    gtk_label_set_text(GTK_LABEL(worker), to_string(calculate_move_damage(ptr, 4)).c_str());
    updateDisplay(ptr);
}
void profile_changed_handler(GtkWidget *wid, gpointer ptr) { updateDisplay(ptr); }
void load_button_handler(GtkWidget *wid, gpointer ptr) {

    pokemans.clear();
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
    fin.close();
}
void save_button_handler(GtkWidget *wid, gpointer ptr) {
    GtkBuilder *builder = (GtkBuilder *)ptr;
    GtkWidget *load_button = (GtkWidget *)gtk_builder_get_object(builder, "load_button");
    ofstream fout;
    const char *loadFile;
    loadFile = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(load_button));
    fout.open(loadFile);
    if (!fout.is_open()) {
        fout.open("default.txt");
    }
    for (map<string, Pokemon>::iterator it = pokemans.begin(); it != pokemans.end(); it++) {
        Pokemon poke = it->second;
        // write start
        // clang-format off
        fout << "Pokemon," << poke.name << "," << poke.nature << "," << poke.currentLevel << ",;" << endl;
        fout << poke.hp.current << "," << poke.hp.base << "," << poke.hp.topIV << "," << poke.hp.bottomIV << "," << poke.hp.EV << "," << print_nature(poke.hp.nature) << ",;" << endl;
        fout << poke.att.current << "," << poke.att.base << "," << poke.att.topIV << "," << poke.att.bottomIV << "," << poke.att.EV << "," << print_nature(poke.att.nature) << ",;" << endl;
        fout << poke.def.current << "," << poke.def.base << "," << poke.def.topIV << "," << poke.def.bottomIV << "," << poke.def.EV << "," << print_nature(poke.def.nature) << ",;" << endl;
        fout << poke.spec_attack.current << "," << poke.spec_attack.base << "," << poke.spec_attack.topIV << "," << poke.spec_attack.bottomIV << "," << poke.spec_attack.EV << "," << print_nature(poke.spec_attack.nature) << ",;" << endl;
        fout << poke.spec_def.current << "," << poke.spec_def.base << "," << poke.spec_def.topIV << "," << poke.spec_def.bottomIV << "," << poke.spec_def.EV << "," << print_nature(poke.spec_def.nature) << ",;" << endl;
        fout << poke.speed.current << "," << poke.speed.base << "," << poke.speed.topIV << "," << poke.speed.bottomIV << "," << poke.speed.EV << "," << print_nature(poke.speed.nature) << ",;" << endl;
        fout << poke.move1.name << "," << poke.move1.power << "," << poke.move1.type << "," << poke.move1.stab << ",;" << endl;        
        fout << poke.move2.name << "," << poke.move2.power << "," << poke.move2.type << "," << poke.move2.stab << ",;" << endl;
        fout << poke.move3.name << "," << poke.move3.power << "," << poke.move3.type << "," << poke.move3.stab << ",;" << endl;
        fout << poke.move4.name << "," << poke.move4.power << "," << poke.move4.type << "," << poke.move4.stab << ",;*" << endl;
        // clang-format on
    }
    fout.close();
}

//****************************
// new Pokemon Window handlers
//****************************

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

//****************************
// New Move handlers
//****************************

void new_move_ok_handler(GtkWidget *wid, gpointer ptr) {
    GtkBuilder *builder = (GtkBuilder *)ptr;
    // stats
    GtkWidget *nameEntry = (GtkWidget *)gtk_builder_get_object(builder, "new_move_name_entry");
    GtkWidget *powerEntry = (GtkWidget *)gtk_builder_get_object(builder, "new_move_power_entry");
    GtkWidget *stabEntry = (GtkWidget *)gtk_builder_get_object(builder, "new_move_STAB_button");
    GtkWidget *typeEntry = (GtkWidget *)gtk_builder_get_object(builder, "new_move_type_combo");
    GtkWidget *slot_entry = (GtkWidget *)gtk_builder_get_object(builder, "move_slot_combo_box");
    GtkWidget *comboBox = (GtkWidget *)gtk_builder_get_object(builder, "profiles_combo_box");

    int debug = atoi(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(slot_entry)));
    if (pokemans.size() > 0 && (gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBox))) != NULL) {
        Pokemon poke = pokemans[gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBox))];
        switch (atoi(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(slot_entry)))) {

        case 1:
            poke.set_move(poke.move1,
                          gtk_entry_get_text(GTK_ENTRY(nameEntry)),
                          atoi(gtk_entry_get_text(GTK_ENTRY(powerEntry))),
                          atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(typeEntry))),
                          gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(stabEntry)));
            break;
        case 2:
            poke.set_move(poke.move2,
                          gtk_entry_get_text(GTK_ENTRY(nameEntry)),
                          atoi(gtk_entry_get_text(GTK_ENTRY(powerEntry))),
                          atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(typeEntry))),
                          gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(stabEntry)));
            break;
        case 3:
            poke.set_move(poke.move3,
                          gtk_entry_get_text(GTK_ENTRY(nameEntry)),
                          atoi(gtk_entry_get_text(GTK_ENTRY(powerEntry))),
                          atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(typeEntry))),
                          gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(stabEntry)));
            break;
        case 4:
            poke.set_move(poke.move4,
                          gtk_entry_get_text(GTK_ENTRY(nameEntry)),
                          atoi(gtk_entry_get_text(GTK_ENTRY(powerEntry))),
                          atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(typeEntry))),
                          gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(stabEntry)));
            break;
        };
        pokemans[gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBox))] = poke;
        updateDisplay(ptr);
    }

    GtkWidget *newWin = (GtkWidget *)gtk_builder_get_object(builder, "new_move");
    gtk_widget_hide(newWin);
}
void new_move_no_handler(GtkWidget *wid, gpointer ptr) {
    GtkBuilder *builder = (GtkBuilder *)ptr;
    GtkWidget *newWin = (GtkWidget *)gtk_builder_get_object(builder, "new_move");
    gtk_widget_hide(newWin);
}

int main(int argc, char *argv[]) {
    // clang-format off
    gtk_init(&argc, &argv);
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "mylayout.glade", NULL);

    //***********************
    //main window and buttons
    //***********************
    GtkWidget *mainWindow = (GtkWidget *)gtk_builder_get_object(builder, "window1");
    GtkWidget *updateButton = (GtkWidget *)gtk_builder_get_object(builder, "update_button");
    GtkWidget *updateIVsButton = (GtkWidget *)gtk_builder_get_object(builder, "update_iv_button");
    GtkWidget *newPokemonButton = (GtkWidget *)gtk_builder_get_object(builder, "new_button");
    GtkWidget *deleteButton = (GtkWidget *)gtk_builder_get_object(builder, "delete_button");
    GtkWidget *newMoveButton = (GtkWidget *)gtk_builder_get_object(builder, "new_move_button");
    GtkWidget *calculateMoveButton = (GtkWidget *)gtk_builder_get_object(builder, "calculate_move_damage_button");
    GtkWidget *profilesComboBox  = (GtkWidget *)gtk_builder_get_object(builder, "profiles_combo_box");
    GtkWidget *saveButton = (GtkWidget *)gtk_builder_get_object(builder, "save_button");
    GtkWidget *loadButton = (GtkWidget *)gtk_builder_get_object(builder, "load_button");

    //******************************
    //new Pokemon window and buttons
    //******************************
    GtkWidget *newPokemonWindow = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon");
    GtkWidget *newPokemonCreateButton = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_ok_button");
    GtkWidget *newPokemonCancelButton = (GtkWidget *)gtk_builder_get_object(builder, "new_pokemon_no_button");

    //***************************
    //new move window and buttons
    //***************************
    GtkWidget *newMoveWin = (GtkWidget *)gtk_builder_get_object(builder, "new_move");
    GtkWidget *newMoveCreateButton = (GtkWidget *)gtk_builder_get_object(builder, "new_move_ok_button");
    GtkWidget *newMoveCancelButton = (GtkWidget *)gtk_builder_get_object(builder, "new_move_no_button");

    //main window handler mapping
    g_signal_connect(mainWindow, "delete_event", G_CALLBACK(end_program), NULL);
    g_signal_connect(updateButton, "clicked", G_CALLBACK(update_button_handler), builder);
    g_signal_connect(updateIVsButton, "clicked", G_CALLBACK(update_iv_button_handler), builder);
    g_signal_connect(newPokemonButton, "clicked", G_CALLBACK(new_pokemon_window_handler), builder);
    g_signal_connect(deleteButton, "clicked", G_CALLBACK(delete_pokemon_handler), builder);
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
