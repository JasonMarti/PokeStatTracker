#include "Pokemon.h"
#include <cmath>
#include <cstring>
#include <map>
#include <string>

using namespace std;
Pokemon::Pokemon() {}

void Pokemon::blank_init() {
    this->name = "";
    this->nature = "adamant";
    this->currentLevel = 10;
    init_natures("adamant");
    init_stat_from_base(this->hp, 0, 1);
    init_stat_from_base(this->att, 0, 1);
    init_stat_from_base(this->def, 0, 1);
    init_stat_from_base(this->spec_attack, 0, 1);
    init_stat_from_base(this->spec_def, 0, 1);
    init_stat_from_base(this->speed, 0, 1);
    set_move(this->move1, "move1", 10, 0, false);
    set_move(this->move2, "move2", 10, 0, false);
    set_move(this->move3, "move3", 10, 0, false);
    set_move(this->move4, "move4", 10, 0, false);
}
void Pokemon::init_stat_from_string(Stat &stat, string csv) {
    char input[csv.length()];
    strcpy(input, csv.c_str());
    char *token[6];
    token[0] = strtok(input, ",");
    for (int i = 1; i < 6; i++) {
        token[i] = strtok(NULL, ",");
    }
    stat.current = atoi(token[0]);
    stat.base = atoi(token[1]);
    stat.topIV = atoi(token[2]);
    stat.bottomIV = atoi(token[3]);
    stat.EV = atoi(token[4]);
    if (!strcmp(token[5], "n")) {
        stat.nature = 1.0;
    } else if (!strcmp(token[5], "u")) {
        stat.nature = 1.1;
    } else if (!strcmp(token[5], "d")) {
        stat.nature = 0.9;
    }
}
void Pokemon::init_header_from_string(string csv) {
    char input[csv.length()];
    strcpy(input, csv.c_str());
    char *token;
    token = strtok(input, ",");
    if (!strcmp(token, "Pokemon")) {
        this->name = strtok(NULL, ",");
        this->nature = strtok(NULL, ",");
        this->currentLevel = atoi(strtok(NULL, ","));
    } else {
        blank_init();
        return;
    }
}

Pokemon::Pokemon(string csv) {
    char input[csv.length()];
    strcpy(input, csv.c_str());
    char *section[11];
    char *token;
    section[0] = strtok(input, ";");
    for (int i = 1; i < 11; i++) {
        section[i] = strtok(NULL, ";");
    }
    init_header_from_string(section[0]);
    init_stat_from_string(this->hp, section[1]);
    init_stat_from_string(this->att, section[2]);
    init_stat_from_string(this->def, section[3]);
    init_stat_from_string(this->spec_attack, section[4]);
    init_stat_from_string(this->spec_def, section[5]);
    init_stat_from_string(this->speed, section[6]);
    init_move_from_string(this->move1, section[7]);
    init_move_from_string(this->move2, section[8]);
    init_move_from_string(this->move3, section[9]);
    init_move_from_string(this->move4, section[10]);
    // TODO moves
}

// assumsIVs are 0
Pokemon::Pokemon(string name, int hp, int att, int def, int satt, int sdef, int speed, string newNature, int level) {
    this->nature = newNature;
    this->currentLevel = level;
    init_natures(newNature);
    init_hp_from_base(this->hp, hp, level);
    init_stat_from_base(this->att, att, level);
    init_stat_from_base(this->def, def, level);
    init_stat_from_base(this->spec_attack, satt, level);
    init_stat_from_base(this->spec_def, sdef, level);
    init_stat_from_base(this->speed, speed, level);

    calc_hp_IV_min_and_Max(this->hp, level);
    calc_IV_min_and_Max(this->att, level, this->att.nature);
    calc_IV_min_and_Max(this->def, level, this->def.nature);
    calc_IV_min_and_Max(this->spec_attack, level, this->spec_attack.nature);
    calc_IV_min_and_Max(this->spec_def, level, this->spec_def.nature);
    calc_IV_min_and_Max(this->speed, level, this->speed.nature);
    set_move(this->move1, "move 1", 0, 0, false);
    set_move(this->move2, "move 2", 0, 0, false);
    set_move(this->move3, "move 3", 0, 0, false);
    set_move(this->move4, "move 4", 0, 0, false);
    this->name = name;
}
void Pokemon::init_stat_from_base(Stat &stat, int base, int level) {
    stat.base = base;
    stat.bottomIV = 0;
    stat.EV = 0;
    stat.topIV = 0;
    calc_current_stat(stat, level, stat.nature);
}

void Pokemon::init_hp_from_base(Stat &stat, int base, int level) {
    stat.base = base;
    stat.bottomIV = 0;
    stat.EV = 0;
    stat.topIV = 0;
    calc_current_hp(stat, level);
}

