#include <vector>

struct pos{
	int o;
	float x, y;
};

std::vector<std::vector<std::vector<float> > > objs;
std::vector<pos>map;
std::vector<pos>map2;

void oload(){
	freopen("objs.txt", "r", stdin);
	int n, m;
	float a, b;
	std::cin >> n;
	objs.resize(n);
	for (int i = 0; i < n; i++){
		std::cin >> m;
		objs[i].resize(m);
		std::cin >> a;
		for (int j = 0; j < m; j++){
			objs[i][j].resize(9);
			for (int k = 0; k < 9; k++){
				std::cin >> b;
				if (k>2) objs[i][j][k] = a*b; else objs[i][j][k] = b;
			}
		}
	}
	fclose(stdin);
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