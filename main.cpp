#include <iostream>
#include <cstdlib>
#include <conio.h> 
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;
bool gameOver;
const int height=20;
const int width=20;
int x,y,fruitX,fruitY,score;
int nTail;
int	tailX[100],tailY[100];
enum direction{STOP=0,LEFT,RIGHT,UP,DOWN};
direction dir;
char name[20];
void  setup()
{
	gameOver=false;	
	dir=STOP;
	x=width/2;
	y=height/2;
	fruitX= rand() % width;
	fruitY= rand() % height;
	score=0;	
	
}
void draw()
{	
	system("cls");
	for(int i=0;i<width+2;i++)
	{
		cout<<"#";
	}
	cout<<endl;
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width+2;j++)
			{
				if(j==0)
				cout<<"#";
				
				if(i==y && j==x)
				cout<<"O";			
				
				else if(i==fruitY && j==fruitX)
				cout<<"F";
				
				else
				{	bool print = false;
					for(int k=0; k<nTail; k++)
					{
						if(tailX[k]==j && tailY[k]==i)
						{
							cout<<"o";
							print = true;
						}
					}	
					if(!print)
					cout<<" ";
				}
				
				if(j==width-1)
				cout<<"#";
			}
		cout<<endl;
	}
	for(int i=0;i<width+2;i++)
	cout<<"#";
	cout<<endl;
	cout<<"score: "<<score;
	
}
void Input()
{	
	if(_kbhit())   /* without _kbhit() function in if statement the output will be different i.e we have to continously press the key to dmove
					our snake but with this function our snake moves automatically we just have to provide the directions*/
	{
		switch(_getch())
		{
			case 'a': dir=LEFT;
				break;
			case 'd': dir=RIGHT;
				break;
			case 'w': dir=UP;
				break;
			case 's': dir=DOWN;
				break;
			case 'x': 
				gameOver=true;
				break;	
		}
	}
		
}
void Logic()
{	
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for(int i=1; i<nTail; i++)
	{
		prev2X = tailX[i]; // ith value of tail assigned to prev2
		prev2Y = tailY[i];
		tailX[i] = prevX; // head value assigned
		tailY[i] = prevY;
		prevX = prev2X; 
		prevY = prev2Y;
	}
	switch(dir)
	{
		case LEFT: x--;
			break;
		case RIGHT: x++;
			break;
		case UP: y--;
			break;
		case DOWN : y++;
			break;	
	}
	if(x > width || x < 0 || y > height || y < 0)
		gameOver = true;
		
	for( int i=0; i<nTail; i++)
	{
		if(tailX[i] == x && tailY[i] == y)
		gameOver = true;
	}
	
	if( x == fruitX && y == fruitY )
		{			
			score += 10;
			fruitX= rand() % width;
			fruitY= rand() % height;
			nTail++;
		}
}
int main() 
{	int details;
	string line;
	char s;
	setup();
	while(!gameOver)
	{
		draw();
		Input();
		Logic();
		Sleep(10);
	}	
	if(gameOver == true )
	{
		cout<<"\n\t\t\t\t\tBetter luck next time";
		cout<<"\n\t\t\t\t\tYour final score is: "<<score;
		cout<<"\n\t\t\t\t\tPlease enter your name : ";
		cin>>name;
		cout<<"\n\t\t\t\t\tYour name has been entered in the score list \n ";
		ofstream fout;
		fout.open("highS",std::ios_base::app);
		while(fout)
		{
			fout<<name<<" = "<<score<<"\n";
			fout.close();
		}
		cout<<"Do you want to see the score list(y/n): ";
		cin>>s;
		if(s == 'y')
		{
			cout<<"The score list is as follows: \n";
			ifstream ifs;
			ifs.open("highS",std::ios_base::app);
			if (ifs.is_open())
	 		{
   			 	while ( getline ( ifs , line ) )
   				{
   			   		cout << line << '\n';
  				}
  			}
   		 	ifs.close();
   		}
 	}			
	return 0;
}
