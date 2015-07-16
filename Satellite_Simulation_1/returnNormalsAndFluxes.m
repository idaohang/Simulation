%This program is meant to provide a graphical representation of what's
%going on in the C++ flux calculator.
%Made by David Jackson Summer 2015
function [unitVectMatrix,dFluxMatrix]=returnNormalsAndFluxes(SAT_VECT,SUN_VECT,albedo)
tic;
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

NUM_STEPS_ALPHA=10;
NUM_STEPS_THETA=10;

INTERVAL_ALPHA=MAX_SAT_ANGLE/NUM_STEPS_ALPHA;
THETA_MAX=2*pi;
INTERVAL_THETA=THETA_MAX/NUM_STEPS_THETA;

%Preallocation, the maximum number of possible spots...
maxCounterValue=(NUM_STEPS_THETA+1)*(NUM_STEPS_ALPHA+1);
dFluxMatrix=zeros(maxCounterValue,1);
unitVectMatrix=zeros(maxCounterValue,3);

counter=0;

% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %Between these comments is a test of a smarter algorithm that should get
% %the same answer
% %Looks for closest point and then calculates from there...walking around
% %both ways...
% 
% %First create a sun copy point that has z=0; use an alpha in range [>0 :
% %<pi/2] to determine theta sun...
% 
% SUN_COPY_X=SUN_X;
% SUN_COPY_Y=SUN_Y;
% SUN_COPY_Z=0;
% 
% A=[SUN_COPY_X,SUN_COPY_Y,SUN_COPY_Z];
% B=[0,1,0];
% 
% angleBetweenSunAndThetaZero=acos(dot(A,B)/(norm(A)*norm(B)));
% 
% %Find closest theta and then determine if you must round up or down...
% 
% remainderAngle=angleBetweenSunAndThetaZero-mod(angleBetweenSunAndThetaZero,INTERVAL_THETA);
% 
% if (remainderAngle==0)
%     START_THETA=angleBetweenSunAndThetaZero;
% elseif (remainderAngle-INTERVAL_THETA>0) % round up...
%     START_THETA=angleBetweenSunAndThetaZero+(INTERVAL_THETA-remainderAngle);
% else %round down...
%     START_THETA=angleBetweenSunAndThetaZero-remainderAngle;
% end
% 
% %Now that we've identified our START_THETA, we're ready to iterate...
% 
% SUN_VECTOR=[SUN_X SUN_Y SUN_Z];
% SAT_VECTOR=[SAT_X SAT_Y SAT_Z];

% I think an angle of theta=0 corresponds to unit vector [0 1 0] //TODO CHECK THIS

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for alpha=0:.1:pi %MAX_SAT_ANGLE
    for theta=0:.1:2*pi %THETA_MAX-INTERVAL_THETA
% for alpha=INTERVAL_ALPHA/2:INTERVAL_ALPHA:MAX_SAT_ANGLE
%     for theta=0:INTERVAL_THETA:THETA_MAX-INTERVAL_THETA
        x=EARTH_RADIUS*sin(alpha)*cos(theta);
        y=EARTH_RADIUS*sin(alpha)*sin(theta);
        z=EARTH_RADIUS*cos(alpha);
        

        
        %find the unit vector from earth element to satellite
        earthElementToSatVect=[SAT_X-x,SAT_Y-y,SAT_Z-z];
        unitElementToSatVect=earthElementToSatVect/norm(earthElementToSatVect);
        Rtrans=transpose(R);
        unitElementToSatVect=unitElementToSatVect*Rtrans;
        
        ACTUAL_DISTANCE_TO_SATELLITE=((x-SAT_X)^2+(y-SAT_Y)^2+(z-SAT_Z)^2)^.5;
        ACTUAL_DISTANCE_TO_SUN=((x-SUN_X)^2+(y-SUN_Y)^2+(z-SUN_Z)^2)^.5;
        
        if ACTUAL_DISTANCE_TO_SATELLITE<MAX_DISTANCE_TO_SATELLITE && ACTUAL_DISTANCE_TO_SUN<MAX_DISTANCE_TO_SUN
            scatter3(x,y,z,'red'); % TODO DELETE IN FINAL VERSION...
            hold on;
            %visible to both satellite and the sun.
            %This is the case where we calculate flux...
            r = ( (x-SAT_X)^2 + (y-SAT_Y)^2 + (z-SAT_Z)^2 )^.5;  %distance between area element and the satellite.
            
            areaEarthElement=EARTH_RADIUS^2*sin(alpha)*INTERVAL_THETA*INTERVAL_ALPHA;
            
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
            end
        else
            scatter3(x,y,z,'black'); % TODO DELETE IN FINAL VERSION...
            hold on;
        end
    end
    


