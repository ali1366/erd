#include <utility.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <part_func.h>
#include <utils.h>



/// Calculate time between start and end.
float runtime(long start,int milistart,long end ,int miliend)
{
    float rtime;

    rtime=end-start;
    if(rtime>0)
    {
        rtime--;
        rtime=rtime+(float)(1000-milistart+miliend)/1000;
        return rtime;
    }
    else
    {
        rtime=(float)(miliend-milistart)/1000;
        return rtime;
    }
}

/// Concatinate three strings.
char * merg_string(char*string1,char*string2,char*string3)
{
    int i=0;
    int size=(strlen(string1)+strlen(string2)+strlen(string3));
    char*merg_str=(char* ) malloc((size+1)*sizeof(char));
    for(i=0;i<size;i++)
    {
        if(i<strlen(string1))
        {
            merg_str[i]=(char)string1[i];
        }
        else if(i<(strlen(string1)+strlen(string2)))
        {
            merg_str[i]=(char)string2[i-strlen(string1)];
        }
        else
        {
            merg_str[i]=(char)string3[i-(strlen(string1)+strlen(string2))];
        }
    }
    merg_str[size]='\0';
    return merg_str;
}

/// Return parts of string between start and end.
char * strpar(char*string,int start,int end)
{
    int i=0;
    char* Seq=(char* ) malloc((end-start+2)*sizeof(char));
    for(i=0;i<=end-start;i++)
    {
        Seq[i]=(char)string[i+start];
    }
    Seq[end-start+1]='\0';
    return Seq;
}

/// Finds first target character after certain position.
int findfirst(char* string,int index_start_search,char target)
{
    int Size=strlen(string);
    int i=index_start_search;
    for(i=index_start_search;i<Size;i++)
    {
        if(string[i]==target)
        return i;
    }
    return -1;
}


/// Finds last target character before certain position.
int findlast(char* string,int index_end_search,char target)
{
    int i=index_end_search;
    for(i=index_end_search;i>=0;i--)
    {
        if(string[i]==target)
        return i;
    }
    return -1;
}


/// Deletes part of array between start and end.
void delete_elements(int*array,int start,int end,int *size)
{
    int diff=end-start;
    int index=end;
    for(index=end;index<*size;index++)
    {
        array[index-diff]=array[index+1];
    }
    array = (int*)realloc(array, ((*size - (diff)) * sizeof(int)));
    //for malloc index started from 1,not 0.
    *size=*size-diff-1;
}


/// Deletes part of string between start and end.
void delete_string_elements(char*string,int start,int end,int *size)
{
    int diff=end-start;
    int index=end;
    for(index=end;index<=*size-1;index++)
    {
        string[index-diff]=string[index+1];
    }
    string[*size-diff]='\0';
    string = (char*)realloc(string, ((*size - (diff)+1) * sizeof(char)));
    //for malloc index started from 1,not 0.

//    *size=*size-diff-1;
    *size=*size-diff;
}


/// Calculate summation of array elements from start to end.
int sum(int*array,int start,int end)
{
    int i=start;
    int sumation=0;
    for(i=start;i<=end;i++)
    {
        sumation=sumation+array[i];
    }
    return sumation;
}


/// Elements position in array with certain value is returned.
int* find(int*array,char unequal,int comparison_value,int *size)
{
    int *result=(int*)malloc((*size+1)*sizeof(int));
    int resultIndex=0;
    result[0]=resultIndex;
    int i=1;
    if(unequal=='>')
    {
        for(i=1;i<=*size;i++)
        {
            if(array[i]>comparison_value)
            {
                result[resultIndex+1]=i;
                resultIndex++;
            }
        }
    }
    else if(unequal=='<')
    {
        for(i=1;i<=*size;i++)
        {
            if(array[i]<comparison_value)
            {
                result[resultIndex+1]=i;
                resultIndex++;
            }
        }

    }
    else
    {
        for(i=1;i<=*size;i++)
        {
            if(array[i]==comparison_value)
            {
                result[resultIndex+1]=i;
                resultIndex++;
            }
        }
    }
    result[0]=resultIndex;
    return (int *) result;

}


/// Generate random number between start and end.
int rand_diff(int start,int end)
{
//    struct   timeval time;
//    gettimeofday(&time, NULL);
//    long millis = (time.tv_sec * 1) + (time.tv_usec /1);
//    srand(millis%rand()+lrand48());
//    int randomNumber=rand() % ((end+1)-start);
//    randomNumber=randomNumber+start;


    //srand(rand());
    int randomNumber=rand() % ((end+1)-start);
    randomNumber=randomNumber+start;
    return randomNumber;
}


