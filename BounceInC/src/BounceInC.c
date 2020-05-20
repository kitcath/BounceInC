/*
 * bounce.c
 *
 *  Created on: Nov 16, 2019
 *      Author: cath
 */

#include <stdio.h>
#include<stdlib.h>
#include <math.h>


//defining simulation coordinates
#define g 9.8
#define initialX 5 //initial position of ball in X
#define initialY  1.0
#define Pi 3.141592654
#define k 0.0016
#define TICK 0.1 // delta t
#define ETHR 0.01
#define false 0
#define true !false


// entry point for the code
int main() {
	double Vo, launchAngle,loss, bSize;

	//read simulation parameters to users
	printf("Enter the initial velocity of the ball [0,100]:");
	scanf("%lf",&Vo);

	printf("Enter the initial launch angle in degrees [0,90]:");
	scanf("%lf",&launchAngle);

	printf("Enter the energy lost parameter [0,1]:");
	scanf("%lf",&loss);

	printf("Enter the radius of the ball in meters [0.1,5.0]:");
	scanf("%lf",&bSize);

	/*Initializing parameters for Simulation*/
		double time = 0.0;
		double  offsetX = initialX;
		double X = 0;
		double Y = 0;
		double  Xlast = 0;
		double Ylast = 0;
		double Vx = 0;
		double Vy = 0;
		double KEx = 0.0; /*kinetic energy of ball in the X direction */
		double KEy =0.0; /*kinetic energy of ball in the Y direction*/

	/*Initializing variables*/
	double Vt = (g)/(4*Pi*bSize*bSize*k);
	double Vox = Vo*cos(launchAngle*Pi/180);
	double Voy=Vo*sin(launchAngle*Pi/180);

	/* the path taken by the ball once its launched*/
			while(true) { /* an infinite loop which will run till a break statement is issued*/
				X = Vox*Vt/g*(1-exp(-g*time/Vt));
				Y= bSize+Vt/g*(Voy+Vt)*(1-exp(-g*time/Vt))-Vt*time;
				Vx = (X-Xlast)/TICK;
				Vy = (Y-Ylast)/TICK;

				printf("t: %.2f X: %.2f Y:%.2f Vx: %.2f Vy: %.2f\n", time, offsetX+X, Y, Vx, Vy);


			// loop when there is a collision
			if (Y <= bSize && Vy <0 ) {
				KEx = 0.5*Vx*Vx*(1-loss);
				KEy = 0.5*Vy*Vy*(1-loss);

				Vox = sqrt(2*KEx);
				Voy =sqrt(2*KEy);

				time = 0.0; // must re-initialize time
				offsetX += X; // distance of ball
				X= 0; // the location where there is the collision becomes the new initial point
				Y=bSize;



			if ((KEx <= ETHR)|| (KEy <= ETHR))
			break;
			} // end of the collision loop

			time += TICK;
			Xlast = X;
			Ylast = Y;


			}// end of the while loop
} // end of the run method
