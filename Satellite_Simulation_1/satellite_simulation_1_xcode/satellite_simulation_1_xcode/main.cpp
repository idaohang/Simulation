//
//  main.cpp
//  satellite_simulation_1_xcode
//
//  Created by David Jackson on 6/23/15.
//  Copyright (c) 2015 DJackson. All rights reserved.
//

//The simulation simulates sunlight bouncing off the earth and then hitting a satellite. All relative math is detailed in a paper written by P. C. Knocke *, J. C. Ries, and B. D. Tapley, Center for Space Research, The University of Texas at Austin, Austin, Texas.

//For a list of assumptions read that paper. Definitions of constants are defined here.

// function example
#include <iostream>
#include <math.h>       /* pow */
#include <fstream>
using namespace std;

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////CONSTANT DEFINITIONS:

//units defined in SI

//Satellite is centered {0,0,0}

//Function headers

double returnDistanceBetweenPoints(double X, double Y, double Z, double X0, double Y0, double Z0);

//THESE VARIABLES ARE SET IN MAIN...///
double SUN_X;
double SUN_Y;
double SUN_Z;

double SAT_X_POSITION;
double SAT_Y_POSITION;
double SAT_Z_POSITION;

double albedo;
///////////////////////////////////////

const double EARTH_RADIUS=6371000;

const double e=1-albedo; //emmisivity

#warning TODO replace with Satellite area...
const double Ac=1.0;

double MAX_ACCEPTABLE_DISTANCE;

#warning Sumeet has a better expression for this...
const double E_s=120; //wiki (W/m^2)

const double M_b=E_s/4; //As derived in the paper.

const int NUM_STEPS_THETA=20;

const int NUM_STEPS_ALPHA=20;

const double THETA_MAX=2*M_PI;

const double ALPHA_MAX=acos(EARTH_RADIUS/returnDistanceBetweenPoints(0, 0, 0, SAT_X_POSITION, SAT_Y_POSITION, SAT_Z_POSITION));

const double theta_interval=THETA_MAX/NUM_STEPS_THETA;

const double alpha_interval=ALPHA_MAX/NUM_STEPS_ALPHA;

/////////////////////////////////////////////////////END CONSTANT DEFINITIONS
//////////////////////////////////////////////////////////////////////////

//FUNCTIONS
double magnitudeOfVector (double x, double y, double z)  {
    return pow( (pow(x,2) + pow(y,2) + pow(z,2)) ,  .5);
}

double returnSunAngleForAreaElementAt(double alpha, double theta)  { //this is the angle between the sun and the normal to the earth element.
    double x=EARTH_RADIUS*cos(theta)*sin(alpha); //just translating from cartesian to spherical.
    double y=EARTH_RADIUS*sin(theta)*sin(alpha);
    double z=EARTH_RADIUS*cos(alpha);
    
    //use dot product
    double denom=magnitudeOfVector(x, y, z)*magnitudeOfVector(SUN_X, SUN_Y, SUN_Z);
    double angle=acos((x*SUN_X+y*SUN_Y+z*SUN_Z)/denom);
    return angle;
}

double calculateSunlightEffect(double alpha, double theta) { //related math in djax notes...
    double x=EARTH_RADIUS*cos(theta)*sin(alpha); //just translating from cartesian to spherical.
    double y=EARTH_RADIUS*sin(theta)*sin(alpha);
    double z=EARTH_RADIUS*cos(alpha);
    
    double r = returnDistanceBetweenPoints(x, y, z, SAT_X_POSITION, SAT_Y_POSITION, SAT_Z_POSITION);  //distance between area element and the satellite.
    
    return (albedo*E_s*cos(returnSunAngleForAreaElementAt(alpha,theta))+e*M_b)*Ac/(M_PI*pow(r,2))*cos(alpha)*theta_interval*alpha_interval; //this is an approximation for our area, using dA=d_alpha*d_theta. This probably introduces a slight error (as opposed to a flat integral, an integral over a curved surface mutates your dA).
}

double returnDistanceBetweenPoints(double X, double Y, double Z, double X0, double Y0, double Z0)    {
    double distance=0;
    distance=pow( (pow(X-X0,2) + pow(Y-Y0,2)  + pow(Z-Z0,2)) ,  .5);
    return distance;
}

bool returnValidPointInRelationToSun (double alpha, double theta) //returns whether a point
{
    double x=EARTH_RADIUS*cos(theta)*sin(alpha); //just translating from cartesian to spherical.
    double y=EARTH_RADIUS*sin(theta)*sin(alpha);
    double z=EARTH_RADIUS*cos(alpha);
    
    double ACTUAL_DISTANCE=returnDistanceBetweenPoints(x, y, z, SUN_X, SUN_Y, SUN_Z);
    
    return (  MAX_ACCEPTABLE_DISTANCE   > ACTUAL_DISTANCE );
}

