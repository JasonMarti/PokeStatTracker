#include "Pokemon.h"
#include <cmath>
#include <cstring>
#include <string>

using namespace std;
Pokemon::Pokemon() {}

void Pokemon::blank_init() {
  this->name = "";
  this->nature = "adamant";
  this->currentLevel = 10;
  init_natures("adamant", this->hp, this->att, this->def, this->spec_attack,
               this->spec_def, this->speed);
  init_stat_from_base(this->hp, 0, 1);
  init_stat_from_base(this->att, 0, 1);
  init_stat_from_base(this->def, 0, 1);
  init_stat_from_base(this->spec_attack, 0, 1);
  init_stat_from_base(this->spec_def, 0, 1);
  init_stat_from_base(this->speed, 0, 1);
}
void Pokemon::init_stat_from_string(Stat &stat, string csv) {
  char input[csv.length()];
  strcpy(input, csv.c_str());
  char *token[6];
  token[0] = strtok(input, ",");
  for (int i = 1; i < 6; i++) {
    token[i] = strtok(NULL, ",");
  }
  stat.base = atoi(token[0]);
  stat.current = atoi(token[1]);
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
  char *section[7];
  char *token;
  section[0] = strtok(input, ";");
  for (int i = 1; i < 7; i++) {
    section[i] = strtok(NULL, ";");
  }
  init_header_from_string(section[0]);
  init_stat_from_string(this->hp, section[1]);
  init_stat_from_string(this->att, section[2]);
  init_stat_from_string(this->def, section[3]);
  init_stat_from_string(this->spec_attack, section[4]);
  init_stat_from_string(this->spec_def, section[5]);
  init_stat_from_string(this->speed, section[6]);
  // TODO moves
}

// assumsIVs are 0
Pokemon::Pokemon(string name, int hp, int att, int def, int satt, int sdef,
                 int speed, string newNature, int level) {
  this->nature = newNature;
  this->currentLevel = level;
  init_natures(newNature, this->hp, this->att, this->def, this->spec_attack,
               this->spec_def, this->speed);
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

  this->name = name;
}
void Pokemon::init_stat_from_base(Stat &stat, int base, int level) {
  stat.base = base;
  stat.bottomIV = 0;
  stat.EV = 0;
  stat.topIV = 0;
  stat.current = calc_current_stat(stat, level, stat.nature);
}

void Pokemon::init_hp_from_base(Stat &stat, int base, int level) {
  stat.base = base;
  stat.bottomIV = 0;
  stat.EV = 0;
  stat.topIV = 0;
  stat.current = calc_current_hp(stat, level);
}

void Pokemon::init_natures(string nature, Stat &hp, Stat &att, Stat &def,
                           Stat &spec_attack, Stat &spec_def, Stat &speed) {
  hp.nature = 1.0;
  att.nature = 1.0;
  def.nature = 1.0;
  spec_attack.nature = 1.0;
  spec_def.nature = 1.0;
  speed.nature = 1.0;

  if (nature == "adamant") {
    att = set_nature_stat(att, true);
    spec_attack = set_nature_stat(spec_attack, false);
    // att spec att
  } else if (nature == "bold") {
    def = set_nature_stat(def, true);
    att = set_nature_stat(att, false);
    // def att
  } else if (nature == "Brave") {
    // att speed
    att = set_nature_stat(att, true);
    speed = set_nature_stat(speed, false);
  } else if (nature == "calm") {
    spec_def = set_nature_stat(spec_def, true);
    att = set_nature_stat(att, false);
  } else if (nature == "careful") {
    spec_def = set_nature_stat(spec_def, true);
    spec_attack = set_nature_stat(spec_attack, false);
  } else if (nature == "gentle") {
    spec_def = set_nature_stat(spec_def, true);
    def = set_nature_stat(def, false);
  } else if (nature == "hasty") {
    speed = set_nature_stat(speed, true);
    def = set_nature_stat(def, false);
  } else if (nature == "impish") {
    def = set_nature_stat(def, true);
    spec_attack = set_nature_stat(spec_attack, false);
  } else if (nature == "jolly") {
    speed = set_nature_stat(speed, true);
    spec_attack = set_nature_stat(spec_attack, false);
  } else if (nature == "lax") {
    def = set_nature_stat(def, true);
    spec_def = set_nature_stat(spec_def, false);
  } else if (nature == "lonely") {
    att = set_nature_stat(att, true);
    def = set_nature_stat(def, false);
  } else if (nature == "mild") {
    spec_attack = set_nature_stat(spec_attack, true);
    def = set_nature_stat(def, false);
  } else if (nature == "modest") {
    spec_attack = set_nature_stat(spec_attack, true);
    att = set_nature_stat(att, false);
  } else if (nature == "naive") {
    speed = set_nature_stat(speed, true);
    spec_def = set_nature_stat(spec_def, false);
  } else if (nature == "naughty") {
    att = set_nature_stat(att, true);
    spec_def = set_nature_stat(spec_def, false);
  } else if (nature == "quiet") {
    spec_attack = set_nature_stat(spec_attack, true);
    speed = set_nature_stat(speed, false);
  } else if (nature == "rash") {
    spec_attack = set_nature_stat(spec_attack, true);
    spec_def = set_nature_stat(spec_def, false);
  } else if (nature == "relaxed") {
    def = set_nature_stat(def, true);
    speed = set_nature_stat(speed, false);
  } else if (nature == "sassy") {
    spec_def = set_nature_stat(spec_def, true);
    speed = set_nature_stat(speed, false);
  } else if (nature == "timid") {
    speed = set_nature_stat(speed, true);
    att = set_nature_stat(att, false);
  }
}

void Pokemon::update_IVs() {}
void Pokemon::calc_IV_min_and_Max(Stat &stat, int level, float nature) {
  for (int i = 0; i < 32; i++) {
    if ((int)floor(
            ((((i + (2 * stat.base) + (stat.EV / 4)) * level) / 100) + 5) *
            nature) == stat.current) {
      stat.bottomIV = i;
      break;
    }
  }
  for (int i = 31; i >= 0; i--) {
    if ((int)floor(
            ((((i + (2 * stat.base) + (stat.EV / 4)) * level) / 100) + 5) *
            nature) == stat.current) {
      stat.topIV = i;
      break;
    }
  }
}
void Pokemon::calc_hp_IV_min_and_Max(Stat &stat, int level) {
  for (int i = 0; i < 32; i++) {
    if ((((i + (2 * hp.base) + (hp.EV / 4)) * level) / 100) + 10 + level ==
        stat.current) {
      stat.bottomIV = i;
      break;
    }
  }
  for (int i = 31; i >= 0; i--) {
    if ((((i + (2 * hp.base) + (hp.EV / 4)) * level) / 100) + 10 + level ==
        stat.current) {
      stat.topIV = i;
      break;
    }
  }
}
int Pokemon::calc_current_stat(Stat stat, int level, float nature) {
  int ivAverage = (stat.bottomIV + stat.topIV) / 2;
  int temp = (int)floor(
      ((((ivAverage + (2 * stat.base) + (stat.EV / 4)) * level) / 100) + 5) *
      nature);
  return temp;
}
int Pokemon::calc_current_hp(Stat hp, int level) {
  int ivAverage = (hp.bottomIV + hp.topIV) / 2;
  int temp =
      (((ivAverage + (2 * hp.base) + (hp.EV / 4)) * level) / 100) + 10 + level;
  return temp;
}
Stat Pokemon::set_nature_stat(Stat stat, bool increase) {
  if (increase) {
    stat.nature = 1.1;
  } else {
    stat.nature = 0.9;
  }
  return stat;
}