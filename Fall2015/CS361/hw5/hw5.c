#define _XOPEN_SOURCE 600
#include "hw5.h"
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;

static struct ElevatorList{
	int current_floor;
	int direction;
	int occupancy;
	int state;
	int workload[PASSENGERS * 2][2];
	int workingOn;
	int initilized;
} elevatorList[ELEVATORS];

static struct PassengerList{
	int elevator;
	int fromFloor;
	int toFloor;
	int id;
	pthread_barrier_t open;
} passengerList[PASSENGERS];

pthread_mutex_t lock;
enum {ELEVATOR_ARRIVED=1, ELEVATOR_OPEN=2, ELEVATOR_CLOSED=3};	

void scheduler_init() {
	int i, j;
	for(i = 0; i < ELEVATORS; ++i){
		elevatorList[i].current_floor=0;//i % (FLOORS - 1);		
		elevatorList[i].direction=-1;
		elevatorList[i].occupancy=0;
		elevatorList[i].state=ELEVATOR_ARRIVED;
		elevatorList[i].initilized = 0;
		for(j = 0; j < PASSENGERS * 2; ++j){
			elevatorList[i].workload[j][0] = -1;
		}
		elevatorList[i].workingOn = 0;
	}
	for(i = 0; i < PASSENGERS; ++i){
	pthread_barrier_init(&(passengerList[i].open), 0, 2);
	}
	pthread_mutex_init(&lock, 0);
}
void passenger_request(int passenger, int from_floor, int to_floor, void (*enter)(int, int), void(*exit)(int, int)){	
	// wait for the elevator to arrive at our origin floor, then get in
	//pthread_mutex_lock(&lock);
	passengerList[passenger].fromFloor = from_floor;
	passengerList[passenger].toFloor = to_floor;
	passengerList[passenger].id = passenger;
	passengerList[passenger].elevator = (passenger % (ELEVATORS));// - 1));
	log(2, "%d is waiting on %d\n", passenger, passengerList[passenger].elevator);
	//pthread_mutex_unlock(&lock);
	int elevator = passengerList[passenger].elevator;
	log(3, "%d is waiting for their door to open\n", passenger);
	pthread_barrier_wait(&(passengerList[passenger].open));
	enter(passenger, elevator);
	// say passenger is on
	pthread_barrier_wait(&(passengerList[passenger].open));
	++elevatorList[elevator].occupancy;
	//wait for door to open
	log(3, "%d is waiting for the door to open so they can get off\n", passenger);
	pthread_barrier_wait(&(passengerList[passenger].open));
	exit(passenger, elevator);
	pthread_barrier_wait(&(passengerList[passenger].open));
	--elevatorList[elevator].occupancy;
}
void initlize(int elevator){
	// organizing the list of floors and passengers to optimize how often the elevator
	// open
	//int fromList[PASSENGERS][2];
	//int toList[PASSENGERS];
	int i, current = 0;
	log(3, "Elevator %d is starting the copy\n", elevator);
	for(i = 0; i < PASSENGERS; ++i){
		if(passengerList[i].elevator == elevator){
			log(2, "Elevator %d found that it needs to go to the %d and %d floor making it now going to %d floors\n", elevator, passengerList[i].fromFloor, passengerList[i].toFloor, current * 2);
			elevatorList[elevator].workload[current][0] = passengerList[i].fromFloor;
			elevatorList[elevator].workload[current + 1][0] = passengerList[i].toFloor;
			elevatorList[elevator].workload[current][1] = passengerList[i].id;
			elevatorList[elevator].workload[current+ 1][1] = passengerList[i].id;
			current += 2;
		}
	}
	//log(3, "Elevator %d has finished copying now starting the fill for the rest of the array\n", elevator);
	//while(current < PASSENGERS){
	//	fromList[current][0] = -1;
	//	toList[current] = -1;
	//	++current;
	//}
	//int j;
	//log(3, "Elevator %d is moving the obtained to and from floors into its elevator struct\n", elevator);
	//for(i = 0; i < PASSENGERS * 2; i += MAX_CAPACITY * 2){
	//	for(j = 0; j < MAX_CAPACITY; ++j){
	//		elevatorList[elevator].workload[i + j][0] = fromList[i + j][0];
	//		elevatorList[elevator].workload[i + j][1] = fromList[i + j][1];
	//		elevatorList[elevator].workload[i + MAX_CAPACITY + j][0] = toList[i + j];
	//		elevatorList[elevator].workload[i + MAX_CAPACITY + j][1] = fromList[i + j][1];
	//	}
	//}
}

void elevator_ready(int elevator, int at_floor, void(*move_direction)(int, int), void(*door_open)(int), void(*door_close)(int)) {	
	int workingOn = elevatorList[elevator].workingOn;
	if(elevatorList[elevator].workload[workingOn][0] == -1 && elevatorList[elevator].initilized == 1){
		log(2, "%d is being killed after %d passengers served\n", elevator, (workingOn / MAX_CAPACITY));
		pthread_exit(NULL);
	}
 	log(3, "%d is seeing if it needs to initilize\n", elevator);
	if((elevatorList[elevator].initilized) == 0){
		//pthread_mutex_lock(&lock);
		log(3, "Starting the initlization of %d\n", elevator);
		initlize(elevator);
		log(2, "Initilized %d\n", elevator);
		elevatorList[elevator].initilized = 1;
		//pthread_mutex_unlock(&lock);
	}else if(elevatorList[elevator].state == ELEVATOR_ARRIVED && elevatorList[elevator].workload[workingOn][0] == at_floor) {
		door_open(elevator);
		//say the door is open
		log(3, "%d is starting to waiting for %d to get on\n", elevator, elevatorList[elevator].workload[workingOn][1]);
		pthread_barrier_wait(&(passengerList[elevatorList[elevator].workload[workingOn][1]].open));
		elevatorList[elevator].state=ELEVATOR_OPEN;
	} else if(elevatorList[elevator].state == ELEVATOR_OPEN) {
		//wait for passenger to get on
		log(3, "%d is waiting for %d to get on\n", elevator, elevatorList[elevator].workload[workingOn][1]);
		pthread_barrier_wait(&(passengerList[elevatorList[elevator].workload[workingOn][1]].open));
		door_close(elevator);
		++elevatorList[elevator].workingOn;
		elevatorList[elevator].state=ELEVATOR_CLOSED;
	} else {
		if(at_floor==0 || at_floor==FLOORS-1) 
			elevatorList[elevator].direction*=-1;
		move_direction(elevator,elevatorList[elevator].direction);
		elevatorList[elevator].current_floor=at_floor+elevatorList[elevator].direction;
		elevatorList[elevator].state=ELEVATOR_ARRIVED;
	}
}
