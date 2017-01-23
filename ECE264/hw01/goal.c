// vim: fileencoding=utf8 expandtab tabstop=4 shiftwidth=4
#include <stdio.h>

const int NUM_HOMEWORK = 15;
const float HOMEWORK_SCORES[] = {
    100,  // hw1
    100,  // hw2
    100,  // hw3
    100,  // hw4
     70,  // hw5
     80,  // hw6
    100,  // hw7
     80,  // hw8
    100,  // hw9
    100,  // hw10
     80,  // hw11
    100,  // hw12
     70,  // hw13
     80,  // hw14
    100   // hw15
};
const float HOMEWORK_WEIGHTS[] = {
    1.0,  // hw1
    1.0,  // hw2
    1.0,  // hw3
    1.0,  // hw4
    1.0,  // hw5
    1.0,  // hw6
    1.0,  // hw7
    1.0,  // hw8
    1.0,  // hw9
    1.0,  // hw10
    1.0,  // hw11
    1.0,  // hw12
    1.0,  // hw13
    1.0,  // hw14
    1.0   // hw15
};

const int NUM_QUIZZES = 16;
const float QUIZ_SCORES[] = {
      7,  // quiz1
      7,  // quiz2
      9,  // quiz3
     10,  // quiz4
      9,  // quiz5
      8,  // quiz6
     10,  // quiz7
      7,  // quiz8
      9,  // quiz9
      7,  // quiz10
      9,  // quiz11
      9,  // quiz12
      7,  // quiz13
      9,  // quiz14
      9,  // quiz15
     10   // quiz16
};

const int NUM_EXAMS = 3;
const float EXAM_SCORES[] = {
     80,  // exam1
     95,  // exam2
     75   // exam3
};
const float EXAM_WEIGHTS[] = {
   0.20,  // exam1
   0.25,  // exam2
   0.30   // exam3
};
const float QUIZZES_WEIGHT = 0.25;

const float BONUS_POINTS = 3.0;
const float PARTICIPATION_POINTS = 2.0;

float average(const float values[], const int num_values) {
    float sum = 0.0;
    for(int i = 0; i < num_values; i++) {
        sum += values[i];
    }
    return sum / num_values;
}

float weighted_sum(const float values[], const float weights[], const int num_values) {
    float sum = 0.0;
    for(int i = 0; i < num_values; i++) {
        sum += values[i] * weights[i];
    }
    return sum;
}

float weighted_average(const float values[], const float weights[], const int num_values) {
    return weighted_sum(values, weights, num_values) / num_values;
}

void print_grade(float summary_score) {
    if(summary_score >= 93) {
        printf("A+\n");
    }
    else if(summary_score >= 90) {
        printf("A\n");
    }
    else if(summary_score >= 87) {
        printf("A-\n");
    }
    else if(summary_score >= 83) {
        printf("B+\n");
    }
    else if(summary_score >= 80) {
        printf("B\n");
    }
    else if(summary_score >= 77) {
        printf("B-\n");
    }
    else if(summary_score >= 73) {
        printf("C+\n");
    }
    else if(summary_score >= 70) {
        printf("C\n");
    }
    else if(summary_score >= 67) {
        printf("C-\n");
    }
    else if(summary_score >= 63) {
        printf("D+\n");
    }
    else if(summary_score >= 60) {
        printf("D\n");
    }
    else if(summary_score >= 57) {
        printf("D-\n");
    }
    else {
        printf("F\n");
    }
}

int main(int argc, char *argv[]) {
    float quiz_score = average(QUIZ_SCORES, NUM_QUIZZES) * 10;
    float exam_score = weighted_sum(EXAM_SCORES, EXAM_WEIGHTS, NUM_EXAMS)
                     + quiz_score * QUIZZES_WEIGHT;
    float hw_score = weighted_average(HOMEWORK_SCORES, HOMEWORK_WEIGHTS, NUM_HOMEWORK);
    float summary_score = exam_score * 0.5
                        + hw_score   * 0.5
                        + PARTICIPATION_POINTS
                        + BONUS_POINTS;
    print_grade(summary_score);
    return 0;
}
