/***********************************
* student ID: R07922009
* name: kuoteng ding
* compile:
* execute: 
* style with astyle:
    --style=linux --indent=spaces --convert-tabs --lineend=linux --formatted --recursive --max-code-length=80
* description:
* sample output:
* sample output:
* last edited date:2019/04/02
*************************************/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "hmm.h"

#define MAX_HMM 30
const double eps =  1e-8;

int main(int argc, char *argv[])
{
    //./test modellist.txt testing_data.txt result.txt
    if (argc != 4) {
        printf("Usage:%s [model list file] [testing data] [result file]\n(Hint:you should specify that as file path)\n",
               argv[0]);
        exit(1);
    }
    HMM load_hmms[MAX_HMM];
    int load_num;
    load_num = load_models(argv[1], load_hmms, MAX_HMM); //5??? TODO:ask TA
    FILE *modellist = NULL;
    // if ((modellist = fopen(argv[2], "r")) == NULL) {
    //     printf("ERROR: can't read the modellist data %s", argv[2]);
    //     exit(1);
    // }
    modellist = open_or_die(argv[1], "r");
    int trace = 0;
    char model_name_list[MAX_HMM][100000]; //row major
    memset(model_name_list[0], 0, sizeof(model_name_list[0]));
    // while (fgets(model_name_list[trace], sizeof(model_name_list[trace]),
    //              modellist)) {
    while (fscanf(modellist, "%s", model_name_list[trace]) == 1) {
        printf("loaded file: %s\n", model_name_list[trace]);
        trace++;
        memset(model_name_list[trace], 0, sizeof(model_name_list[trace]));
    }
    fclose(modellist);
    fflush(NULL);
    printf("--------------\nyou have loaded %d models\n", load_num);
    FILE *test_data = NULL;
    test_data = open_or_die(argv[2], "r");
    // if ((test_data = fopen(argv[2], "r")) == NULL) {
    //     printf("ERROR: can't read the modellist data %s", argv[2]);
    //     exit(1);
    // }
    char y[MAX_SEQ];
    memset(y, 0, sizeof(y));
    double delta[MAX_SEQ][MAX_STATE];
    FILE *w = NULL;
    w = open_or_die(argv[3], "w");
    // if ((w = fopen(argv[3], "w")) == NULL) {
    //     printf("ERROR: can't write the model data %s", argv[3]);
    //     exit(1);
    // }
    // while(fgets(input, sizeof(input), test_data)) {
    int updatetime = 0;
    while (fscanf(test_data, "%s", y)==1) {
        int T = strlen(y);
        if(updatetime++ == 0) {
        printf("line:%s\n",y);

        }
        double final_max = 0.0;
        int final_model = -1;
        memset(delta, 0, sizeof(delta));
        for (int hmm_index = 0; hmm_index < load_num; hmm_index++) {
            for (int i = 0; i < load_hmms[hmm_index].state_num; i++) {
                delta[0][i] = load_hmms[hmm_index].initial[i] *
                              load_hmms[hmm_index].observation[y[0] - 'A'][i];
                // printf("a = %lf\n",delta[0][i]);
            }
            double tmp;
            double max;
            for (int t = 1; t < T; t++) {
                for (int j = 0; j < load_hmms[hmm_index].state_num; j++) {
                    delta[t][j] = 0.0;
                    for (int i = 0; i < load_hmms[hmm_index].state_num; i++) {
                        tmp = delta[t - 1][i] * load_hmms[hmm_index].transition[i][j];
                        if ( tmp > delta[t][j]) {
                            delta[t][j] = tmp;
                        }
                    }
                    delta[t][j] *= load_hmms[hmm_index].observation[y[t] - 'A'][j];
                }
            }
            max = delta[T - 1][0];
            for (int i = 1; i < load_hmms[hmm_index].state_num; i++) {
                if (max < delta[T - 1][i]) {
                    max = delta[T - 1][i];
                }
            }
            if (final_max < max) {
                final_max = max;
                final_model = hmm_index;
            }
        }
        if (final_model == -1) {
            printf("the recursive procedure failed\n");
            exit(1);
        }
        // fprintf(stdout, "%s\t%lf\n", model_name_list[final_model], final_max);
        fprintf(w, "%s\t%lf\n", model_name_list[final_model], final_max);
    }

    /*FILE *fpwa = open_or_die( "acc.txt", "w");
    fprintf(fpwa, "%f", (float)hit / (float)data_count);
    fclose(fpa);
    fclose(fpwa);*/

    //V_{1,k}&=&\mathrm {P} {\big (}y_{1}\ |\ k{\big )}\cdot \pi _{k}
    //V_{t,k}&=&\max _{x\in S}\left(\mathrm {P} {\big (}y_{t}\ |\ k{\big )}\cdot a_{x,k}\cdot V_{t-1,x}\right)
    return 0;
}