void Pokemon::init_natures(string nature) {
    this->hp.nature = 1.0;
    this->att.nature = 1.0;
    this->def.nature = 1.0;
    this->spec_attack.nature = 1.0;
    this->spec_def.nature = 1.0;
    this->speed.nature = 1.0;

    if (nature == "adamant") {
        set_nature_stat(this->att, true);
        set_nature_stat(this->spec_attack, false);
        // att spec att
    } else if (nature == "bold") {
        set_nature_stat(this->def, true);
        set_nature_stat(this->att, false);
        // def att
    } else if (nature == "Brave") {
        // att speed
        set_nature_stat(this->att, true);
        set_nature_stat(this->speed, false);
    } else if (nature == "calm") {
        set_nature_stat(this->spec_def, true);
        set_nature_stat(this->att, false);
    } else if (nature == "careful") {
        set_nature_stat(this->spec_def, true);
        set_nature_stat(this->spec_attack, false);
    } else if (nature == "gentle") {
        set_nature_stat(this->spec_def, true);
        set_nature_stat(this->def, false);
    } else if (nature == "hasty") {
        set_nature_stat(this->speed, true);
        set_nature_stat(this->def, false);
    } else if (nature == "impish") {
        set_nature_stat(this->def, true);
        set_nature_stat(this->spec_attack, false);
    } else if (nature == "jolly") {
        set_nature_stat(this->speed, true);
        set_nature_stat(this->spec_attack, false);
    } else if (nature == "lax") {
        set_nature_stat(this->def, true);
        set_nature_stat(this->spec_def, false);
    } else if (nature == "lonely") {
        set_nature_stat(this->att, true);
        set_nature_stat(this->def, false);
    } else if (nature == "mild") {
        set_nature_stat(this->spec_attack, true);
        set_nature_stat(this->def, false);
    } else if (nature == "modest") {
        set_nature_stat(this->spec_attack, true);
        set_nature_stat(this->att, false);
    } else if (nature == "naive") {
        set_nature_stat(this->speed, true);
        set_nature_stat(this->spec_def, false);
    } else if (nature == "naughty") {
        set_nature_stat(this->att, true);
        set_nature_stat(this->spec_def, false);
    } else if (nature == "quiet") {
        set_nature_stat(this->spec_attack, true);
        set_nature_stat(this->speed, false);
    } else if (nature == "rash") {
        set_nature_stat(this->spec_attack, true);
        set_nature_stat(this->spec_def, false);
    } else if (nature == "relaxed") {
        set_nature_stat(this->def, true);
        set_nature_stat(this->speed, false);
    } else if (nature == "sassy") {
        set_nature_stat(this->spec_def, true);
        set_nature_stat(this->speed, false);
    } else if (nature == "timid") {
        set_nature_stat(this->speed, true);
        set_nature_stat(this->att, false);
    }
}
void Pokemon::set_move(Move &move, string name, int power, int type, bool stab) {
    move.name = name;
    move.power = power;
    move.type = type;
    move.stab = stab;
}
void Pokemon::init_move_from_string(Move &move, string csv) {
    char input[csv.length()];
    strcpy(input, csv.c_str());
    char *token[4];
    token[0] = strtok(input, ",");
    for (int i = 1; i < 4; i++) {
        token[i] = strtok(NULL, ",");
    }
    move.name = token[0];
    move.power = atoi(token[1]);
    move.type = atoi(token[2]);
    move.stab = atoi(token[3]);
}
void Pokemon::recalculate_stats() {
    recalculate_current_stat(this->hp, true);
    recalculate_current_stat(this->att, false);
    recalculate_current_stat(this->def, false);
    recalculate_current_stat(this->spec_attack, false);
    recalculate_current_stat(this->spec_def, false);
    recalculate_current_stat(this->speed, false);
}

void Pokemon::update_IVs() {
    calc_hp_IV_min_and_Max(this->hp, this->currentLevel);
    calc_IV_min_and_Max(this->att, this->currentLevel, this->att.nature);
    calc_IV_min_and_Max(this->def, this->currentLevel, this->def.nature);
    calc_IV_min_and_Max(this->spec_attack, this->currentLevel, this->spec_attack.nature);
    calc_IV_min_and_Max(this->spec_def, this->currentLevel, this->spec_def.nature);
    calc_IV_min_and_Max(this->speed, this->currentLevel, this->speed.nature);
    // TODO
}
void Pokemon::recalculate_current_stat(Stat &stat, bool isHp) {
    // TODO
    if (isHp) {
        calc_current_hp(stat, this->currentLevel);
    } else {
        calc_current_stat(stat, this->currentLevel, stat.nature);
    }
}

void Pokemon::calc_IV_min_and_Max(Stat &stat, int level, float nature) {
    for (int i = 0; i < 32; i++) {
        int statBase = stat.base *2;
        int statEV = stat.EV /4;
        if ((int)floor(((((i + statBase + statEV) * level) / 100) + 5) * nature) == stat.current) {
            stat.bottomIV = i;
            break;
        } 
    }
    for (int i = 31; i >= 0; i--) {
        if ((int)floor(((((i + (2 * stat.base) + (stat.EV / 4)) * level) / 100) + 5) * nature) == stat.current) {
            stat.topIV = i;
            break;
        } 
    }
}
void Pokemon::calc_hp_IV_min_and_Max(Stat &stat, int level) {
    for (int i = 0; i < 32; i++) {
        if ((((i + (2 * hp.base) + (hp.EV / 4)) * level) / 100) + 10 + level == stat.current) {
            stat.bottomIV = i;
            break;
        } 
    }
    for (int i = 31; i >= 0; i--) {
        if ((((i + (2 * hp.base) + (hp.EV / 4)) * level) / 100) + 10 + level == stat.current) {
            stat.topIV = i;       
            break;
        }
    }
}
void Pokemon::calc_current_stat(Stat &stat, int level, float nature) {
    int ivAverage = (stat.bottomIV + stat.topIV) / 2;
    stat.current = (int)floor(((((ivAverage + (2 * stat.base) + (stat.EV / 4)) * level) / 100) + 5) * nature);
}
void Pokemon::calc_current_hp(Stat &hp, int level) {
    int ivAverage = (hp.bottomIV + hp.topIV) / 2;
    hp.current = (((ivAverage + (2 * hp.base) + (hp.EV / 4)) * level) / 100) + 10 + level;
}
void Pokemon::set_nature_stat(Stat &stat, bool increase) {
    if (increase) {
        stat.nature = 1.1;
    } else {
        stat.nature = 0.9;
    }
}