%This program is meant to provide a graphical representation of what's
%going on in the C++ flux calculator5. I'm using
%this as a graphical representation of what's going on in the other
%program.
clc;
clear all;
close all;
EARTH_RADIUS=6371000;

SUN_X=3.581118709561659*10^10;
SUN_Y=-1.308927327368016*10^11;
SUN_Z=-5.677199113568006*10^10;

albedo=.3

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
    
    SAT_VECT=[SAT_X,SAT_Y,SAT_Z];
    SUN_VECT=[SUN_X,SUN_Y,SUN_Z];
    
    [unitVectMatrix,dFluxMatrix]=optimizedCalculation_FINAL(SAT_VECT,SUN_VECT,albedo)
end
