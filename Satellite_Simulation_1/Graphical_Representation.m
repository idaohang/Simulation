%This program is meant to provide a graphical representation of what's
%going on in the C++ flux calculator5. I'm using
%this as a graphical representation of what's going on in the other
%program.
clc;
clear all;
close all;
EARTH_RADIUS=6371000;

VOID NOTUPDATED NOT USED ANYMORE

% NUM_STEPS_BETA=100;
% NUM_STEPS_THETA=100;

SUN_X=3.581118709561659*10^10;
SUN_Y=-1.308927327368016*10^11;
SUN_Z=-5.677199113568006*10^10;

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
    scatter3(SAT_X,SAT_Y,SAT_Z,'cyan');
    hold on;
    
    for alpha=0:.2:pi/2
        for theta=0:.2:2*pi
            x=EARTH_RADIUS*sin(alpha)*cos(theta);
            y=EARTH_RADIUS*sin(alpha)*sin(theta);
            z=EARTH_RADIUS*cos(alpha);
            
            DISTANCE_FROM_EARTH_CENTER_TO_SAT=(SAT_X^2+SAT_Y^2+SAT_Z^2)^.5;
            DISTANCE_FROM_EARTH_CENTER_TO_SUN=(SUN_X^2+SUN_Y^2+SUN_Z^2)^.5;
            
            MAX_SUN_ANGLE=acos(EARTH_RADIUS/DISTANCE_FROM_EARTH_CENTER_TO_SAT);
            MAX_SAT_ANGLE=acos(EARTH_RADIUS/DISTANCE_FROM_EARTH_CENTER_TO_SUN);
            
%             MAX_DISTANCE_TO_SATELLITE=EARTH_RADIUS*sin(MAX_SUN_ANGLE);
%             MAX_DISTANCE_TO_SUN=EARTH_RADIUS*sin(MAX_SAT_ANGLE);

            MAX_DISTANCE_TO_SATELLITE=DISTANCE_FROM_EARTH_CENTER_TO_SAT*sin(MAX_SAT_ANGLE);
            MAX_DISTANCE_TO_SUN=DISTANCE_FROM_EARTH_CENTER_TO_SUN*sin(MAX_SUN_ANGLE);
            
            ACTUAL_DISTANCE_TO_SATELLITE=((x-SAT_X)^2+(y-SAT_Y)^2+(z-SAT_Z)^2)^.5;
            ACTUAL_DISTANCE_TO_SUN=((x-SUN_X)^2+(y-SUN_Y)^2+(z-SUN_Z)^2)^.5;
            
            if ACTUAL_DISTANCE_TO_SATELLITE<MAX_DISTANCE_TO_SATELLITE && ACTUAL_DISTANCE_TO_SUN<MAX_DISTANCE_TO_SUN
                %visible to both satellite and the sun.
                scatter3(x,y,z,'red');    
            elseif ACTUAL_DISTANCE_TO_SATELLITE<MAX_DISTANCE_TO_SATELLITE %only visible to the satellite.
                scatter3(x,y,z,'black');
            elseif ACTUAL_DISTANCE_TO_SUN<MAX_DISTANCE_TO_SUN % only visible to the sun.
                scatter3(x,y,z,'yellow');
            else % not visible to the sun or the satellite
                scatter3(x,y,z,'green');
            end
            hold on;
            
            z=-z;
            
            DISTANCE_FROM_EARTH_CENTER_TO_SAT=(SAT_X^2+SAT_Y^2+SAT_Z^2)^.5;
            DISTANCE_FROM_EARTH_CENTER_TO_SUN=(SUN_X^2+SUN_Y^2+SUN_Z^2)^.5;
            
            MAX_SUN_ANGLE=acos(EARTH_RADIUS/DISTANCE_FROM_EARTH_CENTER_TO_SAT);
            MAX_SAT_ANGLE=acos(EARTH_RADIUS/DISTANCE_FROM_EARTH_CENTER_TO_SUN);

            MAX_DISTANCE_TO_SATELLITE=DISTANCE_FROM_EARTH_CENTER_TO_SAT*sin(MAX_SUN_ANGLE);
            MAX_DISTANCE_TO_SUN=DISTANCE_FROM_EARTH_CENTER_TO_SUN*sin(MAX_SAT_ANGLE);
            
            ACTUAL_DISTANCE_TO_SATELLITE=((x-SAT_X)^2+(y-SAT_Y)^2+(z-SAT_Z)^2)^.5;
            ACTUAL_DISTANCE_TO_SUN=((x-SUN_X)^2+(y-SUN_Y)^2+(z-SUN_Z)^2)^.5;
            
            if ACTUAL_DISTANCE_TO_SATELLITE<MAX_DISTANCE_TO_SATELLITE && ACTUAL_DISTANCE_TO_SUN<MAX_DISTANCE_TO_SUN
                %visible to both satellite and the sun.
                scatter3(x,y,z,'red');   
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
    
    tline = fgets(fileID);
    xlabel('x (meters)');
     ylabel('y (meters)');
      zlabel('z (meters)');
      
      
      


    saveas( gcf, int2str(imageNameCounter), 'jpg' );

      imageNameCounter=imageNameCounter+1;
    pause(2);
    
    close all;
end
