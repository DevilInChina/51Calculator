void My_state_ONE() {

    if ((num >= '0' && num <= '9') && (index < MAX_LEN)) {
        state = TWO;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '(') {
        operator3 = operator1;
        operator4 = operator2;
        operand1[0] = operand[0];
        operand1[1] = operand[1];
        operand1[2] = operand[2];
        state = EIGHT;
        showData(num);
    } else if (num == '~') {
        state = EIGHT;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '.') {
        state = TWO;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else {
        beep();
    }
}

void My_state_TWO() {
    if ((num >= '0' && num <= '9') && (index < MAX_LEN)) {

        state = TWO;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '+' || num == '-') {
        state = THREE;
        PushOperArray(QUEUE, index, 0);
        //print(QUEUE,i);
        index = 0;

        operator1 = num;
        showData(num);
    } else if (num == '*') {
        state = FOUR;
        PushOperArray(QUEUE, index, 0);
        //print(QUEUE,i);
        index = 0;
        operator1 = num;
        showData(num);
    } else if (num == '/') {
        state = FIVE;
        PushOperArray(QUEUE, index, 0);
        //print(QUEUE,i);
        index = 0;
        operator1 = num;
        showData(num);
    } else if (num == '.') {
        state = TWO;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '=') {
        state = ONE;
        PushOperArray(QUEUE, index, 0);
        index = 0;
        showData(num);
        showAnswer();
        //clear();
    } else {
        beep();
    }
}

void My_state_THREE() {
    if ((num >= '0' && num <= '9') && (index < MAX_LEN)) {
        state = THREE;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '+' || num == '-') {       //A+B+
        //caculate();
        state = THREE;
        PushOperArray(QUEUE, index, 1);
        index = 0;
        firstCaculate();
        operator1 = num;
        showData(num);


    } else if (num == '*') {
        state = SIX;
        PushOperArray(QUEUE, index, 1);
        // print(QUEUE,i);
        index = 0;
        //firstCaculate();
        operator2 = num;
        showData(num);
    } else if (num == '/') {
        state = SEVEN;
        PushOperArray(QUEUE, index, 1);
        //print(QUEUE,i);
        index = 0;
        // firstCaculate();
        operator2 = num;
        showData(num);
    } else if (num == '.') {
        state = THREE;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '~') {
        state = THREE;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '=') {
        state = ONE;
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
        state = EIGHT;
        showData(num);
    } else if (num == ')') {
        state = THREE;
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


void My_state_FOUR() {
    if ((num >= '0' && num <= '9') && (index < MAX_LEN)) {
        state = FOUR;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '+' || num == '-') {      //A*B+ --> A+
        //caculate();
        state = THREE;
        PushOperArray(QUEUE, index, 1);
        index = 0;
        firstCaculate();
        operator1 = num;
        showData(num);
    } else if (num == '*') {
        // caculate();
        state = FOUR;
        PushOperArray(QUEUE, index, 1);
        // print(QUEUE,i);
        index = 0;
        firstCaculate();
        operator1 = num;
        showData(num);
    } else if (num == '/') {
        //caculate();
        state = FIVE;
        PushOperArray(QUEUE, index, 1);
        // print(QUEUE,i);
        index = 0;
        firstCaculate();
        operator1 = num;
        showData(num);
    } else if (num == '.') {
        state = FOUR;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '~') {
        state = FOUR;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '=') {
        state = ONE;
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
        state = EIGHT;
        showData(num);
    } else if (num == ')') {
        state = THREE;
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

void My_state_FIVE() {
    if ((num >= '0' && num <= '9') && (index < MAX_LEN)) {
        state = FIVE;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '+' || num == '-') {
        // caculate();
        state = THREE;
        PushOperArray(QUEUE, index, 1);
        //print(QUEUE,i);
        index = 0;
        firstCaculate();
        operator1 = num;
        showData(num);
    } else if (num == '*') {
        //caculate();
        state = FOUR;
        PushOperArray(QUEUE, index, 1);
        // print(QUEUE,i);
        index = 0;
        firstCaculate();
        operator1 = num;
        showData(num);
    } else if (num == '/') {
        //caculate();
        state = FIVE;
        PushOperArray(QUEUE, index, 1);
        // print(QUEUE,i);
        index = 0;
        firstCaculate();
        operator1 = num;
        showData(num);
    } else if (num == '.') {
        state = FIVE;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '~') {
        state = FIVE;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '=') {
        state = ONE;
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
        state = EIGHT;
        showData(num);
    } else if (num == ')') {
        state = THREE;
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

void My_state_SIX() {

    if ((num >= '0' && num <= '9') && (index < MAX_LEN)) {
        state = SIX;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '+' || num == '-') {
        // caculate();
        // caculate();
        state = THREE;
        PushOperArray(QUEUE, index, 2);
        //print(QUEUE,i);
        index = 0;
        lastCaculate();
        firstCaculate();
        operator1 = num;
        showData(num);

    } else if (num == '*') {
        //caculate();
        state = SIX;
        PushOperArray(QUEUE, index, 2);
        // print(QUEUE,i);
        index = 0;
        lastCaculate();
        operator2 = num;
        showData(num);
    } else if (num == '/') {
        //caculate();
        state = SEVEN;
        PushOperArray(QUEUE, index, 2);
        // print(QUEUE,i);
        index = 0;
        lastCaculate();
        operator2 = num;
        showData(num);
    } else if (num == '.') {
        state = SIX;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '~') {
        state = SIX;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '=') {
        state = ONE;
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
        state = EIGHT;
        showData(num);
    } else if (num == ')') {
        state = THREE;
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

void My_state_SEVEN() {
    if ((num >= '0' && num <= '9') && (index < MAX_LEN)) {
        state = SEVEN;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '+' || num == '-') {
        state = THREE;
        PushOperArray(QUEUE, index, 2);
        // print(QUEUE,i);
        index = 0;
        lastCaculate();
        firstCaculate();
        operator1 = num;
        showData(num);
    } else if (num == '*') {
        //caculate();
        state = SIX;
        PushOperArray(QUEUE, index, 2);
        // print(QUEUE,i);
        index = 0;
        lastCaculate();
        operator2 = num;
        showData(num);
    } else if (num == '/') {
        state = SEVEN;
        PushOperArray(QUEUE, index, 2);
        index = 0;
        lastCaculate();
        operator2 = num;
        showData(num);
    } else if (num == '.') {
        state = SEVEN;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '~') {
        state = SEVEN;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '=') {
        state = ONE;
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
        state = EIGHT;
        showData(num);
    } else if (num == ')') {
        state = THREE;
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


void My_state_EIGHT() {
    if ((num >= '0' && num <= '9') && (index < MAX_LEN)) {
        state = TWO;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else if (num == '(') {
        operator3 = operator1;
        operator4 = operator2;
        operand1[0] = operand[0];
        operand1[1] = operand[1];
        operand1[2] = operand[2];
        state = EIGHT;
        showData(num);
    } else if (num == '~') {
        state = EIGHT;
        QUEUE[index] = num;
        showData(num);
        index++;
    } else {
        beep();
    }
}
