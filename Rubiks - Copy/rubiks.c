/*
 * Filename:    RubiksCube.c
 * Author:      Christopher Bergsveinsson
 * Date:        9/8/2024
 *
 * Simulates a Rubiks cube
 *

 Format for the array:

 Side 0: Default is front and white
 W W W
 W W W
 W W W

 Side 1: Default is left and green
 G G G
 G G G
 G G G

 Side 2: Default is right and blue
 B B B
 B B B
 B B B

 Side 3: Default is top and orange
 O O O
 O O O
 O O O

 Side 4: Default is bottom and red
 R R R
 R R R
 R R R

 Side 5: Default is rear and yellow
 Y Y Y
 Y Y Y
 Y Y Y
 */

#include <stdio.h>
#include <msp430.h>
#include <stdbool.h>

extern char rubiks[6][3][3] =
        { { { 'W', 'W', 'W' }, { 'W', 'W', 'W' }, { 'W', 'W', 'W' } }, {
                { 'G', 'G', 'G' }, { 'G', 'G', 'G' }, { 'G', 'G', 'G' } },
          { { 'B', 'B', 'B' }, { 'B', 'B', 'B' }, { 'B', 'B', 'B' } }, {
                  { 'O', 'O', 'O' }, { 'O', 'O', 'O' }, { 'O', 'O', 'O' } },
          { { 'R', 'R', 'R' }, { 'R', 'R', 'R' }, { 'R', 'R', 'R' } }, {
                  { 'Y', 'Y', 'Y' }, { 'Y', 'Y', 'Y' }, { 'Y', 'Y', 'Y' } } }; // the array for all of the rubik's characters

extern int rmap[6][3][3] =
          { { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } },
          { { 10, 11, 12 }, { 13, 14, 15 }, { 16, 17, 18 } },
          { { 19, 20, 21 }, { 22, 23, 24 }, { 25, 26, 27 } },
          { { 28, 29, 30 }, { 31, 32, 33 }, { 34, 35, 36 } },
          { { 37, 38, 39 }, { 40, 41, 42 }, { 43, 44, 45 } },
          { { 46, 47, 48 }, { 49, 50, 51 }, { 52, 53, 54 } } }; // array for the mapping of all rubik's characters

void turn(char, int, char, int); // initialization of the turn function
void printSides(); // initialization of the function for printing all sides
void printTS(); // initialization of the function for the printing of temporary sides
void rotate(int side, char cw); // initialization of the rotate function

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stops watchdog timer

    printSides();

    return 0;
}