end

%Eliminate extra rows:
unitVectMatrix = unitVectMatrix(1:counter,1:3);
dFluxMatrix=sparse(dFluxMatrix);

NET_FLUX=sum(dFluxMatrix);

disp('***************')
disp('NET FLUX NON-OPTIMIZED')
disp(NET_FLUX);
disp('***************')

toc
end

%BEGIN FUNCTIONS THAT ARE OPTIMIZES AND WILL ATTEMPT TO REPLICATE THE
%ORIGINAL RESULTS % TODO CONFIRM AND DELETE THIS COMMENT.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 
% function [dFluxMatrixOptimized,unitVectMatrixOptimized,NET_FLUX_OPTIMIZED]=conductBandSearch(START_THETA,INTERVAL_THETA,INTERVAL_ALPHA,SUN_VECTOR,SAT_VECTOR,MAX_SAT_ANGLE,MAX_SUN_ANGLE,dFluxMatrix,unitVectMatrix,R)
% % 
% counter=0; %number of rows in dflux vector and unit vector.
% % 
% %iterate over the alphas...each alpha defining a new band...
% for alpha=INTERVAL_ALPHA/2:INTERVAL_ALPHA:MAX_SAT_ANGLE
%     
%     %we can walk our way around each band...
%     
%     LEFT_HAND_THETA=START_THETA;
%     RIGHT_HAND_THETA=START_THETA+INTERVAL_THETA; % arbitrary decision for which is where; we're just ballparking where we start.
%     
%     %"normalize anytime we change angle to make sure its between 0 and 2pi"
%     %//TODO CHECK THE EDGE CASES LIKE 0 and 2pi
%     %
%     
%     [LEFT_HAND_THETA]=correctAngle(LEFT_HAND_THETA);
%     
%     [RIGHT_HAND_THETA]=correctAngle(RIGHT_HAND_THETA);
%     
%     handCounter=0; % just allows me to alternate between RHS AND LHS walkers.
%     
%     LHS_COMPLETE=false;
%     RHS_COMPLETE=false;
%     
%     while ( bugy...   (LEFT_HAND_THETA>RIGHT_HAND_THETA) && ~(RHS_COMPLETE && LHS_COMPLETE))
% 
%         if mod(handCounter,2)==0
%             %before advancing, calculate the dflux
%             
%             %For each alpha, let's calculate the flux at the START_THETA
% 
%             [dflux,unitElementToSatVect]=calculateDfluxForParameters(alpha,RIGHT_HAND_THETA,SUN_X,SUN_Y,SUN_Z,R)
% 
%             if dflux>0 %~dflux==0
%                 counter=counter+1;
%                 unitVectMatrix(counter,1)=unitElementToSatVect(1,1);
%                 unitVectMatrix(counter,2)=unitElementToSatVect(1,2);
%                 unitVectMatrix(counter,3)=unitElementToSatVect(1,3);
%                 
%                 
%                 dFluxMatrix(counter,1)=dflux;
%                 
%             else
%                 %add it to the vector....
%                 RHS_COMPLETE=true;
%             end
%             
%             %advance RHS
%             RIGHT_HAND_THETA=RIGHT_HAND_THETA+THETA_INCREMENT;
%             
%             %adjust if above or below 2*pi
%             [RIGHT_HAND_THETA]=correctAngle(RIGHT_HAND_THETA);
%         else
%             
%             %before advancing, calculate the dflux
%             
%             %For each alpha, let's calculate the flux at the START_THETA
%             
%             [dflux,unitElementToSatVect]=calculateDfluxForParameters(alpha,LEFT_HAND_THETA,SUN_X,SUN_Y,SUN_Z,R)
% 
%             if dflux>0 %~dflux==0
%                 counter=counter+1;
%                 unitVectMatrix(counter,1)=unitElementToSatVect(1,1);
%                 unitVectMatrix(counter,2)=unitElementToSatVect(1,2);
%                 unitVectMatrix(counter,3)=unitElementToSatVect(1,3);
%                 
%                 dFluxMatrix(counter,1)=dflux;
%                 
%             else
%                 %add it to the vector....
%                 LHS_COMPLETE=true;
%             end
%             
%             %advance RHS
%             LEFT_HAND_THETA=LEFT_HAND_THETA+THETA_INCREMENT;
%             
%             %adjust if above or below 2*pi
%             [LEFT_HAND_THETA]=correctAngle(LEFT_HAND_THETA);
%             
%         end
%         handCounter=handCounter+1;
%     end
% end
% %here we should have everything done...
% NET_FLUX_OPTIMIZED=sum(dFluxMatrix);
% unitVectMatrixOptimized=unitVectMatrix;
% dFluxMatrixOptimized=dFluxMatrix;
% disp('**************');
% disp('**************');
% disp('Net Flux Using Optimized algorithm:');
% disp(NET_FLUX_OPTIMIZED);
% disp('**************');
% disp('**************');
% end
% 
% function [dflux,unitElementToSatVect]=calculateDfluxForParameters(alpha,theta,SUN_X,SUN_Y,SUN_Z,R) % includes rotation matrix so we can rotate
% x=EARTH_RADIUS*sin(alpha)*cos(theta);
% y=EARTH_RADIUS*sin(alpha)*sin(theta);
% z=EARTH_RADIUS*cos(alph?a);
% 
% %find the unit vector from earth element to satellite
% earthElementToSatVect=[SAT_X-x,SAT_Y-y,SAT_Z-z];
% unitElementToSatVect=earthElementToSatVect/norm(earthElementToSatVect);
% Rtrans=transpose(R);
% unitElementToSatVect=unitElementToSatVect*Rtrans;
% 
% ACTUAL_DISTANCE_TO_SATELLITE=((x-SAT_X)^2+(y-SAT_Y)^2+(z-SAT_Z)^2)^.5;
% ACTUAL_DISTANCE_TO_SUN=((x-SUN_X)^2+(y-SUN_Y)^2+(z-SUN_Z)^2)^.5;
% 
% if ACTUAL_DISTANCE_TO_SATELLITE<MAX_DISTANCE_TO_SATELLITE && ACTUAL_DISTANCE_TO_SUN<MAX_DISTANCE_TO_SUN
%     %visible to both satellite and the sun.
%     %This is the case where we calculate flux...
%     r = ( (x-SAT_X)^2 + (y-SAT_Y)^2 + (z-SAT_Z)^2 )^.5;  %distance between area element and the satellite.
%     
%     areaEarthElement=EARTH_RADIUS^2*sin(alpha)*INTERVAL_THETA*INTERVAL_ALPHA;
%     
%     a=[x,y,z]; %vector normal to earth element.
%     b=[SUN_X-x,SUN_Y-y,SUN_Z-z]; % vector from earth element to sun
%     
%     sunAngle=acos(dot(a,b)/(norm(a)*norm(b))); %angle between a and b
%     dflux=(albedo*E_s*cos(sunAngle)+e*M_b)/(pi*r^2)*cos(alpha)*areaEarthElement; %flux calculation, value in watts/m^2
% end
% 
% end
% 
% function [angle]=correctAngle(angle)
% % as we're walking around angles, we correct them...so they aren't 
%     if (angle<0)
%        angle=2*pi+angle;
%     elseif angle>=2*pi
%         angle=mod(angle,2*pi);
%     end
% 
% end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%END FUNCTIONS FOR OPTIMIZED VERSION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [SAT_X0,SAT_Y0,SAT_Z0,SUN_X0,SUN_Y0,SUN_Z0,R]=adjustSatAndSunPositions(SAT_X,SAT_Y,SAT_Z,SUN_X,SUN_Y,SUN_Z)

a=[0,0,1];
new_z=[SAT_X,SAT_Y,SAT_Z];
new_z=new_z/norm(new_z);
b=new_z;

angle=acos(dot(a,b)/(norm(a)*norm(b)));
if (angle==0 || angle==pi) % Satellite already on vertical.
    
    R=[1,0,0;0,1,0;0,0,1]; % just a unit vector
    SUN_X0=SUN_X;
    SUN_Y0=SUN_Y;
    SAT_X0=SAT_X;
    SAT_Y0=SAT_Y;
    
    if (SAT_Z<0);
        SAT_Z0=abs(SAT_Z);
        SUN_Z0=abs(SUN_Z);
    else
        SAT_Z0=SAT_Z;
        SUN_Z0=SUN_Z;
    end
    
else % We do the transformation
   
    
    new_x=cross(a,b);
    
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





end



