#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

FILE *fin;//file data reservation
FILE *fout;

int wire_length[3] = {20, 30, 50};//dynamic and static massives
int *e_current = NULL;
int *e_potential = NULL;
float *r = NULL;
float res[3];

void read_file(){//reading file
    float tempA, tempB;
    int i = 0;
    while(i < 30){
        fscanf(fin, "%f %f\n", &tempA, &tempB);
        e_current = (int*)realloc(e_current, (i + 1) * sizeof(int));
        e_potential = (int*)realloc(e_potential, (i + 1) * sizeof(int));
        r = (float*)realloc(r, ((i + 1) * sizeof(float)));
        e_potential[i] = tempA;
        e_current[i] = tempB;
        r[i] = tempA / tempB;
        i++;
    }
}

void print_file(){//printing in file
    for(int j = 0; j < 3; j++){
        float q = 0;
        fprintf(fout, "For wire_length = %d\n", wire_length[j]);
        for(int i = j * 10; i < 10 * (j + 1); i++){
                fprintf(fout, "\t Potential:%d Current:%d \n", e_potential[i], e_current[i]);
                fprintf(fout, "\t Resist: %f \n", r[i]);
                q += r[i];
        }
        res[j] = q/10;
        fprintf(fout, "\n\n");
        fprintf(fout, "For wire length = %d\n", wire_length[j]);
        fprintf(fout, "\t Mean value of resistance: %f \n\n", res[j]);
        }
}

int main(){
    fin = fopen("input.in", "r");//open files
    fout = fopen("output.out", "w");
    read_file();// reading
    print_file();// printing
    free(e_current);//free memory dynamic massives
    free(e_potential);
    fclose(fin);//close files
    fclose(fout);
    system("PAUSE");
    return 0;
}
