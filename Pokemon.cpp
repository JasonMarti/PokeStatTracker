#include "Pokemon.h"
#include <string>
#include <cmath>

using namespace std;

Pokemon::Pokemon()
{
    this->name = "";
    this->nature = "adamant";
    initNatures("adamant", this->hp, this->att, this->def, this->spec_attack, this->spec_def, this->speed);
    init_stat_from_base(this->hp, 0, 1);
    init_stat_from_base(this->att, 0, 1);
    init_stat_from_base(this->def, 0, 1);
    init_stat_from_base(this->spec_attack, 0, 1);
    init_stat_from_base(this->spec_def, 0, 1);
    init_stat_from_base(this->speed, 0, 1);
}

Pokemon::Pokemon(string name, Stat hp, Stat att, Stat def, Stat spec_attack, Stat spec_def, Stat speed, string newNature)
{
    initNatures(newNature, this->hp, this->att, this->def, this->spec_attack, this->spec_def, this->speed);
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
    initNatures(newNature, this->hp, this->att, this->def, this->spec_attack, this->spec_def, this->speed);
    init_stat_from_base(this->hp, hp, level);
    init_stat_from_base(this->att, att, level);
    init_stat_from_base(this->def, def, level);
    init_stat_from_base(this->spec_attack, satt, level);
    init_stat_from_base(this->spec_def, sdef, level);
    init_stat_from_base(this->speed, speed, level);

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

void Pokemon::initNatures(string nature, Stat &hp, Stat &att, Stat &def, Stat &spec_attack, Stat &spec_def, Stat &speed)
{
    hp.nature = 1.0;
    att.nature = 1.0;
    def.nature = 1.0;
    spec_attack.nature = 1.0;
    spec_def.nature = 1.0;
    speed.nature = 1.0;

    if (nature == "adamant")
    {
        att = setNatureStat(att, true);
        spec_attack = setNatureStat(spec_attack, false);
        //att spec att
    }
    else if (nature == "bold")
    {
        def = setNatureStat(def, true);
        att = setNatureStat(att, false);
        //def att
    }
    else if (nature == "Brave")
    {
        //att speed
        att = setNatureStat(att, true);
        speed = setNatureStat(speed, false);
    }
    else if (nature == "calm")
    {
        spec_def = setNatureStat(spec_def, true);
        att = setNatureStat(att, false);
    }
    else if (nature == "careful")
    {
        spec_def = setNatureStat(spec_def, true);
        spec_attack = setNatureStat(spec_attack, false);
    }
    else if (nature == "gentle")
    {
        spec_def = setNatureStat(spec_def, true);
        def = setNatureStat(def, false);
    }
    else if (nature == "hasty")
    {
        speed = setNatureStat(speed, true);
        def = setNatureStat(def, false);
    }
    else if (nature == "impish")
    {
        def = setNatureStat(def, true);
        spec_attack = setNatureStat(spec_attack, false);
    }
    else if (nature == "jolly")
    {
        speed = setNatureStat(speed, true);
        spec_attack = setNatureStat(spec_attack, false);
    }
    else if (nature == "lax")
    {

        def = setNatureStat(def, true);
        spec_def = setNatureStat(spec_def, false);
    }
    else if (nature == "lonely")
    {
        att = setNatureStat(att, true);
        def = setNatureStat(def, false);
    }
    else if (nature == "mild")
    {
        spec_attack = setNatureStat(spec_attack, true);
        def = setNatureStat(def, false);
    }
    else if (nature == "modest")
    {
        spec_attack = setNatureStat(spec_attack, true);
        att = setNatureStat(att, false);
    }
    else if (nature == "naive")
    {
        speed = setNatureStat(speed, true);
        spec_def = setNatureStat(spec_def, false);
    }
    else if (nature == "naughty")
    {
        att = setNatureStat(att, true);
        spec_def = setNatureStat(spec_def, false);
    }
    else if (nature == "quiet")
    {
        spec_attack = setNatureStat(spec_attack, true);
        speed = setNatureStat(speed, false);
    }
    else if (nature == "rash")
    {
        spec_attack = setNatureStat(spec_attack, true);
        spec_def = setNatureStat(spec_def, false);
    }
    else if (nature == "relaxed")
    {
        def = setNatureStat(def, true);
        speed = setNatureStat(speed, false);
    }
    else if (nature == "sassy")
    {
        spec_def = setNatureStat(spec_def, true);
        speed = setNatureStat(speed, false);
    }
    else if (nature == "timid")
    {
        speed = setNatureStat(speed, true);
        att = setNatureStat(att, false);
    }
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