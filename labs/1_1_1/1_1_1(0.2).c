#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>

FILE *fin;//file data reservation
FILE *fout;

int wireLength[3] = {20, 30, 50};//dynamic and static massives
int *eCurrent = NULL;
int *ePotential = NULL;
float r[30];
float r1[10];
float r2[10];
float r3[10];
float meanRs[3];

float observationalError[3] = {0.007, 0.001, 0.001};



void readFile(){//reading file
    int i = 0;
    float eCurrentTemp, ePotentialTemp;
    while(fscanf(fin, "%f %f\n", &ePotentialTemp, &eCurrentTemp) != EOF){
        //diameters = (float*)realloc(diameters, (i + 1)*sizeof(float));
        r[i] = ePotentialTemp/eCurrentTemp;
        eCurrent = (int*)realloc(eCurrent, (i + 1) * sizeof(int));
        ePotential = (int*)realloc(ePotential, (i + 1) * sizeof(int));
        ePotential[i] = ePotentialTemp;
        eCurrent[i] = eCurrentTemp;
        i++;
    }
}

void arrayDistribution(){
    for(int i = 0; i < 10; i++){
        r1[i] = r[i];
    }
    for(int i = 10; i < 20; i++){
        r2[i - 10] = r[i];
    }
    for(int i = 20; i < 30; i++){
        r3[i - 20] = r[i];
    }
}

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

float absoluteError(float a, float b){
    return(sqrt(pow(a,2)+pow(b,2)));
}

void printFile(){//printing in file
     for(int j = 0; j < 3; j++){
        fprintf(fout, "For wire length = %d\n", wireLength[j]);
        for(int i = j * 10; i < 10 * (j + 1); i++){
                fprintf(fout, "\t Potential:%d Current:%d \n", ePotential[i], eCurrent[i]);
                fprintf(fout, "\t Resist: %f \n", r[i]);
        }
        fprintf(fout, "\n\n");
        fprintf(fout, "For wire length = %d\n", wireLength[j]);
        fprintf(fout, "\t Mean value of resistance: %f \n\n", meanRs[j]);
        if(j == 0){
            fprintf(fout, "\t Accidential error of resistance: %f \n\n", standardDeviation(r1, sizeof(r1)/sizeof(float)));
            fprintf(fout, "\t Sistematical error of resistance: %f \n\n", observationalError[0]);
            fprintf(fout, "\t Absolute error of resistance: %f \n\n", absoluteError(observationalError[0], standardDeviation(r1, sizeof(r1)/sizeof(float))));
        }
        if(j == 1){
            fprintf(fout, "\t Accidential error of resistance: %f \n\n", standardDeviation(r2, sizeof(r2)/sizeof(float)));
            fprintf(fout, "\t Sistematical error of resistance: %f \n\n", observationalError[1]);
            fprintf(fout, "\t Absolute error of resistance: %f \n\n", absoluteError(observationalError[1], standardDeviation(r2, sizeof(r2)/sizeof(float))));
        }
        if(j == 2){
            fprintf(fout, "\t Accidential error of resistance: %f \n\n", standardDeviation(r3, sizeof(r3)/sizeof(float)));
            fprintf(fout, "\t Sistematical error of resistance: %f \n\n", observationalError[2]);
            fprintf(fout, "\t Absolute error of resistance: %f \n\n", absoluteError(observationalError[2], standardDeviation(r3, sizeof(r3)/sizeof(float))));
        }
    }
}

int main(){
    fin = fopen("input.in", "r");//open files
    fout = fopen("output.out", "w");
    readFile();// reading
    arrayDistribution();
    meanRs[0] = meanValue(r1, sizeof(r1)/sizeof(float));
    meanRs[1] = meanValue(r2, sizeof(r2)/sizeof(float));
    meanRs[2] = meanValue(r3, sizeof(r3)/sizeof(float));
    printFile();// printing
    free(eCurrent);//free memory dynamic massives
    free(ePotential);
    fclose(fin);//close files
    fclose(fout);
    system("PAUSE");
    return 0;
}
