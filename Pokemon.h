#include <string>
using namespace std;

struct Stat {
    int base;
    int current;
    int topIV;
    int bottomIV;
    int EV;
    float nature;
};


class Pokemon 
{
public:
Pokemon();
//load
Pokemon(string name, Stat hp, Stat att, Stat def, Stat spec_attack, Stat spec_def, Stat speed, string nature);
//new
Pokemon(string name, int hp_base, int att_base, int def_base, int spec_att_base, int spec_def_base, int speed_base, string nature, int level);
    string name;
    string nature;
    Stat hp;
    Stat att;
    Stat def;
    Stat spec_attack;
    Stat spec_def;
    Stat speed;
private:
    void init_stat_from_base(Stat &stat, int base, int level);
    int calc_current_stat(Stat stat, int level, float nature);
    Stat calc_IV_min_and_Max(Stat stat, int level, float nature);
    Stat calc_hp_min_and_Max(Stat hp, int level);
    Stat setNatureStat(Stat stat, bool increase);
    void initNatures(string nature, Stat& hp, Stat& att, Stat& def, Stat& spec_attack, Stat& spec_def, Stat& speed);
};