extern char tempRoC[12] = { 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a' }; // temporary row or column to facilitate transfer

extern int tempSide = 0; // temporary side to facilitate transfer

void turncw(int side, char roc, int numroc); // initialization of turn clockwise function
void turnccw(int side, char roc, int numroc); // initialization of turn counter-clockwise function
void settRoC(char roc, char c, int numroc); // initialization of the set temporary row or column function

void turn(char cw, int side, char roc, int numroc) // utilizes the different methods below to turn the rubik's selected rows and columns (and rotate sides as necessary)
{
    switch (cw)
    {
    case 'w': // case for clockwise
        if (roc == 'h') // if for horizontal
        {
            if (numroc == 1)
            {
                turncw(side, roc, numroc);
                break;
            }

            else if ((numroc == 0) || (numroc == 2))
            {
                turncw(side, roc, numroc);
                if (numroc == 0)
                {
                    rotate(3, 'w');
                }
                else if (numroc == 2)
                {
                    rotate(4, 'w');
                }
                break;
            }
        }
        else if (roc == 'v') // if for vertical
        {

            if (numroc == 1)
            {
                turncw(side, roc, numroc);
                break;
            }
            else if ((numroc == 0) || (numroc == 2))
            {
                turncw(side, roc, numroc);
                if (side == 0)
                {
                    if (numroc == 0)
                    {
                        rotate(1, 'w');
                    }
                    else if (numroc == 2)
                    {
                        rotate(2, 'w');
                    }
                }
                else if (side == 1)
                {
                    if (numroc == 0)
                    {
                        rotate(5, 'w');
                    }
                    else if (numroc == 2)
                    {
                        rotate(0, 'w');
                    }
                }
                else if (side == 2)
                {
                    if (numroc == 0)
                    {
                        rotate(0, 'w');
                    }
                    else if (numroc == 2)
                    {
                        rotate(5, 'w');
                    }
                }
                break;
            }
        }
    case 'c': // case for counter-clockwise
        if (roc == 'h') // case for horizontal
        {
            if (numroc == 1)
            {
                turnccw(side, roc, numroc);
                break;
            }
            else if ((numroc == 0) || (numroc == 2))
            {
                turnccw(side, roc, numroc);
                if (numroc == 0)
                {
                    rotate(3, 'c');
                }
                else if (numroc == 2)
                {
                    rotate(4, 'c');
                }
            }
            break;
        }
        else if (roc == 'v') // case for vertical
        {
            if (numroc == 1)
            {
                turnccw(side, roc, numroc);
                break;
            }
            else if ((numroc == 0) || (numroc == 2))
            {
                turnccw(side, roc, numroc);
                if (side == 1)
                {
                    if (numroc == 0)
                    {
                        rotate(5, 'c');
                    }
                    else if (numroc == 2)
                    {
                        rotate(0, 'c');
                    }
                }
                else if (side == 0)
                {
                    if (numroc == 0)
                    {
                        rotate(1, 'c');
                    }
                    else if (numroc == 2)
                    {
                        rotate(2, 'c');
                    }
                }
                else if (side == 1)
                {
                    if (numroc == 0)
                    {
                        rotate(5, 'c');
                    }
                    else if (numroc == 2)
                    {
                        rotate(0, 'c');
                    }
                }
                else if (side == 2)
                {
                    if (numroc == 0)
                    {
                        rotate(0, 'c');
                    }
                    else if (numroc == 2)
                    {
                        rotate(5, 'c');
                    }
                }
                break;
            }
        }
    }
}

void rotate(int side, char cw) // rotates a side based on if an adjacent side is being rotated at a row or column of 0 or 2
{
    char temp, temp2;
    if (cw == 'w') // case for clockwise
    {
        temp = rubiks[side][0][0];
        temp2 = rubiks[side][1][0];
        rubiks[side][1][0] = temp;
        temp = rubiks[side][2][0];
        rubiks[side][2][0] = temp2;
        temp2 = rubiks[side][2][1];
        rubiks[side][2][1] = temp;
        temp = rubiks[side][2][2];
        rubiks[side][2][2] = temp2;
        temp2 = rubiks[side][1][2];
        rubiks[side][1][2] = temp;
        temp = rubiks[side][0][2];
        rubiks[side][0][2] = temp2;
        temp2 = rubiks[side][0][1];
        rubiks[side][0][1] = temp;
        rubiks[side][0][0] = temp2;
    }
    else if (cw == 'c') // case for counter-clockwise
    {
        temp = rubiks[side][0][0];
        temp2 = rubiks[side][0][1];
        rubiks[side][0][1] = temp;
        temp = rubiks[side][0][2];
        rubiks[side][0][2] = temp2;
        temp2 = rubiks[side][1][2];
        rubiks[side][1][2] = temp;
        temp = rubiks[side][2][2];
        rubiks[side][2][2] = temp2;
        temp2 = rubiks[side][2][1];
        rubiks[side][2][1] = temp;
        temp = rubiks[side][2][0];
        rubiks[side][2][0] = temp2;
        temp2 = rubiks[side][1][0];
        rubiks[side][1][0] = temp;
        rubiks[side][0][0] = temp2;

    }
}

void nexttSide(char dir, char dir2); // initializes the next side function for the temporary array
void settSide(int side); // initializes the set side function for the temporary array

extern char d = 'n'; // external variable to keep track of an operation being vertical on the left, right, top and bottom sides

void turncw(int side, char roc, int numroc) // turns rubik's selected row or column clockwise
{
    int i, c;
    int count = 0;

    settSide(side);
    settRoC(roc, 'w', numroc);

    if (roc == 'h') // if for horizontal
    {
        for (i = 0; i < 4; i++)
        {
            nexttSide('h', 'w');
            for (c = 0; c < 3; c++)
            {
                rubiks[tempSide][c][numroc] = tempRoC[count];
                count++;
            }
        }
    }
    else if (roc == 'v') // if for vertical
    {
        if ((side != 1) && (side != 2))
        {
            for (i = 0; i < 4; i++)
            {
                nexttSide('v', 'w');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][numroc][c] = tempRoC[count];
                    count++;
                }
            }
        }
        else if (side == 1) // if for a side being adjacent to the front (last 3 operations of 9)
        {
            if (numroc == 2)
            {
                nexttSide('v', 'w');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][c][2] = tempRoC[count];
                    count++;
                }
                nexttSide('v', 'w');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][0][c] = tempRoC[count];
                    count++;
                }
                nexttSide('v', 'w');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][c][0] = tempRoC[count];
                    count++;
                }
                nexttSide('v', 'w');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][2][c] = tempRoC[count];
                    count++;
                }
            }
            else if (numroc == 1)
            {
                nexttSide('v', 'w');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][c][1] = tempRoC[count];
                    count++;
                }
                nexttSide('v', 'w');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][1][c] = tempRoC[count];
                    count++;
                }
                nexttSide('v', 'w');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][c][1] = tempRoC[count];
                    count++;
                }
                nexttSide('v', 'w');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][1][c] = tempRoC[count];
                    count++;
                }
            }
            else if (numroc == 0)
            {
                nexttSide('v', 'w');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][c][0] = tempRoC[count];
                    count++;
                }
                nexttSide('v', 'w');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][2][c] = tempRoC[count];
                    count++;
                }
                nexttSide('v', 'w');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][c][2] = tempRoC[count];
                    count++;
                }
                nexttSide('v', 'w');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][0][c] = tempRoC[count];
                    count++;
                }
            }
        }
    }
}

