#include <stdio.h>
#include <stdlib.h>
#ifndef ADAPTARRAY_H
#define ADAPTARRAY_H

typedef void* PElement;

typedef void(*DEL_FUNC)(PElement);

typedef PElement(*COPY_FUNC)(PElement);

typedef void(*PRINT_FUNC)(PElement);

typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray, *PAdptArray;

typedef enum  {FAIL = 0, SUCCESS=1} Result;



PAdptArray CreateAdptArray(COPY_FUNC myCopyFunction, DEL_FUNC myDeleteFunction, PRINT_FUNC myPrintFunction)
{
    PAdptArray myArray = (PAdptArray) malloc(sizeof(AdptArray));
    if (myArray == NULL)
    {
        printf("Error allocating memory");
        return NULL;
    }

    // Assign a value to the ArrSize member
    myArray->ArrSize = 10;

    // Allocate memory for the pElemArr array
    myArray->pElemArr = (PElement*) malloc(sizeof(PElement) * myArray->ArrSize);
    myArray->delFunc = myDeleteFunction;
    myArray->copyFunc = myCopyFunction;
    myArray->printFunc = myPrintFunction;
    return myArray;
}


void DeleteAdptArray(PAdptArray arr){
 if (arr == NULL) {
        return;
    }
for (int i = 0; i < arr->ArrSize; i++) {
    if (arr->pElemArr[i]!=NULL){
    arr->delFunc(arr->pElemArr[i]);
    }
}
free(arr->pElemArr);
free (arr);
}

Result SetAdptArrayAt(PAdptArray arr, int a, PElement element) {
    if (arr == NULL || a < 0) {
        return FAIL;
    }

    // check if reallocation is needed
    if (a >= arr->ArrSize) {
        int newSize = a + 1;
        PElement* newElemArr = (PElement*) realloc(arr->pElemArr, sizeof(PElement) * newSize);
        if (newElemArr == NULL) {
            return FAIL;
        }
        arr->pElemArr = newElemArr;
        arr->ArrSize = newSize;
    }

    if (arr->pElemArr[a] != NULL) {
        arr->delFunc(arr->pElemArr[a]);
    }

    // create a copy of the element
    PElement newElement = arr->copyFunc(element);

    if (newElement == NULL) {
        return FAIL;
    }

    arr->pElemArr[a] = newElement;
    return SUCCESS;
}
 


PElement GetAdptArrayAt(PAdptArray arr, int a)
{
    PElement retElement= arr->pElemArr[a];
return retElement;
}

int GetAdptArraySize(PAdptArray arr) {
if (arr ==NULL)
{
    return -1;
}
return arr-> ArrSize;
}



void PrintDB(PAdptArray arr)
{
    if (arr == NULL)
    {
        printf("Error: Array is NULL\n");
        return;
    }

    printf("Printing array:\n");
    for (int i = 0; i < arr->ArrSize; i++)
    {
        if (arr->pElemArr[i] != NULL)
        {
           arr->printFunc(arr->pElemArr[i]);
        printf("succsses \n");
        }
    }
printf("succsses all \n");
}
#endif