#include<iostream>
#include<fstream>
#include <stdio.h>
#include <curses.h>
#include<stdlib.h>
#include<string.h>
#include<list>
#include<string>
#define CTRL(c) ((c) & 037)

using namespace std;
int max_x=0,max_y=0;

list<string> up,down;

int row=0, col=0;
int get_space_loc(int);
int x,y;
int len(int lineno)
{
   int x = COLS - 1;

   while (x >= 0 && mvinch(lineno, x) == ' ')
       x--;
   return x + 1;
}
int input()
{
   int c;
   int i,j;
   char upper[100]={'\0'};
   string s="";
   char str[100]={'\0'};
   attron(A_BOLD|A_UNDERLINE);
   mvaddstr(LINES-1, COLS - 40, "INPUT MODE. PRESS ANY KEY TO CONTINUE");
   attroff(A_BOLD|A_UNDERLINE);
   move(row, col);
   refresh();
   getch();
   move(LINES - 1, COLS - 40);
   clrtoeol();
   move(row, col);
   while(1)
   {
       c = getch();
       
       if (c == 27)
       {
       	getyx(stdscr,row,col);
        col=col-1;
        move(row, col);   
           break;
       }
           if(c==13)
           {
           	innstr(str,80-col);
           	clrtoeol();
           	
           	col=0;
           	if(row==LINES-1)
           	{
           		scrl(1);
           		move(row,col);
           		insertln();
           		addstr(str);
           		move(row,col);
           		refresh();
           		continue;
           	}
           	move(++row,col);
           	insertln();
           	addstr(str);
           	move(row,col);
           	refresh();
           	continue;
           }
           if(c==KEY_BACKSPACE)
           {
           	getyx(stdscr,row,col);
           	if(col==0)
           	{
           		if(row==0)
           		{
           			flash();
           			continue;
           		}
           		else
           		{
           			col=len(row-1);
           			move(--row,col);
           			continue;
           		}
           	}
           			
           	else
           	{
           	col--;
           	move(row,col);
           	delch();
           	refresh();
           	continue;
           	}
           }
       insch((chtype)c);
       
       mvinnstr(row,0,str,90);
       
       y=len(row);
       if(y>80)
       {
       		for(i=row;i<=LINES-1;i++)
       		{
       			
       			 if(i==LINES-1)
       			 {
       			 	y=len(LINES-1);
       			 j=get_space_loc(LINES-1);
       			 mvinnstr(LINES-1,j,str,y+1-j);
       			 clrtoeol();
       			 mvinnstr(0,0,upper,80);
       			s=s+upper;
           		up.push_back(s);
           		scrl(1);
           		
       			 s="";
       			 
       			 for(j=strlen(str)-1;j>=0;j--)
       			 {
       			 	mvinsch(LINES-1,0,str[j]);
       			 	
       			 }
       			 move(--row,++col);
       			 continue;	
       			 }
       			 y=len(i);
       			 j=get_space_loc(i);
       			 mvinnstr(i,j,str,y+1-j);
       			 clrtoeol();
       			 
       			 for(j=strlen(str)-1;j>=0;j--)
       			 {
       			 	mvinsch(i+1,0,str[j]);
       			 	
       			 }
       			 if(len(i+1)<=80)
       			 break;
       			
       		}
       		move(row,++col);
       		
       		refresh();
       		continue;
       	}
     if(col==79)
       {
       		if(row==LINES-1)
       		{
       			
       			mvinnstr(0,0,upper,80);
       			s=s+upper;
           		up.push_back(s);
           		
           		s="";
           		y=len(row);
       			j=get_space_loc(row);
       			mvinnstr(row,j,str,y+1-j);
       			
       			clrtoeol();
       		
           		scrl(1);
           		for(j=strlen(str)-1;j>=0;j--)
       			{
       			mvinsch(row,0,str[j]);
       			
       			}
           		col=strlen(str)-1;
           		move(row,col);
           		continue;
       		}
       		
       		y=len(row);
       		j=get_space_loc(row);
       		mvinnstr(row,j,str,y+1-j);
       		
       		clrtoeol();
       		for(j=strlen(str)-1;j>=0;j--)
       		{
       			mvinsch(row+1,0,str[j]);
       			
       		}
       		col=strlen(str)-1;
       		move(++row,col);
       		for(i=row;i<=LINES-1;i++)
       		{
       			if(i==LINES-1)
       			 {
       			 	y=len(LINES-1);
       			 j=get_space_loc(LINES-1);
       			 mvinnstr(LINES-1,j,str,y+1-j);
       			 clrtoeol();
       			 mvinnstr(0,0,upper,80);
       			s=s+upper;
           		up.push_back(s);
           		scrl(1);
           		
       			 s="";
       			 
       			 for(j=strlen(str)-1;j>=0;j--)
       			 {
       			 	mvinsch(LINES-1,0,str[j]);
       			 	
       			 }
       			 
       			 move(--row,col);
       			 continue;	
       			}
       		y=len(i);
       		j=get_space_loc(i);
       		mvinnstr(i,j,str,y+1-j);
       		
       		clrtoeol();
       		for(j=strlen(str)-1;j>=0;j--)
       		{
       			mvinsch(i+1,0,str[j]);
       			
       		}
       		if(len(i+1)<=80)
       		break;
       		}
       		refresh();
     
       		move(row,col);
       		continue;
       		
       	}
       
     else
       	{
       		move(row, ++col);	
       		refresh();
       		
       }
       			 		
   
       
   }
   
   refresh();
   return 1;
}


