#include "myglobal.h"
#include "math.h"
#include "MyFunc.h"
#include "Vector2.h"

double PI = atan(1.0) * 4;
double DegToRad = PI / 180;

int SEGOE_M_SIZE = 20;
int SEGOE_S_SIZE = 12;
int MARU_GOTHIC_M_SIZE = 35;
int MARU_GOTHIC_S_SIZE = 20;

int SEGOE_M;
int SEGOE_S;
int MARU_GOTHIC_M;
int MARU_GOTHIC_S;

HCURSOR HANDCURSOR;
HCURSOR OCURSOR;

Vector2 SCREEN(800, 600);
Rectangular PLAYER_RANGE(Vector2(0, 0), Vector2(SCREEN.x, SCREEN.x - 20));
Vector2 homePoint(160, 200);