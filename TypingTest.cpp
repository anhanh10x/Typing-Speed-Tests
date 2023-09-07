#include<iostream>
#include<windows.h>
#include<conio.h>
#include<string>
#include<string.h>
#include<stdio.h>
#include<math.h>
#include<ctime>
#include<fstream>
using namespace std;

//==thay mau cho nen va chu ======
void SetColor(int backgound_color, int text_color)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}
//====thay mau cho chu ====
void Setcolor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
//============== làm ẩn trỏ chuột ===========
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

void GoTo(SHORT posX, SHORT posY)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

	SetConsoleCursorPosition(hStdout, Position);
}

//===tach doan thanh cau
void paraToSen(string para, string sen[],int &i)
{
	int length=para.length();
    while(true)
    {
		if(para.find(".")>length)
		{
            break;
		}
        sen[i]=para.substr(0,para.find("."));
		para=para.substr(para.find(".")+1);
		i++;
    }
}

//====tach mot string cau thanh cac tu=====
void separ(string para, string word[],int &i)
{
    int length=para.length();
    while(true)
    {
        word[i]=para.substr(0,para.find(" "));
        if(para.find(" ")>length)
		{ 
			word[i]=para.substr();
            break;
		}
		para=para.substr(para.find(" ")+1);
        i++;
    }
}

//==ham tra ve vi tri x====
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}
//========= lấy tọa độ y =====
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}

//== ham in chu thanh mau do nen trang===
void highLight(int x, int y, string h)
{
	GoTo(x,y);
	SetColor(7,0);
	cout<<h;
}

//== ham in chu tro lai binh thuong===
void ColorBack(int x, int y, string h)
{

	GoTo(x,y);
	SetColor(0,7);
	cout<<h;
}

//== ham in chu bi go sai===
void ColorWrong(int x, int y, string h)
{
	GoTo(x,y);
	SetColor(0,4);
	cout<<h;
}
//==ham ket thuc==
void end()
{
	ShowCur(0);
	for(int i=0; i<20; i++)
	{
		system("cls");
		GoTo(40,5);
		SetColor(0,6);
		cout<<" Game Over "<<endl;
		Sleep(50);
		GoTo(40,5);
		SetColor(0,1);
    	cout<<" Game Over "<<endl;
		SetColor(0,2);
		GoTo(32,6);
		Sleep(50);
		cout<<" Thank to play my game!!! "<<endl;
		SetColor(0,5);
		Sleep(50);
		GoTo(32,6);
		cout<<" Thank to play my game!!! "<<endl;
		Sleep(50);
	}
    return;
}