void printTS() // prints temporary side
{
    int i;
    for (i = 0; i < 12; i++)
    {
        printf("%c", tempRoC[i]);
    }
}

void turnccw(int side, char roc, int numroc) // turns rubik's selected row or column counter-clockwise
{
    int i, c;
    int count = 0;

    settSide(side);
    settRoC(roc, 'c', numroc);

    if (roc == 'h') // if for horizontal
    {
        for (i = 0; i < 4; i++)
        {
            nexttSide('h', 'c');
            for (c = 0; c < 3; c++)
            {
                rubiks[tempSide][c][numroc] = tempRoC[count];
                count++;
            }
        }
    }
    else if (roc == 'v') // if for vertical
    {
        if ((side != 1) && (side != 2))
        {
            for (i = 0; i < 4; i++)
            {
                nexttSide('v', 'c');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][numroc][c] = tempRoC[count];
                    count++;
                }
            }
        }
        else if (side == 1) // if for a side being adjacent to the front (last 3 operations of 9)
        {
            if (numroc == 2)
            {
                nexttSide('v', 'c');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][c][0] = tempRoC[count];
                    count++;
                }
                nexttSide('v', 'c');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][0][c] = tempRoC[count];
                    count++;
                }
                nexttSide('v', 'c');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][c][2] = tempRoC[count];
                    count++;
                }
                nexttSide('v', 'c');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][2][c] = tempRoC[count];
                    count++;
                }
            }
            if (numroc == 1)
            {
                nexttSide('v', 'c');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][c][1] = tempRoC[count];
                    count++;
                }
                nexttSide('v', 'c');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][1][c] = tempRoC[count];
                    count++;
                }
                nexttSide('v', 'c');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][c][1] = tempRoC[count];
                    count++;
                }
                nexttSide('v', 'c');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][1][c] = tempRoC[count];
                    count++;
                }
            }
            if (numroc == 0)
            {
                nexttSide('v', 'c');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][c][2] = tempRoC[count];
                    count++;
                }
                nexttSide('v', 'c');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][2][c] = tempRoC[count];
                    count++;
                }
                nexttSide('v', 'c');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][c][0] = tempRoC[count];
                    count++;
                }
                nexttSide('v', 'c');
                for (c = 0; c < 3; c++)
                {
                    rubiks[tempSide][0][c] = tempRoC[count];
                    count++;
                }
            }
        }

    }
}
void settRoC(char roc, char c, int numroc) //copies rows or columns to tempRoC
{
    int i, d;
    int counter = 0;
    if (roc == 'h') // if for horizontal
    {
        for (d = 0; d < 4; d++)
        {
            for (i = 0; i < 3; i++)
            {
                tempRoC[counter] = rubiks[tempSide][i][numroc];
                counter++;
            }
            nexttSide('h', c);
        }
    }
    else if (roc == 'v') // if for vertical
    {
        for (d = 0; d < 4; d++)
        {
            for (i = 0; i < 3; i++)
            {
                tempRoC[counter] = rubiks[tempSide][numroc][i];
                counter++;
            }
            nexttSide('v', c);
        }
    }
}

