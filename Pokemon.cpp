#include "Pokemon.h"
#include <string>
#include <cmath>

using namespace std;

Pokemon::Pokemon()
{
    this->name = "";
    this->nature = "adamant";
    init_natures("adamant", this->hp, this->att, this->def, this->spec_attack, this->spec_def, this->speed);
    init_stat_from_base(this->hp, 0, 1);
    init_stat_from_base(this->att, 0, 1);
    init_stat_from_base(this->def, 0, 1);
    init_stat_from_base(this->spec_attack, 0, 1);
    init_stat_from_base(this->spec_def, 0, 1);
    init_stat_from_base(this->speed, 0, 1);

}

Pokemon::Pokemon(string name, Stat hp, Stat att, Stat def, Stat spec_attack, Stat spec_def, Stat speed, string newNature, int level)
{
    init_natures(newNature, this->hp, this->att, this->def, this->spec_attack, this->spec_def, this->speed);
    this->currentLevel = level;
    this->nature = newNature;
    this->name = name;
    this->hp = hp;
    this->att = att;
    this->def = def;
    this->spec_attack = spec_attack;
    this->spec_def = spec_def;
    this->speed = speed;
}

//assumsIVs are 0
Pokemon::Pokemon(string name, int hp, int att, int def, int satt, int sdef, int speed, string newNature, int level)
{
    this->nature = newNature;
    this->currentLevel = level;
    init_natures(newNature, this->hp, this->att, this->def, this->spec_attack, this->spec_def, this->speed);
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
void Pokemon::init_stat_from_base(Stat &stat, int base, int level)
{
    stat.base = base;
    stat.bottomIV = 0;
    stat.EV = 0;
    stat.topIV = 0;
    stat.current = calc_current_stat(stat, level, stat.nature);
}

void Pokemon::init_hp_from_base(Stat &stat, int base, int level)
{
    stat.base = base;
    stat.bottomIV = 0;
    stat.EV = 0;
    stat.topIV = 0;
    stat.current = calc_current_hp(stat, level);
}

void Pokemon::init_natures(string nature, Stat &hp, Stat &att, Stat &def, Stat &spec_attack, Stat &spec_def, Stat &speed)
{
    hp.nature = 1.0;
    att.nature = 1.0;
    def.nature = 1.0;
    spec_attack.nature = 1.0;
    spec_def.nature = 1.0;
    speed.nature = 1.0;

    if (nature == "adamant")
    {
        att = set_nature_stat(att, true);
        spec_attack = set_nature_stat(spec_attack, false);
        //att spec att
    }
    else if (nature == "bold")
    {
        def = set_nature_stat(def, true);
        att = set_nature_stat(att, false);
        //def att
    }
    else if (nature == "Brave")
    {
        //att speed
        att = set_nature_stat(att, true);
        speed = set_nature_stat(speed, false);
    }
    else if (nature == "calm")
    {
        spec_def = set_nature_stat(spec_def, true);
        att = set_nature_stat(att, false);
    }
    else if (nature == "careful")
    {
        spec_def = set_nature_stat(spec_def, true);
        spec_attack = set_nature_stat(spec_attack, false);
    }
    else if (nature == "gentle")
    {
        spec_def = set_nature_stat(spec_def, true);
        def = set_nature_stat(def, false);
    }
    else if (nature == "hasty")
    {
        speed = set_nature_stat(speed, true);
        def = set_nature_stat(def, false);
    }
    else if (nature == "impish")
    {
        def = set_nature_stat(def, true);
        spec_attack = set_nature_stat(spec_attack, false);
    }
    else if (nature == "jolly")
    {
        speed = set_nature_stat(speed, true);
        spec_attack = set_nature_stat(spec_attack, false);
    }
    else if (nature == "lax")
    {

        def = set_nature_stat(def, true);
        spec_def = set_nature_stat(spec_def, false);
    }
    else if (nature == "lonely")
    {
        att = set_nature_stat(att, true);
        def = set_nature_stat(def, false);
    }
    else if (nature == "mild")
    {
        spec_attack = set_nature_stat(spec_attack, true);
        def = set_nature_stat(def, false);
    }
    else if (nature == "modest")
    {
        spec_attack = set_nature_stat(spec_attack, true);
        att = set_nature_stat(att, false);
    }
    else if (nature == "naive")
    {
        speed = set_nature_stat(speed, true);
        spec_def = set_nature_stat(spec_def, false);
    }
    else if (nature == "naughty")
    {
        att = set_nature_stat(att, true);
        spec_def = set_nature_stat(spec_def, false);
    }
    else if (nature == "quiet")
    {
        spec_attack = set_nature_stat(spec_attack, true);
        speed = set_nature_stat(speed, false);
    }
    else if (nature == "rash")
    {
        spec_attack = set_nature_stat(spec_attack, true);
        spec_def = set_nature_stat(spec_def, false);
    }
    else if (nature == "relaxed")
    {
        def = set_nature_stat(def, true);
        speed = set_nature_stat(speed, false);
    }
    else if (nature == "sassy")
    {
        spec_def = set_nature_stat(spec_def, true);
        speed = set_nature_stat(speed, false);
    }
    else if (nature == "timid")
    {
        speed = set_nature_stat(speed, true);
        att = set_nature_stat(att, false);
    }
}

void Pokemon::calc_IV_min_and_Max(Stat &stat, int level, float nature)
{
    for (int i = 0; i < 32; i++)
    {
        if ((int)floor(((((i + (2 * stat.base) + (stat.EV / 4)) * level) / 100) + 5) * nature) == stat.current)
        {
            stat.bottomIV = i;
            break;
        }
    }
    for (int i = 31; i >= 0; i--)
    {
        if ((int)floor(((((i + (2 * stat.base) + (stat.EV / 4)) * level) / 100) + 5) * nature) == stat.current)
        {
            stat.topIV = i;
            break;
        }
    }
}
void Pokemon::calc_hp_IV_min_and_Max(Stat &stat, int level)
{
    for (int i = 0; i < 32; i++)
    {
        if ((((i + (2 * hp.base) + (hp.EV / 4)) * level) / 100) + 10 + level == stat.current)
        {
            stat.bottomIV = i;
            break;
        }
    }
    for (int i = 31; i >= 0; i--)
    {
        if ((((i + (2 * hp.base) + (hp.EV / 4)) * level) / 100) + 10 + level == stat.current)
        {
            stat.topIV = i;
            break;
        }
    }
}
int Pokemon::calc_current_stat(Stat stat, int level, float nature)
{
    int ivAverage = (stat.bottomIV + stat.topIV) / 2;
    int temp = (int)floor(((((ivAverage + (2 * stat.base) + (stat.EV / 4)) * level) / 100) + 5) * nature);
    return temp;
}
int Pokemon::calc_current_hp(Stat hp, int level)
{
    int ivAverage = (hp.bottomIV + hp.topIV) / 2;
    int temp = (((ivAverage + (2 * hp.base) + (hp.EV / 4)) * level) / 100) + 10 + level;
    return temp;
}
Stat Pokemon::set_nature_stat(Stat stat, bool increase)
{
    if (increase)
    {
        stat.nature = 1.1;
    }
    else
    {
        stat.nature = 0.9;
    }
    return stat;
}