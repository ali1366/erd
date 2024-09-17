/*
 ============================================================================
 Name          : ERD - Evolutionary RNA Designer
 Author        : Ali Esmaili Taheri
 First Version : 1.0.0.0
 Last  Version : 2.0.0.0
 Copyright     : 2012 @ free
 Last Edit     : 2014
 Description   : This code is for RNA Inverse folding
 ============================================================================
 */

//#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <Genetic_Algorithm.h>
//#include <test.h>
#include <utility.h>
#include "utils.h"
#include "loaddata.h"
//#include <sys/time.h>
#include <Split_Structure.h>
#include <sys/timeb.h>
#include <fold.h>
//#include <part_func.h>
#include <inverse.h>
#include <Generate_Sequence.h>

time_t Global_Time;
int Result_Flag;
int Global_lenght;
int Ittration_Flag;
int iteration_size;
short flag_constrain_seq;
short flag_constrain_energy;
float global_avr_max_energy;
float global_avr_min_energy;
int target_structure_length;

///-----------------------------------------------------------
/// Global arrays include pools of RNA sub-sequences
/// corresponding to different components with different lengths
///
char *Data_Hp_Array[100];
char *Data_St_Array[18];
char *Data_Ml_Array[90];
int count_Array[3][100];
///-----------------------------------------------------------

float temperature;

