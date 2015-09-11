#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
    srand(time(NULL));
    int randNum = rand() % 9 ;
    
    // avaliable chars to choose form
    char chArray[9];
    chArray[0] = '[';
    chArray[1] = '(';
    chArray[2] = '{';
    chArray[3] = ' ';
    chArray[4] = 'a';
    chArray[5] = 'x';
    chArray[6] = '}';
    chArray[7] = ')';
    chArray[8] = ']';
    
    //printf("the rand number == %d ", randNum);
    // printf("the Char is == %c\n", chArray[randNum]);
    
    return chArray[randNum];
}

char *inputString()
{
    // TODO: rewrite this function
    // This initializes the random number generator
    srand(time(NULL));
    
    int randNum;
    int array[10];
    int random_nums[10];
    int x, p;
    int count;
    int i = 0;
    
    // Loads the array
    for (count = 0; count < 4; count++)
        array[count] = rand() % 5 ;
    char *restWord = malloc(8 * sizeof(char * ));
    char *randWord = malloc(8 * sizeof(char * ));
    restWord = "reset";
    // printf("this is restWord[4] == %c  \n", restWord[4]);
    
    
    // Cycles through making sure numbers are 0-4
    while (i < 6)
    {
        int r = rand() % 6;
        
        for (x = 0; x < i; x++)
            if (array[x] == r)
                break;
        
        if (x == i)
            array[i++] = r;
    }
    
    // Places random numbers into random_num array
    for (p = 0; p < 6; p++)
        random_nums[p] = * (array + p);
    
    
    // creates the size of the strings
    
    for (i = 0; i < 6; i++)
    {
        randNum = random_nums[i];
        randWord[i] = restWord[randNum];
    }
    //randWord[5] = '\0';
    
    
    return randWord;
}

void testme()
{
    int tcCount = 0;
    char *s;
    char c;
    int state = 0;
    while (1)
    {
        tcCount++;
        c = inputChar();
        s = inputString();
        printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);
        
        if (c == '[' && state == 0) state = 1;
        if (c == '(' && state == 1) state = 2;
        if (c == '{' && state == 2) state = 3;
        if (c == ' '&& state == 3) state = 4;
        if (c == 'a' && state == 4) state = 5;
        if (c == 'x' && state == 5) state = 6;
        if (c == '}' && state == 6) state = 7;
        if (c == ')' && state == 7) state = 8;
        if (c == ']' && state == 8) state = 9;
        if (s[0] == 'r' && s[1] == 'e'
            && s[2] == 's' && s[3] == 'e'
            && s[4] == 't' && s[5] == '\0'
            && state == 9)
        {
            printf("error ");
            exit(200);
        }
    }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}