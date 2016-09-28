#include <fstream>
#include <vector>
extern std::vector<std::vector<float> >hex;
extern std::vector<std::vector<int> >lines;
extern std::vector<bool>outline;
extern std::vector<int>pos2;
extern int current;
extern int phase;
extern int pos1;
extern bool menuup;
extern bool menudown;
extern bool menu;
void Rend_init();
void Rend_lep();
void Render();
void counter_add();
void counter_reset();
void movemup(long long);
void movemdown(long long);