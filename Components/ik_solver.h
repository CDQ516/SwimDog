#ifndef _COMPONENTS_IK_SOLVER_H
#define _COMPONENTS_IK_SOLVER_H
#include "main.h"

typedef struct {
	float l1;
	float l2;
	float l1s;
	float l2s;
	float x;
	float y;
	float rou;
	float ls;
	float gamma;
	float theta;
	float omega;
	float alpha;
	float beta;
}IK_solver;

static void IK_init(IK_solver *ik_solver, float l1, float l2) {
	ik_solver->l1 = l1;
	ik_solver->l2 = l2;
	ik_solver->l1s = l1 * l1;
	ik_solver->l2s = l2 * l2;
}

void IK_calc(IK_solver *ik_solver, float x, float y, float rou);

#endif
