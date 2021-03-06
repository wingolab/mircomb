/*
 * pearson: calculates Pearson's r and t-value
 *
 * Pau Erola <pauerola@gmail.com>
 * CIBEREHD - Plataforma de bioinformatica
 * September 2014
 *
 */

#include <R.h>
#include <Rdefines.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void pearson(double *X, double *Y, int *pnrx,  int *pnry, int *pnc, double *r, double *t)
{
    double *sX;     // sum of X
    double *sY;     // sum of Y
    double *sX2;    // sum of X^2
    double *sY2;    // sum of Y^2
    double **sXY;   // sum of X*Y

    double sqrtN2;

    int i,j,k;
    int Nrx,Nry,Nc;
    
    Nrx=pnrx[0]; // number of rows (vectors) in matrix X
    Nry=pnry[0]; // number of rows (vectors) in matrix Y
    Nc=pnc[0];   // number of pairs per vector

    // memory allocation
    sX = (double *) calloc(1,Nrx*sizeof(double));    
    sY = (double *) calloc(1,Nry*sizeof(double));    
    sX2 = (double *) calloc(1,Nrx*sizeof(double));    
    sY2 = (double *) calloc(1,Nry*sizeof(double));    
    sXY = (double **) malloc(Nrx*sizeof(double*));    
    for (i=0;i<Nrx;i++) 
        sXY[i] = (double *) calloc(1,Nry*sizeof(double));    
    
    // sum of X and X^2
    for (i=0;i<Nrx;i++) {
        for (k=0;k<Nc;k++) {
            sX[i] = sX[i] + X[i*Nc+k];
            sX2[i] = sX2[i] + (X[i*Nc+k] * X[i*Nc+k]);
        }
    }

    // sum of Y and Y^2
    for (j=0;j<Nry;j++) {
        for (k=0;k<Nc;k++) {
            sY[j] = sY[j] + Y[j*Nc+k];
            sY2[j] = sY2[j] + (Y[j*Nc+k] * Y[j*Nc+k]);
        }
    }

    // sum of X*Y
    for (i=0;i<Nrx;i++) {
        for (j=0;j<Nry;j++) {
            for (k=0;k<Nc;k++) {
                sXY[i][j] = sXY[i][j] + (X[i*Nc+k] * Y[j*Nc+k]);
            }
        }
    }
    
    sqrtN2 = sqrt((double)(Nc-2));
    for (i=0;i<Nrx;i++) {
        for (j=0;j<Nry;j++) {
            // Pearson's r
            r[i*Nry+j] = (Nc*sXY[i][j] - (sX[i]*sY[j])) / ( sqrt(Nc*sX2[i] - (sX[i]*sX[i])) * sqrt(Nc*sY2[j] - (sY[j]*sY[j])) );
            // t-value
            t[i*Nry+j] = sqrtN2 * r[i*Nry+j] / sqrt( (double)1.f - (r[i*Nry+j]*r[i*Nry+j]) );
        }
    }
    
    // free memory allocated
    free(sX);
    free(sY);
    free(sX2);
    free(sY2);
    for (i=0;i<Nrx;i++) 
        free(sXY[i]);
    free(sXY);
    
}

