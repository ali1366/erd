#include <Genetic_Algorithm.h>
#include <utility.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "fold_vars.h"
#include "fold.h"
#include <Split_Structure.h>
#include <Generate_Sequence.h>
#include <time.h>

time_t Global_Time;
int Result_Flag;
int Global_lenght;
int Ittration_Flag;
int iteration_size;
float global_avr_max_energy;
float global_avr_min_energy;
short flag_constrain_energy;
short flag_constrain_seq;
int target_structure_length;

/// --------------------------------------------------------------------
/// Select three of best sequence with maximum energy
/// in target structure among evolutionary algorithm population.
///
int *selected_sequence(char *SeqArray,char *structure)
{
    float energy[15];
    int maxenergy=30000;
    int *min=(int*)malloc(3*sizeof(int));
    float energymin=0;
    int j=0;
    int i=0;
    for(i=0;i<15;i++)
    {
        energy[i] = energy_of_struct(&SeqArray[0]+i*(strlen((structure))+1), structure);
        //free_arrays();
    }


    /**
     //this section is for Genetic algorithm  and decomposition test and not related to the main aligorithm

if(strlen(structure)==193)
{
    FILE *fpe,*fpd;
    fpe=fopen("ERD-Result//HD//HDE193.txt","a+");
    fpd=fopen("ERD-Result//HD//HDD193.txt","a+");
    fseek(fpe, 0, SEEK_END);
    fseek(fpd, 0, SEEK_END);
    int hdist=0;
    float entest=0;
    char* teststr=(char*)malloc((strlen(structure)+1)*sizeof(char));
    for(i=0;i<15;i++)
    {
        entest = fold(&SeqArray[0]+i*(strlen((teststr))+1), teststr);
        hdist=hamming(teststr,structure);
        fprintf(fpe,"%f  ",entest);
        fprintf(fpd,"%d  ",hdist);
    }
    fprintf(fpe,"\n");
    fprintf(fpd,"\n");
    fclose(fpe);
    fclose(fpd);
    free(teststr);
}

**/
    energymin=maxenergy;
    if(rand_diff(0,100)<89)
    {
        for(j=0;j<3;j++)
        {
            for(i=0;i<15;i++)
            {
                if(energymin>energy[i])
                {
                      min[j]=i;
                      energymin=energy[i];
                }
            }
            energy[min[j]]=maxenergy;
            energymin=maxenergy;
        }
    }
    else
    {
        for(i=0;i<15;i++)
            {
                if(energymin>energy[i])
                {
                      min[0]=i;
                      energymin=energy[i];
                }
            }
        min[1]=rand_diff(0,14);
        energy[min[0]]=maxenergy;
        energymin=maxenergy;
        for(i=0;i<15;i++)
            {
                if(energymin>energy[i])
                {
                      min[2]=i;
                      energymin=energy[i];
                }
            }

    }
    return (int *)&min[0];
}


int *selected_sequence_constrain_energy(char *SeqArray,char *structure,float max_energy,float min_energy)
{
    float energy[15];
    //float temp_energy[15];
    int maxenergy=30000;
    int *min=(int*)malloc(3*sizeof(int));
    float energymin=0;
    int j=0;
    int i=0;
    for(i=0;i<15;i++)
    {
        energy[i] = energy_of_struct(&SeqArray[0]+i*(strlen((structure))+1), structure);
        if(energy[i]<min_energy||energy[i]>max_energy)
        {
            energy[i]=0;
        }

        //free_arrays();
    }


    energymin=maxenergy;
    if(rand_diff(0,100)<89)
    {
        for(j=0;j<3;j++)
        {
            for(i=0;i<15;i++)
            {
                if(energymin>energy[i])
                {
                      min[j]=i;
                      energymin=energy[i];
                }
            }
            energy[min[j]]=maxenergy;
            energymin=maxenergy;
        }
    }
    else
    {
        for(i=0;i<15;i++)
            {
                if(energymin>energy[i])
                {
                      min[0]=i;
                      energymin=energy[i];
                }
            }
        min[1]=rand_diff(0,14);
        energy[min[0]]=maxenergy;
        energymin=maxenergy;
        for(i=0;i<15;i++)
            {
                if(energymin>energy[i])
                {
                      min[2]=i;
                      energymin=energy[i];
                }
            }

    }
    return (int *)&min[0];
}


