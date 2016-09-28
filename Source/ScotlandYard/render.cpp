#include "MlinkR.h"
#include "RlinkOGL.h"
#include "IlinkR.h"

struct pos{
	int o;
	float x, y;
};

std::vector<std::vector<std::vector<float> > > objs;
std::vector<pos>map;
std::vector<pos>map2;
std::vector<pos>mapgui;
std::vector<pos>mapmenu;
std::vector<std::vector<int> >pos2s;
std::vector<std::vector<bool> >outlines;
std::vector<int> pos1s;
float a, b;
std::vector<float> c;
float wrat, hrat;
int width1 = 100, height1 = 100;
std::vector<std::vector<float> >hitb;
std::vector<std::vector<float> >menuhitb;
float undox, undoy;
bool undoe = false;;

void oload(){
	std::ifstream ifs;
	ifs.open("objs.txt", std::ifstream::in);
	int n, m;
	float a, b;
	ifs >> n;
	objs.resize(n);
	for (int i = 0; i < n; i++){
		ifs >> m;
		objs[i].resize(m);
		ifs >> a;
		for (int j = 0; j < m; j++){
			objs[i][j].resize(9);
			for (int k = 0; k < 9; k++){
				ifs >> b;
				if (k>2) objs[i][j][k] = a*b; else objs[i][j][k] = b;
			}
		}
	}
	ifs.close();
}

void orescale(int a, float x, float y){
	for (int i = 0; i < objs[a].size(); i++){
		objs[a][i][3] = objs[a][i][3] * x;
		objs[a][i][4] = objs[a][i][4] * y;
		objs[a][i][5] = objs[a][i][5] * x;
		objs[a][i][6] = objs[a][i][6] * y;
		objs[a][i][7] = objs[a][i][7] * x;
		objs[a][i][8] = objs[a][i][8] * y;
	}
}

void Menuhitbox(){
	menuhitb[0][0] = mapmenu[3].x - objs[0][0][5];
	menuhitb[0][1] = mapmenu[3].y + objs[0][0][8];
	menuhitb[0][2] = mapmenu[3].x + objs[0][0][5];
	menuhitb[0][3] = mapmenu[3].y - objs[0][0][8];
	menuhitb[1][0] = mapmenu[4].x - objs[0][0][5];
	menuhitb[1][1] = mapmenu[4].y + objs[0][0][8];
	menuhitb[1][2] = mapmenu[4].x + objs[0][0][5];
	menuhitb[1][3] = mapmenu[4].y - objs[0][0][8];
	for (int i = 5; i < mapmenu.size(); i++){
		menuhitb[i-3][0] = mapmenu[i].x - objs[mapmenu[i].o][0][7];
		menuhitb[i-3][1] = mapmenu[i].y + objs[mapmenu[i].o][0][8];
		menuhitb[i-3][2] = mapmenu[i].x + objs[mapmenu[i].o][0][7];
		menuhitb[i-3][3] = mapmenu[i].y - objs[mapmenu[i].o][0][8];
	}
}

void Hitbox(){
	for (int i = 0; i < map2.size(); i++){
		hitb[i][0] = map2[i].x - objs[0][0][5];
		hitb[i][1] = map2[i].y + objs[0][0][8];
		hitb[i][2] = map2[i].x + objs[0][0][5];
		hitb[i][3] = map2[i].y - objs[0][0][8];
	}
}

