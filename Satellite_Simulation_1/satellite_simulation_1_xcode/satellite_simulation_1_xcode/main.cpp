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

//class types:
class vec
{
public:
    float x, y, z;
};

//Function headers

double returnDistanceBetweenPoints(double X, double Y, double Z, double X0, double Y0, double Z0);
double returnAngleBetweenTwoVectors(double X, double Y, double Z, double X0, double Y0, double Z0);
void setUpRotationMatrix(float angle, float u, float v, float w);
void multiplyMatrix();
vec crossproduct(double Ax, double Ay, double Az, double Bx, double By, double Bz);
//THESE VARIABLES ARE SET IN MAIN...///
double SUN_X;
double SUN_Y;
double SUN_Z;

double SAT_X;
double SAT_Y;
double SAT_Z;

double albedo;
///////////////////////////////////////

const double EARTH_RADIUS=6371000;

const double e=1-albedo; //emmisivity

#warning TODO replace with Satellite area...
const double Ac=.5;

double MAX_ACCEPTABLE_DISTANCE;

#warning Sumeet has a better expression for this...
const double E_s=1360; //wiki (W/m^2)

const double M_b=E_s/4; //As derived in the paper.

const int NUM_STEPS_THETA=2;

const int NUM_STEPS_beta=2;

double THETA_MAX;

double BETA_MAX;

double theta_interval;

double beta_interval;

//For rotation matrix...
float rotationMatrix[4][4];
float inputMatrix[4][1] = {0.0, 0.0, 0.0, 0.0};
float outputMatrix[4][1] = {0.0, 0.0, 0.0, 0.0};

/////////////////////////////////////////////////////END CONSTANT DEFINITIONS
//////////////////////////////////////////////////////////////////////////

//FUNCTIONS
double magnitudeOfVector (double x, double y, double z)  {
    return pow( (pow(x,2) + pow(y,2) + pow(z,2)) ,  .5);
}

double returnSunAngleForAreaElementAt(double beta, double theta)  { //this is the angle between the sun and the normal vector to the earth element.
    double x=EARTH_RADIUS*cos(theta)*sin(beta); //just translating from cartesian to spherical.
    double y=EARTH_RADIUS*sin(theta)*sin(beta);
    double z=EARTH_RADIUS*cos(beta);
    return returnAngleBetweenTwoVectors(x, y, z, SUN_X, SUN_Y, SUN_Z);
}

double calculateSunlightEffect(double beta, double theta) {
    double x=EARTH_RADIUS*cos(theta)*sin(beta); //just translating from cartesian to spherical.
    double y=EARTH_RADIUS*sin(theta)*sin(beta);
    double z=EARTH_RADIUS*cos(beta);
    
    double r = returnDistanceBetweenPoints(x, y, z, SAT_X, SAT_Y, SAT_Z);  //distance between area element and the satellite.
    
    //We have been using the variable beta to denote the limits of our discretization.
    //Note that alpha is used the paper to describe the angle between the normal vector to the area element and the satellite vector. This is different than the beta we have been using an an for loop variable.
    double alpha=returnAngleBetweenTwoVectors(x, y, z, SAT_X, SAT_Y, SAT_Z);
    
    double areaEarthElement=pow(EARTH_RADIUS,2)*sin(theta)*theta_interval*beta_interval;
    
    return (albedo*E_s*cos(returnSunAngleForAreaElementAt(beta,theta))+e*M_b)*Ac/(M_PI*pow(r,2))*cos(alpha)* areaEarthElement;
}

double returnAngleBetweenTwoVectors(double X, double Y, double Z, double X0, double Y0, double Z0) {
    double MAG_1=pow( (pow(X,2) + pow(Y,2)  + pow(Z,2)) ,  .5);
    double MAG_2=pow( (pow(X0,2) + pow(Y0,2)  + pow(Z0,2)) ,  .5);
    double DOT_PROD=X*X0+Y*Y0+Z*Z0;
    return acos(DOT_PROD/(MAG_1*MAG_2));
}

double returnDistanceBetweenPoints(double X, double Y, double Z, double X0, double Y0, double Z0)    {
    double distance=0;
    distance=pow( (pow(X-X0,2) + pow(Y-Y0,2)  + pow(Z-Z0,2)) ,  .5);
    return distance;
}

