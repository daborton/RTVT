/*
 *  bNEVwr.cpp
 *  NEV Writer
 *
 *  Created by Jacob Komar on 9/27/10.
 *  Copyright 2010 Jacob Komar. All rights reserved.
 *
 */

#include "bNEVwr.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <QDateTime>
#include <QDate>

//#include "windows.h"

using namespace std;

FILE * NEV;
unsigned int numHead[] = {2};

bool startFlag = false;

bNEVwr::bNEVwr()
{
}

bNEVwr::bNEVwr(char file_name[], int num_channels, char typeGrid[], char comment[])
{
    NEV = fopen(file_name, "wb");
    char headerName[8] = {'N','E','U','R','A','L','E','V'};
    fwrite(headerName, 1, sizeof(headerName), NEV);

    unsigned short fileSpec[] = {0x0201,0};
    fwrite(fileSpec,sizeof(fileSpec),1,NEV);

    //64*16bits+8bytes header = 136

    unsigned int packetSize = 136;
    unsigned int timeResolution = 40000;
    unsigned int Fs = 40000;
    unsigned int headerSize = 400 + num_channels*32; // 336 + 32 (extended) + 32 (extended)
    unsigned int bytes[] = {headerSize,packetSize,timeResolution,Fs};
    fwrite(bytes,sizeof(bytes),1,NEV);

    QDate theDate = QDate::currentDate();
    short year = theDate.year();
    short month = theDate.month();
    short day = theDate.day();
    short dayOfWeek = theDate.dayOfWeek();

    QTime theTime = QTime::currentTime();
    short hour = theTime.hour();
    short minute = theTime.minute();
    short second = theTime.second();
    short msec = theTime.msec();

    //GetSystemTime(&time);
    //fwrite(&time,sizeof(time),1,NEV);

    //short systemTime[2] = {1111111,999999};
    //fwrite(fakeSYSTEMTIME,sizeof(fakeSYSTEMTIME),1,NEV);

    short timeToWrite[8] = {year,month,day,dayOfWeek,hour,minute,second,msec};
    fwrite(timeToWrite,sizeof(timeToWrite),1,NEV);

    char appName[32] = "BIC NEV Writer v1.0";
    fwrite(appName,sizeof(char),32,NEV);

    // Must be NULL terminated
    char *commentWrite = (char*)malloc(256);
    strcpy(commentWrite,comment);
    fwrite(commentWrite,sizeof(char),256,NEV);


    fwrite(numHead,sizeof(numHead),1,NEV);

    ////////////////////////////////////////////////

    char arrayName[8] = {'A','R','R','A','Y','N','M','E'};
    fwrite(arrayName, 1, sizeof(arrayName), NEV);

    char *gridWrite = (char*)malloc(24);
    strcpy(gridWrite,typeGrid);
    fwrite(gridWrite,sizeof(char),24,NEV);

    ////////////////////////////////////////////////

    char NSASName[8] = {'N','S','A','S','E','X','E','V'};
    fwrite(NSASName, 1, sizeof(NSASName), NEV);

    // No periodic generation - random
    unsigned short tempShort[1]= {0};
    fwrite(tempShort,sizeof(tempShort),1,NEV);

    // Digital Input Changes should not be ignored...
    unsigned char tempChar[1]= {1};
    fwrite(tempChar,sizeof(tempChar),1,NEV);

    //Analog Channel 1
    tempChar[0] = 2;
    fwrite(tempChar,sizeof(tempChar),1,NEV);
    tempShort[0] = 2500;
    fwrite(tempShort,sizeof(tempShort),1,NEV);

    //Analog Channel 2
    tempChar[0] = 2;
    fwrite(tempChar,sizeof(tempChar),1,NEV);
    tempShort[0] = 2500;
    fwrite(tempShort,sizeof(tempShort),1,NEV);

    //Analog Channel 3
    tempChar[0] = 2;
    fwrite(tempChar,sizeof(tempChar),1,NEV);
    tempShort[0] = 2500;
    fwrite(tempShort,sizeof(tempShort),1,NEV);

    //Analog Channel 4
    tempChar[0] = 2;
    fwrite(tempChar,sizeof(tempChar),1,NEV);
    tempShort[0] = 2500;
    fwrite(tempShort,sizeof(tempShort),1,NEV);

    //Analog Channel 5
    tempChar[0] = 2;
    fwrite(tempChar,sizeof(tempChar),1,NEV);
    tempShort[0] = 2500;
    fwrite(tempShort,sizeof(tempShort),1,NEV);

    char tempBlanks[6] = {0,0,0,0,0,0};
    fwrite(tempBlanks,sizeof(tempBlanks),1,NEV);
	
}

