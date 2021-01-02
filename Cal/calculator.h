//
// Created by Administrator on 2021/1/2.
//

#ifndef AUTOMACHINEGENERATOR_CALCULATOR_H
#define AUTOMACHINEGENERATOR_CALCULATOR_H
#include <reg51.h>
#include "stdio.h"
#include "calculator.h"
#include <intrins.h>
#include <math.h>

#define uchar unsigned char
#define uint unsigned int
#define  MAX_LEN 16
sbit EN = P2 ^7;
sbit RS = P2 ^6;
sbit RW = P2 ^5;

sbit K1 = P1 ^0;
sbit K2 = P1 ^1;
sbit K3 = P1 ^2;
sbit K4 = P1 ^3;
sbit K5 = P1 ^4;
sbit K6 = P1 ^5;
sbit K7 = P1 ^6;
sbit K8 = P1 ^7;
sbit BEEP = P2 ^5;

uchar KEY_CODE[] = {
        0xee, 0xde, 0xbe, 0x7e,
        0xed, 0xdd, 0xbd, 0x7d,
        0xeb, 0xdb, 0xbb, 0x7b,
        0xe7, 0xd7, 0xb7, 0x77
};

uchar *ops = "123+456-789*.0=/";

/**
1 2 3 +
4 5 6 -
7 8 9 *
. 0 = /

( ) ~ c
*/

uchar index = 0;
uchar num = 0xff;
uchar bef = 0xff;
//	uchar start=0;

typedef enum CAL_STATE {
    ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, TOTAL_STATE
} CAL_STATE;
CAL_STATE state = ONE;
unsigned char operator1, operator2;
unsigned char operator3, operator4;
double operand[3];
double operand1[3];
uchar QUEUE[MAX_LEN];

void scanf2(uchar *var);

void delay5MS();

void delay100MS();

void writeCMD(uchar com);

void showData(uchar dat);

void init();

void clear();

void stateChange();

void PushOperArray(uchar *arr, int i, int locationOperand);

void firstCaculate();

void lastCaculate();

void beep();

void showAnswer();


#endif //AUTOMACHINEGENERATOR_CALCULATOR_H
