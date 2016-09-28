#include <vector>
void move(float x, float y);
void size(float c);
void zoom(float rat);
void zoomb(float rat);
void undo();
extern std::vector<std::vector<float> >hitb;
extern std::vector<std::vector<float> >menuhitb;
extern int hover;
extern bool hovere;
extern float undox;
extern float undoy;