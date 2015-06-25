//
//  main.cpp
//  satellite_simulation_1_xcode
//
//  Created by David Jackson on 6/23/15.
//  Copyright (c) 2015 DJackson. All rights reserved.
//

//The simulation simulates sunlight hitting a satellite. All relative math is detailed in a paper written by P. C. Knocke *, J. C. Ries, and B. D. Tapley, Center for Space Research, The University of Texas at Austin, Austin, Texas.

//For a list of assumptions read that paper. Definitions of constants are defined here.

// function example
#include <iostream>
#include <math.h>       /* pow */
using namespace std;

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////CONSTANT DEFINITIONS:

//(all units in meters)

//Satellite is centered {0,0,0}

//Sun position, cartesian coordinates.
const double SUN_X=0;
const double SUN_Y=0;
const double SUN_Z=94000000;

//Satellite position is directly above origin... (SAT_Y_POSITION)

const double EARTH_RADIUS=6371000;

const double SAT_Y_POSITION=1200.0+EARTH_RADIUS; //distance above the center of the earth

const double albedo=.8;

const double e=1-albedo; //emmisivity

const double Ac=1.0;

double MAX_ACCEPTABLE_DISTANCE;

const double E_s=120; //wiki

const int NUM_STEPS=20;

const double interval=2*M_PI/NUM_STEPS;

/////////////////////////////////////////////////////END CONSTANT DEFINITIONS
//////////////////////////////////////////////////////////////////////////

double magnitudeOfVector (double x, double y, double z)  {
    return pow( (pow(x,2) + pow(y,2) + pow(z,2)) ,  .5);
}

double sunAngle()  { //dot product.
    double SUN_VECTOR_MAG=magnitudeOfVector(SUN_X,SUN_Y,SUN_Z);
    double OTHER_VECTOR_MAG=1; //unit vector pointing to the satellite; leaving this here for bookeeping.
    double sunAngle=acos(SUN_Z/(SUN_VECTOR_MAG*OTHER_VECTOR_MAG));
    return sunAngle;
}

double returnRForAlpha(double alpha)   { //defined in a diagram made by djax
    return pow(   pow(SAT_Y_POSITION-EARTH_RADIUS*cos(alpha),2)+  pow(EARTH_RADIUS*sin(alpha),2)       ,.5);
}

double calculateSunlightEffect(double alpha, double theta) { //related math in djax notes...
    double r = returnRForAlpha(alpha); //as defined in djax notes.
    return (albedo*E_s*cos(sunAngle())+e*E_s/4)*Ac/(M_PI*pow(r,2))*cos(alpha)*pow(interval,2);
}

double returnDistanceBetweenPoints(double X, double Y, double Z, double X0, double Y0, double Z0)    {
    double distance=0;
    distance=pow( (pow(X-X0,2) + pow(Y-Y0,2)  + pow(Z-Z0,2)) ,  .5);
    return distance;
}

bool returnValidPointInRelationToSun (double alpha, double theta) //returns whether a point
{
    double x=EARTH_RADIUS*cos(theta)*sin(alpha);
    double y=EARTH_RADIUS*sin(theta)*sin(alpha);
    double z=EARTH_RADIUS*cos(alpha);
    
    double ACTUAL_DISTANCE=returnDistanceBetweenPoints(x, y, z, SUN_X, SUN_Y, SUN_Z);
    
    return (  MAX_ACCEPTABLE_DISTANCE   > ACTUAL_DISTANCE );
}

double runForLoop()    { //function that simply iterates over a square, and calculates sunlight effect accordinly...
    
    double SUN_POSITION_ABOVE_EARTH=returnDistanceBetweenPoints(0, 0, 0, SUN_X, SUN_Y, SUN_Z);
    
    double MAX_ANGLE=acos(EARTH_RADIUS/SUN_POSITION_ABOVE_EARTH);
    
    //defined in diagram, different than alpha
    MAX_ACCEPTABLE_DISTANCE=sin(MAX_ANGLE)*SUN_POSITION_ABOVE_EARTH;
    
    double NET_FLUX=0;

    double alpha_max=acos(EARTH_RADIUS/SAT_Y_POSITION); //returning NAN, not a number...
    for(double alpha = 0; alpha < alpha_max; alpha = alpha + interval)
    {
        for(double theta = 0; theta <2*M_PI; theta = theta + interval)
        {
            //round the corners of the for loop
            
            if (returnValidPointInRelationToSun(alpha,theta))  {
                //calculate the z position for this discrete piece
                
                double dFLUX;
                
                dFLUX=calculateSunlightEffect(alpha,theta);
                
                NET_FLUX=NET_FLUX+dFLUX;
            }
        }
    }
    return NET_FLUX;
}

int main ()
{
    double answer = runForLoop();
    cout << "Result: " << answer;
}







