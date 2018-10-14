#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define M_PI           3.141592653589793238  /* pi */

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

FILE *fin;//file data reservation
FILE *fout;
FILE *finD;
FILE *foutD;

float **eCurrent = NULL;//array declaration
float **ePotential = NULL;
float **resists = NULL;
float *diameters = NULL;
float *eResistivity = NULL;
float *absER = NULL;
float meanRs[3];
float meanRsLSM[3];
float accRLSM[3];
float sysRLSM[3];
float absRLSM[3];

float observationalError[3] = { 0.007, 0.001, 0.001 };
float observationalErrorD[1] = { 0.01 };
float observationalErrorL[3] = { 1, 1, 1 };
int wireLength[3] = { 200, 300, 500 };

float observationalErrorV = 0.529;
float observationalErrorA = 2.5;
int number = 0;
int numberD = 0;
int numberER = 0;

void readFile() {
	int i = 0;
	float eCurrentTemp = 0, ePotentialTemp = 0;
	ePotential = (float**)malloc(3 * sizeof(float*));
	eCurrent = (float**)malloc(3 * sizeof(float*));
	resists = (float**)malloc(3 * sizeof(float*));
	for (int j = 0; j < 3; j++) {
		eCurrent[j] = (float*)malloc(10 * sizeof(float));
		ePotential[j] = (float*)malloc(10 * sizeof(float));
		resists[j] = (float*)malloc(10 * sizeof(float));
	}
	while (fscanf(fin, "%f %f\n", &ePotentialTemp, &eCurrentTemp) != EOF) {
		ePotential[i / 10][i - 10 * (i / 10)] = ePotentialTemp;
		eCurrent[i / 10][i - 10 * (i / 10)] = eCurrentTemp;
		resists[i / 10][i - 10 * (i / 10)] = ePotentialTemp / eCurrentTemp;
		i++;
	}
	float diameter = 0;
	int j = 0;
	while (fscanf(finD, "%f\n", &diameter) != EOF) {
		diameters = (float*)realloc(diameters, (j + 1) * sizeof(float));
		diameters[j] = diameter;
		j++;
	}
	number = i;
	numberD = j;
}

float amount(float* valueArray, int number) {
	float quantity = 0;
	for (int i = 0; i < number; i++) {
		quantity += valueArray[i];
	}
	return quantity;
}

float meanValue(float* valueArray, int number) {
	return(amount(valueArray, number) / number);
}

float fMaxArr(float* valueArray, int number) {
	float temp = 0;
	for (int i = 1; i < number; i++) {
		temp = max(valueArray[i], valueArray[i - 1]);
	}
	return temp;
}

float standardDeviation(float* valueArray, int number) {
	float amount = 0;
	for (int i = 0; i < number; i++) {
		amount += pow((valueArray[i] - meanValue(valueArray, number)), 2);
	}
	return(sqrt(amount / (number - 1)));
}

float accidentalError(float* valueArray, int number) {
	return(standardDeviation(valueArray, number) / sqrt(number));
}

float absoluteError(float* valueArray, float* observationalError, int number, int index) {
	return(sqrt(pow(accidentalError(valueArray, number), 2) + pow(observationalError[index], 2)));
}

float leastSquaresMethod(float* valueArrayX, float* valueArrayY, int number) {
	float* valueArrayXY;
	float* valueArraySqX;
	valueArrayXY = (float*)malloc(number * sizeof(float));
	valueArraySqX = (float*)malloc(number * sizeof(float));
	for (int i = 0; i < number; i++) {
		valueArrayXY[i] = valueArrayX[i] * valueArrayY[i];
	}
	for (int i = 0; i < number; i++) {
		valueArraySqX[i] = pow(valueArrayX[i], 2);
	}
	return(meanValue(valueArrayXY, number) / meanValue(valueArraySqX, number));
	free(valueArrayXY);
}