bool returnValidPointInRelationToSun (double beta, double theta) //returns whether a point is within the area seen by the sun. (We're iterating to find common area visible to the satellite and the sun)
{
    double x=EARTH_RADIUS*cos(theta)*sin(beta); //just translating from cartesian to spherical.
    double y=EARTH_RADIUS*sin(theta)*sin(beta);
    double z=EARTH_RADIUS*cos(beta);
    
    double earthRadius=magnitudeOfVector(x, y, z);
    
    double ACTUAL_DISTANCE=returnDistanceBetweenPoints(x, y, z, SUN_X, SUN_Y, SUN_Z);
    
    return (MAX_ACCEPTABLE_DISTANCE > ACTUAL_DISTANCE);
}

double returnFluxForParameters(double SAT_X_PARAM, double SAT_Y_PARAM, double SAT_Z_PARAM,double SUN_X_PARAM, double SUN_Y_PARAM, double SUN_Z_PARAM, double albedo_PARAM)    { //function that simply iterates over a circle area defined by beta and theta, and calculates sunlight effect accordinly...
    
    //asign parameters as global variables.
    SAT_X=SAT_X_PARAM;
    SAT_Y=SAT_Y_PARAM;
    SAT_Z=SAT_Z_PARAM;
    SUN_X=SUN_X_PARAM;
    SUN_Y=SUN_Y_PARAM;
    SUN_Z=SUN_Z_PARAM;
    albedo=albedo_PARAM;
    
    //We use the input params to determine a few other global constants.
    THETA_MAX=2*M_PI;
    
    BETA_MAX=acos(EARTH_RADIUS/returnDistanceBetweenPoints(0, 0, 0, SAT_X, SAT_Y, SAT_Z));
    
    theta_interval=THETA_MAX/NUM_STEPS_THETA;
    
    beta_interval=BETA_MAX/NUM_STEPS_beta;
    
    double SUN_POSITION_FROM_EARTH_CENTER=returnDistanceBetweenPoints(0, 0, 0, SUN_X, SUN_Y, SUN_Z);
    
    double MAX_ANGLE=acos(EARTH_RADIUS/SUN_POSITION_FROM_EARTH_CENTER);
    
    //defined in diagram, different than beta
    MAX_ACCEPTABLE_DISTANCE=sin(MAX_ANGLE)*SUN_POSITION_FROM_EARTH_CENTER;
    
    double NET_FLUX=0;
    
    for(double beta = 0; beta < BETA_MAX; beta = beta + beta_interval)
    {
        for(double theta = 0; theta <THETA_MAX; theta = theta + theta_interval)
        {
            if (returnValidPointInRelationToSun(beta,theta))  {
                //calculate the z position for this discrete piece
                
                double dFLUX;
                
                dFLUX=calculateSunlightEffect(beta,theta);
                
                NET_FLUX=NET_FLUX+dFLUX;
            }
        }
    }
    return NET_FLUX;
}

