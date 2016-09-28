#include "IlinkWIN.h"
#include "IlinkR.h"
#include "IlinkM.h"

float px=0, py=0, nx,ny;
int hover;
bool hovere = false;
void Click(){
	if ((px > -1 && px<undox) && (-py> -1 && -py < undoy)) undo();
	if (menu){
		for (int i = 0; i < menuhitb.size(); i++){
			if ((px>menuhitb[i][0] && px<menuhitb[i][2]) && (-py>menuhitb[i][3] && -py < menuhitb[i][1])){
				if (i == 0) resrabl();
				if (i == 1) resrend();
				if (i == 2) resmult();
				if (i == 3) swfullscreen();
				if (i == 4) quit();
				return;
			}
		}
	}
	else{
		if (hovere) Lep(hover);
	}
}
void Key(int a){
	if (a == 0x43) zoom(1.1f);
	if (a == 0x56) zoom(0.9f);
	if (a == 0x44) zoomb(1.1f);
	if (a == 0x46) zoomb(0.9f);
	if (a == 0x4F) size(1.1f);
	if (a == 0x50) size(0.9f);
	if (a == 0x1B) SwitchMenu();
}
void MouseMove(int x, int y){
	nx = float(x - centerx) / float(wwidth - centerx);
	ny = float(y - centery) / float(wheight - centery);
	if (rbutton) move(nx - px, py - ny);
	px = nx;
	py = ny;
	for (int i = 0; i < hitb.size(); i++){
		if ((px>hitb[i][0] && px<hitb[i][2]) && (-py>hitb[i][3] && -py < hitb[i][1])){
			hovere = true;
			hover = i;
			return;
		}
	}
	hovere = false;
}