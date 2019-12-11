/*
 * tasks.h
 *
 *  Created on: Nov 15, 2019
 *      Author: archer
 */

#ifndef SRC_TASKS_H_
#define SRC_TASKS_H_
#include "cmsis_os.h"

//
// external handles for the tasks
//
extern osThreadId TaskMainHandle;
extern osThreadId TaskSocket1Handle;
extern osThreadId TaskSocket2Handle;
extern osThreadId TaskSocket3Handle;
extern osThreadId TaskSocket4Handle;

//
// message queue
//
extern osMessageQId SocketQ1Handle;
extern osMessageQId ResultsQHandle;
extern osMessageQId SocketQ2Handle;
extern osMessageQId SocketQ3Handle;
extern osMessageQId SocketQ4Handle;

//
// Task prototypes
//

void StartThreads();
void StartTaskMain(void const *argument);
void StartTaskSocket(void const *argument);


#endif /* SRC_TASKS_H_ */
