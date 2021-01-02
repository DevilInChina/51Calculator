#include "calculator.h"



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
uchar index = 0;
uchar num = 0xff;
uchar bef = 0xff;
//	uchar start=0;


CAL_STATE state = INIT;
unsigned char operator1, operator2;
unsigned char operator3, operator4;
double operand[3];
double operand1[3];
uchar QUEUE[MAX_LEN];


void main() {
    init();
    while (1) {
        bef = num;
        scanf2(&num);
        stateChange();
    }
}


void stateChange() {
    states[state]();
}

void scanf2(uchar *var) {
    uchar temp;
    int q = 1;
    temp = q;
    q = 0;
    while (1) {
        P3 = 0xff;
        if (K1 == 0) {
            delay100MS();
            if (K1 == 0) {
                while (!K1);
                *var = '(';
                break;
            }
        }
        if (K2 == 0) {
            delay100MS();
            if (K2 == 0) {
                while (!K2);
                *var = ')';
                break;
            }
        }
        if (K3 == 0) {
            delay100MS();
            if (K3 == 0) {
                while (!K3);
                *var = '~';
                break;
            }
        }
        if (K4 == 0) {
            delay100MS();
            if (K4 == 0) {
                while (!K4);
                clear();
                state = INIT;
                index = 0;
                num = '+';
                break;
            }
        }

        P3 = 0x0f;
        if (P3 != 0x0f) {
            delay100MS();
            temp = P3;
            P3 = 0xf0;
            if (P3 != 0xf0) {
                num = temp | P3;
                for (q = 0; q < 16; q++) if (num == KEY_CODE[q]) *var = ops[q];
                break;
            }
        }

    }
    if (state == INIT) clear();
}

void PushOperArray(uchar *arr, int i, int locationOperand) {
    if (bef != ')') {
        int n = 0;
        double total = 0;
        uchar j = 0;
        if (arr[0] == '~') {
            for (j = 1; j < i; j++) {
                if (arr[j] == 0x2e)
                    n = i - j - 1;
                else total = total * 10 + (arr[j] - 0x30);
            }
            for (; n > 0; n--)
                total /= 10;
            operand[locationOperand] = sqrt(total);
        } else {
            for (j = 0; j < i; j++) {
                if (arr[j] == 0x2e)
                    n = i - j - 1;
                else total = total * 10 + (arr[j] - 0x30);
            }
            for (; n > 0; n--)
                total /= 10;
            operand[locationOperand] = total;
        }

    }
}

void delay5MS() {
    int n = 3000;
    while (n--);
}

void delay100MS() {
    uint n = 8000;
    while (n--);
}

void writeCMD(uchar com) {
    P0 = com;
    RS = 0;
    RW = 0;
    delay5MS();
    EN = 1;
    delay5MS();
    EN = 0;
}

void showData(uchar dat) {
    // EN = 1;
    RW = 1;
    RS = 0;
    if (P0 == 0x11) {
        writeCMD(0xC0);
    }
    P0 = dat;
    RS = 1;
    RW = 0;
    EN = 1;
    delay5MS();
    EN = 0;
}

void init() {
    EN = 0;
    writeCMD(0x38);
    writeCMD(0x0e);
    writeCMD(0x06);
    writeCMD(0x01);
    writeCMD(0x80);
}

void clear() {
    EN = 0;
    writeCMD(0x01);
}

void firstCaculate() {
    double num1, num2, ans;
    char str[] = "ERROR";
    int m = 0;
    unsigned char op;
    num1 = operand[0];
    num2 = operand[1];
    op = operator1;
    switch (op) {
        case '+':
            ans = num1 + num2;
            break;
        case '-':
            ans = num1 - num2;
            break;
        case '*':
            ans = num1 * num2;
            break;
        case '/':
            if (operand[1] != 0) {
                ans = num1 / num2;
            } else {
                delay5MS();
                clear();
                while (1) {
                    if (str[m] == '\0')
                        break;
                    else {
                        showData(str[m]);
                        m++;
                    }
                }
                state = INIT;
            }
            break;
    }

    operand[0] = ans;
}

void lastCaculate() {
    double num1, num2, ans;
    unsigned char op;
    char str[] = "ERROR";
    int m = 0;
    num1 = operand[1];
    num2 = operand[2];
    op = operator2;
    switch (op) {
        case '+':
            ans = num1 + num2;
            break;
        case '-':
            ans = num1 - num2;
            break;
        case '*':
            ans = num1 * num2;
            break;
        case '/':
            if (operand[2] != 0) {
                ans = num1 / num2;
            } else {
                delay5MS();
                clear();
                while (1) {
                    if (str[m] == '\0')
                        break;
                    else {
                        showData(str[m]);
                        m++;
                    }
                }
                state = INIT;
            }
            break;
    }
    operand[1] = ans;
}


void showAnswer() {
    double ans = operand[0];
    char str[MAX_LEN * 2];
    uchar m;
    sprintf(str, "%g", ans);
    m = 0;
    while (str[m++]);
    writeCMD(0x4f + 0x80);
    writeCMD(0x04);
    --m;
    while (m--) showData(str[m]);
}

void beep() {
    unsigned char q, j;
    for (q = 0; q < 100; q++) {
        BEEP = !BEEP;
        for (j = 0; j < 250; j++)
            _nop_();
    }
    BEEP = 1;
}