void drawmap(){
	poly[2].resize(0);
	for (int i = 0; i < map.size(); i++){
		for (int j = 0; j < objs[map[i].o].size(); j++){
			c[0] = objs[map[i].o][j][0];
			c[1] = objs[map[i].o][j][1];
			c[2] = objs[map[i].o][j][2];
			c[3] = objs[map[i].o][j][3] + map[i].x;
			c[4] = objs[map[i].o][j][4] + map[i].y;
			c[5] = objs[map[i].o][j][5] + map[i].x;
			c[6] = objs[map[i].o][j][6] + map[i].y;
			c[7] = objs[map[i].o][j][7] + map[i].x;
			c[8] = objs[map[i].o][j][8] + map[i].y;
			poly[2].push_back(c);
		}
	}
}
void drawmap2(){
	poly[3].resize(0);
	for (int i = 0; i < map2.size(); i++){
		for (int j = 0; j < objs[map2[i].o].size(); j++){
			c[0] = objs[map2[i].o][j][0];
			c[1] = objs[map2[i].o][j][1];
			c[2] = objs[map2[i].o][j][2];
			c[3] = objs[map2[i].o][j][3] + map2[i].x;
			c[4] = objs[map2[i].o][j][4] + map2[i].y;
			c[5] = objs[map2[i].o][j][5] + map2[i].x;
			c[6] = objs[map2[i].o][j][6] + map2[i].y;
			c[7] = objs[map2[i].o][j][7] + map2[i].x;
			c[8] = objs[map2[i].o][j][8] + map2[i].y;
			poly[3].push_back(c);
		}
	}
	Hitbox();
}
void drawgui(){
	poly[4].resize(0);
	for (int i = 0; i < mapgui.size(); i++){
		for (int j = 0; j < objs[mapgui[i].o].size(); j++){
			c[0] = objs[mapgui[i].o][j][0];
			c[1] = objs[mapgui[i].o][j][1];
			c[2] = objs[mapgui[i].o][j][2];
			c[3] = objs[mapgui[i].o][j][3] + mapgui[i].x;
			c[4] = objs[mapgui[i].o][j][4] + mapgui[i].y;
			c[5] = objs[mapgui[i].o][j][5] + mapgui[i].x;
			c[6] = objs[mapgui[i].o][j][6] + mapgui[i].y;
			c[7] = objs[mapgui[i].o][j][7] + mapgui[i].x;
			c[8] = objs[mapgui[i].o][j][8] + mapgui[i].y;
			poly[4].push_back(c);
		}
	}
	undox = -1.0f + objs[6][0][7];
	undoy = -1.0f + objs[6][0][8];
}
void drawmenu(){
	poly[6].resize(0);
	for (int i = 0; i < mapmenu.size(); i++){
		for (int j = 0; j < objs[mapmenu[i].o].size(); j++){
			c[0] = objs[mapmenu[i].o][j][0];
			c[1] = objs[mapmenu[i].o][j][1];
			c[2] = objs[mapmenu[i].o][j][2];
			c[3] = objs[mapmenu[i].o][j][3] + mapmenu[i].x;
			c[4] = objs[mapmenu[i].o][j][4] + mapmenu[i].y;
			c[5] = objs[mapmenu[i].o][j][5] + mapmenu[i].x;
			c[6] = objs[mapmenu[i].o][j][6] + mapmenu[i].y;
			c[7] = objs[mapmenu[i].o][j][7] + mapmenu[i].x;
			c[8] = objs[mapmenu[i].o][j][8] + mapmenu[i].y;
			poly[6].push_back(c);
		}
	}
	Menuhitbox();
}

void movemup(long long t){
	float m = t / 200.0f;
	for (int i = 0; i < mapmenu.size(); i++){
		mapmenu[i].y = mapmenu[i].y + m;
	}
	poly[5][0][4] = poly[5][0][4] + m;
	poly[5][0][6] = poly[5][0][6] + m;
	poly[5][0][8] = poly[5][0][8] + m;

	poly[5][1][4] = poly[5][1][4] + m;
	poly[5][1][6] = poly[5][1][6] + m;
	poly[5][1][8] = poly[5][1][8] + m;
	if (poly[5][0][4] >= 1.0f){
		menuup = false;
		mapmenu[0].y = 2.8f;
		mapmenu[1].y = 2.5;
		mapmenu[2].y = 2.5;
		mapmenu[3].y = 2.5;
		mapmenu[4].y = 2.5;
		mapmenu[5].y = 2.2;
		mapmenu[6].y = 2;
		mapmenu[7].y = 1.8;
		poly[5][0][4] = 1.0f;
		poly[5][0][6] = 3.0f;
		poly[5][0][8] = 3.0f;

		poly[5][1][4] = 1.0f;
		poly[5][1][6] = 1.0f;
		poly[5][1][8] = 3.0f;
	}
	drawmenu();
}
void movemdown(long long t){
	float m = t / 200.0f;
	for (int i = 0; i < mapmenu.size(); i++){
		mapmenu[i].y = mapmenu[i].y - m;
	}
	poly[5][0][4] = poly[5][0][4] - m;
	poly[5][0][6] = poly[5][0][6] - m;
	poly[5][0][8] = poly[5][0][8] - m;

	poly[5][1][4] = poly[5][1][4] - m;
	poly[5][1][6] = poly[5][1][6] - m;
	poly[5][1][8] = poly[5][1][8] - m;
	if (poly[5][0][4] <= -1.0f){
		menuup = false;
		mapmenu[0].y = 0.8f;
		mapmenu[1].y = 0.5;
		mapmenu[2].y = 0.5;
		mapmenu[3].y = 0.5;
		mapmenu[4].y = 0.5;
		mapmenu[5].y = 0.2;
		mapmenu[6].y = 0;
		mapmenu[7].y = -0.2;
		poly[5][0][4] = -1.0f;
		poly[5][0][6] = 1.0f;
		poly[5][0][8] = 1.0f;

		poly[5][1][4] = -1.0f;
		poly[5][1][6] = -1.0f;
		poly[5][1][8] = 1.0f;
	}
	drawmenu();
}
void counter_reset(){
	mapgui[1].o = 11;
	mapgui[2].o = 11;
	mapgui[3].o = 11;
	drawgui();
}


