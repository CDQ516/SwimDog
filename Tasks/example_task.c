#include "example_task.h"
#include "os.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "components.h"
#include "ik_solver.h"
/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
//float ang1[4] = {47.6,36.5,56.5,63.2};
//float ang2[4] = {91.0,116.7,112.8,87.5};
float ang1[3] = {47.6,46.4,63.2};
float ang2[3] = {91.0,115.8,87.5};
float pos[3][3] = {{0, 40, 0},{5, 35, 0},{10, 40, 0}};

leg_status_t leg_status;
servo_t servo[SERVO_NUM];
uint32_t cnt = 0;

IK_solver ik1;
/* USER CODE END PV */

/* Private functions declaration ---------------------------------------------*/
/* USER CODE BEGIN PFD */
static void leg_init(void);
static void leg_status_switch(void);
static void leg_angle_set(void);
static void leg_duty_set(void);
/* USER CODE END PFD */

/**
* @breif 		main task of example_task
* @param 		args: avoid some funtions put parameters to this function
* @return		none
* @note
*/

void Example_task(void * arg) {
	/* You can write your own code here */
	/* USER CODE BEGIN */
	leg_init();
	/* USER CODE END */
	
	while(1) {
		/* You can write your own code here */
		/* USER CODE BEGIN */
		leg_status_switch();
		leg_angle_set();
		leg_duty_set();
		PWM_SetDutyRatio(&pwm1[3], servo[0].duty);
		PWM_SetDutyRatio(&pwm1[1], servo[1].duty);
		PWM_SetDutyRatio(&pwm1[2], servo[2].duty);
		/* USER CODE END */
		delay(5);
	}
}

/* Private functions ---------------------------------------------------------*/
/*	Remember to declare your functions at the beginning of this file and in the .h file */
/* USER CODE BEGIN PF */
static void leg_init(void) {
	PWM_SetFrequency(&pwm1[1], 50);
	PWM_SetFrequency(&pwm1[2], 50);
	PWM_SetFrequency(&pwm1[3], 50);
	
	IK_init(&ik1, 30, 27);
	
	leg_status = LEG_STATUS1;
	servo[0].angle = ang1[leg_status];
	servo[1].angle = ang2[leg_status];
	servo[2].duty = 0.075;
}

static void leg_status_switch(void) {
	switch(leg_status) {
		case LEG_STATUS1:
			if(cnt > TIME_MX / 2) {
				leg_status = LEG_STATUS2;
				cnt = 0;
			}
			else 
				cnt++;
			break;
		case LEG_STATUS2:
			if(cnt > TIME_MX / 2) {
					leg_status = LEG_STATUS3;
					cnt = 0;
				}
			else
				cnt++;
			break;
		case LEG_STATUS3:
			if(cnt > TIME_MX) {
					leg_status = LEG_STATUS1;
					cnt = 0;
				}
			else
				cnt++;
			break;
		case LEG_STATUS4:
			if(cnt > TIME_MX) {
				leg_status = LEG_STATUS1;
				cnt = 0;
			}
			else
				cnt++;
			break;
		default:
			break;
	}
}

static void leg_angle_set(void) {
	IK_calc(&ik1, pos[leg_status][0], pos[leg_status][1], pos[leg_status][2]);
	servo[0].angle = ik1.alpha;
	servo[1].angle = ik1.beta;
}

static void leg_duty_set(void) {
	float angle0 = servo[0].angle;
	float angle1 = servo[1].angle - 26.0f;
	
	servo[0].duty = -(angle0 / 180.0f) * 0.1f + 0.125;
	servo[1].duty = (angle1 / 180.0f) * 0.1f + 0.025;
}
/* USER CODE END PF */
