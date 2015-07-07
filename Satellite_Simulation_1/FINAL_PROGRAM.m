%This program is meant to provide a graphical representation of what's
%going on in the C++ flux calculator.
%Made by David Jackson Summer 2015
function [unitVectMatrix,dFluxMatrix]=main[SAT_VECT,SUN_VECT,albedo]

EARTH_RADIUS=6371000;
E_s=1360;
e=1-albedo;
M_b=E_s/4;

SUN_ORIGINAL_X=SUN_VECT(1,1);
SUN_ORIGINAL_Y=SUN_VECT(1,2);
SUN_ORIGINAL_Z=SUN_VECT(1,3);

SAT_X=SAT_VECT(1,1);
SAT_Y=SAT_VECT(1,2);
SAT_Z=SAT_VECT(1,3);

[SAT_X,SAT_Y,SAT_Z,SUN_X,SUN_Y,SUN_Z,R]=adjustSatAndSunPositions(SAT_X,SAT_Y,SAT_Z,SUN_ORIGINAL_X,SUN_ORIGINAL_Y,SUN_ORIGINAL_Z);

DISTANCE_FROM_EARTH_CENTER_TO_SAT=(SAT_X^2+SAT_Y^2+SAT_Z^2)^.5;
DISTANCE_FROM_EARTH_CENTER_TO_SUN=(SUN_X^2+SUN_Y^2+SUN_Z^2)^.5;

MAX_SAT_ANGLE=acos(EARTH_RADIUS/DISTANCE_FROM_EARTH_CENTER_TO_SAT);
MAX_SUN_ANGLE=acos(EARTH_RADIUS/DISTANCE_FROM_EARTH_CENTER_TO_SUN);

MAX_DISTANCE_TO_SATELLITE=DISTANCE_FROM_EARTH_CENTER_TO_SAT*sin(MAX_SAT_ANGLE);
MAX_DISTANCE_TO_SUN=DISTANCE_FROM_EARTH_CENTER_TO_SUN*sin(MAX_SUN_ANGLE);

NUM_STEPS_BETA=10;
NUM_STEPS_THETA=10;

INTERVAL_BETA=MAX_SAT_ANGLE/NUM_STEPS_BETA;
THETA_MAX=2*pi;
INTERVAL_THETA=THETA_MAX/NUM_STEPS_THETA;

%Preallocation, the maximum number of possible spots...
dFluxMatrix=zeros(NUM_STEPS_BETA*NUM_STEPS_THETA,1);
unitVectMatrix=zeros(NUM_STEPS_BETA*NUM_STEPS_THETA,3);
counter=0;

for alpha=0:INTERVAL_BETA:MAX_SAT_ANGLE
    for theta=0:INTERVAL_THETA:THETA_MAX
        x=EARTH_RADIUS*sin(alpha)*cos(theta);
        y=EARTH_RADIUS*sin(alpha)*sin(theta);
        z=EARTH_RADIUS*cos(alpha);
        
        counter=counter+1;
        
        %find the unit vector from earth element to satellite
        earthElementToSatVect=[SAT_X-x,SAT_Y-y,SAT_Z-z];
        unitElementToSatVect=earthElementToSatVect/norm(earthElementToSatVect);
        Rtrans=transpose(R);
        unitElementToSatVect=unitElementToSatVect*Rtrans;
         
        ACTUAL_DISTANCE_TO_SATELLITE=((x-SAT_X)^2+(y-SAT_Y)^2+(z-SAT_Z)^2)^.5;
        ACTUAL_DISTANCE_TO_SUN=((x-SUN_X)^2+(y-SUN_Y)^2+(z-SUN_Z)^2)^.5;
        
        if ACTUAL_DISTANCE_TO_SATELLITE<MAX_DISTANCE_TO_SATELLITE && ACTUAL_DISTANCE_TO_SUN<MAX_DISTANCE_TO_SUN
            %visible to both satellite and the sun.
            %This is the case where we calculate flux...
            r = ( (x-SAT_X)^2 + (y-SAT_Y)^2 + (z-SAT_Z)^2 )^.5;  %distance between area element and the satellite.
            
            areaEarthElement=EARTH_RADIUS^2*sin(alpha)*INTERVAL_THETA*INTERVAL_BETA;
            
            a=[x,y,z]; %vector normal to earth element.
            b=[SUN_X-x,SUN_Y-y,SUN_Z-z]; % vector from earth element to sun
            
            sunAngle=acos(dot(a,b)/(norm(a)*norm(b))); %angle between a and b
            dflux=(albedo*E_s*cos(sunAngle)+e*M_b)/(pi*r^2)*cos(alpha)*areaEarthElement; %flux calculation, value in watts/m^2
            
            if ~dflux==0               
                unitVectMatrix(counter,1)=unitElementToSatVect;
                dFluxMatrix(counter,1)=dflux;
            end
             
        end
        
    end
end
end

function [SAT_X0,SAT_Y0,SAT_Z0,SUN_X0,SUN_Y0,SUN_Z0,R]=adjustSatAndSunPositions(SAT_X,SAT_Y,SAT_Z,SUN_X,SUN_Y,SUN_Z)
new_z=[SAT_X,SAT_Y,SAT_Z];
new_z=new_z/norm(new_z);

new_x=cross([0,0,1],new_z);
new_x=new_x/norm(new_x);
new_y=cross(new_z,new_x);
new_y=new_y/norm(new_y);

R=[new_x;new_y;new_z];

SUN_NEW_VECTOR=R*[SUN_X;SUN_Y;SUN_Z];
SUN_X0=SUN_NEW_VECTOR(1,1);
SUN_Y0=SUN_NEW_VECTOR(2,1);
SUN_Z0=SUN_NEW_VECTOR(3,1);

SAT_OLD=[SAT_X;SAT_Y;SAT_Z];
SAT_NEW_VECTOR=R*SAT_OLD;
SAT_X0=SAT_NEW_VECTOR(1,1);
SAT_Y0=SAT_NEW_VECTOR(2,1);
SAT_Z0=SAT_NEW_VECTOR(3,1);
end


