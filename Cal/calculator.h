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



extern uchar KEY_CODE[] ;

extern uchar *ops;

/**
1 2 3 +
4 5 6 -
7 8 9 *
. 0 = /

( ) ~ c
*/

extern uchar index ;
extern uchar num ;
extern uchar bef ;
//	uchar start=0;

typedef enum CAL_STATE {
    INIT, CORE, ADDMINS, MULTIFIRST, DIVIDEFIRST, MULTISECOND, DIVIDESECOND, DONE, TOTAL_STATE
} CAL_STATE;
extern CAL_STATE state ;
extern unsigned char operator1, operator2;
extern unsigned char operator3, operator4;
extern double operand[3];
extern double operand1[3];
extern uchar QUEUE[MAX_LEN];


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



void My_state_INIT() {

    if ((num >= '0' && num <= '9') && (index < MAX_LEN)) {
        state = CORE;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '(') {
        operator3 = operator1;
        operator4 = operator2;
        operand1[0] = operand[0];
        operand1[1] = operand[1];
        operand1[2] = operand[2];
        state = DONE;
        showData(num);
    } else if (num == '~') {
        state = DONE;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '.') {
        state = CORE;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else {
        beep();
    }
}

void My_state_CORE() {
    if ((num >= '0' && num <= '9') && (index < MAX_LEN)) {

        state = CORE;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '+' || num == '-') {
        state = ADDMINS;
        PushOperArray(QUEUE, index, 0);
        //print(QUEUE,i);
        index = 0;

        operator1 = num;
        showData(num);
    } else if (num == '*') {
        state = MULTIFIRST;
        PushOperArray(QUEUE, index, 0);
        //print(QUEUE,i);
        index = 0;
        operator1 = num;
        showData(num);
    } else if (num == '/') {
        state = DIVIDEFIRST;
        PushOperArray(QUEUE, index, 0);
        //print(QUEUE,i);
        index = 0;
        operator1 = num;
        showData(num);
    } else if (num == '.') {
        state = CORE;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '=') {
        state = INIT;
        PushOperArray(QUEUE, index, 0);
        index = 0;
        showData(num);
        showAnswer();
        //clear();
    }
    else {
        beep();
    }
}

void My_state_ADDMINS() {
    if ((num >= '0' && num <= '9') && (index < MAX_LEN)){
        state = ADDMINS;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '+' || num == '-') {       //A+B+
        //caculate();
        state = ADDMINS;
        PushOperArray(QUEUE, index, 1);
        index = 0;
        firstCaculate();
        operator1 = num;
        showData(num);


    } else if (num == '*')  {
        state = MULTISECOND;
        PushOperArray(QUEUE, index, 1);
        // print(QUEUE,i);
        index = 0;
        //firstCaculate();
        operator2 = num;
        showData(num);
    } else if (num == '/') {
        state = DIVIDESECOND;
        PushOperArray(QUEUE, index, 1);
        //print(QUEUE,i);
        index = 0;
        // firstCaculate();
        operator2 = num;
        showData(num);
    } else if (num == '.') {
        state = ADDMINS;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '~') {
        state = ADDMINS;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '=') {
        state = INIT;
        PushOperArray(QUEUE, index, 1);
        index = 0;
        showData(num);
        firstCaculate();
        showAnswer();
        //clear();
    } else if (num == '(') {
        operator3 = operator1;
        operator4 = operator2;
        operand1[0] = operand[0];
        operand1[1] = operand[1];
        operand1[2] = operand[2];
        state = DONE;
        showData(num);
    } else if (num == ')') {
        state = ADDMINS;
        PushOperArray(QUEUE, index, 1);
        index = 0;
        firstCaculate();
        operand1[1] = operand[0];
        operand[0] = operand1[0];
        operand[1] = operand1[1];
        operand[2] = operand1[2];
        operator1 = operator3;
        operator2 = operator4;
        showData(num);
    } else {
        beep();
    }
}


void My_state_MULTIFIRST() {
    if ((num >= '0' && num <= '9') && (index < MAX_LEN)){
        state = MULTIFIRST;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '+' || num == '-') {      //A*B+ --> A+
        //caculate();
        state = ADDMINS;
        PushOperArray(QUEUE, index, 1);
        index = 0;
        firstCaculate();
        operator1 = num;
        showData(num);
    } else if (num == '*') {
        // caculate();
        state = MULTIFIRST;
        PushOperArray(QUEUE, index, 1);
        // print(QUEUE,i);
        index = 0;
        firstCaculate();
        operator1 = num;
        showData(num);
    } else if (num == '/') {
        //caculate();
        state = DIVIDEFIRST;
        PushOperArray(QUEUE, index, 1);
        // print(QUEUE,i);
        index = 0;
        firstCaculate();
        operator1 = num;
        showData(num);
    } else if (num == '.') {
        state = MULTIFIRST;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '~') {
        state = MULTIFIRST;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '=') {
        state = INIT;
        PushOperArray(QUEUE, index, 1);
        index = 0;
        showData(num);
        firstCaculate();
        showAnswer();
        //clear();
    } else if (num == '(') {
        operator3 = operator1;
        operator4 = operator2;
        operand1[0] = operand[0];
        operand1[1] = operand[1];
        operand1[2] = operand[2];
        state = DONE;
        showData(num);
    } else if (num == ')') {
        state = ADDMINS;
        PushOperArray(QUEUE, index, 1);
        index = 0;
        firstCaculate();
        operand1[1] = operand[0];
        operand[0] = operand1[0];
        operand[1] = operand1[1];
        operand[2] = operand1[2];
        operator1 = operator3;
        operator2 = operator4;
        showData(num);
    } else {
        beep();
    }
}

void My_state_DIVIDEFIRST() {
    if ((num >= '0' && num <= '9') && (index < MAX_LEN)) {
        state = DIVIDEFIRST;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '+' || num == '-') {
        // caculate();
        state = ADDMINS;
        PushOperArray(QUEUE, index, 1);
        //print(QUEUE,i);
        index = 0;
        firstCaculate();
        operator1 = num;
        showData(num);
    } else if (num == '*') {
        //caculate();
        state = MULTIFIRST;
        PushOperArray(QUEUE, index, 1);
        // print(QUEUE,i);
        index = 0;
        firstCaculate();
        operator1 = num;
        showData(num);
    } else if (num == '/') {
        //caculate();
        state = DIVIDEFIRST;
        PushOperArray(QUEUE, index, 1);
        // print(QUEUE,i);
        index = 0;
        firstCaculate();
        operator1 = num;
        showData(num);
    } else if (num == '.') {
        state = DIVIDEFIRST;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '~') {
        state = DIVIDEFIRST;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '=') {
        state = INIT;
        PushOperArray(QUEUE, index, 1);
        index = 0;
        showData(num);
        firstCaculate();
        showAnswer();
        //clear();
    } else if (num == '(') {
        operator3 = operator1;
        operator4 = operator2;
        operand1[0] = operand[0];
        operand1[1] = operand[1];
        operand1[2] = operand[2];
        state = DONE;
        showData(num);
    } else if (num == ')') {
        state = ADDMINS;
        PushOperArray(QUEUE, index, 1);
        index = 0;
        firstCaculate();
        operand1[1] = operand[0];
        operand[0] = operand1[0];
        operand[1] = operand1[1];
        operand[2] = operand1[2];
        operator1 = operator3;
        operator2 = operator4;
        showData(num);
    } else {
        beep();
    }
}

void My_state_MULTISECOND() {

    if ((num >= '0' && num <= '9') && (index < MAX_LEN)) {
        state = MULTISECOND;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '+' || num == '-') {
        // caculate();
        // caculate();
        state = ADDMINS;
        PushOperArray(QUEUE, index, 2);
        //print(QUEUE,i);
        index = 0;
        lastCaculate();
        firstCaculate();
        operator1 = num;
        showData(num);

    } else if (num == '*') {
        //caculate();
        state = MULTISECOND;
        PushOperArray(QUEUE, index, 2);
        // print(QUEUE,i);
        index = 0;
        lastCaculate();
        operator2 = num;
        showData(num);
    } else if (num == '/') {
        //caculate();
        state = DIVIDESECOND;
        PushOperArray(QUEUE, index, 2);
        // print(QUEUE,i);
        index = 0;
        lastCaculate();
        operator2 = num;
        showData(num);
    } else if (num == '.') {
        state = MULTISECOND;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '~') {
        state = MULTISECOND;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '=') {
        state = INIT;
        PushOperArray(QUEUE, index, 2);
        index = 0;
        showData(num);
        lastCaculate();
        firstCaculate();
        showAnswer();
        // clear();
    } else if (num == '(') {
        operator3 = operator1;
        operator4 = operator2;
        operand1[0] = operand[0];
        operand1[1] = operand[1];
        operand1[2] = operand[2];
        state = DONE;
        showData(num);
    } else if (num == ')') {
        state = ADDMINS;
        PushOperArray(QUEUE, index, 1);
        index = 0;
        lastCaculate();
        firstCaculate();
        operand1[2] = operand[0];
        operand[0] = operand1[0];
        operand[1] = operand1[1];
        operand[2] = operand1[2];
        operator1 = operator3;
        operator2 = operator4;
        showData(num);
    } else {
        beep();
    }
}

void My_state_DIVIDESECOND() {
    if ((num >= '0' && num <= '9') && (index < MAX_LEN)) {
        state = DIVIDESECOND;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '+' || num == '-') {
        state = ADDMINS;
        PushOperArray(QUEUE, index, 2);
        // print(QUEUE,i);
        index = 0;
        lastCaculate();
        firstCaculate();
        operator1 = num;
        showData(num);
    } else if (num == '*') {
        //caculate();
        state = MULTISECOND;
        PushOperArray(QUEUE, index, 2);
        // print(QUEUE,i);
        index = 0;
        lastCaculate();
        operator2 = num;
        showData(num);
    } else if (num == '/') {
        state = DIVIDESECOND;
        PushOperArray(QUEUE, index, 2);
        index = 0;
        lastCaculate();
        operator2 = num;
        showData(num);
    } else if (num == '.') {
        state = DIVIDESECOND;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '~') {
        state = DIVIDESECOND;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '=') {
        state = INIT;
        PushOperArray(QUEUE, index, 2);
        index = 0;
        showData(num);
        lastCaculate();
        firstCaculate();
        showAnswer();
        // clear();
    } else if (num == '(') {
        operator3 = operator1;
        operator4 = operator2;
        operand1[0] = operand[0];
        operand1[1] = operand[1];
        operand1[2] = operand[2];
        state = DONE;
        showData(num);
    } else if (num == ')') {
        state = ADDMINS;
        PushOperArray(QUEUE, index, 1);
        index = 0;
        lastCaculate();
        firstCaculate();
        operand1[2] = operand[0];
        operand[0] = operand1[0];
        operand[1] = operand1[1];
        operand[2] = operand1[2];
        operator1 = operator3;
        operator2 = operator4;
        showData(num);
    } else {
        beep();
    }
}


void My_state_DONE() {
    if ((num >= '0' && num <= '9') && (index < MAX_LEN)) {
        state = CORE;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '(') {
        operator3 = operator1;
        operator4 = operator2;
        operand1[0] = operand[0];
        operand1[1] = operand[1];
        operand1[2] = operand[2];
        state = DONE;
        showData(num);
    } else if (num == '~') {
        state = DONE;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else {
        beep();
    }
}
typedef void(*state_func)();

state_func states[TOTAL_STATE]={
    My_state_INIT,
    My_state_CORE,
    My_state_ADDMINS,
    My_state_MULTIFIRST,
    My_state_DIVIDEFIRST,
    My_state_MULTISECOND,
    My_state_DIVIDESECOND,
    My_state_DONE
};
#endif //AUTOMACHINEGENERATOR_CALCULATOR_H
