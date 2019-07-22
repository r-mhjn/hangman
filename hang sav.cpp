#include<iostream>
#include<string>
#include<ctime>
#include<vector>
#include<cstdlib>
#include<windows.h>
#include<conio.h>
#include <cwchar>
#include<fstream>
//#include<thread>
using namespace std;
#define N 30
// make sure the file names do not change


class Hangman
{
	public:
    int score,dash_count,score_k;   // here h increments after every score decrement to give out the index of the file to be printed form the vector
	char matrix[N][N];
	char ch;
    string word,guess_word,hint;
	vector<string> vecwords;
	vector<string> file_name;
    vector<string> hints;
	Hangman(){
		score=9;
		dash_count=0;
		score_k=-1;
	}
	public:
    void build();
	void getWord();
	void initializeFileVector();
	void initializeVectorWords();
	void initialize();
	void initializeHints();
	void initializeGuess();
	void makeBorder();
	void dispMan();
	void timer();
	void display();
	void clearScreen();
};
HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);


void Hangman::clearScreen()
{
    COORD top_left= {0, 0};
	SetConsoleCursorPosition(hout,top_left);
}

void Hangman::initializeHints()
{
	fstream fin;
	string line;
	fin.open("hint.txt",ios::in);
	if(fin.is_open())
	{
		while(getline(fin,line))
		{		
		   hints.push_back(line);
		}	
		fin.close();	
	}
	
}
void Hangman::makeBorder()
{
for (int i=0; i<N; i++)
  {
    for (int j=0; j<N; j++)
  	 {         	
		 if (i==0 || j==0 || i==29||j==29)
		 {
		 	matrix[i][j]=(char)219;
		 }
		 else
		 {
		 	 matrix[i][j]=' '; 
			 }	
	  }
  }	
	
}
void Hangman::initializeFileVector()
{
	fstream fin;
	string line;
	fin.open("files.txt",ios::in);
	if (fin.is_open())
	{
		while(getline(fin,line))
		{    
			file_name.push_back(line);
		}
		fin.close();
	}		
}
void Hangman::dispMan()          // trouble in this funtion
{
	fstream fin;
	int r,c;
	string filename=file_name[score_k];   // selecting files depeding upon the score
	fin.open(filename.c_str(),ios::in);
	if (fin.is_open())
	{
		while(!fin.eof())
         {
           fin>>r>>c;
            SetConsoleTextAttribute(hout,FOREGROUND_RED | FOREGROUND_INTENSITY);
           matrix[r][c]='*';	 
		 }		
		fin.close();
	}
	
}
void Hangman::initializeVectorWords()
{		
    string line;
    fstream fin;	
	fin.open("words.txt",ios::in);
    if (fin.is_open())
	{	
	  	while(getline(fin,line))
	     {
	       	vecwords.push_back(line);	     	
		    
		 }		
	 fin.close();
   } 
}
void Hangman::getWord()
{
	srand(time(0));	
	int random=rand()%vecwords.size();
	word=vecwords[random];	
	hint=hints[random];
}
void Hangman::initializeGuess()
{
	//cout<<word;     // remove this later on
	for(int i=0; i<word.size(); i++)
	{
		guess_word.insert(guess_word.begin(),'-');
	 }
}

void Hangman::build()
{
	int dash_prev;
	dash_count=word.size();

	while(dash_count>0 && score>0)
	{
	    cin>>ch;
	    dash_prev=dash_count;
	 	 clearScreen();		
	 	for (int i=0; i<word.size(); i++)
	 	{
	 		char chh=word[i];
	        chh+=32;
	 		if (word[i]==ch && guess_word[i]=='-' || chh==ch && guess_word[i]=='-')
	 		{
	 			guess_word.erase(guess_word.begin()+i);
	 			guess_word.insert(guess_word.begin()+i,word[i]);
	 			dash_count--;
			 }     
		 }
		 if(dash_prev==dash_count)
		 {
		 	score--;	
			score_k++;
			dispMan();	 	
		 }
		 display();				 
	 }
	 if (dash_count<=0)
	 {
	 	cout<<"Score  = "<<score<<endl<<"You Won!!";
	 }
	 else
	 {
	 	cout<<"Correct Word = "<<word<<endl;
	 	cout<<"You Lost!! ..Game Over"<<endl;
	 } 	 
}
void Hangman::display()
{
	cout<<"\t\t\t\t\t\t"<<"HangMan"<<"\n\n\n\n";
		cout<<guess_word<<endl;
		cout<<hint<<"\n\n\n";
		
	for (int i=0; i<N; i++)
	{
		cout<<"\t\t\t\t\t\t";
		for (int j=0; j<N; j++)
		{
			if(matrix[i][j]==(char)219)
			{			
			cout<<matrix[i][j];}			
			else
			{
			   SetConsoleTextAttribute(hout,FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout<<matrix[i][j];	   		   		
			}	    
			
		}
		cout<<endl;
	}
} 
int main()
{
       // code for console size	
       CONSOLE_FONT_INFOEX cfi;
       cfi.cbSize = sizeof(cfi);
       cfi.nFont = 0;
       cfi.dwFontSize.X = 15;                   // Width of each character in the font
       cfi.dwFontSize.Y = 15;                  // Height
       cfi.FontFamily = FF_DONTCARE;
       cfi.FontWeight = FW_NORMAL;
       std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
       SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
       //std::cout << "Font: Consolas, Size: 24\n";

	   CONSOLE_CURSOR_INFO ci;
       ci.dwSize=100;
       ci.bVisible=0;
	   SetConsoleCursorInfo(hout,&ci);
	   Hangman obj;
	   obj.initializeFileVector();
	   obj.makeBorder();
	   obj.initializeHints();
	   obj.initializeVectorWords();
	   obj.getWord();
	   obj.initializeGuess();
	   obj.display();
	   obj.build();
	  return 0;
}