float meanSquareAccidentalError(float* valueArrayX, float* valueArrayY, int number) {
	float* valueArraySqX;
	float* valueArraySqY;
	valueArraySqX = (float*)malloc(number * sizeof(float));
	valueArraySqY = (float*)malloc(number * sizeof(float));
	for (int i = 0; i < number; i++) {
		valueArraySqX[i] = pow(valueArrayX[i], 2);
	}
	for (int i = 0; i < number; i++) {
		valueArraySqY[i] = pow(valueArrayY[i], 2);
	}
	return(sqrt((pow(number, -1)) * (meanValue(valueArraySqY, number) / meanValue(valueArraySqX, number) - pow(leastSquaresMethod(valueArrayX, valueArrayY, number), 2))));
}

float meanSquareSystematicError(float* valueArrayX, float* valueArrayY, int number) {
	return(leastSquaresMethod(valueArrayX, valueArrayY, number) * sqrt(pow((observationalErrorV / fMaxArr(valueArrayY, number)), 2) + pow((observationalErrorA / fMaxArr(valueArrayX, number)), 2)));
}

float absoluteErrorLSM(float* valueArrayX, float* valueArrayY, int number) {
	return(sqrt(pow(meanSquareAccidentalError(valueArrayX, valueArrayY, number), 2) + pow(meanSquareSystematicError(valueArrayX, valueArrayY, number), 2)));
}

float absoluteErrorResistivity(int index) {
	return(eResistivity[index] * sqrt(pow(absRLSM[index] / meanRsLSM[index], 2) + pow(absoluteError(diameters, observationalErrorD, numberD, 0) / meanValue(diameters, numberD), 2) + pow(observationalErrorL[index]/wireLength[index], 2)));
}

void printFile() {
	for (int i = 0; i < sizeof(wireLength) / sizeof(float); i++) {
		fprintf(fout, "For wire length = %i\n", wireLength[i]);
		fprintf(fout, "\tMean value of Resistance:%f\n\tMean value of Resistance according to Least squares method:%f\n\tLSM Accidental error:%f\n\tLSM systematic error:%f\n\tLSM absolute error:%f\n", meanRs[i], meanRsLSM[i], accRLSM[i], sysRLSM[i], absRLSM[i]);
	}
	fprintf(fout, "\nFor diameter:\n\tMean value: %f\n\tStandard Deviation:%f\n\tAccidential Error:%f\n\tAbsolute Error:%f\n\n", meanValue(diameters, numberD), standardDeviation(diameters, numberD), accidentalError(diameters, numberD), absoluteError(diameters, observationalErrorD, numberD, 0));
	for (int i = 0; i < sizeof(wireLength) / sizeof(float); i++) {
		fprintf(fout, "For wire length:%i\n\t", wireLength[i]);
		fprintf(fout, "Electric Resistivity:%f\n\tAbsolute Error of Electric Resistivity:%f\n\n", eResistivity[i], absER[i]);
	}
	fprintf(fout, "\t\tConclusion:\n\t\t\tElectric Resistivity = %f +- %f Ohm*Centimetre", (meanValue(eResistivity, numberER) * 1000), (meanValue(absER, numberER) * 1000));
}

int main() {
	fin = fopen("input.in", "r");//open files
	finD = fopen("inputD.in", "r");
	fout = fopen("output.out", "w");
	readFile();
	for (int i = 0; i < number / 10; i++) {
		meanRs[i] = meanValue(resists[i], number / 3);
		meanRsLSM[i] = leastSquaresMethod(eCurrent[i], ePotential[i], number / 3);
		accRLSM[i] = meanSquareAccidentalError(eCurrent[i], ePotential[i], number / 3);
		sysRLSM[i] = meanSquareSystematicError(eCurrent[i], ePotential[i], number / 3);
		absRLSM[i] = absoluteErrorLSM(eCurrent[i], ePotential[i], number / 3);
	}
	for (int i = 0; i < sizeof(meanRsLSM) / sizeof(float*); i++) {
		eResistivity = (float*)realloc(eResistivity, (i + 1) * sizeof(float));
		eResistivity[i] = (M_PI * meanRsLSM[i] * pow(meanValue(diameters, numberD), 2)) / (4 * wireLength[i]);
		absER = (float*)realloc(absER, (i + 1) * sizeof(float));
		absER[i] = absoluteErrorResistivity(i);
		numberER++;
	}
	printFile();// printing
	free(eCurrent);//free memory dynamic massives
	free(ePotential);
	fclose(fin);//close files
	fclose(finD);
	fclose(fout);
	system("PAUSE");
	return 0;
}