/// --------------------------------------------------------------------
/// Select best structure in terms of hamming distance.
///
int* selected_structure(char*structure,char*StrArray,int *best_dist)
{
        int i,j;
        int distance=0;
        int max_distance=30000;
        int dist[4];
        int *best_dist_index=(int*)malloc(3*sizeof(int));
        for(i=0;i<4;i++)
        {
            for(j=0;j<=strlen(structure);j++)
            {
                if(StrArray[j+(i)*(strlen(structure)+1)]!=structure[j])
                {
                    distance++;
                }
            }
            dist[i]=distance;
            distance=0;
        }
    distance=max_distance;
    if(rand_diff(0,100)<89)
    {
        for(j=0;j<3;j++)
        {
            for(i=0;i<4;i++)
            {
                if(distance>dist[i])
                {
                      best_dist_index[j]=i;
                      distance=dist[i];
                      best_dist[j]=dist[i];
                }
            }
            dist[best_dist_index[j]]=max_distance;
            distance=max_distance;
        }

    }
    else
    {
        for(i=0;i<4;i++)
            {
                if(distance>dist[i])
                {
                      best_dist_index[0]=i;
                      distance=dist[i];
                      best_dist[0]=dist[i];
                }
            }
        best_dist_index[1]=rand_diff(0,3);
        best_dist[1]= dist[best_dist_index[1]];
        dist[best_dist_index[0]]=max_distance;
        distance=max_distance;
        for(i=0;i<4;i++)
            {
                if(distance>dist[i])
                {
                      best_dist_index[2]=i;
                      distance=dist[i];
                      best_dist[2]=dist[i];
                }
            }

    }
    return (int *)&best_dist_index[0];
}