/// Insert a string between positions start and end in another string.
char * insert_in_string(char*string,char*inserted_string,int start_point,int end_point)
{
    //char*temp_string=(char *)malloc((strlen(string)+1)*sizeof(char));
    //strcpy(temp_string,string);
    int i=start_point;
    for(i=start_point;i<=end_point;i++)
    {
       // strcpy(string[i],insert_in_string[i-start_point]);
       // temp_string[i]=(char)inserted_string[i-start_point];
       string[i]=(char)inserted_string[i-start_point];
       //string[i]='c';
    }
    return &string[0];
}

/***********************************************/

/// Print help instruction
void usage_help(char* name)
{
   printf( "\ncall:  %s  -x 'structure'  \n" ,name);

   printf( "  Usage:\n");
   printf( " ~$ cd ERD-2.0.0                                  Moves into the directory ERD-2.0.0 . \n");
   printf( " ~ERD-2.0.0$ ./ERD-2 -x 'structure'                     Use this command.\n");
   printf( " \n");
   printf( "-----------------------------------------------------\n");
   printf("Samples command:\n");
   printf( "./ERD-2 -x '....(((((.....))...)))...'\n");
   printf( "./ERD-2 -x '....(((((.....))...)))...' -c NNNNNNNNNNNAANNNNNNNCGANN \n");
   printf( "./ERD-2 -o input.txt -f output.txt \n");
   printf( "./ERD-2 -r 10 -x '....(((((.....))...)))...'\n");
   printf( "./ERD-2 -r 10 -e 5 -E 50 -x '....(((((.....))...)))...'\n");
   printf( "./ERD-2 -r 10 -s 1000 -x '....(((((.....))...)))...'  \n");
   printf( "./ERD-2 -x '....(((((.....))...)))...' -c NNNNNNNNNNNAANNNNNNNCGANN \n");
   printf( "./ERD-2 -o input.txt -f output.txt -r 10 \n");
   printf( "./ERD-2 -r 10 -s 1000 -t 30 -x '....(((((.....))...)))...'  \n");
   printf( "./ERD-2 -x '....(((((.....))...)))...' -r 10 -s 1000 \n");
   printf( "./ERD-2 -x '....(((((.....))...)))...' -r 10 -s 1000 -t 30 \n");
   printf( "./ERD-2 -t 30 -x '....(((((.....))...)))...' -r 10 -s 1000 \n");
   printf( " \n\n");
   printf( "where options are: \n");
   printf( "  -h          : Print help instruction\n");
   printf( "  -r          : Number of execution\n");
   printf( "  -s          : Randoom Seed \n");
   printf( "  -t          : Temperature \n");
   printf( "  -x          : Target structure \n");
   printf( "  -c          : Constraint sequence \n");
   printf( "  -f          : Output file \n");
   printf( "  -o          : Input file \n");
   printf( "  -e          : Maximum energy \n");
   printf( "  -E          : Minimum energy \n");

   printf( " ----------------------------------------------------");
   printf( "\n");

  // exit(1);
}


void usage(char* name)
{
   printf( "\ncall:  %s  -x 'structure'  \n" ,name);
      printf( " ---------------------------------------------------- \n");
   printf( "  Usage:\n");
   printf( " ~$ cd ERD-2.0.0                          Moves into the directory ERD-2.0.0  . \n");
   printf( " ~ERD-2.0.0 $./ERD-2 -x 'structure'       Use this command.\n");

   printf( " \n");
   printf ("  Use -h argumant to see help message.             \n");
   printf( " ---------------------------------------------------- \n");
  // exit(1);
}
/***************************************************************/


float run_RNAfold_probability(char*sequence)
{

    int i;
    int length;
    char*command;
    char* result;
    char* probability;
    float prob;

        FILE *fptemp2=fopen("temp11.txt","w");
        fprintf(fptemp2,"%s\n",sequence);
        fclose(fptemp2);
        command=merg_string("RNAfold -p   ","< 'temp11.txt'"," > out11.txt");

            system(command);
            FILE *fptemp=fopen("out11.txt","r");
            result=get_line(fptemp);
            free(result);
            result=get_line(fptemp);
            free(result);
            result=get_line(fptemp);
            free(result);
            result=get_line(fptemp);
            free(result);
            result=get_line(fptemp);
            fclose(fptemp);
            length=strlen(result);
            for(i=41;i<length;i++)
            {
                if(result[i]==';')
                {
                    probability=strpar(result,40,i-1);
                    break;
                }
            }
            free(result);
            prob=atof(probability);
            free(probability);

        free(command);
        return prob;
}
