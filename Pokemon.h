#include <string>
#include <map>
using namespace std;

struct Stat
{
    int base;
    int current;
    int topIV;
    int bottomIV;
    int EV;
    float nature;
};

struct Move
{
  string name;
  int power;
  int type;
  bool stab;
};

class Pokemon
{
public:
    
    Pokemon();
    //load
    Pokemon(string csv);
    //new
    Pokemon(string name, int hp_base, int att_base, int def_base, int spec_att_base, int spec_def_base, int speed_base, string nature, int level);
    string name;
    string nature;
    int currentLevel;
    Stat hp;
    Stat att;
    Stat def;
    Stat spec_attack;
    Stat spec_def;
    Stat speed;
    Move move1;
    Move move2;
    Move move3;
    Move move4;
    void recalculate_stats(); //TODO
    void update_IVs(); //TODO

private:
    void blank_init();
    void init_stat_from_base(Stat &stat, int base, int level);
    int calc_current_stat(Stat stat, int level, float nature);
    int calc_current_hp(Stat hp, int level);
    void init_hp_from_base(Stat &stat, int base, int level);
    void calc_IV_min_and_Max(Stat &stat, int level, float nature);
    void calc_hp_IV_min_and_Max(Stat &stat, int level);
    void recalculate_current_stat(Stat &stat, int level, bool isHp);
    void recalculate_IV_range(Stat &stat, int level, bool isHp); 
    Stat set_nature_stat(Stat stat, bool increase);
    void init_natures(string nature, Stat &hp, Stat &att, Stat &def, Stat &spec_attack, Stat &spec_def, Stat &speed);
    void init_stat_from_string(Stat &stat, string csv);
    void init_header_from_string(string csv);
    void set_move(Move &move, string name, int power, int type, bool stab);
    void init_move_from_string(Move &move, string csv);
};
