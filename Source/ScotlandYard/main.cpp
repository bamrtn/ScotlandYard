#include "MlinkWIN.h"
#include "MlinkR.h"

std::vector<std::vector<float> >hex;
std::vector<std::vector<int> >lines;
std::vector<std::vector<int> >g;
std::vector<bool>outline;
std::vector<int>pos2bak;
std::vector<int>pos2;
std::vector<int>tav1;
std::vector<int>tav2;
int current;
bool rablo;
int phase;
int pos1bak;
int pos1;
bool phases;
int n,m,x,y,rend;
bool menudown = false;
bool menuup = false;
bool menu = true;
bool multi = false;

void rendai(){

}

void rablai(){
	for (int i = 0; i < m; i++){

	}
}

void Lep(int c) {
	if (!outline[c]) return;
	for (int i = 0; i < n; i++){
		outline[i] = false;
	}
	if (rablo){
		pos1 = c;
		if (!multi){
			outline[pos1] = true;
			for (int i = 0; i < g[pos1].size(); i++) outline[g[pos1][i]] = true;
			counter_add();
			rendai();
		}
		else{
			outline[pos2[rend]] = true;
			for (int j = 0; j < g[pos2[rend]].size(); j++) outline[g[pos2[rend]][j]] = true;
			rablo = false;
		}
	}else{
		pos2[rend] = c;
		rend++;
		if (!multi){
			if (rend == pos2.size()){
				rend = 0;
				counter_add();
				rablai();
			}
			outline[pos2[rend]] = true;
			for (int j = 0; j < g[pos2[rend]].size(); j++) outline[g[pos2[rend]][j]] = true;
		}
		else{
			if (rend == pos2.size()){
				rablo = true;
				rend = 0;
				for (int i = 0; i < g[pos1].size(); i++) outline[g[pos1][i]] = true;
				counter_add();
			}
			else{
				outline[pos2[rend]] = true;
				for (int j = 0; j < g[pos2[rend]].size(); j++) outline[g[pos2[rend]][j]] = true;
			}
		}
	}
	Rend_lep();
}

void restart(){
	counter_reset();
	pos1 = pos1bak;
	pos2 = pos2bak;
	for (int i = 0; i < n; i++){
		outline[i] = false;
	}
	if (rablo){
		outline[pos1] = true;
		for (int i = 0; i < g[pos1].size(); i++) outline[g[pos1][i]] = true;
	}
	else{
		outline[pos2[rend]] = true;
		for (int j = 0; j < g[pos2[rend]].size(); j++) outline[g[pos2[rend]][j]] = true;
	}
	Rend_lep();
}

void resrend(){
	rablo = false;
	multi = false;
	restart();
}
void resrabl(){
	rablo = true;
	multi = false;
	restart();
}
void resmult(){
	rablo = true;
	multi = true;
	restart();
}
void quit(){
	e = false;
}

void Init(){
	float a;
	rend = 0;
	std::ifstream ifs;
	ifs.open("graf.txt", std::ifstream::in);
	ifs >> a >> n >> m;
	outline.resize(n);
	hex.resize(n);
	g.resize(n);
	lines.resize(m);
	for (int i = 0; i < n; i++){
		ifs >> x >> y;
		hex[i].push_back(x*a);
		hex[i].push_back(y*a);
	}
	for (int i = 0; i < m; i++){
		ifs >> x >> y;
		lines[i].push_back(x);
		lines[i].push_back(y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	ifs >> pos1bak;
	ifs >> m;
	pos2bak.resize(m);
	for (int i = 0; i < m; i++){
		ifs >> pos2bak[i];
	}
	ifs.close();
	phase = 1000;
	phases = true;
	rablo = true;
	pos1 = pos1bak;
	pos2 = pos2bak;
	if (rablo){
		outline[pos1] = true;
		for (int i = 0; i < g[pos1].size(); i++) outline[g[pos1][i]] = true;
	}
	else{
		outline[pos2[rend]] = true;
		for (int j = 0; j < g[pos2[rend]].size(); j++) outline[g[pos2[rend]][j]] = true;
	}
	Rend_init();
	Rend_lep();
}

void SwitchMenu(){
	if (menu) {
		if (!menuup){
			menuup = true;
			menudown = false;
			menu = false;
		}
	}
		else{
			if (!menudown){
				menudown = true;
				menuup = false;
				menu = true;
			}

		}
	
}

void Cycle(long long t){
	if (phase > 3000) phases = false;
	if (phase < 1000) phases = true;
	if (phases) phase = phase + t; else phase = phase - t;
	if (menuup) movemup(t);
	if (menudown) movemdown(t);
	Render();
}