void counter_add(){
	mapgui[1].o++;
	if (mapgui[1].o == 21){
		mapgui[1].o = 11;
		mapgui[2].o++;
		if (mapgui[2].o == 21){
			mapgui[2].o = 11;
			mapgui[3].o++;
			if (mapgui[3].o == 21) mapgui[3].o = 11;
		}
	}
	drawgui();
}

void Rend_lep(){
	for (int i = 0; i < map.size(); i++){
		if (outline[i]){
			map[i].o = 3;
		}else{
			map[i].o = 4;
		}
	}
	for (int i = 0; i < map2.size(); i++){
		map2[i].o = 0;
	}
	map2[pos1].o = 1;
	for (int i = 0; i < pos2.size(); i++){
		map2[pos2[i]].o = 2;
	}
	if (undoe){
		undoe = false;
	}
	else{
		pos1s.push_back(pos1);
		pos2s.push_back(pos2);
		outlines.push_back(outline);
	}
	drawmap();
	drawmap2();
}

void undo(){
	if (pos1s.size() > 1 && pos2s.size() > 1 && outlines.size() > 1){
		undoe = true;
		pos1 = pos1s[pos1s.size() - 2];
		pos1s.resize(pos1s.size() - 1);
		pos2 = pos2s[pos2s.size() - 2];
		pos2s.resize(pos2s.size() - 1);
		outline = outlines[outlines.size() - 2];
		outlines.resize(outlines.size() - 1);
	}
	Rend_lep();
}

void asprc(){
	wrat = float(width1) / float(wwidth);
	hrat = float(height1) / float(wheight);
	for (int i = 0; i < objs.size(); i++) orescale(i, wrat, hrat);
	for (int i = 0; i < map.size(); i++){
		map[i].x = map[i].x * wrat;
		map[i].y = map[i].y * hrat;
	}
	for (int i = 0; i < map2.size(); i++){
		map2[i].x = map2[i].x * wrat;
		map2[i].y = map2[i].y * hrat;
	}
	width1 = wwidth;
	height1 = wheight;
	drawmap();
	drawmap2();
	drawgui();
}

void zoom(float rat){
	for (int i = 0; i < map.size(); i++){
		map[i].x = map[i].x * rat;
		map[i].y = map[i].y * rat;
	}
	for (int i = 0; i < map2.size(); i++){
		map2[i].x = map2[i].x * rat;
		map2[i].y = map2[i].y * rat;
	}
	orescale(0, rat, rat);
	orescale(1, rat, rat);
	orescale(2, rat, rat);
	orescale(3, rat, rat);
	orescale(4, rat, rat);
	orescale(5, rat, rat);
	orescale(22, rat, rat);
	orescale(23, rat, rat);
	orescale(24, rat, rat);
	Render();
	drawmap();
	drawmap2();
}

void zoomb(float rat){
	for (int i = 0; i < map.size(); i++){
		map[i].x = map[i].x * rat;
		map[i].y = map[i].y * rat;
	}
	for (int i = 0; i < map2.size(); i++){
		map2[i].x = map2[i].x * rat;
		map2[i].y = map2[i].y * rat;
	}
	Render();
	drawmap();
	drawmap2();
}