double returnFluxForParameters(double SAT_X_PARAM, double SAT_Y_PARAM, double SAT_Z_PARAM,double SUN_X_PARAM, double SUN_Y_PARAM, double SUN_Z_PARAM, double albedo_PARAM)    { //function that simply iterates over a square, and calculates sunlight effect accordinly...
    
    //asign parameters as global variables.
    SAT_X_POSITION=SAT_X_PARAM;
    SAT_Y_POSITION=SAT_Y_PARAM;
    SAT_Z_POSITION=SAT_Z_PARAM;
    SUN_X=SUN_X_PARAM;
    SUN_Y=SUN_Y_PARAM;
    SUN_Z=SUN_Z_PARAM;
    albedo=albedo_PARAM;
    
    double SUN_POSITION_ABOVE_EARTH=returnDistanceBetweenPoints(0, 0, 0, SUN_X, SUN_Y, SUN_Z);
    
    double MAX_ANGLE=acos(EARTH_RADIUS/SUN_POSITION_ABOVE_EARTH);
    
    //defined in diagram, different than alpha
    MAX_ACCEPTABLE_DISTANCE=sin(MAX_ANGLE)*SUN_POSITION_ABOVE_EARTH;
    
    double NET_FLUX=0;
    
    for(double alpha = 0; alpha < ALPHA_MAX; alpha = alpha + alpha_interval)
    {
        for(double theta = 0; theta <THETA_MAX; theta = theta + theta_interval)
        {
            double alpha_new=alpha+alpha_interval/2; //approximating the centroid.
            double theta_new=theta+theta_interval/2;
            
            if (returnValidPointInRelationToSun(alpha_new,theta_new))  {
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
    //Alter the below params to change the setup for the flux result.
    double SAT_X_PARAM=0;
    double SAT_Y_PARAM=0;
    double SAT_Z_PARAM=160000+EARTH_RADIUS;
    double SUN_X_PARAM=0;
    double SUN_Y_PARAM=0;
    double SUN_Z_PARAM=150*pow(10,9);
    double albedo_PARAM=.8;
    
    double result= returnFluxForParameters(SAT_X_PARAM, SAT_Y_PARAM, SAT_Z_PARAM, SUN_X_PARAM, SUN_Y_PARAM, SUN_Z_PARAM, albedo_PARAM);
    cout << result << endl;
    
//    //ToCheck the above function, let's run a for loop that simulates if the earth and satellite didn't move but the sun rose and set...
//    
//    //    //let's iterate through some values of the sun to check ...
//    //
//    double x_initial=150*pow(10,9); //sun starts out on the horizon.
//    double x_final=-150*pow(10,9);
//    int NUM_STEPS=20;
//    double sun_interval=fabs((x_final-x_initial)/NUM_STEPS);
//    
//    ofstream myfile;
//    myfile.open("outPutFile", std::ofstream::out | std::ofstream::trunc); //open and delete the previous contents of the file from past simulation runs...
//    if (!myfile.is_open()) {
//        cerr << "Fail to open output file\n";
//        exit(EXIT_FAILURE);
//    }
//    
//    for(double SUN_X = x_initial; SUN_X > x_final; SUN_X = SUN_X - sun_interval)
//    {
//        //we're not varying y, so we don't need to worry about that
//        //we have to calculate our z value.
//        double Z_Pos=pow( pow(150*pow(10,9),2) - pow(SUN_X,2) , .5 );
//        double result=returnFluxForParameters(SAT_X_PARAM, SAT_Y_PARAM, SAT_Z_PARAM, SUN_X, 0, Z_Pos, albedo_PARAM);
//        
//        myfile << result;
//        myfile << "\n";
//        myfile.close();
   // }
    
    //    double answer = runForLoop();
    //    cout << "Result: " << answer;
    //
    //    ofstream myfile;
    //    myfile.open("example.txt", std::ofstream::out | std::ofstream::trunc); //open and delete the previous contents of the file from past simulation runs...
    //    if (!myfile.is_open()){
    //        cerr << "Fail to open output file\n";
    //        exit(EXIT_FAILURE);
    //    }
    //    myfile << answer;
    //    myfile << "\n";
    //    myfile.flush();
    //    myfile.close();
}



//TODO movement of sun...

//Optimizations are going to be a critical way to make our program more efficient. In this sections, I hope to add inteligent optimizations.

//End optimizations.







