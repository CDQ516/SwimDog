#include "ik_solver.h"
#include "main.h"
#include "os.h"
#include <math.h>


void IK_calc(IK_solver *ik_solver, float x, float y, float rou) {
	ik_solver->x = fabsf(x);
	ik_solver->y = y;
	if(x < 0.001f) {
		ik_solver->gamma = 90.0f;
	}
	else {
		ik_solver->gamma = atanf(y / x) / 3.1415926f * 180.0f;
	}
	ik_solver->ls = x * x + y * y;
	
	float t1 = ik_solver->l1s + ik_solver->l2s - ik_solver->ls;
	float t2 = 2.0f * ik_solver->l1 * ik_solver->l2;
	float temp1 = t1 / t2;
	ik_solver->theta = acosf(temp1) / 3.1415926f * 180.0f;
	
	float t3 = ik_solver->l1s - ik_solver->l2s + ik_solver->ls;
	float t4 = 2.0f * ik_solver->l1 * sqrtf(ik_solver->ls);
	float temp2 = t3 / t4;
	ik_solver->omega = acosf(temp2) / 3.1415926f * 180.0f;
	
	ik_solver->alpha = 180 - ik_solver->omega - ik_solver->gamma;
	ik_solver->beta = 180 - ik_solver->theta;	
	ik_solver->rou = rou;
}