int detect_cmd()
{
     int c,x=0,y=0,t=0,z=0;
     char upper[100]={'\0'};
     string s="";
     char *ch;
     char *temp;
     while(1)
     {
       move(row, col);
       refresh();
       c = getch();
       switch (c)
       {
       	case KEY_LEFT:
           if (col > 0)
               col--;
           else
               flash();
               beep();
           break;

       case KEY_DOWN:
           
           if((row==LINES-1)&&!down.empty())
           {
           	temp=new char[down.front().length()+1];
           	strcpy(temp,down.front().c_str());
           	mvinnstr(0,0,upper,80);
           	s=s+upper;
           	up.push_back(s);
           	
           	s="";
           	scrl(1);
           	mvaddstr(LINES-1,0,temp);
           	down.pop_front();
           	delete[] temp;
           }
           else if(row==LINES-1)
           {
           	flash();
           }
           else
           ++row;
          
           break;

       
       case KEY_UP:
           if (row > 0)
               row--;
           else if(row==0&&!up.empty())
           {
           	temp=new char[up.back().length()+1];
           	strcpy(temp,up.back().c_str());
           	s="";           	
           	mvinnstr(LINES-1,0,upper,80);
           	s=s+upper;
           	down.push_front(s);
           	scrl(-1);
           	s="";
           	mvaddstr(0,0,temp);
           	up.pop_back();
           	delete[] temp;
           }
           else if(row==0)
           {
               flash();
               beep();
              }
                         
           break;

       
       case KEY_RIGHT:
           getyx(stdscr,x,y);
           if(x==row&&y==len(row)-1)
           	break;
           else if (col < COLS - 1)
               col++;
           else 
               flash();
               beep();
           break;
       case 'i':
           input();
           break;
           
       case 'x':
           delch();
           break;
       
       
       case 'l':
           mvinnstr(LINES-1,0,upper,80);
           down.push_front(upper);
           move(++row, col = 0);
           insertln();
           input();
           break;
 
       case 'd':        
           deleteln();
           if(!down.empty())
           {
           ch=new char[down.front().length()+1];
           	strcpy(ch,down.front().c_str());
           mvaddstr(LINES-1,0,ch);
           down.pop_front();
           move(row,col);
           delete[] ch;
           }
           
           break;

       
       case KEY_CLEAR:
       case CTRL('L'):
           wrefresh(curscr);
           break;
      
       case 'w':
           return 1;
       
       case 'q':
           endwin();
           exit(EXIT_SUCCESS);
       default:
           flash();
           beep();
           break;
       }
   }
}
int get_space_loc(int x)
{
	
	int y=80;
	int c;
	while(1)
	{
		c=mvinch(x,--y);
		if(c==' ')
		break;
		/*else
		y--;*/ 
	}
	
	return y+1;
}
int init(char fname[])
{
   int i=0, n, l,flag=0;
   int x,y;
   int c;
   int line = 0;
   string str="";
   char ch;
   char temp[100];
   char buff[100];
   int j;
   ifstream fin(fname,ios::in);
   initscr();
   cbreak();
   nonl();
   noecho();
   idlok(stdscr, TRUE);
   keypad(stdscr, TRUE);
   scrollok(stdscr, TRUE);
   mvprintw(0,COLS-90,"WELCOME TO MINI TEXT EDITOR");
   mvprintw(LINES/4,COLS-80,"PLEASE REMEMBER THE FOLLOWING COMMANDS : ");
   mvprintw(LINES/4+1,COLS-80,"i=input mode");
   mvprintw(LINES/4+2,COLS-80,"d=delete line");
   mvprintw(LINES/4+3,COLS-80,"l=new line + input mode");
   mvprintw(LINES/4+4,COLS-80,"x=delete character");
   mvprintw(LINES/4+5,COLS-80,"esc=quit input mode");
   mvprintw(LINES/4+6,COLS-80,"w=write and quit");
   mvprintw(LINES/4+7,COLS-80,"q=quit without writing");
   mvprintw(LINES/4+8,COLS-80,"PRESS ANY KEY TO CONTINUE!");
   getch();
   erase();
   int count=0,sloc=0;
   move(0,0);
   if(!fin.is_open())
   {
   	attron(A_BOLD|A_UNDERLINE);
   	mvaddstr(LINES-1, COLS - 20, "NEW FILE");
   	attroff(A_BOLD|A_UNDERLINE);
   }
   else
   {
   while ((c=fin.get())!=EOF)
   {
 
       	getyx(stdscr,x,y);
       	line=x;
       
       	if(line==LINES-1)
       	break;
       	printw("%c",c);
       	if(y==80)
       	{
       		j=get_space_loc(line);
       		mvinnstr(line,j,buff,81-j);
        	clrtoeol();
       		y=0;
       		mvaddstr(line+1,0,buff);
       		move(line+1,strlen(buff));
       	}

   }         	
         	
         	if(c!='\n')
         	str=str+(char)c;
         	
         	count=1;
         	while((ch=fin.get())!=EOF)
		{
		
			if(ch=='\n')
			{
				down.push_back(str);
				str="";
				count=0;
				continue;
			}
			else if(count==81)
			{
			
				size_t loc=str.find_last_of(' ');
				down.push_back(str.substr(0,loc+1));
				str=str.substr(loc+1);
				count=0;
				str=str+ch;
				count++;
				continue;
			}
			count++;
			str=str+ch;
			
			
		}
		if(!str.empty())
		down.push_back(str);
		
         

   fin.close();
   }
  
   refresh();
   detect_cmd();
   ofstream fout(fname,ios::trunc);
   if(!fout.is_open())
   {
   	mvprintw(LINES-1,0,"Error opening file!");
   	exit(EXIT_FAILURE);
   }
   if(!up.empty())
   {
   	list<string>::iterator it;
   	for(it=up.begin();it!=up.end();it++)
   	{
   		fout<<*it;
   	}
   }
   
   for (l = 0; l <=LINES - 1; l++)
   {
      n = len(l);
       c=mvinch(l,0)&A_CHARTEXT;
       for (i = 0; i<n; i++)
       {
           
           c=mvinch(l,i)&A_CHARTEXT;
           fout.put(c);
           
       }
       
       if(n<80&&c!='\n')
       fout.put('\n');
   }
   if(!down.empty())
   {
   	list<string>::iterator it;
   	for(it=down.begin();it!=down.end();it++)
   	{
   		fout<<*it;
   	}
   }
   fout.close();
  str.~string();
   
   endwin();
   delwin(stdscr);
}

int main(int argc,char *argv[])
{
   
   if (argc != 2)
   {
       cout<<"Please provide filename. "<<endl;
       return 1;
   }
   init(argv[1]);
   return 0;
}
