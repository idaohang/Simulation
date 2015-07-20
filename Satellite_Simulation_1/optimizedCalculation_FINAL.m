%This program is meant to provide a graphical representation of what's
%going on in the C++ flux calculator.
%Made by David Jackson, Summer 2015

%assumes half angle for sun visibility, since sun is so far away.
function [unitVectMatrix,dFluxMatrix]=optimizedCalculation_FINAL(SAT_VECT,SUN_VECT,albedo)
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

MAX_ALPHA=acos(EARTH_RADIUS/DISTANCE_FROM_EARTH_CENTER_TO_SAT);

NUM_STEPS_ALPHA=5; % Alter to your desired level of accuracy...
NUM_STEPS_THETA=5;

ALPHA_INTERVAL=MAX_ALPHA/(NUM_STEPS_ALPHA);

%Preallocation, the maximum number of possible spots...
maxCounterValue=(NUM_STEPS_THETA+1)*(NUM_STEPS_ALPHA+1);
dFluxMatrix=zeros(maxCounterValue,1);
unitVectMatrix=zeros(maxCounterValue,3);

counter=0;

%%% Due to our transformation, we now know the sun, the satellite and x axis are all in the same place. We need to calculate the angle between the sun and the z axis (bearing angle).
%%% (let's call this angle kappa);
SUN_V=[SUN_X SUN_Y SUN_Z];
normal=[0 0 1]; %Bearing angle from axis of the satellite...

kappa=acos(dot(SUN_V,normal)/(norm(SUN_V)*norm(normal)));

%We can also determine a "minimum alpha" for our calculations
MIN_ALPHA=0;

%If the sun is below zero, we know the sun can't see the very top of the
%satellit visibility area; thus we can constrain our minimum alpha.
if SUN_Z<0
    MIN_ALPHA=kappa-pi/2;
end

%Now we can use geometry to calculate how far around

[betaBool]=BETA_CHECK_PASSED(SUN_V,MAX_ALPHA); %Check if any area sees sun
if ~betaBool % if no band can see sun.
    dFluxMatrix=[];
    unitVectMatrix=[];
else
    for alpha=MIN_ALPHA:ALPHA_INTERVAL:MAX_ALPHA
        

        %For every alpha, we can use our trigonometry calculations.
        
        %We're just going to run over one side of the band for y=y && y=-y since the problem is symmetric the way we've set up the
        %axes.
        THETA_LOWER_BOUND=0;
        
        kappaCopy=kappa; % kappaCopy is the angle between the bearing kappa (the bearing angle) and the xy plane.
        if (kappaCopy>pi/2)
            kappaCopy=kappaCopy-pi/2;
        else
            kappaCopy=pi/2-kappaCopy;
        end
        [boolAllBandVisible]=allBandVisible(alpha,kappa);
        THETA_UPPER_BOUND=0;
        if (boolAllBandVisible)
            THETA_UPPER_BOUND=pi;
        else
            q=EARTH_RADIUS*cos(alpha);
            
            h=EARTH_RADIUS*(1-cos(alpha));
            
            d=q*sin(kappaCopy);
            
            zed=EARTH_RADIUS*sin(alpha);
            
            sci=acos(d/zed);
            
            if SUN_Z<0
                lambda=sci;
            else
                lambda=pi-sci;
            end
            
            THETA_UPPER_BOUND=lambda;
        end
        
        if (SUN_X<0)
            THETA_LOWER_BOUND=THETA_LOWER_BOUND+pi;
            THETA_UPPER_BOUND=THETA_UPPER_BOUND+pi;
        end
        
        THETA_INTERVAL=(THETA_UPPER_BOUND-THETA_LOWER_BOUND)/NUM_STEPS_THETA;
        
        for theta=THETA_LOWER_BOUND:THETA_INTERVAL:THETA_UPPER_BOUND
            
            x=EARTH_RADIUS*sin(alpha)*cos(theta);
            y=EARTH_RADIUS*sin(alpha)*sin(theta);
            z=EARTH_RADIUS*cos(alpha);
            
            for (i=1:-2:-1) %little hack just sets y=y and y=-y (since we're dealing with a symmetric problem).
                if (i==-1 && y==0) %don't double count element when y=0 (reflected so it's equivalent)
                    continue;
                end
                
                y=i*y;
                
                %find the unit vector from earth element to satellite
                earthElementToSatVect=[SAT_X-x,SAT_Y-y,SAT_Z-z];
                unitElementToSatVect=earthElementToSatVect/norm(earthElementToSatVect);
                
                unitElementToSatVect=(R'*unitElementToSatVect')';
                
                %Calculate flux
                r = ( (x-SAT_X)^2 + (y-SAT_Y)^2 + (z-SAT_Z)^2 )^.5;  %distance between area element and the satellite.
                
                areaEarthElement=EARTH_RADIUS^2*sin(alpha)*THETA_INTERVAL*ALPHA_INTERVAL;
                
                a=[x,y,z]; %vector normal to earth element.
                b=[SUN_X-x,SUN_Y-y,SUN_Z-z]; % vector from earth element to sun
                
                sunAngle=acos(dot(a,b)/(norm(a)*norm(b))); %angle between a and b
                
                dflux=(albedo*E_s*cos(sunAngle)+e*M_b)/(pi*r^2)*cos(alpha)*areaEarthElement; %flux calculation, value in watts/m^2
                
                if dflux>0 %~dflux==0
                    counter=counter+1;
                    unitVectMatrix(counter,1)=unitElementToSatVect(1,1);
                    unitVectMatrix(counter,2)=unitElementToSatVect(1,2);
                    unitVectMatrix(counter,3)=unitElementToSatVect(1,3);
                    
                    dFluxMatrix(counter,1)=dflux;
                    
                else
                    
                end
            end
        end
    end
    
    %Eliminate extra rows:
    unitVectMatrix = unitVectMatrix(1:counter,1:3);
    dFluxMatrix=sparse(dFluxMatrix);
    
    %We can use our calculation for flux to find out what the acceleration
    %is...
    Ac=.5; % assume satellite area of .5 meters.
    NET_FLUX=sum(dFluxMatrix);
    MASS_SAT=100; %100kg
    Cr=.2;
    vect=[0 0 1];
    c=299792458; %speed of light, m/s
    accelerationVector=NET_FLUX*Ac/(c*MASS_SAT) * (2*Cr*vect+(1-Cr)*vect);
    disp('acceleration vector: ');
    disp(accelerationVector);
    disp('*********************');
end
end

%adjusts the coordinate system so the sun and the satellite are in the same
%plane...
function [SAT_X0,SAT_Y0,SAT_Z0,SUN_X0,SUN_Y0,SUN_Z0,R]=adjustSatAndSunPositions(SAT_X,SAT_Y,SAT_Z,SUN_X,SUN_Y,SUN_Z)
SUN_VECTOR=[SUN_X,SUN_Y,SUN_Z];
a=SUN_VECTOR;

new_z=[SAT_X,SAT_Y,SAT_Z];
new_z=new_z/norm(new_z);
b=new_z;

angle=acos(dot(a,b)/(norm(a)*norm(b)));
if (angle==0 || angle==pi) % Satellite and sun already on vertical; no need to rotate...
    
    %Find the magnitude of the satellit vector
    
    MAG_SAT_VECTOR=norm([SAT_X,SAT_Y,SAT_Z]);
    
    SAT_X0=0;
    SAT_Y0=0;
    SAT_Z0=MAG_SAT_VECTOR;
    
    MAG_SUN_VECTOR=norm([SUN_X SUN_Y SUN_Z]);
    
    SUN_X0=0;
    SUN_Y0=0;
    
    if angle==pi
        SUN_Z0=-MAG_SUN_VECTOR;
    else
        SUN_Z0=MAG_SUN_VECTOR;
    end
    
    R=[1,0,0;0,1,0;0,0,1]; % return Indentity matrix, since we require that this function return a rotation matrix.
    
else % We do the transformation
    
    %In this fashion we ensure that the axis direction which we use for positive x and y is always
    %pointed is consistent...
    if SUN_Y>0
        new_y=cross(new_z,SUN_VECTOR);
    else
        new_y=cross(SUN_VECTOR,new_z);
    end
    
    new_y=new_y/norm(new_y);
    
    new_x=[];
    new_x=cross(new_y,new_z);
    new_x=new_x/norm(new_x);
    
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
end

%Beta angle provides a limit on where the sun can be to contribute light...
function [boolBetaCheckPassed]=BETA_CHECK_PASSED(SUN_VECT,alpha)
boolBetaCheckPassed=true;
SUN_Z=SUN_VECT(1,3);
if SUN_Z<0
    N_0=[0 0 1];
    angle=returnAngleBetweenVectors(N_0,SUN_VECT);
    if angle-pi/2>alpha % can't see the sun
        boolBetaCheckPassed=false;
    end
end
end

%This function returns true if all of a band can see the sun...
function [boolAllBandVisible]=allBandVisible(alpha,sunAngleToPolar)
boolAllBandVisible=(sunAngleToPolar<pi/2-alpha);
end

function [angle]=returnAngleBetweenVectors(a,b)
angle=acos(dot(a,b)/(norm(a)*norm(b)));
end

