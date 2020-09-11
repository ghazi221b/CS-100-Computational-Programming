#include <iostream>
#include <conio.h>
#include <iomanip>
#include <cstdlib>
#include "rlutil.h"
#include <fstream>
using namespace std;

void fileout(int highscore)
{//stores value of highscore in file
    ofstream outfile;
    outfile.open("highscore.txt");
    if(outfile.fail())
    {
        cout<<"failure"<<endl;
    }
    else
        outfile<<highscore;
        outfile.close();

}
int filein()
{//gets value of file at the beginning
    int highsc;
    ifstream infile;
    infile.open("highscore.txt");

    infile>>highsc;
    infile.close();
    return highsc;


}
void turner(int grid[4][4])
{
    //turners 90 degree clockwise
    int temp[4][4]={0};
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            temp[j][3-i]=grid[i][j];
        }
    }
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            grid[i][j]=temp[i][j];
        }

    }
}
void copygrid(int grid[4][4],int undo[4][4])
{
    //makes a copy of the grid before the command for undo function
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            undo[i][j]=grid[i][j];
        }
    }
}
void reversecopygrid(int grid[4][4],int undo[4][4])
{
    //takes the already made undo copy and turns that into current grid
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            grid[i][j]=undo[i][j];
        }
    }
}
int mirrorcounter(int grid[4][4],int undo[4][4])
{
    //sees if the grid has changed at all after the wasd commands
    int counter=0;

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(grid[i][j]==undo[i][j])
            {
                counter++;
            }
        }
    }
    return counter;

}


int checker(int grid[4][4])
{
    //checks for victory
    int zerocounter=0;
    for(int i=0;i<4;i++)
    {
        for(int j=0; j<4;j++)
        {
            if(grid[i][j]==2048)
            {
                return 1;
            }
        }
    }
    //checks for any zeros
    for(int i=0;i<4;i++)
    {
        for(int j=0; j<4;j++)
        {
            if(grid[i][j]==0)
            {
                zerocounter++;
            }
        }
    }
    if(zerocounter>0)
        return 2;
        //checks for same numbers near each other
    else if(zerocounter==0)
    {
           for(int i=0;i<4;i++)
    {
        for(int j=0; j<4;j++)
        {
            if(grid[i][j]==grid[i+1][j] && (i+1)<4)
                return 2;

            else if(grid[i][j]==grid[i][j+1] && (j+1)<4)
                return 2;
            else if(grid[i][j]==grid[i-1][j] && (i-1)>0)
                return 2;

            else if(grid[i][j]==grid[i][j-1] && (j-1)>0)
                return 2;

        }
    }

    }

        return 0;


}

void moveup(int grid[4][4])
{
    //just moves everything up
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(grid[i][j]==0)
            {
                for(int k=i+1;k<4;k++)
                {
                    if(grid[k][j]!=0)
                    {
                        grid[i][j]=grid[k][j];
                        grid[k][j]=0;
                        break;
                    }

                }
            }
        }
    }




}
void add(int grid[][4],int s,int &total)
{//adds the same numbers
    for(int d=0;d<4;d++)

    {for(int i=0;i<s;i++)
    {
        if(grid[i][d]==grid[i+1][d] && (i+1)<4)
        {
            grid[i][d]+=grid[i+1][d];
            grid[i+1][d]=0;
            total+=grid[i][d];
            moveup(grid);
        }
    }
    }

}
void zerogrid(int grid[4][4],int &total)
{//makes grid and score zero
    for(int i=0; i<4; i++)
    {
        for(int j=0;j<4;j++)
        {grid[i][j]=0;
        }
    }
    total=0;



}
int gamestartfirst()
{//randomly selects a coordinate
    int d1 = rand() % 4 + 0;
    return d1;
}
void starttile(int grid[4][4])
{
//randommly places 2 in any 2 places
int a,b,c,d;
  do{
    a=gamestartfirst();
    b=gamestartfirst();
    c=gamestartfirst();
    d=gamestartfirst();
    }while(a==c && b==d);

     grid[a][b]={2};
     grid[c][d]={2};

}

