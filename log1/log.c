#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FOR(i, b, e) for((i)=(b); (i)<(e); ++i)
typedef unsigned int uint;

enum {DAY=0, MAX = 10000};

FILE *logfp, *infp, *outfp;
uint temp[MAX] = {0, };
uint logLine, inpLine, recL;
uint i, j, k, cnt;
uint d_beg, t_beg, d_end, t_end;
uint** logTable = NULL;
uint* eleSz = NULL;

void setTable();
void findNum();

int main()
{
    logfp = fopen("syslog.txt", "rb");
    infp = fopen("log.inp", "rb");
    outfp = fopen("log.out", "wb");

    fscanf(logfp, "%u", &logLine);
    fscanf(infp, "%u", &inpLine);

    setTable();
    findNum();

    fclose(outfp);
    fclose(infp);
    fclose(logfp);

    FOR(i, 0, logLine){
        free(logTable[i]);
    }
    free(logTable);
    free(eleSz);
    return EXIT_SUCCESS;
}

void setTable()
{
    logTable = (uint**)malloc(sizeof(uint*)*logLine);
    eleSz = (uint*)calloc(logLine, sizeof(uint));

    FOR(i, 0, logLine){
        for(j=0; !(fscanf(logfp, "%u", temp+j)!=1); ++j)
            if(temp[j] == 0) break;
        eleSz[i] = j;
        recL = j+1;
        logTable[i] = (uint*)malloc(sizeof(uint)*recL);
        FOR(j, 0, recL)
            logTable[i][j] = temp[j];
    }
}

void findNum()
{
    cnt = 0;
    FOR(i, 0, inpLine){
        fscanf(infp, "%u%u%u%u", &d_beg, &t_beg, &d_end, &t_end);
        FOR(j, 0, logLine){
            if((d_beg == d_end) && (logTable[j][DAY] == d_beg)){
                cnt+=eleSz[j]-1;
                FOR(k, 1, eleSz[j])
                    if (logTable[j][k]<t_beg || logTable[j][k]>t_end)
                        cnt--;
            }
            else if(logTable[j][DAY] > d_beg && logTable[j][DAY] < d_end){
               cnt+=eleSz[j]-1;
            }
            else if(logTable[j][DAY] == d_beg){
                cnt+=eleSz[j]-1;
                FOR(k, 1, eleSz[j])
                    if(logTable[j][k]<t_beg) cnt--;
            }
            else if(logTable[j][DAY] == d_end){
                cnt+=eleSz[j]-1;
                FOR(k, 1, eleSz[j])
                    if(logTable[j][k]>t_end) cnt--;
            }
        }
        if(i < inpLine - 1) fprintf(outfp, "%u\n", cnt);
        else fprintf(outfp, "%u", cnt);
        cnt = 0;
    }
}
