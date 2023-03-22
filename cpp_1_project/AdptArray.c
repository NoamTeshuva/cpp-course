#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"

/*רציתי לציין שהשתמשתי ב צאט גיפטי00 על מנת לסדר ולבדוק את נכנונות הקוד*/
/*בנוסף נעזרתי בתשובה של המבחן לשאלת הזאת שהיתה במבחן*/
/*ובפונקציות שצריך לתת עותק קצת נתעקתי אז נעזרת בחבר יובל זיגדון 314648510*/
typedef struct AdptArray_
{
    int ArrSize;
    PElement *pElemArr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
} AdptArray, *PAdptArray;


PAdptArray CreateAdptArray(COPY_FUNC myCopyFunction, DEL_FUNC myDeleteFunction, PRINT_FUNC myPrintFunction)
{
    PAdptArray myArray = (PAdptArray)malloc(sizeof(AdptArray));
    if (myArray == NULL)
    {
        printf("Error allocating memory");
        return NULL;
    }

    // Assign a value to the ArrSize member
    myArray->ArrSize = 0;

    // Allocate memory for the pElemArr array
    myArray->pElemArr = (PElement *)calloc(1, (sizeof(PElement)));
    if (myArray->pElemArr == NULL)
    {
        free(myArray);
       printf("Error allocating memory");
        return NULL;
    }    
    myArray->delFunc = myDeleteFunction;
    myArray->copyFunc = myCopyFunction;
    myArray->printFunc = myPrintFunction;
    return myArray;
}

void DeleteAdptArray(PAdptArray arr)
{
    if (arr == NULL)
    {
        return;
    }
    // if (arr->pElemArr == NULL)
    // {
    //     return;
    // }
    for (int i = 0; i < arr->ArrSize; i++)
    {
        if (arr->pElemArr[i] != NULL)
        {
            arr->delFunc(arr->pElemArr[i]);
        }

    }
    free(arr->pElemArr);
    free(arr);
}


Result SetAdptArrayAt(PAdptArray arr, int a, PElement element)
{
    if (arr == NULL || a < 0)
    {
        return FAIL;
    }
    // check if reallocation is needed
   if (a >= arr->ArrSize)
{
    int newSize = a + 1;
    PElement *newElemArr = (PElement *)calloc(newSize, (sizeof(PElement)));
    if (newElemArr == NULL)
    {
        return FAIL;
    }
    // copy old elements into new array
    
    for (int i = 0; i < arr->ArrSize; i++)
    {
        if(arr->pElemArr[i] != NULL)
        {
        newElemArr[i] = arr->copyFunc(arr->pElemArr[i]);
        arr->delFunc(arr->pElemArr[i]);
        }
    }
    // free old array
    free(arr->pElemArr);
    // update struct members
    arr->pElemArr = newElemArr;
    arr->pElemArr[a] = arr->copyFunc(element);
    arr->ArrSize = newSize;
    return SUCCESS;
}
    else if (arr->pElemArr[a] != NULL)
    {
        arr->delFunc(arr->pElemArr[a]);
        // free(arr->pElemArr[a]);
        arr->pElemArr[a] = arr->copyFunc(element);
        return SUCCESS;
    } 
    arr->pElemArr[a] = arr->copyFunc(element);
    return SUCCESS;
}



PElement GetAdptArrayAt(PAdptArray arr, int a)
{
    if (arr == NULL)
    {
        return NULL;
    }
    if (arr->pElemArr[a] == NULL)
    {
        return NULL;
    }

    PElement retElement = arr->copyFunc(arr->pElemArr[a]);
    return retElement;
}

int GetAdptArraySize(PAdptArray arr)
{
    if (arr == NULL)
    {
        return -1;
    }
    return arr->ArrSize;
}

void PrintDB(PAdptArray arr)
{
    if (arr == NULL)
    {
        printf("Error: Array is NULL\n");
        return;
    }
    if (arr->pElemArr == NULL)
    {
        return;
    }
    for (int i = 0; i < arr->ArrSize; i++)
    {
        if (arr->pElemArr[i] != NULL)
        {
            arr->printFunc(arr->pElemArr[i]);

        }
    }
}