void printgrid(int grid[4][4],int highscore,int total)
{   //Main display function that shows the game which user interacts with
    rlutil::setColor(12);
    cout<<"\n\n\n           \t\t\t\t  THE 2048 GAME"<<endl;
    cout<<"     \t\t\t\t\t   TOTAL SCORE   \t\tHIGH SCORE"<<endl;

    cout<<setw(50)<<total<<"                           "<<highscore<<endl;
    for(int i=0; i<4; i++)
    {

        cout<<"\n\t\t\t\t|---------|---------|---------|---------|\n"<<endl;
        cout<<"\t\t\t\t";
        for(int j=0;j<4;j++)
        {


            if(grid[i][j]==0)
               {
                   cout<<"|";


                cout<<setw(5)<<" "<<"    ";
               }
            else if(grid[i][j]==2)
               {
                    cout<<"|";
                    rlutil::setColor(14);
                    cout <<setw(5)<< grid[i][j] << "    ";
                    rlutil::setColor(12);
               }

            else if(grid[i][j]==4)
               {
                    cout<<"|";
                    rlutil::setColor(15);
                    std::cout <<setw(5)<< grid[i][j] << "    ";
                    rlutil::setColor(12);}
            else if(grid[i][j]==8)
               {
                    cout<<"|";
                    rlutil::setColor(13);
                    std::cout <<setw(5)<< grid[i][j] << "    ";
                    rlutil::setColor(12);}
            else if(grid[i][j]==16)
               {
                    cout<<"|";
                    rlutil::setColor(10);
                    std::cout <<setw(5)<< grid[i][j] << "    ";
                    rlutil::setColor(12);}
            else if(grid[i][j]==32)
               {
                    cout<<"|";
                    rlutil::setColor(5);
                    std::cout <<setw(5)<< grid[i][j] << "    ";
                    rlutil::setColor(12);}
            else if(grid[i][j]==64)
               {
                    cout<<"|";
                    rlutil::setColor(6);
                    std::cout <<setw(5)<< grid[i][j] << "    ";
                    rlutil::setColor(12);}
            else if(grid[i][j]==128)
               {
                    cout<<"|";
                    rlutil::setColor(11);
                    std::cout <<setw(5)<< grid[i][j] << "    ";
                    rlutil::setColor(12);}
            else if(grid[i][j]==256)
               {
                    cout<<"|";
                    rlutil::setColor(8);
                    std::cout <<setw(5)<< grid[i][j] << "    ";
                    rlutil::setColor(12);}
            else if(grid[i][j]==512)
               {
                    cout<<"|";
                    rlutil::setColor(9);
                    std::cout <<setw(5)<< grid[i][j] << "    ";
                    rlutil::setColor(12);}
            else if(grid[i][j]==1024)
               {
                    cout<<"|";
                    rlutil::setColor(10);
                    std::cout <<setw(5)<< grid[i][j] << "    ";
                    rlutil::setColor(12);}
            else if(grid[i][j]==2048)
               {
                    cout<<"|";
                    rlutil::setColor(9);
                    std::cout <<setw(5)<< grid[i][j] << "    ";
                    rlutil::setColor(12);}
            else
               {
                cout<<"|";
                    rlutil::setColor(9);
                    std::cout <<setw(5)<< grid[i][j] << "    ";
                    rlutil::setColor(12);}


        }
        cout<<"|";
        cout<<endl;

    }

   cout<<"\n\t\t\t\t|---------|---------|---------|---------|\n"<<endl;

   cout<<"\t\t\t\t\t\t\t\t\t\t     CONTROLS\n"<<endl;
   cout<<"\t\tDEVELOPED BY\t\t\t\tr-restart\t\t\tW \n \t\tGhazi Khan";
   cout<<"\t\t\t\tu-undo\t\t\tA\t\tD \n \t\t\t\t\t\t\tq-quit\n\t\t\t\t\t\t\t\t\t\t\tS"<<endl;

}


void spawntile(int grid[4][4])
{//spawns new tile of 2 after move
    int a;
    int b;
    int condition=0;
    int zerocount=0;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(grid[i][j]==0)
                zerocount++;
        }
    }
    if(zerocount>0)
    {while(condition==0)
    {
        //a=rand()%4+0;
        //b=rand()% 4+0;
        a=gamestartfirst();
        b=gamestartfirst();
        if(grid[a][b]==0)
        {
            grid[a][b]=2;
            condition++;
        }
    }
    }
}

