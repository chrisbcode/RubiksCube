/*
 * Filename:    RubiksCube.c
 * Author:      Christopher Bergsveinsson
 * Date:        9/8/2024
 *
 * Simulates a Rubik's Cube
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
#include <stdlib.h>
#include <stdbool.h>

char rubiks[6][3][3] =
        { { { 'W', 'W', 'W' }, { 'W', 'W', 'W' }, { 'W', 'W', 'W' } }, {
                { 'G', 'G', 'G' }, { 'G', 'G', 'G' }, { 'G', 'G', 'G' } },
          { { 'B', 'B', 'B' }, { 'B', 'B', 'B' }, { 'B', 'B', 'B' } }, {
                  { 'O', 'O', 'O' }, { 'O', 'O', 'O' }, { 'O', 'O', 'O' } },
          { { 'R', 'R', 'R' }, { 'R', 'R', 'R' }, { 'R', 'R', 'R' } }, {
                  { 'Y', 'Y', 'Y' }, { 'Y', 'Y', 'Y' }, { 'Y', 'Y', 'Y' } } }; // the array for all the rubik's characters

int rmap[6][3][3] =
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

void askUser();

int main(void) {


     printf("Hello, welcome to my Rubiks Cube code!\n");
     printSides();
     printf("\nThis is the cube in folds, with the face in the middle (3rd side down) being the front of the cube \n");
     printf("So, what would you like to do?\n");

     askUser();
    return 0;
}

bool quik = false; // boolean for quick mode
bool e = true; // controls whether program continues to iterate or exit

void quikOp();
void randomize();

void askUser() {
    int c, nroc, i, side; // c is the choice the user makes in the console | nroc is the number of the row or column the user chooses | i is the amount of times a rotation will be executed | dir is the direction of the rotation | side
    char hov, dir = 0, rocpos = 0, sta; // hov is the choice the user makes in the console for horizontal / vertical actions | rocpos is the position of the row or column | sta is the starting face (front or adjacent)

    while(e) {
    printf("\n1. Rotate cube\n2. Quick Mode\n3. Randomize\n4. Reset\n5. Exit\n");
    scanf("%d", &c);

    switch(c) {
        case 1:
            printf("Start from front (f) or adjacent (a) side\n");
        scanf(" %c", &sta);

        if(sta == 'a' || sta == 'f') {
            printf("\nHorizontal (h) or Vertical (v):\n");
            scanf(" %c", &hov);
        }

        if(hov == 'h' || hov == 'v') {
            printf("\nTop (t or T), Middle (m or M), or Bottom (b or B) row:\n");
            scanf(" %c", &rocpos);
        }


        if(rocpos == 't' || rocpos == 'T' || rocpos == 'm' || rocpos == 'M' || rocpos == 'b' || rocpos == 'B') {
            printf("\nWhich direction, Clockwise (w) or Counter-clockwise (c):\n");
            scanf(" %c", &dir);
        }



        if('w' == dir || 'c' == dir) {
            printf("\nHow many times?\n");
            scanf(" %d", &i);
        }



        if(rocpos == 't' || rocpos == 'T') // conditionals to decide the number of the row or columnn
            nroc = 0;
        else if(rocpos == 'm' || rocpos == 'M')
            nroc = 1;
        else if(rocpos == 'b' || rocpos == 'B')
            nroc = 2;



        if (sta == 'f') { // conditionals to decide the starting face
            side = 0;
        }
        else if(sta == 'a') {
            side = 1;
        }



        if(i == 1) {
            printf("%c%c%d", dir, hov, nroc);
            turn(dir, side, hov, nroc);
            printSides();
        }
        else if (i > 1) {
            for(int a = 0; a < i; a++)
                turn(dir, side, hov, nroc);
            printSides();
        }

        break;

        case 2:
            printf("\n1. Start\n2. Guide\n3. Exit\n");
        scanf(" %d", &c);
        if(c == 2) {
            printf("Operation 1: Front Top Horizontal\n");
            printf("Operation 2: Front Middle Horizontal\n");
            printf("Operation 3: Front Bottom Horizontal\n");
            printf("Operation 4: Front Left Vertical\n");
            printf("Operation 5: Front Middle Vertical\n");
            printf("Operation 6: Front Right Vertical\n");
            printf("Operation 7: Adjacent Left Vertical\n");
            printf("Operation 8: Adjacent Middle Vertical\n");
            printf("Operation 9: Adjacent Right Vertical\n");
            printf("After one of these operations, you would then type clockwise (w) or counter-clockwise (c), and the number of iterations you want the spin to be executed");
            printf("To exit: Just type '0'\n");
            printf("Example: 1c3 would be front (side 0), top, horizontal, clockwise, executed 3 times.\n");
            printf("\n1. Start\n2. Exit\n");
            scanf(" %c", &c);
        }
        if(c == 1) {
            quikOp();
            askUser();
        }
        else if (c == 2) {
            askUser();
            break;
        }

        case 3: ;
        randomize();
        break;

        case 4: ;
        int y, z;
        for(y = 0; y < 3; y++)
            for(z = 0; z < 3; z++)
                rubiks[0][y][z] = 'W';
        for(y = 0; y < 3; y++)
            for(z = 0; z < 3; z++)
                rubiks[1][y][z] = 'G';
        for(y = 0; y < 3; y++)
            for(z = 0; z < 3; z++)
                rubiks[2][y][z] = 'B';
        for(y = 0; y < 3; y++)
            for(z = 0; z < 3; z++)
                rubiks[3][y][z] = 'O';
        for(y = 0; y < 3; y++)
            for(z = 0; z < 3; z++)
                rubiks[4][y][z] = 'R';
        for(y = 0; y < 3; y++)
            for(z = 0; z < 3; z++)
                rubiks[5][y][z] = 'Y';

        printSides();

        break;

        case 5:
            e = false;
        break;

        default: ;
    }
}

}

void quikOp() {
    printf("check");
    bool kpgn = true; // Keep going is default set true
    int opnum, it; // operation number | iteration number
    char cow; // clockwise or counter-clockwise

    while( kpgn == true ) {

        scanf(" %d%c%d", &opnum, &cow, &it);

        if(opnum == 0) {
            kpgn = false;
        }
        for(int i = 0; i < it; i++) {
            if (opnum == 1) {
                turn(cow, 0, 'h', 0);
            }
            else if (opnum == 2) {
                turn(cow, 0, 'h', 1);
            }
            else if (opnum == 3) {
                turn(cow, 0, 'h', 2);
            }
            else if (opnum == 4) {
                turn(cow, 0, 'v', 0);
            }
            else if (opnum == 5) {
                turn(cow, 0, 'v', 1);
            }
            else if (opnum == 6) {
                turn(cow, 0, 'v', 2);
            }
            else if (opnum == 7) {
                turn(cow, 1, 'v', 0);
            }
            else if (opnum == 8) {
                turn(cow, 1, 'v', 1);
            }
            else if (opnum == 9) {
                turn(cow, 1, 'v', 2);
            }
            printSides();
        }
    }
}

void randomize() {
    int r, r2;
    char cow;

    printf("Randomizing...");

    for(int i = 0; i < 25; i++) {

        r = (rand() % 6) + 1;
        r2 = (rand() % 2);

        if(r2 == 0) cow = 'w';
        else cow = 'c';

        if (r == 1) {
            turn(cow, 0, 'h', 0);
        }
        else if (r == 2) {
            turn(cow, 0, 'h', 1);
        }
        else if (r == 3) {
            turn(cow, 0, 'h', 2);
        }
        else if (r == 4) {
            turn(cow, 0, 'v', 0);
        }
        else if (r == 5) {
            turn(cow, 0, 'v', 1);
        }
        else if (r == 6) {
            turn(cow, 0, 'v', 2);
        }

    }

    printSides();
}





char tempRoC[12] = { 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a' }; // temporary row or column to facilitate transfer

int tempSide = 0; // temporary side to facilitate transfer

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
            if ((numroc == 0) || (numroc == 2))
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
            if ((numroc == 0) || (numroc == 2))
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
            if ((numroc == 0) || (numroc == 2))
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
        if (roc == 'v') // case for vertical
        {
            if (numroc == 1)
            {
                turnccw(side, roc, numroc);
                break;
            }
            if ((numroc == 0) || (numroc == 2))
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
    default: ;
    }
}

void rotate(int side, char cw) {
    char temp[3][3];
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            temp[i][j] = rubiks[side][i][j];

    if(cw == 'w') { // clockwise
        for(int i=0; i<3; i++)
            for(int j=0; j<3; j++)
                rubiks[side][j][2-i] = temp[i][j];
    } else { // counter-clockwise
        for(int i=0; i<3; i++)
            for(int j=0; j<3; j++)
                rubiks[side][2-j][i] = temp[i][j];
    }
}


void nexttSide(char dir, char dir2); // initializes the next side function for the temporary array
void settSide(int side); // initializes the set side function for the temporary array

char d = 'n'; // variable to keep track of an operation being vertical on the left, right, top and bottom sides

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
            default: ;
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
            default: ;
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
                default: ;
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
                default: ;
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
                default: ;
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
                default: ;
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
    printf("\n");

}
