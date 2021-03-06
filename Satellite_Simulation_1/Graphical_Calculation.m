    %This program is meant to provide a graphical representation of what's
    %going on in the C++ flux calculator5. I'm using
    %this as a graphical representation of what's going on in the other
    %program.
function main
    clc;
    clear all;
    close all;
    EARTH_RADIUS=6371000;
    albedo=.3;
    E_s=1360;
    e=1-albedo;
    M_b=E_s/4;
    
    MASS_SAT=100; %kg
    Ac=.5;
    
    SUN_ORIGINAL_X=3.581118709561659*10^10;
    SUN_ORIGINAL_Y=-1.308927327368016*10^11;
    SUN_ORIGINAL_Z=-5.677199113568006*10^10;
   
    SAT_X=0;
    SAT_Y=0;
    SAT_Z=0;
    
    fileID = fopen('satPositionsTest.txt','r');
    imageNameCounter=1;
    tline = fgets(fileID);
    
    while ischar(tline)
        
        tline=strtrim(tline);
        %break up the line by spaces into an array...
        stringsArray = strsplit(tline,' ');

        cell1=stringsArray(1);
        SAT_X=str2num(cell1{1,1});

        cell2=stringsArray(2);
        SAT_Y=str2num(cell2{1,1});

        cell3=stringsArray(3);
        SAT_Z=str2num(cell3{1,1});
        
        [SAT_X,SAT_Y,SAT_Z,SUN_X,SUN_Y,SUN_Z]=adjustSatAndSunPositions(SAT_X,SAT_Y,SAT_Z,SUN_ORIGINAL_X,SUN_ORIGINAL_Y,SUN_ORIGINAL_Z);
        
        scatter3(SAT_X,SAT_Y,SAT_Z,'cyan');
        hold on;
        
        DISTANCE_FROM_EARTH_CENTER_TO_SAT=(SAT_X^2+SAT_Y^2+SAT_Z^2)^.5;
        DISTANCE_FROM_EARTH_CENTER_TO_SUN=(SUN_X^2+SUN_Y^2+SUN_Z^2)^.5;

        MAX_SAT_ANGLE=acos(EARTH_RADIUS/DISTANCE_FROM_EARTH_CENTER_TO_SAT);
        MAX_SUN_ANGLE=acos(EARTH_RADIUS/DISTANCE_FROM_EARTH_CENTER_TO_SUN);

        MAX_DISTANCE_TO_SATELLITE=DISTANCE_FROM_EARTH_CENTER_TO_SAT*sin(MAX_SAT_ANGLE);
        MAX_DISTANCE_TO_SUN=DISTANCE_FROM_EARTH_CENTER_TO_SUN*sin(MAX_SUN_ANGLE);
        
        NUM_STEPS_BETA=30;
        NUM_STEPS_THETA=40;
        
        INTERVAL_ALPHA=MAX_SAT_ANGLE/NUM_STEPS_BETA;
        THETA_MAX=2*pi;
        INTERVAL_THETA=THETA_MAX/NUM_STEPS_THETA;
        
        NET_FLUX=0;
        
for alpha=INTERVAL_ALPHA/2:INTERVAL_ALPHA:MAX_SAT_ANGLE
    for theta=0:INTERVAL_THETA:THETA_MAX-INTERVAL_THETA
        x=EARTH_RADIUS*sin(alpha)*cos(theta);
        y=EARTH_RADIUS*sin(alpha)*sin(theta);
        z=EARTH_RADIUS*cos(alpha);

                ACTUAL_DISTANCE_TO_SATELLITE=((x-SAT_X)^2+(y-SAT_Y)^2+(z-SAT_Z)^2)^.5;
                ACTUAL_DISTANCE_TO_SUN=((x-SUN_X)^2+(y-SUN_Y)^2+(z-SUN_Z)^2)^.5;

                if ACTUAL_DISTANCE_TO_SATELLITE<MAX_DISTANCE_TO_SATELLITE && ACTUAL_DISTANCE_TO_SUN<MAX_DISTANCE_TO_SUN
                    %visible to both satellite and the sun.
                    
                    %In the final version, take out the plotting, and only
                    %calculate...
                    scatter3(x,y,z,'red');
                    
%                   This is the case where we calculate flux...
                    r = ( (x-SAT_X)^2 + (y-SAT_Y)^2 + (z-SAT_Z)^2 )^.5;  %distance between area element and the satellite.
    
                    areaEarthElement=EARTH_RADIUS^2*sin(alpha)*INTERVAL_THETA*INTERVAL_ALPHA;
                    
                    a=[x,y,z]; %vector normal to earth element.
                    b=[SUN_X-x,SUN_Y-y,SUN_Z-z]; % vector from earth element to sun
                    
                    sunAngle=acos(dot(a,b)/(norm(a)*norm(b))); % angle between a and b
                    
                    dflux=(albedo*E_s*cos(sunAngle)+e*M_b)/(pi*r^2)*cos(alpha)*areaEarthElement; % flux calculation, returning a dlux value in watts/m^2
                    
                    NET_FLUX=NET_FLUX+dflux;
                    
                elseif ACTUAL_DISTANCE_TO_SATELLITE<MAX_DISTANCE_TO_SATELLITE %only visible to the satellite.
                    scatter3(x,y,z,'black');
                elseif ACTUAL_DISTANCE_TO_SUN<MAX_DISTANCE_TO_SUN % only visible to the sun.
                    scatter3(x,y,z,'yellow');
                else % not visible to the sun or the satellite
                    scatter3(x,y,z,'green');
                end
                hold on;
            end
        end
        
        %Now calculate the force every satellite gets:
        accelerationVector=zeros(1,3);
        
        %Vector form earth element to satellite
        vect=[SAT_X-x,SAT_Y-y,SAT_Z-z];
        vect=vect/norm(vect);
        
        Cr=.2;
        c= 299792458; %speed of light, m/s
        accelerationVector=NET_FLUX*Ac/(c*MASS_SAT) * (2*Cr*vect+(1-Cr)*vect);

        title(strcat(strcat(strcat(strcat('Reflected Flux Hitting Satellite: ',num2str(NET_FLUX),'W/m^2')),' with acceleration vector: '),num2str(accelerationVector)));
        tline = fgets(fileID);
        xlabel('x (meters)');
        ylabel('y (meters)');
        zlabel('z (meters)');

        saveas( gcf, int2str(strcat(imageNameCounter,'nonrotated')), 'jpg' );

        %no need to save images in the final version, TODO DELETE
%         saveas( gcf, int2str(imageNameCounter), 'jpg' ); % saves the plot as image; optional...
        imageNameCounter=imageNameCounter+1;
        close all;
    end
end

function [SAT_X0,SAT_Y0,SAT_Z0,SUN_X0,SUN_Y0,SUN_Z0]=adjustSatAndSunPositions(SAT_X,SAT_Y,SAT_Z,SUN_X,SUN_Y,SUN_Z)

a=[0,0,1];
new_z=[SAT_X,SAT_Y,SAT_Z];
new_z=new_z/norm(new_z);
b=new_z;

angle=acos(dot(a,b)/(norm(a)*norm(b)));
if (angle==0 || angle==pi) % Satellit already on vertical.
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