void settSide(int side) // sets tempSide to the number of a side
{
    tempSide = side;
}

void nexttSide(char dir, char dir2) // makes tempSide the next side in line depending on the direction
{
    if (dir == 'h') // 'h' is short for horizontal
    {
        if (dir2 == 'c') // 'c' is short for counter clockwise
        {
            switch (tempSide)
            {
            case 0: // Front to Left
                tempSide = 1;
                break;
            case 1: // Left to Back
                tempSide = 5;
                break;
            case 5: // Back to Right
                tempSide = 2;
                break;
            case 2: // Right to Front
                tempSide = 0;
            }
        }

        else if (dir2 == 'w') // 'w' is short for clockwise
        {
            switch (tempSide)
            {
            case 0: // Front to Right
                tempSide = 2;
                break;
            case 2: // Right to Back
                tempSide = 5;
                break;
            case 5: // Back to Left
                tempSide = 1;
                break;
            case 1: // Left to Back
                tempSide = 0;
                break;
            }
        }
    }
    else if (dir == 'v') // 'v' is short for vertical
    {
        if (dir2 == 'c') // 'c' is short for counter clockwise
        {
            if ((tempSide != 1 && tempSide != 2) && (d != 'a'))
            {
                switch (tempSide)
                {
                case 0: // Front to Top
                    tempSide = 3;
                    break;
                case 3: // Top to Back
                    tempSide = 5;
                    break;
                case 5: // Back to Bottom
                    tempSide = 4;
                    break;
                case 4: // Bottom to Front
                    tempSide = 0;
                    break;

                }
            }
            else
            {
                d = 'a';
                switch (tempSide)
                {
                case 1: // Left to Bottom
                    tempSide = 4;
                    break;
                case 4: // Bottom to Right
                    tempSide = 2;
                    break;
                case 2: // Right to Top
                    tempSide = 3;
                    break;
                case 3: // Top to Left
                    tempSide = 1;
                    break;
                }
            }
        }
        else if (dir2 == 'w') // 'w' is short for clockwise
        {
            if ((tempSide != 1 && tempSide != 2) && (d != 'a'))
            {
                switch (tempSide)
                {
                case 0: // Front to Bottom
                    tempSide = 4;
                    break;
                case 4: // Bottom to Back
                    tempSide = 5;
                    break;
                case 5: // Back to Top
                    tempSide = 3;
                    break;
                case 3: // Top to Front
                    tempSide = 0;
                    break;
                }
            }
            else
            {
                d = 'a';
                switch (tempSide)
                {
                case 1: // Left to Top
                    tempSide = 3;
                    break;
                case 3: // Top to Right
                    tempSide = 2;
                    break;
                case 2: // Right to Bottom
                    tempSide = 4;
                    break;
                case 4: // Bottom to Left
                    tempSide = 1;
                    break;
                }
            }

        }

    }
}

void printSide(int side, int tabs) // prints selected side (used for printSides)
{
    int i, c, t;

    for (c = 0; c < 3; c++)
    {
        printf("\n");
        for (t = 0; t < tabs; t++)
        {
            printf("\t");
        }

        for (i = 0; i < 3; i++)
        {
            printf("%c ", rubiks[side][i][c]);
        }

    }
}

void printSides() // prints the six faces of the cube in a cross
{

    int i, c;
    printSide(5, 2);
    printSide(3, 2);

    for (c = 0; c < 3; c++)
    {

        printf("\n");
        printf("\t  ");
        for (i = 0; i < 3; i++)
        {
            printf("%c ", rubiks[1][i][c]);
        }

        for (i = 0; i < 3; i++)
        {
            printf("%c ", rubiks[0][i][c]);
        }

        for (i = 0; i < 3; i++)
        {
            printf("%c ", rubiks[2][i][c]);
        }

    }

    printSide(4, 2);

}