void luuFile(int &i)
{
	ifstream f;
	f.open("D:\\level.txt", ios::in);
	f>>i;
	f.close();
}
void writeFile(int i)
{
    ofstream f;
    f.open("D:\\level.txt", ios::out);
	if(i==4)
		i=1;
	else
		i++;
	f<<i;
	f.close();
}
int main()
{
	system("cls");
	int n,count=0,index=0, j=0,dung=0,sai=0,soCau=0,soTu=0;
	time_t now = time(0);
    tm *ltm = localtime(&now);
	int hStart,pStart,sStart;
	bool check,checkBackspace=true;
	HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);
    PCONSOLE_FONT_INFOEX font = new CONSOLE_FONT_INFOEX() ;
    font->cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(cons,0,font);
    font->dwFontSize.X = 33;
    font->dwFontSize.Y = 33;
    //font->FontWeight = 22;
    //font->FontFamily = FF_DECORATIVE;
    SetCurrentConsoleFontEx(cons,0,font);
	char key_press[11];
    string para[4];
	para[0]="I think of Seattle as having a gray-green heart.I is a city shaped by nature, a city of snow-covered mountains, sparkling glaciers and blue lakes.It has been called America's Most dynamic City, the No.1 City of the Future, and America's Athens by three major U.S publication.But why has a town that is so far away from the nation's major power centers attracted so much attention? The answers may lie in Seattle's youthful energy and its scenery.";
	para[1]="Seattle began as a wild pioneer town, and its energy continues in vigorous political activity and in the quiet creation of more millionaires per capita than any other urban area in the United State.Through six generations of gold seekers, lumberjacks, teachers, fishermen, airplane builders, and software inventors, we all share the feeling that living here ins an adventure.";
	para[2]="Fires would not burn in the same way.The sunset would not be interesting, and blood would not be surprisingly beautiful.Red is powerful when it appears in nature, and it is also powerful when it appears in our emotions.Red is love.Red is anger.Red is beauty.I like to live in a strong way, so I think I will always admire the color red. ";
	para[3]="Sometimes I bought toys with my lucky New Year money.A long time later, when I was old enough to go out, I went around to the corner to find the child who gave me that special gift, but nobody was in that house.My neighbor said that a girl used to live there, and she was the same age as me. ";
	string sent[50];
	string word[120];
	cout<<"Nhap so luong tu muon go [0;100]: ";
	cin>>n;
	int level=0;
	luuFile(level);
	writeFile(level);
	if(n>0 && n<=50)
		if(level==1)
			paraToSen(para[0],sent,soCau);
		else if(level==2)
			paraToSen(para[1],sent,soCau);
		else 
			paraToSen(para[2],sent,soCau);
	else if(n>50)
	{
		if(level==1)
		{
			paraToSen(para[0],sent,soCau);
			paraToSen(para[1],sent,soCau);
		}
		else if(level==2)
		{
			paraToSen(para[2],sent,soCau);
			paraToSen(para[3],sent,soCau);
		}
		else
		{
			paraToSen(para[3],sent,soCau);
			paraToSen(para[2],sent,soCau);
		}
	}
	else
		cout<<"Wronggggg!!!";
	for(int i=0; i<soCau; i++)
	{
		separ(sent[i],word,soTu);
	}
	system("cls");
	cout<<" An enter de bat dau ......... ";
    if((int)getch()==13)
    {
		system("cls");
        int countDown=5,timeBefore=ltm->tm_sec;
        cout<<" Bat dau luyen go sau: 5";
        while(countDown>=0)
        {
            time_t now = time(0);
            tm *ltm = localtime(&now);
            if(ltm->tm_sec-timeBefore>=1)
            {
                system("cls");
                cout<<"     ";
                cout<<" Bat dau luyen go sau: ";
                timeBefore=ltm->tm_sec;
                cout<<countDown;
                countDown--;
            }
        }
	}
    system("cls");
    hStart=ltm->tm_hour; 
    pStart=ltm->tm_min;
    sStart=ltm->tm_sec;
	for(int z=0; z<soCau; z++)
	{
		system("cls");
		GoTo(5,10);
		cout<<"An esc de thoat nhe !!!";
		GoTo(0,0);
		GoTo(5,0);
		cout<<sent[z];
		for(int i=0; i<sent[z].length(); i++)
		{	
			if(sent[z][i]==' ' || sent[z][i]=='.' )
			{
				highLight(5+i-word[count].length(),0,word[count]);
				ColorBack(20,5,word[count]);
				GoTo(20,6);
				while(true)
				{
					key_press[j]=getch();
            		if(key_press[j]==' ')
            		{
						key_press[j]='\0';
						GoTo(20,5);
						for(int k=0; k<word[count].length(); k++)
							cout<<" ";
						GoTo(20,6);
						for(int k=0; k<=j; k++)
							cout<<" ";
                		break;
            		}
            		if((int)key_press[j]==27)
            		{
						end();
						return 0;
            		}
				
            		if((int)key_press[j]==8)
            		{
						if(j==0)
						{
                    		continue;
                		}
                		GoTo(19+j,6);
						cout<<" ";
						GoTo(19+j,6);
						j=j-2;
						checkBackspace=true;
					}
					else
						cout<<key_press[j];

					if(checkBackspace==true)
					{
						check=true;
						for(int k=0; k<=j; k++)
						{
							if(key_press[k]!=word[count][k])
							{
								ColorWrong(20,5,word[count]);
								GoTo(21+j,6);
								SetColor(0,7);
								check=false;
								checkBackspace=false;
								break;
							}
						}
							if(check==true)
							{
							ColorBack(20,5,word[count]);
							GoTo(21+j,6);
							checkBackspace=true;
						}
					}
					j++;
				}
				if(strcmp((char*)word[count].c_str(),(char*)key_press) == 0)
        		{
            		dung++;
            		ColorBack(5+i-word[count].length(),0,word[count]);
					j=0;
        		}
        		else
        		{
            		sai++;
            		ColorWrong(5+i-word[count].length(),0,word[count]);
					j=0;
        		}
				SetColor(0,7);
				count++;
				if(count>=n)
					break;
			}
			if(count>=n)
				break;
		}
		if(count>=n)
			break;
	}
	system("cls");
	for(int i=1; i<2; i++)
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        dung=count-sai;
        float wpm=round(dung*60/(3600*(ltm->tm_hour-hStart)+ 60*(ltm->tm_min-pStart)+(ltm->tm_sec-sStart)));
        cout << "Time Start: "<< hStart << " : ";
        cout << pStart << " : ";
        cout << sStart << endl;
        cout << "Time Finish: "<<ltm->tm_hour << " : ";
        cout <<ltm->tm_min << " : ";
        cout <<ltm->tm_sec << endl;
        cout<<"Tong so tu: "<<count<<" ----- "<<"So tu dung: "<<count-sai<<" --------- "<<"So tu sai: "<<sai<<endl;
        cout<<"Words per Minute: "<<wpm<<" w/m"<<endl;
		cout<<" An phim bat ky de thoat!!";
		getch();
		end();
    }
		return 0;
		
}