/// --------------------------------------------------------------------
/// Evolutionary algorithm for designing an RNA sequence
/// that folds into a given target structure.
///
char * GeneticAl_eval15(char * structure,char*sequence,char* constrain_sequence)
{
 //   printf("%s*\n",sequence);
//    int size_structure=strlen(structure);
//    char* bestSequence=(char*)malloc((size_structure+1)*sizeof(char));
//     printf("%s\n",sequence);
//    strcpy(bestSequence,sequence);
   // #define MAX 500
    time_t end;
    int minimum_distance=30000;
    float energy[4];
    int size;
    int itr=1;
    int size_structure=strlen(structure);
    int i,j;
    int stem_select;
    int select_pair;
    int *cons_table;
    int *best_seq_index=NULL;
    int *best_dist=(int*)malloc(3*sizeof(int));
    int *best_dist_index=NULL;
    char* SeqArray=(char*)malloc (15*(size_structure+1)*sizeof(char));
    char* StrArray=(char*)malloc (4*(size_structure+1)*sizeof(char));
    char* bestSequence=(char*)malloc((size_structure+1)*sizeof(char));
    char* beststructure=(char*)malloc((size_structure+1)*sizeof(char));
    //sequence[size_structure]='\0';
   // sequence[size_structure+1]=char('91');
    int *starray=(int*)malloc(size_structure *3* sizeof(int));
    int *hparray=(int*)malloc(size_structure *2* sizeof(int));
    int *mlarray=(int*)malloc(size_structure *2* sizeof(int));
    char* bestSequence1=(char*)malloc ((size_structure+1)*sizeof(char));
    char* bestSequence2=(char*)malloc ((size_structure+1)*sizeof(char));
    char* beststructure1=(char*)malloc ((size_structure+1)*sizeof(char));
    char* beststructure2=(char*)malloc ((size_structure+1)*sizeof(char));
    int open_pra=open_prantesis(structure);
    //split_structure(&starray[0],&hparray[0],structure,&size);
    splite_structure_multiloop_unpair(starray,hparray,mlarray,structure,&size );
   //  printf("%s\n",sequence);
    strcpy(bestSequence,sequence);
    cons_table=constarin_table( constrain_sequence);

    set_constraint_sequence(bestSequence,cons_table);
    for(i=0;i<4;i++)
    {
        for(j=0;j<(size_structure);j++)
        {
            StrArray[i*(size_structure+1)+j]=structure[j];
        }
        StrArray[-1]='\0';
    }
    initialize_fold(strlen(bestSequence));
    energy[3] = fold(bestSequence, beststructure);
    GenerateNewSequence(&SeqArray[0],bestSequence,beststructure,&starray[0],&hparray[0],mlarray,&size);
    GenerateNewSequence(&SeqArray[0]+5*(size_structure+1),bestSequence,beststructure,&starray[0],&hparray[0],mlarray,&size);
    GenerateNewSequence(&SeqArray[0]+10*(size_structure+1),bestSequence,beststructure,&starray[0],&hparray[0],mlarray,&size);
    if(flag_constrain_seq==1&&target_structure_length==strlen(structure))
    {
       for(i=0;i<15;i++)
        {
            set_constraint_sequence(&SeqArray[0]+i*(size_structure+1),cons_table);
        }
    }

    for(itr=1;itr<iteration_size;itr++)
    {
        if(flag_constrain_energy!=1)
        {
            best_seq_index=selected_sequence(&SeqArray[0],structure);
        }
        else
        {

            best_seq_index=selected_sequence_constrain_energy(&SeqArray[0],structure,open_pra*global_avr_max_energy,open_pra*global_avr_min_energy);
            //best_seq_index=selected_sequence(&SeqArray[0],structure);
        }

        for(i=0;i<3;i++)
        {
            energy[i]=fold(&SeqArray[0]+best_seq_index[i]*(size_structure+1),&StrArray[0]+i*(size_structure+1));
        }
        strcpy(&StrArray[0]+3*(size_structure+1),beststructure);
        best_dist_index= selected_structure(structure,StrArray,&best_dist[0]);
        if(best_dist[0]==0 )
        {
            if(best_dist_index[0]!=3)
            {
                strcpy(bestSequence,(char*)&SeqArray[0]+best_seq_index[best_dist_index[0]]*(size_structure+1));
            }

            if(target_structure_length==strlen(structure))
            {
               // printf("%f\t%f\t%d\t%f\t%s\n",open_pra*global_avr_min_energy,open_pra*global_avr_max_energy,itr,energy[best_dist_index[0]],bestSequence);
                if(energy[best_dist_index[0]]>=open_pra*global_avr_min_energy&&energy[best_dist_index[0]]<=open_pra*global_avr_max_energy)
                {
                    free(best_dist);
                    best_dist=NULL;
                    free(bestSequence1);
                    bestSequence1=NULL;
                    free(bestSequence2);
                    bestSequence2=NULL;
                    free(beststructure1);
                    beststructure1=NULL;
                    free(beststructure2);
                    beststructure2=NULL;
                    free(beststructure);
                    beststructure=NULL;
                    free(StrArray);
                    StrArray=NULL;
                    free(SeqArray);
                    SeqArray=NULL;
                    free(starray);
                    starray=NULL;
                    free(hparray);
                    free(mlarray);
                    mlarray=NULL;
                    free_arrays();
                    free(best_seq_index);
                    best_seq_index=NULL;
                    free(best_dist_index);
                    best_dist_index=NULL;
                    free(cons_table);
                    return (char*)&bestSequence[0];
                }
                else
                {
                    if(energy[best_dist_index[0]]<open_pra*global_avr_min_energy)
                    {
                        stem_select=rand_diff(1,starray[0]);
                        if(starray[stem_select+2*size]==1)
                            stem_select++;
                        select_pair=rand_diff(1,starray[stem_select+size*2]);
                        bestSequence[starray[stem_select]-1+select_pair-1]='A';
                        bestSequence[starray[stem_select+size]-1+starray[stem_select+2*size]-1-select_pair+1]='U';
                        energy[best_dist_index[0]]=fold(bestSequence,beststructure);

                    }
                    if(energy[best_dist_index[0]]>open_pra*global_avr_max_energy)
                    {
                        stem_select=rand_diff(1,starray[0]);
                        if(starray[stem_select+2*size]==1)
                            stem_select++;
                        select_pair=rand_diff(1,starray[stem_select+size*2]);
                        bestSequence[starray[stem_select]-1+select_pair-1]='C';
                        bestSequence[starray[stem_select+size]-1+starray[stem_select+2*size]-1-select_pair+1]='G';
                        energy[best_dist_index[0]]=fold(bestSequence,beststructure);

                    }
                }
            }
            else
            {

                free(best_dist);
                best_dist=NULL;
                free(bestSequence1);
                bestSequence1=NULL;
                free(bestSequence2);
                bestSequence2=NULL;
                free(beststructure1);
                beststructure1=NULL;
                free(beststructure2);
                beststructure2=NULL;
                free(beststructure);
                beststructure=NULL;
                free(StrArray);
                StrArray=NULL;
                free(SeqArray);
                SeqArray=NULL;
                free(starray);
                starray=NULL;
                free(hparray);
                free(mlarray);
                mlarray=NULL;
                free_arrays();
                free(best_seq_index);
                best_seq_index=NULL;
                free(best_dist_index);
                best_dist_index=NULL;
                free(cons_table);
                return (char*)&bestSequence[0];
            }
        }
        time(&end);
        if(difftime(end,Global_Time)>Global_lenght&&Ittration_Flag<3)
        {
            free(best_dist);
            best_dist=NULL;
            free(bestSequence1);
            bestSequence1=NULL;
            free(bestSequence2);
            bestSequence2=NULL;
            free(beststructure1);
            beststructure1=NULL;
            free(beststructure2);
            beststructure2=NULL;
            free(beststructure);
            beststructure=NULL;
            free(StrArray);
            StrArray=NULL;
            free(SeqArray);
            SeqArray=NULL;
            free(starray);
            starray=NULL;
            free(hparray);
            free(mlarray);
            starray=NULL;
            free_arrays();
            free(best_seq_index);
            best_seq_index=NULL;
            free(best_dist_index);
            best_dist_index=NULL;
            Result_Flag=1;
            free(cons_table);
            return bestSequence;
        }

        if(minimum_distance>=best_dist[0])
        {
            if(best_dist_index[1]!=3)
            {
                strcpy(bestSequence1,&SeqArray[0]+best_seq_index[best_dist_index[1]]*(size_structure+1));
                strcpy(beststructure1,&StrArray[0]+best_dist_index[1]*(size_structure+1));
            }
            else
            {
                strcpy(bestSequence1,bestSequence);
                strcpy(beststructure1,beststructure);
            }

            if(best_dist_index[2]!=3)
            {
                strcpy(bestSequence2,&SeqArray[0]+best_seq_index[best_dist_index[2]]*(size_structure+1));
                strcpy(beststructure2,&StrArray[0]+best_dist_index[2]*(size_structure+1));
            }
            else
            {
                strcpy(bestSequence2,bestSequence);
                strcpy(beststructure2,beststructure);
            }
            if(best_dist_index[0]!=3)
            {
                strcpy(bestSequence,&SeqArray[0]+best_seq_index[best_dist_index[0]]*(size_structure+1));
                strcpy(beststructure,&StrArray[0]+best_dist_index[0]*(size_structure+1));
                minimum_distance=best_dist[0];
                energy[3]=energy[best_dist_index[0]];
            }
        }
        GenerateNewSequence(&SeqArray[0],bestSequence,beststructure,&starray[0],&hparray[0],mlarray,&size);
        GenerateNewSequence(&SeqArray[0]+5*(size_structure+1),bestSequence1,beststructure1,&starray[0],&hparray[0],mlarray,&size);
        GenerateNewSequence(&SeqArray[0]+10*(size_structure+1),bestSequence2,beststructure2,&starray[0],&hparray[0],mlarray,&size);
        free(best_seq_index);
        free(best_dist_index);
        if(flag_constrain_seq==1&&target_structure_length==strlen(structure))
        {
            for(i=0;i<15;i++)
            {
                set_constraint_sequence(&SeqArray[0]+i*(size_structure+1),cons_table);
            }
        }

    }

        free(best_dist);
        best_dist=NULL;
        free(bestSequence1);
        bestSequence1=NULL;
        free(bestSequence2);
        bestSequence2=NULL;
        free(beststructure1);
        beststructure1=NULL;
        free(beststructure2);
        beststructure2=NULL;
        free(beststructure);
        beststructure=NULL;
        free(StrArray);
        StrArray=NULL;
        free(SeqArray);
        SeqArray=NULL;
        free(starray);
        starray=NULL;
        free(hparray);
        free(mlarray);
        starray=NULL;
        free_arrays();
        free(cons_table);
        return (char*)&bestSequence[0];
}


