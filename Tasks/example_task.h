#ifndef _EXAMPLE_TASK_H
#define _EXAMPLE_TASK_H


void Example_task(void * arg);

#define STATUS_NUM 4
#define SERVO_NUM 3
#define TIME_MX 100

typedef enum{
	LEG_STATUS1,
	LEG_STATUS2,
	LEG_STATUS3,
	LEG_STATUS4
}leg_status_t;

typedef struct{
	float angle;
	float duty;
}servo_t;

extern leg_status_t leg_status;
extern servo_t servo[SERVO_NUM];

/* Private functions declaration ---------------------------------------------*/
/* USER CODE BEGIN PFD */

/* USER CODE END PFD */

#endif