void move(float x,float y){
	for (int i = 0; i < map.size(); i++){
		map[i].x = map[i].x + x;
		map[i].y = map[i].y + y;
	}
	for (int i = 0; i < map2.size(); i++){
		map2[i].x = map2[i].x + x;
		map2[i].y = map2[i].y + y;
	}
	Render();
	drawmap();
	drawmap2();
}

void size(float c){
	for (int i = 0; i < objs.size(); i++) orescale(i, c, c);
	Render();
	drawmap();
	drawmap2();
	drawgui();
}

void Rend_init(){
	//load objects
	oload();
	//maps
	map.resize(hex.size());
	map2.resize(hex.size());
	//outlines backup
	objs.resize(25);
	objs[22] = objs[3];
	objs[23] = objs[4];
	objs[24] = objs[5];
	//hitbox init
	hitb.resize(hex.size());
	for (int i = 0; i < hex.size(); i++){
		hitb[i].resize(4);
	}
	//draw init
	c.resize(9);
	poly.resize(7);
	//maps init
	for (int i = 0; i < hex.size(); i++){
		map[i].x = hex[i][0];
		map[i].y = hex[i][1];
		map2[i].x = hex[i][0];
		map2[i].y = hex[i][1];
	}
	//gui
	mapgui.resize(4);
	mapgui[0].o = 6;
	mapgui[0].x = -1;
	mapgui[0].y = -1;
	mapgui[1].o = 11;
	mapgui[1].x = -0.7f;
	mapgui[1].y = 1;
	mapgui[2].o = 11;
	mapgui[2].x = -0.8f;
	mapgui[2].y = 1;
	mapgui[3].o = 11;
	mapgui[3].x = -0.9f;
	mapgui[3].y = 1;
	//menu
	menuhitb.resize(5);
	for (int i = 0; i < menuhitb.size(); i++){
		menuhitb[i].resize(4);
	}
	mapmenu.resize(8);
	mapmenu[0].o = 7;
	mapmenu[0].x = 0;
	mapmenu[0].y = 0.8f;
	mapmenu[1].o = 4;
	mapmenu[1].x = -0.1;
	mapmenu[1].y = 0.5;
	mapmenu[2].o = 4;
	mapmenu[2].x = 0.1;
	mapmenu[2].y = 0.5;
	mapmenu[3].o = 1;
	mapmenu[3].x = -0.1;
	mapmenu[3].y = 0.5;
	mapmenu[4].o = 2;
	mapmenu[4].x = 0.1;
	mapmenu[4].y = 0.5;
	mapmenu[5].o = 10;
	mapmenu[5].x = 0;
	mapmenu[5].y = 0.2;
	mapmenu[6].o = 8;
	mapmenu[6].x = 0;
	mapmenu[6].y = 0;
	mapmenu[7].o = 9;
	mapmenu[7].x = 0;
	mapmenu[7].y = -0.2;
	//menubackground
	poly[5].resize(2);
	poly[5][0].resize(9);
	poly[5][1].resize(9);
	poly[5][0][0] = 1.0f;
	poly[5][0][1] = 0.5f;
	poly[5][0][2] = 0.0f;
	poly[5][0][3] = -0.3f;
	poly[5][0][4] = -1.0f;
	poly[5][0][5] = 0.3f;
	poly[5][0][6] = 1.0f;
	poly[5][0][7] = -0.3f;
	poly[5][0][8] = 1.0f;

	poly[5][1][0] = 1.0f;
	poly[5][1][1] = 0.5f;
	poly[5][1][2] = 0.0f;
	poly[5][1][3] = -0.3f;
	poly[5][1][4] = -1.0f;
	poly[5][1][5] = 0.3f;
	poly[5][1][6] = -1.0f;
	poly[5][1][7] = 0.3f;
	poly[5][1][8] = 1.0f;
	// background
	poly[0].resize(4);
	poly[0][0].resize(9);
	poly[0][1].resize(9);
	poly[0][2].resize(9);
	poly[0][3].resize(9);

	poly[0][0][0] = 0.8f;
	poly[0][0][1] = 0.8f;
	poly[0][0][2] = 0.8f;
	poly[0][0][3] = 0.0f;
	poly[0][0][4] = 0.0f;
	poly[0][0][5] = 1.0f;
	poly[0][0][6] = 1.0f;
	poly[0][0][7] = -1.0f;
	poly[0][0][8] = 1.0f;

	poly[0][1][0] = 0.8f;
	poly[0][1][1] = 0.8f;
	poly[0][1][2] = 0.8f;
	poly[0][1][3] = 0.0f;
	poly[0][1][4] = 0.0f;
	poly[0][1][5] = 1.0f;
	poly[0][1][6] = -1.0f;
	poly[0][1][7] = -1.0f;
	poly[0][1][8] = -1.0f;

	poly[0][2][0] = 0.9f;
	poly[0][2][1] = 0.9f;
	poly[0][2][2] = 0.9f;
	poly[0][2][3] = 0.0f;
	poly[0][2][4] = 0.0f;
	poly[0][2][5] = 1.0f;
	poly[0][2][6] = 1.0f;
	poly[0][2][7] = 1.0f;
	poly[0][2][8] = -1.0f;

	poly[0][3][0] = 0.9f;
	poly[0][3][1] = 0.9f;
	poly[0][3][2] = 0.9f;
	poly[0][3][3] = 0.0f;
	poly[0][3][4] = 0.0f;
	poly[0][3][5] = -1.0f;
	poly[0][3][6] = 1.0f;
	poly[0][3][7] = -1.0f;
	poly[0][3][8] = -1.0f;

	//lines init
	poly[1].resize(lines.size() * 4);
	for (int i = 0; i < lines.size() * 4; i++){
		poly[1][i].resize(9);
			poly[1][i][0] = 0.0f;
			poly[1][i][1] = 0.0f;
			poly[1][i][2] = 0.0f;
	}
	//draw
	drawmap();
	drawmap2();
	drawgui();
}
void Render(){
	//check hover
	if (hovere){
		map[hover].o = 5;
		drawmap();
	//undo hover
	}else{
		if (hover != -1){
			if (!outline[hover]){
				map[hover].o = 4;
				hover = -1;
				drawmap();
			}
			else{
				map[hover].o = 3;
				hover = -1;
				drawmap();
			}
		}
	}
	//breathig effect
	 //outlines
	a = (1.0f + (phase / 10000.0f));
	objs[3] = objs[22];
	objs[4] = objs[23];
	objs[5] = objs[24];
	orescale(3, a, a);
	orescale(4, a, a);
	orescale(5, a, a);
	 //lines
	b = objs[0][0][7]*0.5f;
	for (int i = 0; i < lines.size(); i++){
		poly[1][i * 4 + 0][3] = map[lines[i][0]].x;
		poly[1][i * 4 + 0][4] = map[lines[i][0]].y + b*a;
		poly[1][i * 4 + 0][5] = map[lines[i][0]].x;
		poly[1][i * 4 + 0][6] = map[lines[i][0]].y;
		poly[1][i * 4 + 0][7] = map[lines[i][1]].x;
		poly[1][i * 4 + 0][8] = map[lines[i][1]].y + b*a;

		poly[1][i * 4 + 1][3] = map[lines[i][0]].x + b*a;
		poly[1][i * 4 + 1][4] = map[lines[i][0]].y;
		poly[1][i * 4 + 1][5] = map[lines[i][0]].x;
		poly[1][i * 4 + 1][6] = map[lines[i][0]].y;
		poly[1][i * 4 + 1][7] = map[lines[i][1]].x;
		poly[1][i * 4 + 1][8] = map[lines[i][1]].y;

		poly[1][i * 4 + 2][3] = map[lines[i][1]].x;
		poly[1][i * 4 + 2][4] = map[lines[i][1]].y + b*a;
		poly[1][i * 4 + 2][5] = map[lines[i][1]].x;
		poly[1][i * 4 + 2][6] = map[lines[i][1]].y;
		poly[1][i * 4 + 2][7] = map[lines[i][0]].x;
		poly[1][i * 4 + 2][8] = map[lines[i][0]].y;

		poly[1][i * 4 + 3][3] = map[lines[i][1]].x + b*a;
		poly[1][i * 4 + 3][4] = map[lines[i][1]].y;
		poly[1][i * 4 + 3][5] = map[lines[i][1]].x;
		poly[1][i * 4 + 3][6] = map[lines[i][1]].y;
		poly[1][i * 4 + 3][7] = map[lines[i][0]].x + b*a;
		poly[1][i * 4 + 3][8] = map[lines[i][0]].y;
	}
	drawmap();
	if (menu || menuup) drawmenu();
}