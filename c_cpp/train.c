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

int main(int argc, char *argv[])
{
    /*
        ./train iteration model_init.txt seq_model_01.txt model_01.txt
        ./test modellist.txt testing_data.txt result.txt
    */
    if (argc != 5) {
        printf("Usage:%s [iteration_time] [init model] [sequence model] [output model]\n(Hint:you should specify that as file path)\n",
               argv[0]);
        exit(1);
    }
    int iteration = 0;
    sscanf(argv[1], "%d", &iteration);
    HMM hmm;

    loadHMM(&hmm, argv[2]);
    FILE *sequence_file = NULL;
    // if ((sequence_file = fopen(argv[3], "r")) == NULL) {
    //     printf("ERROR: can't read the sequence file %s", argv[3]);
    //     exit(1);
    // }
    // fflush(NULL);
    char y[MAX_SEQ]; // MAX_SEQ should be T max, maybe?
    double alpha[MAX_STATE][MAX_SEQ];
    double beta[MAX_STATE][MAX_SEQ];
    double gamma[MAX_STATE][MAX_SEQ];
    double epsilon[MAX_STATE][MAX_STATE][MAX_SEQ];

    double pi_new[MAX_STATE];            //initial prob.
    double a_new[MAX_STATE][MAX_STATE];  //transition prob.
    double b_new[MAX_OBSERV][MAX_STATE]; //observation prob.
    double sum_epsilon[MAX_STATE][MAX_STATE];
    double sum_gamma[MAX_STATE];
    double sum_gamma_tminus1[MAX_STATE];
    double sum_condition_gamma[MAX_OBSERV][MAX_STATE];
    double sum_gamma_init[MAX_STATE];
    for (int i = 0; i < iteration; i++) {
        int total_update = 0;
        memset(y, 0, sizeof(y));
        memset(sum_epsilon, 0, sizeof(sum_epsilon));
        memset(sum_condition_gamma, 0, sizeof(sum_condition_gamma));
        memset(sum_gamma, 0, sizeof(sum_gamma));
        memset(sum_gamma_tminus1, 0, sizeof(sum_gamma_tminus1));
        memset(sum_gamma_init, 0, sizeof(sum_gamma_init));
        sequence_file = open_or_die(argv[3], "r");
        while (fscanf(sequence_file, "%s", y) == 1) {
            int T = strlen(y);
            memset(gamma, 0, sizeof(gamma));
            memset(alpha, 0, sizeof(alpha));
            memset(beta, 0, sizeof(beta));
            memset(epsilon, 0, sizeof(epsilon[0][0][0]) * MAX_STATE * MAX_STATE * MAX_SEQ);
            for (int i = 0; i < hmm.state_num; i++) {
                //Forward
                //{\alpha _{i}(1)=\pi _{i}b_{i}(y_{1}),}
                alpha[i][0] = hmm.initial[i] * hmm.observation[y[0] - 'A'][i];
            }
            //{\alpha _{i}(t+1)=b_{i}(y_{t+1})\sum _{j=1}^{N} \alpha _{j}(t)a_{ji}.}
            for (int t = 0; t < T - 1; t++) {
                for (int i = 0; i < hmm.state_num; i++) {
                    double sum_alpha = 0.0;
                    for (int j = 0; j < hmm.state_num; j++) {
                        //transition[MAX_STATE][MAX_STATE];
                        sum_alpha += alpha[j][t] * hmm.transition[j][i];
                    }
                    alpha[i][t + 1] = sum_alpha * hmm.observation[y[t + 1] - 'A'][i];
                }
            }
            //backward
            /*{ \beta _{i}(T)=1,}
            {\beta _{i}(t)=\sum _{j=1}^{N}\beta _{j}(t+1)a_{ij}b_{j}(y_{t+1}).}
            */
            for (int i = 0; i < hmm.state_num; i++) {
                beta[i][T - 1] = 1.0;
            }
            for (int t = T - 2; t >= 0; t--) {
                for (int i = 0; i < hmm.state_num; i++) {
                    for (int j = 0; j < hmm.state_num; j++) {
                        beta[i][t] += beta[j][t + 1] * hmm.transition[i][j] *
                                      hmm.observation[y[t + 1] - 'A'][j];
                    }
                    //beta[i][t] = sum_alpha * (&model).observation[y[0] - 'A'][t];
                }
            }
            //update
            //gamma = {\frac {\alpha _{i}(t)\beta _{i}(t)}{\sum _{j=1}^{N}\alpha _{j}(t)\beta _{j}(t)}},}
            //epsilon = {\frac {\alpha _{i}(t)a_{ij}\beta _{j}(t+1)b_{j}(y_{t+1})}
            //{\sum _{i=1}^{N}\sum _{j=1}^{N}\alpha _{i}(t)a_{ij}\beta _{j}(t+1)b_{j}(y_{t+1})}},}
            double tmp, tmp2;
            for (int t = 0; t < T; t++) {
                tmp = tmp2 = 0.0;
                for (int j = 0; j < hmm.state_num; j++) {
                    //\alpha _{j}(t)\beta _{j}(t)
                    tmp += alpha[j][t] * beta[j][t];
                }
                for (int i = 0; i < hmm.state_num; i++) {
                    for (int j = 0; j < hmm.state_num; j++) {
                        //\alpha _{i}(t)a_{ij}\beta _{j}(t+1)b_{j}(y_{t+1}
                        tmp2 += alpha[i][t] * hmm.transition[i][j] * beta[j][t + 1] *
                                hmm.observation[y[t + 1] - 'A'][j];
                    }
                }
                for (int i = 0; i < hmm.state_num; i++) {
                    gamma[i][t] = (alpha[i][t] * beta[i][t]) / tmp;
                    for (int j = 0; j < hmm.state_num; j++) {
                        epsilon[i][j][t] = (alpha[i][t] * hmm.transition[i][j] * beta[j][t + 1] *
                                            hmm.observation[y[t + 1] - 'A'][j]) /
                                           tmp2;
                    }
                }
            }
            /*
            a_{ij}^{*}={\frac {\sum _{t=1}^{T-1}\xi _{ij}(t)}{\sum _{t=1}^{T-1}\gamma _{i}(t)}},}
            */
            for (int i = 0; i < hmm.state_num; i++) {
                for (int t = 0; t < T - 1; t++) {
                    sum_gamma_tminus1[i] += gamma[i][t];
                    for (int j = 0; j < hmm.state_num; j++) {
                        sum_epsilon[i][j] += epsilon[i][j][t];
                    }
                }
            }
            //because of that hw instruction say that it is approaximately same.
            for (int i = 0; i < hmm.state_num; i++) {
                for (int t = 0; t < T; t++) {
                    sum_gamma[i] += gamma[i][t];
                    for (int v_k = 0; v_k < hmm.observ_num; v_k++) {
                        if (v_k == (y[t] - 'A')) {
                            sum_condition_gamma[v_k][i] += gamma[i][t];
                        }
                    }
                }
            }
            for (int i = 0; i < hmm.state_num; i++) {
                sum_gamma_init[i] += gamma[i][0];
            }
            total_update++;
            memset(y, 0, sizeof(y));
        }
        // memset(pi_new, 0, sizeof(pi_new));
        for (int i = 0; i < hmm.state_num; i++) {
            hmm.initial[i] = sum_gamma_init[i] / total_update;
        }
        for (int i = 0; i < hmm.state_num; i++) {
            for (int v_k = 0; v_k < hmm.observ_num; v_k++) {
                hmm.observation[v_k][i] = sum_condition_gamma[v_k][i] / sum_gamma[i];
            }
        }

        for (int i = 0; i < hmm.state_num; i++) {
            for (int j = 0; j < hmm.state_num; j++) {
                hmm.transition[i][j] = sum_epsilon[i][j] / sum_gamma_tminus1[i];
            }
        }
        fclose(sequence_file);
        printf("iteration: %d times\n", i + 1);
        fflush(NULL);
    }
    FILE *w;
    w = open_or_die(argv[4], "w");
    // if ((w = fopen(argv[4], "w")) == NULL) {
    //     printf("ERROR: can't write the model file %s", argv[4]);
    //     exit(1);
    // }
    // fflush(NULL);
    dumpHMM(w, &hmm);
    return 0;
}
