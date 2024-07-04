
#include "snakehlpr.h"
#include "param.h"



char lvl [HIGHT][WIDTH];
int sx = WIDTH/2;
int sy = HIGHT/2;
int rundir= 0;
int slength = 1;
int lvlindicF=(WIDTH+HIGHT)/2*(LEVEL*0.06);
int lvlindicW=(WIDTH+HIGHT)/2*(LEVEL*0.06);
bool run=1;
bool win=0;
char info[WIDTH+50];



void loadlvl(){
    for(int i=0;i<HIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            if(i==0 ||i==(HIGHT-1)){
                lvl[i][j]= '#';
            }
            else if(j==0 || j==(WIDTH-1)){
                lvl[i][j]= '#';
            }
            else{
            lvl[i][j]= EMPTY;
            }
        }
    }
}


void printS(){
    lvl[sy][sx]=SNAKEH;
}


void createF(int f){

    for(int i=1; i<=f;i++){
        
        //srand(time(NULL));
        int x = rand()% WIDTH+1;
        int y = rand()% HIGHT+1;
        if(lvl[y][x]==EMPTY)
            lvl[y][x]=FOOD;
        else
            i--;
    }  

}


void createW(int w){
    for(int i=1; i<=w; i++){
        //srand(time(NULL));
        int wlength = (rand()%(int)((WIDTH+HIGHT)/2*0.4))+2;
        int or = rand()%2+1;
        int dir = rand()%2+1;
        int x = rand()% WIDTH+1;
        int y = rand()% HIGHT+1;
        
        if(lvl[y][x]==EMPTY && (x<(WIDTH/2)*0.9 || x>(WIDTH/2)*1.1) && (y<(HIGHT/2)*0.9 || y>(HIGHT/2)*1.1)){
            for(int j=0; j<=wlength-1;j++){

                //Laufrichtung der Mauer
                if (dir>1)
                    j=j*(-1);
                
                //Orientierung der Mauer
                if (or>1){
                    //Aufhören mit Mauerbau, wenn in geschütztem Bereich
                    if(!(lvl[y+j][x]==EMPTY && (y+j<(HIGHT/2)*0.9 || y+j>(HIGHT/2)*1.1)))
                        break;
                    else
                        lvl[y+j][x]=WALL;
                }
                else{
                     //Aufhören mit Mauerbau, wenn in geschütztem Bereich
                    if(!(lvl[y][x+j]==EMPTY && (x+j<(WIDTH/2)*0.9 || x+j>(WIDTH/2)*1.1)))
                        break;
                    else
                    lvl[y][x+j]=WALL;
                }
                //Umkehren der Negation, das for-Schleife weiterlaufen kann
                if (dir>1)
                    j=j*(-1);
            }
        }

        else
            i--;

    }
}




void printlvl(){
    char sym;
    
    for(int i=0;i<HIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            if(lvl[i][j]=='A'){
                lvl[i][j]=EMPTY;
                sym = lvl[i][j];
                printf("%c",sym);
            }
            else if('A'<(lvl[i][j]) && (lvl[i][j]) <='z'){
                char temp = lvl[i][j];
                lvl[i][j]=SNAKEB;
                sym = lvl[i][j];
                printf("%c",sym);
                lvl[i][j]=temp-1;
            }
            else{
                
            sym = lvl[i][j];
            printf("%c",sym);
            }
        }
        printf("\n");
    }
    printf("Score: %i\n\n", slength-1);
}



void popinfo(int il){
    for(int i = 0; i<il;i++){
        info[i]='.';
    }
}

void printinfo(){
    for(int i = 0; i<WIDTH-1;i++){
        printf("%c",info[i]);
    }
    printf("\n");
}


void shiftinfo(int il){
    for(int i=0; i<il-2;i++){
        info[i]=info[i+1];
    }
}



void finfo(){
    //debug info[WIDTH+1]='A';
    int infolength=strlen(info);
    char messagep1[]= "NamNam, yummy! Still x";
    messagep1[strlen(messagep1)-1]=(char)(lvlindicF+'0');

    char messagep2[]= " foods remaining.";
    int mlength=strlen(messagep1)+strlen(messagep2);
    char message[mlength];
    strcpy(message,messagep1);
    for(int i=strlen(messagep1);i<mlength;i++){
        message[i]=messagep2[i-strlen(messagep1)];
    }

    
    for(int i= WIDTH;i<mlength+WIDTH;i++){
        info[i]=message[i-WIDTH];
    }

}





int status(int sy, int sx){
    if(lvl[sy][sx]== EMPTY || lvl[sy][sx]==FOOD){
        if(lvl[sy][sx]==FOOD){
            slength++;
            lvlindicF--;
            finfo(lvlindicF);
        }
        if(lvlindicF<=0){
            win=1;
            return 0;
        }
        else
            return 1;
    }
    else
        return 0;
}


void moveS(int dir){
    switch (dir)
    {
    case 0:
        lvl[sy][sx]='A'+slength;
        sx++;
        run=status(sy, sx);
        lvl[sy][sx]=SNAKEH;
        break;

    case 1:
        lvl[sy][sx]='A'+slength;
        sy++;
        run=status(sy, sx);
        lvl[sy][sx]=SNAKEH;
        break;

    case 2:
        lvl[sy][sx]='A'+slength;
        sx--;
        run=status(sy, sx);
        lvl[sy][sx]=SNAKEH;
        break;

    case 3:
        lvl[sy][sx]='A'+slength;
        sy--;
        run=status(sy, sx);
        lvl[sy][sx]=SNAKEH;
        break;
    
    default:
        break;
    }
}



void checkkinput(){
    if(kbhit()){
            char k=getchar();
            
            switch(k){
                case 'w':
                if(rundir!=1)
                    rundir=3;
                break;

                case 's':
                if(rundir!=3)
                    rundir=1;
                break;

                case 'a':
                if(rundir!=0)
                    rundir=2;
                break;

                case 'd':
                if(rundir!=2)
                    rundir=0;
                break;

                case 'q':
                run = 0;
                break;
            } 
        }

}




int main()
{
    srand(time(NULL));
    rundir=rand()%3;
    clear();
    loadlvl();
    popinfo(WIDTH+50);
    int infolength=strlen(info);
    createF(lvlindicF);
    createW(lvlindicW);
    printS();
    
    while (run)
    {
        clear();
        printinfo();
        printlvl();
        mssleep(300);
        moveS(rundir);
        checkkinput();
        shiftinfo(infolength);
        
    }
    
    clear();
    int lvlnum= LEVEL;
    if(win)
        printf("\n\n\n!!!YOU WIN!!!\n\n\nCongrats on completing Level %i\n\n",lvlnum);
    else
        printf("\n\n\nGAME OVER\nGAME OVER\nGAME OVER\n\n\n");
    
    return 0;
}