bNEVwr:: ~bNEVwr()
{
    fclose(NEV);
}


void bNEVwr::start()
{
    startFlag = true;
	//fopen(NEV,);
}

void bNEVwr::setupCh(unsigned short chan_num, unsigned char numUnits,
			 unsigned short digitFact, unsigned short energyTh,
			 unsigned short highThres, unsigned short lowThres)
{
    char NSASName[8] = {'N','E','U','E','V','W','A','V'};
    fwrite(NSASName, 1, sizeof(NSASName), NEV);

    fwrite(&chan_num,sizeof(chan_num),1,NEV);

    unsigned char connector;

    if(chan_num<38)
            connector = 1;
    else if (chan_num>=38 && chan_num < 75)
            connector = 2;
    else if (chan_num>=75 && chan_num < 112)
            connector = 3;
    else
            connector = 4;
    fwrite(&connector,sizeof(connector),1,NEV);

    unsigned char pin = chan_num-(37*(connector-1));
    fwrite(&pin,sizeof(pin),1,NEV);

    fwrite(&digitFact,sizeof(digitFact),1,NEV);
    fwrite(&energyTh,sizeof(energyTh),1,NEV);
    fwrite(&highThres,sizeof(highThres),1,NEV);
    fwrite(&lowThres,sizeof(lowThres),1,NEV);
    fwrite(&numUnits,sizeof(numUnits),1,NEV);

    // Length of a waveform sample - 2 bytes **per sample * 1.6ms * 40000samples/sec
    unsigned char bytesPWv = 2;//*(40000*0.0016)+8;
    fwrite(&bytesPWv,sizeof(bytesPWv),1,NEV);

    char tempBlanks[10] = {0,0,0,0,0,0,0,0,0,0};
    fwrite(tempBlanks,sizeof(tempBlanks),1,NEV);

    numHead[0]++;
    long int temp_pointer = ftell(NEV);
    fseek(NEV,332,SEEK_SET);
    fwrite(numHead,sizeof(numHead),1,NEV);
    fseek(NEV,temp_pointer,SEEK_SET);

}

void bNEVwr::wr(unsigned long timestamp, unsigned short channel, unsigned char unit, short (*waveForm)[64])
{
    if (!startFlag)
            return;

    fwrite(&timestamp,sizeof(unsigned long),1,NEV);
    //unsigned short packetID = 0;
    //fwrite(&packetID, sizeof(packetID),1,NEV);
    fwrite(&channel,sizeof(unsigned short),1,NEV);
    fwrite(&unit,sizeof(unsigned char),1,NEV);

    unsigned char resv = 0;
    fwrite(&resv,sizeof(resv),1,NEV);

    fwrite(*waveForm,1,64*sizeof(short),NEV);
	
}

void bNEVwr::wrE(unsigned long timestamp, unsigned char eventNum, bool set)
{
    if (!startFlag)
            return;

    fwrite(&timestamp,sizeof(timestamp),1,NEV);

    unsigned short packet = 0;
    fwrite(&packet,sizeof(packet),1,NEV);

    short newvalue;
    if(set)
            newvalue = 4999;
    else
            newvalue = 111;


    unsigned char reason;
    short setvalue[5] = {-222,-222,-222,-222,-222};


    if(eventNum == 1)
    {
            reason = 2;
            setvalue[0] = newvalue;
    }
    else if (eventNum == 2)
    {
            reason = 4;
            setvalue[1] = newvalue;
    }
    else if (eventNum == 3)
    {
            reason = 8;
            setvalue[2] = newvalue;
    }
    else if (eventNum == 4)
    {
            reason = 16;
            setvalue[3] = newvalue;
    }
    else if (eventNum == 5)
    {
            reason = 32;
            setvalue[4] = newvalue;
    }
    else
    {
            reason = 0;
            setvalue[0] = 666;
            setvalue[1] = 666;
            setvalue[2] = 666;
            setvalue[3] = 666;
            setvalue[4] = 666;
    }

    fwrite(&reason,sizeof(reason),1,NEV);

    unsigned char resv = 0;
    fwrite(&resv,sizeof(resv),1,NEV);

    unsigned short dig = 0;
    fwrite(&dig,sizeof(dig),1,NEV);

    for(int i = 0; i < 5; i++)
    {
            fwrite(&setvalue[i],sizeof(short),1,NEV);
    }
}

void bNEVwr::end()
{
    startFlag = false;
	fclose(NEV);
}