/*
 *  bNEVwr.h
 *  NEV Writer
 *
 *  Created by Jacob Komar on 9/27/10.
 *  Copyright 2010 Jacob Komar. All rights reserved.
 *
 */

#ifndef bNEVwr_h_
#define bNEVwr_h_


class bNEVwr {
public:
	bNEVwr();
	bNEVwr(char file_name[], int num_channels, char typeArray[], char comment[]);
	~bNEVwr();
	void setupCh(unsigned short chan_num, unsigned char numUnits,
			unsigned short digitFact=3000, unsigned short energyTh=0,
			unsigned short highThres=100, unsigned short lowThres=-100);
	void start();
	void wr(unsigned long timestamp, unsigned short channel, unsigned char unit, short (*waveForm)[64]);
	void wrE(unsigned long timestamp, unsigned char eventNum, bool set);
	void end();
	
};


#endif // bNEVwr_h_