char wasd()
{//Place for taking user inputs
    char key = ' ';
     cout << "Enter a valid input" << endl;
     key = _getch();
     return key;
}
int main()
{


    rlutil::setCursorVisibility(0); //erase cursor
    int total=0;//current score
    int highscore=0;
    int undototal=0;
    int a,b,c,d; //refer to coordinates
    int copycheck;//variable to check if there was a change in grid
    int check;//win condition checker
    char direct='d';
    int undo[4][4]={0};
    int grid[4][4]={0};

    highscore=filein();//get value of highscore
    starttile(grid);//get starting 2's
    printgrid(grid,highscore,total);//printing
    copygrid(grid,undo);//initial undo copy


    while(true)
    {
        check=checker(grid);
        if(check==0)
        {
            if(total>highscore)
        {
            highscore=total;
            fileout(highscore);
        }
            cout<<"YOU LOOSE"<<endl;
            cout<<"Your FINAL SCORE WAS "<<total<<" AND YOUR HIGHEST SCORE IS "<<highscore<<endl;
            return 0;
        }
        else if(check==1)
        {
            if(total>highscore)
        {
            highscore=total;
            fileout(highscore);
        }
            cout<<"YOU WIN"<<endl;
            cout<<"Your FINAL SCORE WAS "<<total<<" AND YOUR HIGHEST SCORE IS "<<highscore<<endl;
            return 0;
        }

        direct=wasd();
        cout<<direct<<endl;

        if(direct=='r')
        {
            if(total>highscore)
           {
                highscore=total;
                fileout(highscore);
           }
        undototal=total;
        copygrid(grid,undo);
        system("cls");
        zerogrid(grid,total);
        starttile(grid);
        printgrid(grid,highscore,total);

        }
    else if(direct=='w')
    {
        undototal=total;
        copygrid(grid,undo);
        moveup(grid);
        add(grid,4,total);
        system("cls");
        copycheck=0;
        copycheck=mirrorcounter(grid,undo);
        if(copycheck!=16)
          {
           spawntile(grid);
          }
        else
         cout<<"\a";
        printgrid(grid,highscore,total);


    }
    else if(direct=='a')
    {
        undototal=total;
        copygrid(grid,undo);
        turner(grid);
        moveup(grid);
        add(grid,4,total);
        turner(grid);
        turner(grid);
        turner(grid);
        system("cls");
        copycheck=0;
        copycheck=mirrorcounter(grid,undo);
        if(copycheck!=16)
         {
           spawntile(grid);
         }
        else
          std::cout<<"\a";
        printgrid(grid,highscore,total);


    }
    else if(direct=='d')
    {
        undototal=total;
        copygrid(grid,undo);
        turner(grid);
        turner(grid);
        turner(grid);
        moveup(grid);
        add(grid,4,total);
        turner(grid);
        system("cls");
        copycheck=0;
        copycheck=mirrorcounter(grid,undo);
        if(copycheck!=16)
        {
           spawntile(grid);
        }
        else
         std::cout<<"\a";
        printgrid(grid,highscore,total);


    }
    else if(direct=='s')
    {
        undototal=total;
        copygrid(grid,undo);
        turner(grid);
        turner(grid);
        moveup(grid);
        add(grid,4,total);
        turner(grid);
        turner(grid);
        system("cls");
        copycheck=0;
        copycheck=mirrorcounter(grid,undo);
        if(copycheck!=16)
           {
            spawntile(grid);
           }
        else
         std::cout<<"\a";
        printgrid(grid,highscore,total);

    }
    else if(direct=='u')
    {
        total=undototal;
        reversecopygrid(grid,undo);
        system("cls");
        printgrid(grid,highscore,total);
    }
    else if(direct=='q')
    {
        system("cls");
        printgrid(grid,highscore,total);
    if(total>highscore)
        {
            highscore=total;
            fileout(highscore);
        }

    cout<<"Your FINAL SCORE WAS "<<total<<" AND YOUR HIGHEST SCORE IS "<<highscore<<endl;

    cout<<"GOODBYE AND FARE THEE WELL"<<endl;


        return 0;
    }

    else
    {
        cout<<"\a";
        system("cls");
        printgrid(grid,highscore,total);
    }




}

}