/// --------------------------------------------------------------------
/// decomposition scheme to decompose the target structure into its sub-
/// structures. This decomposition is done in positions
/// where the multi-loops occur.
///
char * GeneticAl_recursive(char*structure,char*sequence,char* constrain_sequence)
{

    int *MultiLoopIndex=(int*)malloc(strlen(structure)*sizeof(int));
    int *MultiloopIndexArray=(int*)malloc(4*strlen(structure)*sizeof(int));

    char*bestSequence=NULL;
    char*SeqL=NULL;
    char*SeqR=NULL;
    char*new_sequence=NULL;
    char*new_sequence1=NULL;
    char*new_constrain_sequence=NULL;
    char*new_constrain_sequence1=NULL;
    char*new_sequence2=NULL;
    char*new_structure=NULL;
    char*new_structure1=NULL;
    char*merg_structure=NULL;
    char*merg_sequence=NULL;
    char*merg_constrain_sequence=NULL;
    splite_structure_multiloop(structure,MultiLoopIndex,MultiloopIndexArray);
    int  MinDistance=strlen(structure);
    int HalfSize=strlen(structure)/2;
    int IndexMin=1;
    int size=MultiLoopIndex[MultiLoopIndex[0]];
    int Spoint=-1;
    int Epoint=-1;
    int StemSize=-1;
    int i=0;
    if(MultiLoopIndex[0]!=1)
    {
        for (i=1;i<MultiLoopIndex[0];i++)
        {
            if(MinDistance >= abs(HalfSize-(MultiloopIndexArray[MultiLoopIndex[i]+size]-MultiloopIndexArray[MultiLoopIndex[i]])))
            {
                MinDistance= abs(HalfSize-(MultiloopIndexArray[MultiLoopIndex[i]+size]-MultiloopIndexArray[MultiLoopIndex[i]]));
                IndexMin=i;
            }
        }
        Spoint=MultiloopIndexArray[MultiLoopIndex[IndexMin]];
        Epoint=MultiloopIndexArray[MultiLoopIndex[IndexMin]+size];
        StemSize=MultiloopIndexArray[MultiLoopIndex[IndexMin]+2*size];
        if(MultiLoopIndex[0]!=2)
        {
            if(StemSize>=4)
            {
                new_structure=strpar(structure,Spoint-1,Epoint-1);
                new_sequence=strpar(sequence,Spoint-1,Epoint-1);
                new_constrain_sequence=strpar(constrain_sequence,Spoint-1,Epoint-1);
                SeqL=GeneticAl_recursive(new_structure,new_sequence,new_constrain_sequence);
                free(new_sequence);
                free(new_constrain_sequence);
                new_sequence=NULL;
                free(new_structure);
                new_structure=NULL;
                if(Result_Flag==1)
                {
                    bestSequence=malloc((strlen(sequence)+1)*sizeof(char));
                    strcpy(bestSequence,sequence);
                    free(SeqL);
                    SeqL=NULL;
                    free(MultiloopIndexArray);
                    MultiloopIndexArray=NULL;
                    free(MultiLoopIndex);
                    MultiLoopIndex=NULL;
                    return bestSequence;
                }
                new_structure=strpar(structure,0,Spoint-2);
                new_structure1=strpar(structure,Epoint,strlen(structure)-1);
                merg_structure=(char*)merg_string(new_structure,"((((...))))",new_structure1);
                free(new_structure);
                new_structure=NULL;
                free(new_structure1);
                new_structure1=NULL;
                new_sequence=strpar(sequence,0,Spoint-2);
                new_constrain_sequence=strpar(constrain_sequence,0,Spoint-2);
                new_sequence1=strpar(sequence,Epoint,strlen(structure)-1);
                new_constrain_sequence1=strpar(constrain_sequence,Epoint,strlen(structure)-1);
                merg_sequence=merg_string(new_sequence,"GGGGAAACCCC",new_sequence1);
                merg_constrain_sequence=merg_string(new_constrain_sequence,"GGGGAAACCCC",new_constrain_sequence1);

                free(new_constrain_sequence);
                free(new_sequence);
                new_sequence=NULL;
                free(new_sequence1);
                free(new_constrain_sequence1);
                new_sequence1=NULL;
                SeqR=GeneticAl_recursive(merg_structure ,merg_sequence,merg_constrain_sequence);
                free(merg_sequence);
                free(merg_constrain_sequence);
                merg_sequence=NULL;
                free(merg_structure);
                merg_structure=NULL;
                if(Result_Flag==1)
                {
                    bestSequence=malloc((strlen(sequence)+1)*sizeof(char));
                    strcpy(bestSequence,sequence);
                    free(SeqR);
                    SeqR=NULL;
                    free(MultiloopIndexArray);
                    MultiloopIndexArray=NULL;
                    free(MultiLoopIndex);
                    MultiLoopIndex=NULL;
                    return bestSequence;
                }
            }
            else if(StemSize==3)
            {
                new_structure=strpar(structure,Spoint-1,Epoint-1);
                new_sequence=strpar(sequence,Spoint-1,Epoint-1);
                new_constrain_sequence=strpar(constrain_sequence,Spoint-1,Epoint-1);
                merg_sequence=merg_string("G",new_sequence,"C");
                merg_constrain_sequence=merg_string("G",new_constrain_sequence,"C");
                merg_structure=merg_string("(",new_structure,")");
                free(new_sequence);
                free(new_constrain_sequence);
                new_sequence=NULL;
                free(new_structure);
                new_structure=NULL;
                SeqL=GeneticAl_recursive(merg_structure,merg_sequence,merg_constrain_sequence);
                free(merg_sequence);
                free(merg_constrain_sequence);
                merg_sequence=NULL;
                free(merg_structure);
                merg_structure=NULL;
                if(Result_Flag==1)
                {
                    bestSequence=malloc((strlen(sequence)+1)*sizeof(char));
                    strcpy(bestSequence,sequence);
                    free(SeqL);
                    SeqL=NULL;
                    free(MultiloopIndexArray);
                    MultiloopIndexArray=NULL;
                    free(MultiLoopIndex);
                    MultiLoopIndex=NULL;
                    return bestSequence;
                }
                new_structure=strpar(structure,0,Spoint-2);
                new_structure1=strpar(structure,Epoint,strlen(structure)-1);
                merg_structure=merg_string(new_structure,"((((...))))",new_structure1);
                free(new_structure);
                new_structure=NULL;
                free(new_structure1);
                new_structure1=NULL;
                new_sequence=strpar(sequence,0,Spoint-2);
                new_constrain_sequence=strpar(constrain_sequence,0,Spoint-2);
                new_sequence1=strpar(sequence,Epoint,strlen(structure)-1);
                new_constrain_sequence1=strpar(constrain_sequence,Epoint,strlen(structure)-1);
                merg_sequence=merg_string(new_sequence,"GGGGAAACCCC",new_sequence1);
                merg_constrain_sequence=merg_string(new_constrain_sequence,"GGGGAAACCCC",new_constrain_sequence1);
                free(new_sequence);
                free(new_constrain_sequence);
                new_sequence=NULL;
                free(new_sequence1);
                free(new_constrain_sequence1);
                new_sequence1=NULL;
                SeqR=GeneticAl_recursive(merg_structure ,merg_sequence,merg_constrain_sequence);
                free(merg_sequence);
                free(merg_constrain_sequence);
                merg_sequence=NULL;
                free(merg_structure);
                merg_structure=NULL;
                if(Result_Flag==1)
                {
                    bestSequence=malloc((strlen(sequence)+1)*sizeof(char));
                    strcpy(bestSequence,sequence);
                    free(SeqR);
                    SeqR=NULL;
                    free(MultiloopIndexArray);
                    MultiloopIndexArray=NULL;
                    free(MultiLoopIndex);
                    MultiLoopIndex=NULL;
                    return bestSequence;
                }
            }
            else if(StemSize==2)
            {
                new_structure=strpar(structure,Spoint-1,Epoint-1);
                new_sequence=strpar(sequence,Spoint-1,Epoint-1);
                new_constrain_sequence=strpar(constrain_sequence,Spoint-1,Epoint-1);
                merg_sequence=(char*)merg_string("GG",new_sequence,"CC");
                merg_constrain_sequence=(char*)merg_string("GG",new_constrain_sequence,"CC");
                merg_structure=(char*)merg_string("((",new_structure,"))");
                SeqL=GeneticAl_recursive(merg_structure,merg_sequence,merg_constrain_sequence);
                free(new_structure);
                new_structure=NULL;
                free(new_sequence);
                free(new_constrain_sequence);
                new_sequence=NULL;
                free(merg_sequence);
                free(merg_constrain_sequence);
                merg_sequence=NULL;
                free(merg_structure);
                merg_structure=NULL;
                if(Result_Flag==1)
                {
                    bestSequence=malloc((strlen(sequence)+1)*sizeof(char));
                    strcpy(bestSequence,sequence);
                    free(SeqL);
                    SeqL=NULL;
                    free(MultiloopIndexArray);
                    MultiloopIndexArray=NULL;
                    free(MultiLoopIndex);
                    MultiLoopIndex=NULL;
                    return bestSequence;
                }
                new_structure=strpar(structure,0,Spoint-2);
                new_structure1=strpar(structure,Epoint,strlen(structure)-1);
                merg_structure=merg_string(new_structure,"((((...))))",new_structure1);
                free(new_structure);
                new_structure=NULL;
                free(new_structure1);
                new_structure1=NULL;
                new_sequence=strpar(sequence,0,Spoint-2);
                new_constrain_sequence=strpar(constrain_sequence,0,Spoint-2);
                new_sequence1=strpar(sequence,Epoint,strlen(structure)-1);
                new_constrain_sequence1=strpar(constrain_sequence,Epoint,strlen(structure)-1);
                merg_sequence=merg_string(new_sequence,"GGGGAAACCCC",new_sequence1);
                merg_constrain_sequence=merg_string(new_constrain_sequence,"GGGGAAACCCC",new_constrain_sequence1);
                free(new_sequence);
                free(new_constrain_sequence);
                new_sequence=NULL;
                free(new_sequence1);
                free(new_constrain_sequence1);
                new_sequence1=NULL;
                SeqR=GeneticAl_recursive(merg_structure ,merg_sequence,merg_constrain_sequence);
                free(merg_sequence);
                free(merg_constrain_sequence);
                merg_sequence=NULL;
                free(merg_structure);
                merg_structure=NULL;
                if(Result_Flag==1)
                {
                    bestSequence=malloc((strlen(sequence)+1)*sizeof(char));
                    strcpy(bestSequence,sequence);
                    free(SeqR);
                    SeqR=NULL;
                    free(MultiloopIndexArray);
                    MultiloopIndexArray=NULL;
                    free(MultiLoopIndex);
                    MultiLoopIndex=NULL;
                    return bestSequence;
                }
            }
            else
            {
                new_structure=strpar(structure,Spoint-1,Epoint-1);
                new_sequence=strpar(sequence,Spoint-1,Epoint-1);
                new_constrain_sequence=strpar(constrain_sequence,Spoint-1,Epoint-1);
                merg_sequence=merg_string("GGG",new_sequence,"CCC");
                merg_constrain_sequence=merg_string("GGG",new_constrain_sequence,"CCC");
                merg_structure=merg_string("(((",new_structure,")))");
                free(new_sequence);
                free(new_constrain_sequence);
                new_sequence=NULL;
                free(new_structure);
                new_structure=NULL;
                SeqL=GeneticAl_recursive(merg_structure,merg_sequence,merg_constrain_sequence);
                free(merg_constrain_sequence);
                merg_sequence=NULL;
                free(merg_structure);
                merg_structure=NULL;
                if(Result_Flag==1)
                {
                    bestSequence=malloc((strlen(sequence)+1)*sizeof(char));
                    strcpy(bestSequence,sequence);
                    free(SeqL);
                    SeqL=NULL;
                    free(MultiloopIndexArray);
                    MultiloopIndexArray=NULL;
                    free(MultiLoopIndex);
                    MultiLoopIndex=NULL;
                    return bestSequence;
                }
                new_structure=strpar(structure,0,Spoint-2);
                new_structure1=strpar(structure,Epoint,strlen(structure)-1);
                merg_structure=merg_string(new_structure,"((((...))))",new_structure1);
                free(new_structure);
                new_structure=NULL;
                free(new_structure1);
                new_structure1=NULL;
                new_sequence=strpar(sequence,0,Spoint-2);
                new_constrain_sequence=strpar(constrain_sequence,0,Spoint-2);
                new_sequence1=strpar(sequence,Epoint,strlen(structure)-1);
                new_constrain_sequence1=strpar(constrain_sequence,Epoint,strlen(structure)-1);
                merg_sequence=merg_string(new_sequence,"GGGGAAACCCC",new_sequence1);
                merg_constrain_sequence=merg_string(new_constrain_sequence,"GGGGAAACCCC",new_constrain_sequence1);
                free(new_sequence);
                free(new_constrain_sequence);
                new_sequence=NULL;
                free(new_sequence1);
                free(new_constrain_sequence1);
                new_sequence1=NULL;
                SeqR=GeneticAl_recursive(merg_structure ,merg_sequence,merg_constrain_sequence);
                free(merg_sequence);
                free(merg_constrain_sequence);
                merg_sequence=NULL;
                free(merg_structure);
                merg_structure=NULL;
                if(Result_Flag==1)
                {
                    bestSequence=malloc((strlen(sequence)+1)*sizeof(char));
                    strcpy(bestSequence,sequence);
                    free(SeqR);
                    SeqR=NULL;
                    free(MultiloopIndexArray);
                    MultiloopIndexArray=NULL;
                    free(MultiLoopIndex);
                    MultiLoopIndex=NULL;
                    return bestSequence;
                }
            }
        }
        if(MultiLoopIndex[0]==2)
        {
            if(strlen(structure)>((Epoint-Spoint)+12))
            {
                bestSequence=GeneticAl_eval15(structure,sequence,constrain_sequence);
                //bestSequence=GeneticAl_recursive_hand(structure,sequence);
            }
            else
            {
                bestSequence=GeneticAl_eval15(structure,sequence,constrain_sequence);
            }
            free(MultiloopIndexArray);
            MultiloopIndexArray=NULL;
            free(MultiLoopIndex);
            MultiLoopIndex=NULL;
            return bestSequence;
        }
        else
        {
            if(StemSize>=4)
            {
                new_sequence=strpar(SeqR,0,Spoint-2);
                new_sequence1=strpar(SeqR,Spoint+10,strlen(SeqR)-1);
                merg_sequence=merg_string(new_sequence,SeqL,new_sequence1);
                free(new_sequence);
                new_sequence=NULL;
                free(new_sequence1);
                new_sequence1=NULL;
                bestSequence=GeneticAl_eval15(structure,merg_sequence,constrain_sequence);
                free(merg_sequence);
                merg_sequence=NULL;
                free(SeqL);
                SeqL=NULL;
                free(SeqR);
                SeqR=NULL;
                free(MultiloopIndexArray);
                MultiloopIndexArray=NULL;
                free(MultiLoopIndex);
                MultiLoopIndex=NULL;
                return bestSequence;
            }
            else if(StemSize==3)
            {
                new_sequence=strpar(SeqR,0,Spoint-2);
                new_sequence1=strpar(SeqR,Spoint+10,strlen(SeqR)-1);
                new_sequence2=strpar(SeqL,1,strlen(SeqL)-2);
                merg_sequence=merg_string(new_sequence,new_sequence2,new_sequence1);
                free(new_sequence);
                new_sequence=NULL;
                free(new_sequence1);
                new_sequence1=NULL;
                free(new_sequence2);
                new_sequence2=NULL;
                bestSequence=GeneticAl_eval15(structure,merg_sequence,constrain_sequence);

                free(merg_sequence);
                merg_sequence=NULL;
                free(SeqL);
                SeqL=NULL;
                free(SeqR);
                SeqR=NULL;
                free(MultiloopIndexArray);
                MultiloopIndexArray=NULL;
                free(MultiLoopIndex);
                MultiLoopIndex=NULL;
                return bestSequence;
            }
            else if(StemSize==2)
            {
                new_sequence=strpar(SeqR,0,Spoint-2);
                new_sequence1=strpar(SeqR,Spoint+10,strlen(SeqR)-1);
                new_sequence2=strpar(SeqL,2,strlen(SeqL)-3);
                merg_sequence=merg_string(new_sequence,new_sequence2,new_sequence1);
                free(new_sequence);
                new_sequence=NULL;
                free(new_sequence1);
                new_sequence1=NULL;
                free(new_sequence2);
                new_sequence2=NULL;
                bestSequence=GeneticAl_eval15(structure,merg_sequence,constrain_sequence);

                free(merg_sequence);
                merg_sequence=NULL;
                free(SeqL);
                SeqL=NULL;
                free(SeqR);
                SeqR=NULL;
                free(MultiloopIndexArray);
                MultiloopIndexArray=NULL;
                free(MultiLoopIndex);
                MultiLoopIndex=NULL;
                return bestSequence;
            }
            else
            {
                new_sequence=strpar(SeqR,0,Spoint-2);
                new_sequence1=strpar(SeqR,Spoint+10,strlen(SeqR)-1);
                new_sequence2=strpar(SeqL,3,strlen(SeqL)-4);
                merg_sequence=merg_string(new_sequence,new_sequence2,new_sequence1);
                free(new_sequence);
                new_sequence=NULL;
                free(new_sequence1);
                new_sequence1=NULL;
                free(new_sequence2);
                new_sequence2=NULL;
                bestSequence=GeneticAl_eval15(structure,merg_sequence,constrain_sequence);

                free(merg_sequence);
                merg_sequence=NULL;
                free(SeqL);
                SeqL=NULL;
                free(SeqR);
                SeqR=NULL;
                free(MultiloopIndexArray);
                MultiloopIndexArray=NULL;
                free(MultiLoopIndex);
                MultiLoopIndex=NULL;
                return bestSequence;
            }
        }
    }
    else
    {
        //bestSequence=GeneticAl_recursive_hand(structure,sequence);
        bestSequence=GeneticAl_eval15(structure,sequence,constrain_sequence);
        free(MultiloopIndexArray);
        MultiloopIndexArray=NULL;
        free(MultiLoopIndex);
        MultiLoopIndex=NULL;
        return bestSequence;
    }
}