int main(int argc, char *argv[])
{

    extern time_t Global_Time;
    extern int Result_Flag;
    extern int Global_lenght;


/// load data from DB3
load_data("");


char *seq,*str,*target_structure,*constrain_sequence,*constrain_sequence_temp;

time(&Global_Time);
Global_lenght=10000000;
Ittration_Flag=1;
iteration_size=251;
Result_Flag=0;

flag_constrain_seq=0;
flag_constrain_energy=0;
 short flag_result_file=0;
 short flag_input_file=0;
//upper_bound_energy=0;
//lower_bound_energy=-1000000;
float probability;
long Seed_Rand=0;
int i,Itreation=1,j;
struct timeb tmb;
long starttime,endtime;
int milistart,miliend;
float rtime;
float energy=0;
float upper_bound_energy=0;
float lower_bound_energy=1000000;
Seed_Rand=time(0);
FILE *fp_out;
FILE *fp_in;


if (argc <=1)
   {
      usage(argv[0]);
      free_data();
      exit(-1);
   }
   i=1;
while(i<=argc-1)
{
    switch(argv[i][1])
    {
        case 'h':
                usage_help(argv[0]);
                free_data();
                exit(1);
            break;
        case 's':
            if(argv[i+1][0]!='-')
            {
                Seed_Rand=atoi(argv[i+1]);
                i++;
            }
            break;
        case 'f':
            if(argv[i+1][0]!='-')
            {
                flag_result_file=1;
                fp_out=fopen(argv[i+1],"w");
                if(fp_out==NULL)
                {
                    printf("Can not open file %s/%s\n",argv[0],argv[i+1]);
                    flag_result_file=0;

                }
                i++;
            }
            break;
        case 'o':
            if(argv[i+1][0]!='-')
            {
                flag_input_file=1;
                fp_in=fopen(argv[i+1],"r");
                if(fp_in==NULL)
                {
                    printf("Can not open file %s\n",argv[i+1]);
                    flag_input_file=0;

                }
                i++;
            }
            break;
        case 'r':
            if(argv[i+1][0]!='-')
            {
                Itreation=atoi(argv[i+1]);
                i++;
            }
            break;
        case 'i':
            if(argv[i+1][0]!='-')
            {
                iteration_size=atoi(argv[i+1]);
                i++;
            }
            break;
        case 'E':
            if(argv[i+1][0]!='-')
            {
                lower_bound_energy =atof(argv[i+1]);
                flag_constrain_energy=1;
                i++;
            }
            break;
        case 'e':
            if(argv[i+1][0]!='-')
            {
                upper_bound_energy =atof(argv[i+1]);
                flag_constrain_energy=1;
                i++;
            }
            break;
        case 't':
            if(argv[i+1][0]!='-')
            {
                temperature=atof(argv[i+1]);
                update_fold_params();
                i++;
            }
            break;
        case 'x':
            if(argv[i+1][0]!='-')
            {
                target_structure=argv[i+1];
//                random_cons=generat_random_cons_seq(target_structure);
//                printf("%s\n",random_cons);
//                free(random_cons);
                target_structure_length=strlen(target_structure);
                if(check_brackets(target_structure)==0)
                    {
                        printf("Erorr: bad structure or mismatch pair\n");
                        exit(-1);
                    }
                i++;
            }
            break;
        case 'c':
            if(argv[i+1][0]!='-')
            {
                //printf("%s\n",argv[i+1]);
                constrain_sequence=check_constraint_sequence(target_structure, argv[i+1]);
                flag_constrain_seq=1;
                //short* ex_co_seq;=extract_sequence_constraint(constraint_sequence);
                //constrain_sequence=argv[i+1];
                i++;
            }
            break;
    }
    i++;
}

if(flag_input_file==1)
{
    target_structure=get_line(fp_in);

    while(target_structure!=NULL)
    {
        constrain_sequence_temp=get_line(fp_in);
        constrain_sequence=check_constraint_sequence(target_structure, constrain_sequence_temp);
         global_avr_max_energy=-(float)(upper_bound_energy/open_prantesis(target_structure));
         global_avr_min_energy=-(float)(lower_bound_energy/open_prantesis(target_structure));

        target_structure_length=strlen(target_structure);
        if(check_brackets(target_structure)==0)
            {
                printf("Erorr: bad structure or mismatch pair\n");
                exit(-1);
            }
        if (flag_result_file==1)
        {
            fprintf(fp_out,"\nTarget Structure:\t %s\n Constraint Sequence:\t %s \n Number of Execution:\t%d\n",target_structure,constrain_sequence,Itreation);
            fprintf(fp_out,"Length\tdist\t\tEnergy\tTime(s)\tGenerated Sequence\n");
        }

        printf("Length  dist      Energy      Time(s)  Generated Sequence\n");

        if(strlen(constrain_sequence)!=strlen(target_structure))
        {
            printf("Erorr:Constraint sequence and target structure are not compatible");
            //constrain_sequence=check_constraint_sequence(target_structure, "");
        }
        flag_constrain_seq=1;

        Global_lenght=strlen(target_structure)/5+6+(iteration_size-251)*2;
        for(i=1;i<Itreation+1;i++)
        {
            ///---------------------------
            /// calculate start time
            ///
            ftime(&tmb);
            starttime=tmb.time;
            milistart=tmb.millitm;
            ///---------------------------

            ///------------------------------------------
            /// ERD
            ///
            srand(Seed_Rand+i);
             Result_Flag=0;
                //Global_lenght=strlen(target_structure)/10+3;
                for(j=1;j<5;j++)
                {
                    time(&Global_Time);
                    seq=GneticAl_final(target_structure,constrain_sequence);
                    if(Result_Flag==0) break;
                    Result_Flag=0;
                    Ittration_Flag++;
                }
                Ittration_Flag=1;
            /// --------------------------------------------

            ///---------------------------
            /// calculate finish time
            ///
            ftime(&tmb);
            endtime=tmb.time;
            miliend=tmb.millitm;
            /// -------------------------

            /// ----------------------------------
            /// Calculate elapsed time.
            ///
            rtime=runtime(starttime,milistart,endtime ,miliend);
            /// ----------------------------------


            str=(char*)malloc ((strlen(seq)+1)*sizeof(char));
            energy=fold(seq,str);
            probability=run_RNAfold_probability(seq);

            /// -----------------------------------
            /// Print results
            ///
            printf("%d	%d	%f  %f   %f   %s \n",strlen(seq),hamming(str,target_structure),energy,probability,rtime,seq);

            if(flag_result_file==1)
            {
                /// -----------------------------------
                /// Write results in output file.
                ///
                fprintf(fp_out,"%d\t%d\t%f\t%f\t%f\t%s\n",strlen(seq),hamming(str,target_structure),energy,probability,rtime,seq);
            }

            free(str);
            free(seq);

        }
        free(target_structure);
        free(constrain_sequence);
        free(constrain_sequence_temp);
        target_structure=get_line(fp_in);
    }
}
else
{
     global_avr_max_energy=-(float)(upper_bound_energy/open_prantesis(target_structure));
    global_avr_min_energy=-(float)(lower_bound_energy/open_prantesis(target_structure));
    if (flag_result_file==1)
    {
        fprintf(fp_out,"Target Structure:\t %s\n Constraint Sequence:\t %s \n Number of Execution:\t%d\n",target_structure,constrain_sequence,Itreation);
        fprintf(fp_out,"Length\tdist\t\tEnergy\tTime(s)\tGenerated Sequence\n");
    }

    printf("Length  dist      Energy      Time(s)  Generated Sequence\n");
    if(flag_constrain_seq==0)
    {
        constrain_sequence=check_constraint_sequence(target_structure, "");
        Global_lenght=strlen(target_structure)/10+3+(iteration_size-251);

    }
    else
    {
        Global_lenght=strlen(target_structure)/5+6+(iteration_size-251)*2;
    }
    for(i=1;i<Itreation+1;i++)
    {
        ///---------------------------
        /// calculate start time
        ///
        ftime(&tmb);
        starttime=tmb.time;
        milistart=tmb.millitm;
        ///--------------------------


        /// -------------------------------------
        /// ERD
        ///
        srand(Seed_Rand+i);
         Result_Flag=0;
            for(j=1;j<5;j++)
            {
                time(&Global_Time);
                seq=GneticAl_final(target_structure,constrain_sequence);
                if(Result_Flag==0) break;
                Result_Flag=0;
                Ittration_Flag++;
            }
            Ittration_Flag=1;
            ///-----------------------------------


        /// ---------------------------------
        /// Calculate finish time.
        ///
        ftime(&tmb);
        endtime=tmb.time;
        miliend=tmb.millitm;
        /// ----------------------------------

        /// ----------------------------------
        /// Calculate elapsed time.
        ///
        rtime=runtime(starttime,milistart,endtime ,miliend);
        ///-----------------------------------


        str=(char*)malloc ((strlen(seq)+1)*sizeof(char));
        energy=fold(seq,str);

        /// -----------------------------------
        /// Print results
        ///
        printf("%d	%d	%f  %f  %s\n",strlen(seq),hamming(str,target_structure),energy,rtime,seq);

        /// -----------------------------------
        /// Write results in output file.
        ///
        if(flag_result_file==1)
        {
            fprintf(fp_out,"%d\t%d\t%f\t%f\t%s\n",strlen(seq),hamming(str,target_structure),energy,rtime,seq);
        }

        free(str);
        free(seq);

    }
}

/// Free alocated memory to pools
free_data();

/// close files
if(flag_result_file==1)
    fclose(fp_out);
if(flag_input_file==1)
    fclose(fp_in);


exit(1);

}
