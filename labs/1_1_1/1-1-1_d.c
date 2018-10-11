#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>

FILE *fin;
FILE *fout;

//float *diameters = NULL;
float diameters[10];

float observationalError = 0.01;

float meanValue(float* valueArray, int number){
    float amount = 0;
    for(int i = 0; i < number; i++){
        amount += valueArray[i];
    }
    return(amount/number);
}

float standardDeviation(float* valueArray, int number){
    float amount = 0;
    for(int i = 0; i < number; i++){
        amount += pow((valueArray[i] - meanValue(valueArray, number)), 2);
    }
    return(sqrt(amount / (number - 1)));
}

float accidentialError(float* valueArray, int number){
    return(standardDeviation(valueArray, number)/(sqrt(number)));
}

float measurementError(float* valueArray, int number){
    return(sqrt(pow(observationalError, 2) + pow(accidentialError(valueArray, number), 2)));
}

void readFile(){
    int i = 0;
    float diameter;
    while(fscanf(fin, "%f\n", &diameter) != EOF){
        //diameters = (float*)realloc(diameters, (i + 1)*sizeof(float));
        diameters[i] = diameter;
        i++;
    }
}

void printFile(){
        fprintf(fout, "Mean value: %f\n", meanValue(diameters, sizeof(diameters)/sizeof(float)));
        fprintf(fout, "Standard deviation is: %f\n", standardDeviation(diameters, sizeof(diameters)/sizeof(float)));
        fprintf(fout, "Accidential Error is: %f\n", accidentialError(diameters, sizeof(diameters)/sizeof(float)));
        fprintf(fout, "Measurement Error is: %f\n", measurementError(diameters, sizeof(diameters)/sizeof(float)));
}

int main(){
    fin = fopen("input_d.in", "r");
    fout = fopen("output_d.out", "w");
    readFile();
    float meanValueOfDiameter = meanValue(diameters, sizeof(diameters)/sizeof(float));
    float standardDeviationOfDiameter = standardDeviation(diameters, sizeof(diameters)/sizeof(float));
    printFile();
    fclose(fin);
    fclose(fout);
    system("PAUSE");
    return 0;
}
