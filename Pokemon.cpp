#include "Pokemon.h"
#include <string>
#include <cmath>

using namespace std;

Pokemon::Pokemon(string name, Stat hp, Stat att, Stat def, Stat spec_attack, Stat spec_def, Stat speed)
{
    this->name = name;
    this->hp = hp;
    this->att = att;
    this->def = def;
    this->spec_attack = spec_attack;
    this->spec_def = spec_def;
    this->speed = speed;
}
//assumsIVs are 0
Pokemon::Pokemon(string name, int hp, int att, int def, int satt, int sdef, int speed, string nature, int level)
{
    this->hp = init_stat_from_base(hp, level);
    this->att = init_stat_from_base(att, level);
    this->def = init_stat_from_base(def, level);
    this->spec_attack = init_stat_from_base(satt, level);
    this->spec_def = init_stat_from_base(sdef, level);
    this->speed = init_stat_from_base(speed, level);

    this->hp.nature = 1.0; //not necessary but for safety
    this->att.nature = 1.0;
    this->def.nature = 1.0;
    this->spec_attack.nature = 1.0;
    this->spec_def.nature = 1.0;
    this->speed.nature = 1.0;

    this->name = name;
    if (nature == "adamant")
    {
        this->att = setNatureStat(this->att, true);
        this->spec_attack = setNatureStat(this->spec_attack, false);
        //att spec att
    }
    else if (nature == "bold")
    {
        this->def = setNatureStat(this->def, true);
        this->att = setNatureStat(this->att, false);
        //def att
    }
    else if (nature == "Brave")
    {
        //att speed
        this->att = setNatureStat(this->att, true);
        this->speed = setNatureStat(this->speed, false);
    }
    else if (nature == "calm")
    {
        this->spec_def = setNatureStat(this->spec_def, true);
        this->att = setNatureStat(this->att, false);
    }
    else if (nature == "careful")
    {
        this->spec_def = setNatureStat(this->spec_def, true);
        this->spec_attack = setNatureStat(this->spec_attack, false);
    }
    else if (nature == "gentle")
    {
        this->spec_def = setNatureStat(this->spec_def, true);
        this->def = setNatureStat(this->def, false);
    }
    else if (nature == "hasty")
    {
        this->speed = setNatureStat(this->speed, true);
        this->def = setNatureStat(this->def, false);
    }
    else if (nature == "impish")
    {
        this->def = setNatureStat(this->def, true);
        this->spec_attack = setNatureStat(this->spec_attack, false);
        }
    else if (nature == "jolly")
    {
        this->speed = setNatureStat(this->speed, true);
        this->spec_attack = setNatureStat(this->spec_attack, false);
    }
    else if (nature == "lax")
    {

        this->def = setNatureStat(this->def, true);
        this->spec_def = setNatureStat(this->spec_def, false);
    }
    else if (nature == "lonely")
    {
        this->att = setNatureStat(this->att, true);
        this->def = setNatureStat(this->def, false);
    }
    else if (nature == "mild")
    {
        this->spec_attack = setNatureStat(this->spec_attack, true);
        this->def = setNatureStat(this->def, false);
    }
    else if (nature == "modest")
    {
        this->spec_attack = setNatureStat(this->spec_attack, true);
        this->att = setNatureStat(this->att, false);
    }
    else if (nature == "naive")
    {
        this->speed = setNatureStat(this->speed, true);
        this->spec_def = setNatureStat(this->spec_def, false);
    }
    else if (nature == "naughty")
    {
        this->att = setNatureStat(this->att, true);
        this->spec_def = setNatureStat(this->spec_def, false);
    }
    else if (nature == "quiet")
    {
        this->spec_attack = setNatureStat(this->spec_attack, true);
        this->speed = setNatureStat(this->speed, false);
    }
    else if (nature == "rash")
    {
        this->spec_attack = setNatureStat(this->spec_attack, true);
        this->spec_def = setNatureStat(this->spec_def, false);
    }
    else if (nature == "relaxed")
    {
        this->def = setNatureStat(this->def, true);
        this->speed = setNatureStat(this->speed, false);
    }
    else if (nature == "sassy")
    {
        this->spec_def = setNatureStat(this->spec_def, true);
        this->speed = setNatureStat(this->speed, false);
    }
    else if (nature == "timid")
    {
        this->speed = setNatureStat(this->speed, true);
        this->att = setNatureStat(this->att, false);
    }
}
Stat Pokemon::init_stat_from_base(int base, int level)
{
    Stat stat;
    stat.base = base;
    stat.bottomIV = 0;
    stat.EV = 0;
    stat.topIV = 0;
    stat.current = calc_current_stat(stat, level, stat.nature);
    return stat;
}

Stat Pokemon::calc_IV_min_and_Max(Stat stat, int level, float nature)
{
    Stat returnStat = stat;
    for (int i = 0; i < 32; i++)
    {
        if ((int)floor((((((2 * stat.base) + i + (stat.EV / 4) * level) / 100)) + 5) * nature) == stat.current)
        {
            returnStat.bottomIV = i;
            break;
        }
    }
    for (int i = 31; i >= 0; i--)
    {
        if ((int)floor((((((2 * stat.base) + i + (stat.EV / 4) * level) / 100)) + 5) * nature) == stat.current)
        {
            returnStat.topIV = i;
            break;
        }
    }
    return returnStat;
}
int Pokemon::calc_current_stat(Stat stat, int level, float nature)
{
    return (int)floor((((((2 * stat.base) + ((stat.bottomIV + stat.topIV) / 2) + (stat.EV / 4) * level) / 100)) + 5) * nature);
}
Stat Pokemon::calc_hp_min_and_Max(Stat hp, int level)
{
    Stat returnStat = hp;
    for (int i = 0; i < 32; i++)
    {
        if ((((((2 * hp.base) + i + (hp.EV / 4) * level) / 100)) + level + 10) == hp.current)
        {
            returnStat.bottomIV = i;
            break;
        }
    }
    for (int i = 31; i >= 0; i--)
    {
        if ((((((2 * hp.base) + i + (hp.EV / 4) * level) / 100)) + level + 10) == hp.current)
        {
            returnStat.topIV = i;
            break;
        }
    }
    return returnStat;
}
Stat Pokemon::setNatureStat(Stat stat, bool increase)
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