/// --------------------------------------------------------------------
/// Reconstruct an initial RNA sequence which is compatible
/// with the given target structure.
///
char *GneticAl_final(char*structure,char*constrain_sequence)
{
    char* bestsequence=NULL;
    char*sequence=NULL;

    int size;
    int *starray=(int*)malloc(strlen(structure) *3* sizeof(int));
    int *hparray=(int*)malloc(strlen(structure) *2* sizeof(int));
    int *mlarray=(int*)malloc(strlen(structure) *2* sizeof(int));

    splite_structure_multiloop_unpair(starray,hparray,mlarray,structure,&size );
    sequence=initialize_multiloop_sequence(strlen(structure),&starray[0],&hparray[0],mlarray,&size);
    if(flag_constrain_energy==1)
    {
        char*temp_seq=(char*)malloc((strlen(structure)+1)*sizeof(char));
        //char*temp_str=(char*)malloc((strlen(structure)+1)*sizeof(char));
        int i;
        int open_pra=open_prantesis(structure);
        float energy;
        float temp_energy=0;
        float avrag_energy=open_pra*global_avr_min_energy+open_pra*global_avr_max_energy/2;
        for(i=1;i<1000*strlen(structure);i++)
        {
            energy=energy_of_struct(sequence,structure);
                if(abs(avrag_energy-temp_energy)>abs(avrag_energy-energy))
                {
                  temp_energy=energy;
                  strcpy(temp_seq,sequence);
                  if(energy>open_pra*global_avr_min_energy&&energy<open_pra*global_avr_max_energy)
                  {
                      break;
                  }
                }
            free(sequence);
            //sequence=initialize_multiloop_sequence(strlen(structure),&starray[0],&hparray[0],mlarray,&size);
            sequence=initial_RNAInvers(structure);
        }
        //free(sequence);
        strcpy(sequence,temp_seq);
        free(temp_seq);
        //free(temp_str);
    }
    free(starray);
    free(hparray);
    free(mlarray);
   bestsequence=GeneticAl_recursive(structure,sequence,constrain_sequence);
   // set_constraint_sequence(sequence,constrain_sequence);
    //bestsequence=GeneticAl_eval15(structure,sequence,constrain_sequence);

    free(sequence);
    return bestsequence;

}
