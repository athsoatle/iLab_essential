float amount(float* valueArray, int number) { /*sum of all elements of the array*/
  float quantity = 0;
  for (int i = 0; i < number; i++) {
    quantity += valueArray[i];
  }
  return quantity;
}

float meanValue(float* valueArray, int number) { /*mean value of all elements of the array*/
  return (amount(valueArray, number) / number);
}

float fMaxArr(float* valueArray, int number) { /*maximum element from all elements of the array*/
  float temp = 0;
  for (int i = 1; i < number; i++) {
    temp = fmax(valueArray[i], valueArray[i - 1]);
  }
  return temp;
}

float standardDeviation(float* valueArray, int number) { /*standard deviation*/
  float amount = 0;
  for (int i = 0; i < number; i++) {
    amount += pow((valueArray[i] - meanValue(valueArray, number)), 2);
  }
  return (sqrt(amount / (number - 1)));
}

float accidentalError(float* valueArray, int number) { /*accidential error*/
  return (standardDeviation(valueArray, number) / sqrt(number));
}

float absoluteError(float* valueArray, float* observationalError, int number, int index) { /*absolute error*/
  return (sqrt(pow(accidentalError(valueArray, number), 2) + pow(observationalError[index], 2)));
}

float leastSquaresMethod(float* valueArrayX, float* valueArrayY, int number) { /*least squares method realization*/
  float* valueArrayXY;
  float* valueArraySqX;
  valueArrayXY = (float*)calloc(number, sizeof(float));
  valueArraySqX = (float*)calloc(number, sizeof(float));
  for (int i = 0; i < number; i++) {
    valueArrayXY[i] = valueArrayX[i] * valueArrayY[i];
  }
  for (int i = 0; i < number; i++) {
    valueArraySqX[i] = pow(valueArrayX[i], 2);
  }
  return (meanValue(valueArrayXY, number) / meanValue(valueArraySqX, number));
  free(valueArrayXY);
  free(valueArraySqX);
}

float meanSquareAccidentalError(float* valueArrayX, float* valueArrayY, int number) { /*accidential error for least squares method*/
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
  return (sqrt(
      (pow(number, -1)) *
      (meanValue(valueArraySqY, number) / meanValue(valueArraySqX, number) -
       pow(leastSquaresMethod(valueArrayX, valueArrayY, number), 2))));
}

float meanSquareSystematicError(float* valueArrayX, float* valueArrayY, int number, float observationalErrorFirst, float observationalErrorSecond) { /*systematic error for least squares method*/
  return (leastSquaresMethod(valueArrayX, valueArrayY, number) *
          sqrt(pow((observationalErrorFirst / fMaxArr(valueArrayY, number)), 2) +
               pow((observationalErrorSecond / fMaxArr(valueArrayX, number)), 2)));
}

float absoluteErrorLSM(float* valueArrayX, float* valueArrayY, int number, float observationalErrorFirst, float observationalErrorSecond) { /*absolute error for least squares method*/
  return (sqrt(
      pow(meanSquareAccidentalError(valueArrayX, valueArrayY, number), 2) +
      pow(meanSquareSystematicError(valueArrayX, valueArrayY, number, observationalErrorFirst, observationalErrorSecond), 2)));
}

