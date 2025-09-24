#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//Function to read and write the values to a given pointer
int readInput(char* str, char** strPtr, bool inputState, int* numEle, int* idx, int key){

    
    if(key < 127 && *idx < *numEle - 1  && inputState && key != 0)
    {
        str[(*idx)++] = (char)key;
        return 0;
    }

    else if( key == KEY_BACKSPACE)
    { 

        //Preventing from decreasing the index below 0
        if(*idx > 0)
        {
            *idx = *idx - 1;
            str[*idx] = '\0';
        }
    }

    else if(*idx == *numEle - 1 && inputState)
    {
        printf("Increasing the required memory...\n");
        *numEle = *numEle + 100;
        strPtr = realloc(str, *numEle);
        return 0;
    }

   /* else
    {
        printf("DANGER idx out of bounds for pointer!");
        return 0;
    }*/

    return 0;

}

int main()
{
    int width = 800;
    int height = 800;

    //Initializing the GUI window
    InitWindow(width, height, "Testing");
    SetTargetFPS(60);

    //Variables for text
    int key;            //Storing the pressed key
    int numEle = 100;     //Number of elements for allocation
    int idx = 0;        //Index for looping the pointer
    int fontSize = 20;


    //Variables for button
    int bWidth = 300;
    int bHeight = 100;
    
    int bPosX = (width - bWidth) / 2;
    int bPosY = height - bHeight - 100;

    //Location for the text
    int tCentreX = bPosX + (bWidth / 2);
    int tCentreY = bPosY + (bHeight / 2);

    char bText1[] = "Click to start inputting";
    char bText2[] = "Click to end inputting";

    bool inputState = false;    //Checker for  reading input

    //Allocating memory for text 
    char* str = calloc(numEle, sizeof(char)); 


    while(WindowShouldClose() == false)
    {
        key = GetKeyPressed();

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            inputState = inputState == false ? true : false ;             
        }

        //Calling the input reading function
        readInput( str, &str, inputState, &numEle, &idx, key);
        
        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangle(bPosX, bPosY, bWidth, bHeight, inputState ? GREEN : BLUE);

        //State rendering
        if(inputState == true)
            DrawText(bText2, tCentreX - (MeasureText(bText2, fontSize) / 2), tCentreY - (fontSize / 2), fontSize, WHITE);
        else
            DrawText(bText1, tCentreX - (MeasureText(bText1, fontSize) / 2), tCentreY - (fontSize / 2), fontSize, WHITE);

        //Displaying the text
        DrawText(str, 400 - (MeasureText(str, fontSize) / 2), 400, fontSize, YELLOW);

        

        EndDrawing();
    }

    //Freeing the memory
    free(str);

    //Closing the window
    CloseWindow();

}