int main ()
{
    //Alter the below params to change the setup for the flux result.
    
    double SUN_X_PARAM=3.581118709561659*pow(10,10);
    double SUN_Y_PARAM=-1.308927327368016*pow(10,11);
    double SUN_Z_PARAM=-5.677199113568006*pow(10,10);
    double albedo_PARAM=.3;
    
    //reading in the file:
    ifstream infile;
    
    string read_file_name("satPositions.txt");
    
    infile.open(read_file_name);
    
    string sLine;
    
    int counter=0;
    
    double SAT_X_PARAM;
    double SAT_Y_PARAM;
    double SAT_Z_PARAM;
    
    ofstream myfile;
    myfile.open("outputFluxes.txt", std::ofstream::out | std::ofstream::trunc); //open and delete the previous contents of the file from past simulation runs...
    if (!myfile.is_open()){
        cerr << "Failed to open output file\n";
        exit(EXIT_FAILURE);
    }
    
    while (!infile.eof())
    {
        infile >> sLine;
        //        cout << sLine.data() << endl;
        
        counter++;
        
        if (counter==1)   {
            SAT_X_PARAM=atof(sLine.data());
        }
        
        if (counter==2)   {
            SAT_Y_PARAM=atof(sLine.data());
        }
        
        if (counter==3)   {
            SAT_Z_PARAM=atof(sLine.data());
            counter=0;
            
            //Before we run our simulation, we need to reorient our axes.
            //The satellite needs to be on the vertical axis (since this is how we iterate alpha/theta)
            //Rotation matrix code is forked from: http://www.programming-techniques.com/2012/03/3d-rotation-algorithm-about-arbitrary.html
            //Rotates counterclockwise about arbitrary axis vector that passes through the origin.

            float angle=returnAngleBetweenTwoVectors(SAT_X_PARAM, SAT_Y_PARAM, SAT_Z_PARAM, 0, 0, 1);
           
            float u, v, w;
            
            inputMatrix[0][0] = SAT_X_PARAM; //rotating the Satellite matrix.
            inputMatrix[1][0] = SAT_Y_PARAM;
            inputMatrix[2][0] = SAT_Z_PARAM;
            inputMatrix[3][0] = 1.0;

            vec vect=crossproduct(SAT_X_PARAM, SAT_Y_PARAM, SAT_Z_PARAM, 0, 0, 1);
            u=vect.x;
            v=vect.y;
            w=vect.z;
            
            setUpRotationMatrix(angle, u, v, w);
            multiplyMatrix();
            
            SAT_X=outputMatrix[0][0];
            SAT_Y=outputMatrix[1][0];
            SAT_Z=outputMatrix[2][0];
            
            inputMatrix[0][0] = SUN_X_PARAM;
            inputMatrix[1][0] = SUN_Y_PARAM;
            inputMatrix[2][0] = SUN_Z_PARAM;
            inputMatrix[3][0] = 1.0;
            
            multiplyMatrix();
            SUN_X=outputMatrix[0][0];
            SUN_Y=outputMatrix[1][0];
            SUN_Z=outputMatrix[2][0];

            double result= returnFluxForParameters(SAT_X_PARAM, SAT_Y_PARAM, SAT_Z_PARAM, SUN_X_PARAM, SUN_Y_PARAM, SUN_Z_PARAM, albedo_PARAM);
            myfile << result;
            myfile << "\n";
            cout << result << endl;
        }
    }
    
    myfile.flush();
    myfile.close();
    infile.close();
}

void multiplyMatrix()
{
    for(int i = 0; i < 4; i++ ){
        for(int j = 0; j < 1; j++){
            outputMatrix[i][j] = 0;
            for(int k = 0; k < 4; k++){
                outputMatrix[i][j] += rotationMatrix[i][k] * inputMatrix[k][j];
            }
        }
    }
}
void setUpRotationMatrix(float angle, float u, float v, float w)
{
    float L = (u*u + v * v + w * w);
    float u2 = u * u;
    float v2 = v * v;
    float w2 = w * w;
    
    rotationMatrix[0][0] = (u2 + (v2 + w2) * cos(angle)) / L;
    rotationMatrix[0][1] = (u * v * (1 - cos(angle)) - w * sqrt(L) * sin(angle)) / L;
    rotationMatrix[0][2] = (u * w * (1 - cos(angle)) + v * sqrt(L) * sin(angle)) / L;
    rotationMatrix[0][3] = 0.0;
    
    rotationMatrix[1][0] = (u * v * (1 - cos(angle)) + w * sqrt(L) * sin(angle)) / L;
    rotationMatrix[1][1] = (v2 + (u2 + w2) * cos(angle)) / L;
    rotationMatrix[1][2] = (v * w * (1 - cos(angle)) - u * sqrt(L) * sin(angle)) / L;
    rotationMatrix[1][3] = 0.0;
    
    rotationMatrix[2][0] = (u * w * (1 - cos(angle)) - v * sqrt(L) * sin(angle)) / L;
    rotationMatrix[2][1] = (v * w * (1 - cos(angle)) + u * sqrt(L) * sin(angle)) / L;
    rotationMatrix[2][2] = (w2 + (u2 + v2) * cos(angle)) / L;
    rotationMatrix[2][3] = 0.0;
    
    rotationMatrix[3][0] = 0.0;
    rotationMatrix[3][1] = 0.0;
    rotationMatrix[3][2] = 0.0;
    rotationMatrix[3][3] = 1.0;
}

vec crossproduct(double Ax, double Ay, double Az, double Bx, double By, double Bz)
{
    vec vector;
    vector.x = (Ay*Bz)-(By*Az);
    vector.y = -(Ax*Bz)+(Bx*Az);
    vector.z = (Ax*By)-(Ay*Bx);
    return vector;
}


//TODO movement of sun...

//Optimizations are going to be a critical way to make our program more efficient. In this sections, I hope to add inteligent optimizations.

//End optimizations.







