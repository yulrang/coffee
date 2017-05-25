// 2012211mapw.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "201221128.h"
#include "egl/egl.h"
#include "vg/openvg.h"
#include "vgLoadImage.h"
#include "DXUTsound.h"
#include <fstream>
#include <stdlib.h>
#include <Time.h>
#include <conio.h>

#define MAX_LOADSTRING 100
#define maph 6
#define mapw 13


#define ESPRESSO 1
#define AMERICANO 2
#define ICEAMERICANO 3
#define CAFELATTE 4
#define CAFEMOCCA 5

CSoundManager* sm;
CSound* crashSound = NULL;
CSound *ilove, *fail, *success, *drag;

void timerProc();

void draw();


VGImage imggameend, imgmain,imggameover,imground1, imground2, imgO, imgX;
VGImage img0,img1,img2,img3,img4,img5,img6,img7,img8,img9;
VGImage imgrecipe1, imgrecipe2, imgrecipe3, imgrecipe4, imgrecipe5, imgstart, imgnext, imgox, imgmade, imgEcup, imgEmachine, imgEmenu, imgEmoney, imgEtimer;
VGImage imgtimer,  imgui, imgmenu, imgback;
VGImage imgamericano1, imgamericano2,imgespresso1, imgespresso2, imgmorning, imgmug, imgmorning1, imgmorning2, imglatte, imgmocca, imgiceamericano;
VGImage imgmilk, imgmachine, imgpot, imgsyrup_cm, imgsyrup_cc, imgicepot;


char map[mapw*maph];

int cx, cy;


int randnum;

int coffee_show;   //true or false , 커피 등장 (엔터누르면 재등장)
int coffee_change;   //커피 만드는 과정 이미지변환 (스페이스 누를때)
int coffee_count;   //만든 커피 개수 세기

int time_count;
int i, j;

int correct;
int correct_show;
int showo, showx; //o이미지 x이미지

int gameplay;
int gameover;
int gameend;

int push;
int rpush;

int sum,sum1,sum2,sum3;
int round1, round2;




// global variables
EGLDisplay display;
EGLSurface surface;
EGLContext context;

// 전역 변수:
HINSTANCE hInst;                                                                // 현재 인스턴스입니다.
TCHAR szTitle[MAX_LOADSTRING];                                        // 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING];                        // 기본 창 클래스 이름입니다.
HWND hWnd;

struct Mug
{
	int x, y;
	int dir;
	int show;
} mug;

struct Espresso
{
	int x, y;
	int dir;
} espresso;

struct Round
{
	int x, y;
	int show;
} round;

struct Timer
{
	int x, y;
	int visible;
} timer[1000];

struct Box
{
	int x, y;
	int visible;
} box[100];

struct Ex
{
	int x, y;
	int visible;
} ex[100];

void readMap(const char* filename, char* map, int W, int H)
{
	char temp[100];

	std::fstream ifs(filename);

	for(int i=0; i<H;i++)
	{
		ifs.read(&(map[(H-i-1)*W]),W);

		ifs.getline( temp,100);
	}
	ifs.close();
}

void draw()
{
	eglMakeCurrent(display, surface, surface, context);
	// transform이 image에 적용되게 함
	vgSeti( VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
	// 화면을 주황색으로 지운다.
	float color[4]={0,0,0,1};
	vgSetfv(VG_CLEAR_COLOR, 4, color );
	vgClear(0,0,1000,1000);


	int k=cx/800;

	vgLoadIdentity();
	vgTranslate(k*800-cx,0);
	vgDrawImage(imgback);

	vgLoadIdentity();
	vgTranslate((k+1)*800-cx,0);
	vgDrawImage(imgback);



	/*vgLoadIdentity();
	vgTranslate(0,0);
	vgDrawImage(imgback);*/

	for(int y=0;y<maph;y++)
		for(int x=0;x<mapw;x++)
		{
			vgLoadIdentity();
			vgTranslate(x*180-cx,y*100);

			switch(map[y*mapw+x])
			{
			case 'm': vgDrawImage( imgmachine );break;
			case 'p': vgDrawImage( imgpot );break;
			case 'M': vgDrawImage( imgmilk );break;
			case 'c': vgDrawImage( imgsyrup_cm );break;
			case 'C': vgDrawImage( imgsyrup_cc );break;
			case 'I': vgDrawImage( imgicepot );break;
			}
		}


		if(gameplay)
		{
			if(coffee_show)
			{
				if(randnum==ESPRESSO) //에스프레소 플레이
				{
					if(coffee_change == 0)
					{
						vgLoadIdentity();
						vgTranslate( (mug.x)-cx, (mug.y) );
						vgDrawImage( imgespresso1 );
					}

					if(coffee_change == 1)
					{
						vgLoadIdentity();
						vgTranslate( (mug.x)-cx, (mug.y) );
						vgDrawImage( imgespresso2 );					
					}
				}

				else if(randnum==AMERICANO)   //아메리카노 플레이
				{
					if(coffee_change == 0)
					{
						vgLoadIdentity();
						vgTranslate( (mug.x)-cx, (mug.y) );
						vgDrawImage( imgmug );
					}

					if(coffee_change == 1)
					{
						vgLoadIdentity();
						vgTranslate( (mug.x)-cx, (mug.y) );
						vgDrawImage( imgamericano1 );
					}


					if(coffee_change == 2)
					{
						vgLoadIdentity();
						vgTranslate( (mug.x)-cx, (mug.y) );
						vgDrawImage( imgamericano2 );
					}
				}


				else if(randnum==ICEAMERICANO)   //아이스아메리카노 플레이
				{
					if(coffee_change == 0)
					{
						vgLoadIdentity();
						vgTranslate( (mug.x)-cx, (mug.y) );
						vgDrawImage( imgmug );
					}

					if(coffee_change == 1)
					{
						vgLoadIdentity();
						vgTranslate( (mug.x)-cx, (mug.y) );
						vgDrawImage( imgamericano1 );
					}


					if(coffee_change == 2)
					{
						vgLoadIdentity();
						vgTranslate( (mug.x)-cx, (mug.y) );
						vgDrawImage( imgamericano2 );
					}

					if(coffee_change == 3)
					{
						vgLoadIdentity();
						vgTranslate( (mug.x)-cx, (mug.y) );
						vgDrawImage( imgiceamericano );
					}

				}

				else if(randnum==CAFELATTE)   //카페라떼 플레이
				{
					if(coffee_change == 0)
					{
						vgLoadIdentity();
						vgTranslate( (mug.x)-cx, (mug.y) );
						vgDrawImage( imgmorning );               
					}

					if(coffee_change == 3)
					{
						vgLoadIdentity();
						vgTranslate( (mug.x)-cx, (mug.y) );
						vgDrawImage( imgmorning1 );               
					}


					if(coffee_change == 4)
					{
						vgLoadIdentity();
						vgTranslate( (mug.x)-cx, (mug.y) );
						vgDrawImage( imgmorning2 );
					}


					if(coffee_change == 5)
					{
						vgLoadIdentity();
						vgTranslate( (mug.x)-cx, (mug.y) );
						vgDrawImage( imglatte );
					}
				}


				else if(randnum==CAFEMOCCA)   //카페모카 플레이
				{
					if(coffee_change == 0)
					{
						vgLoadIdentity();
						vgTranslate( (mug.x)-cx, (mug.y) );
						vgDrawImage( imgmorning );               
					}

					if(coffee_change == 3)
					{
						vgLoadIdentity();
						vgTranslate( (mug.x)-cx, (mug.y) );
						vgDrawImage( imgmorning1 );               
					}


					if(coffee_change == 4)
					{
						vgLoadIdentity();
						vgTranslate( (mug.x)-cx, (mug.y) );
						vgDrawImage( imgmorning2 );
					}


					if(coffee_change == 5)
					{
						vgLoadIdentity();
						vgTranslate( (mug.x)-cx, (mug.y) );
						vgDrawImage( imgmocca );
					}
				}


			}
		}


		//UI 띄우기
		vgLoadIdentity();
		vgTranslate(0,0);
		vgDrawImage(imgui);



		//UI 상단 박스안에 들어갈 주문 내용
		if(gameplay)
		{
			if(coffee_show)
			{
				if(randnum==ESPRESSO)   //에스프레소 주문
				{

					vgLoadIdentity();
					vgTranslate(5,490);
					vgScale(0.7, 0.7);
					vgDrawImage(imgespresso2);
				}

				else if(randnum==AMERICANO)   //아메리카노 주문
				{
					vgLoadIdentity();
					vgTranslate(5,490);
					vgScale(0.7, 0.7);
					vgDrawImage(imgamericano2);
				}

				else if(randnum==ICEAMERICANO)   //아메리카노 주문
				{
					vgLoadIdentity();
					vgTranslate(5,490);
					vgScale(0.7, 0.7);
					vgDrawImage(imgiceamericano);
				}

				else if(randnum==CAFELATTE)   //카페라떼 주문
				{
					vgLoadIdentity();
					vgTranslate(5,490);
					vgScale(0.7, 0.7);
					vgDrawImage(imglatte);
				}

				else if(randnum==CAFEMOCCA)   //카페모카 주문
				{
					vgLoadIdentity();
					vgTranslate(5,490);
					vgScale(0.7, 0.7);
					vgDrawImage(imgmocca);
				}
			}
		}


		//TIMER 처리
		if((gameplay == TRUE) && (round2 == FALSE))
		{
			for(int i=0; i<100; i++)
			{
				if(timer[i].visible)
				{
					vgLoadIdentity();
					vgTranslate(-7*(i),0);
					vgDrawImage(imgtimer);
				}

			}
		}


		if((gameplay == TRUE) && (round2 == TRUE))
		{
			for(int i=0; i<100; i++)
			{
				if(timer[i].visible)
				{
					vgLoadIdentity();
					vgTranslate(-7*(i),0);
					vgDrawImage(imgtimer);
				}

			}
		}

		//게임 방법 보여주기

		if(!ex[14].visible){
			vgLoadIdentity();
			vgTranslate(0,0);
			vgDrawImage(imground1);
		}

		if(!ex[13].visible){
			vgLoadIdentity();
			vgTranslate(0,0);
			vgDrawImage(imgrecipe5);
		}

		if(!ex[12].visible){
			vgLoadIdentity();
			vgTranslate(0,0);
			vgDrawImage(imgrecipe4);
		}

		if(!ex[11].visible){
			vgLoadIdentity();
			vgTranslate(0,0);
			vgDrawImage(imgrecipe3);
		}

		if(!ex[10].visible){
			vgLoadIdentity();
			vgTranslate(0,0);
			vgDrawImage(imgrecipe2);
		}

		if(!ex[9].visible){
			vgLoadIdentity();
			vgTranslate(0,0);
			vgDrawImage(imgrecipe1);
		}

		if(!ex[8].visible){
			vgLoadIdentity();
			vgTranslate(0,0);
			vgDrawImage(imgEtimer);
		}

		if(!ex[7].visible){
			vgLoadIdentity();
			vgTranslate(0,0);
			vgDrawImage(imgox);
		}

		if(!ex[6].visible){
			vgLoadIdentity();
			vgTranslate(0,0);
			vgDrawImage(imgmade);
		}

		if(!ex[5].visible){
			vgLoadIdentity();
			vgTranslate(0,0);
			vgDrawImage(imgEcup);
		}



		if(!ex[4].visible){
			vgLoadIdentity();
			vgTranslate(0,0);
			vgDrawImage(imgEmachine);
		}



		if(!ex[3].visible){
			vgLoadIdentity();
			vgTranslate(0,0);
			vgDrawImage(imgEmoney);
		}

		if(!ex[2].visible){
			vgLoadIdentity();
			vgTranslate(0,0);
			vgDrawImage(imgEmenu);
		}

		if(!ex[1].visible){
			vgLoadIdentity();
			vgTranslate(0,0);
			vgDrawImage(imgnext);

		}

		if(!ex[0].visible){
			vgLoadIdentity();
			vgTranslate(0,0);
			vgDrawImage(imgmain);

		}



		// O, X 이미지 보여주기

		if(rpush)
		{
			if(round1 || round2)
			{
				if(correct_show)
				{
					if(correct) //o이미지
					{   
						vgLoadIdentity();
						vgTranslate(0,0);
						vgDrawImage(imgO);
					}

					if(!correct) //x이미지
					{
						if(ex[15].visible)//게임방법 설명후부터 적용
						{
							vgLoadIdentity();
							vgTranslate(0,0);
							vgDrawImage(imgX);
						}
					}
				}
			}
		}



		//벌어들인 수입 계산

		if(sum>1)
		{
			vgLoadIdentity();
			vgTranslate(710,535);
			vgDrawImage(img0);
			vgLoadIdentity();
			vgTranslate(740,535);
			vgDrawImage(img0);
		}
		if(sum3==1)
		{
			vgLoadIdentity();
			vgTranslate(680,535);
			vgDrawImage(img1);
		}

		if(sum3==2)
		{
			vgLoadIdentity();
			vgTranslate(680,535);
			vgDrawImage(img2);
		}
		if(sum3==3)
		{
			vgLoadIdentity();
			vgTranslate(680,535);
			vgDrawImage(img3);
		}
		if(sum3==4)
		{
			vgLoadIdentity();
			vgTranslate(680,535);
			vgDrawImage(img4);
		}
		if(sum3==5)
		{
			vgLoadIdentity();
			vgTranslate(680,535);
			vgDrawImage(img5);
		}
		if(sum3==6)
		{
			vgLoadIdentity();
			vgTranslate(680,535);
			vgDrawImage(img6);
		}
		if(sum3==7)
		{
			vgLoadIdentity();
			vgTranslate(680,535);
			vgDrawImage(img7);
		}
		if(sum3==8)
		{
			vgLoadIdentity();
			vgTranslate(680,535);
			vgDrawImage(img8);
		}
		if(sum3==9)
		{
			vgLoadIdentity();
			vgTranslate(680,535);
			vgDrawImage(img9);
		}
		if((sum3==0)&&sum>999)
		{
			vgLoadIdentity();
			vgTranslate(680,535);
			vgDrawImage(img0);
		}
		if(sum2==1)
		{
			vgLoadIdentity();
			vgTranslate(650,535);
			vgDrawImage(img1);
		}

		if(sum2==2)
		{
			vgLoadIdentity();
			vgTranslate(650,535);
			vgDrawImage(img2);
		}
		if(sum2==3)
		{
			vgLoadIdentity();
			vgTranslate(650,535);
			vgDrawImage(img3);
		}
		if(sum2==4)
		{
			vgLoadIdentity();
			vgTranslate(650,535);
			vgDrawImage(img4);
		}
		if(sum2==5)
		{
			vgLoadIdentity();
			vgTranslate(650,535);
			vgDrawImage(img5);
		}
		if(sum2==6)
		{
			vgLoadIdentity();
			vgTranslate(650,535);
			vgDrawImage(img6);
		}
		if(sum2==7)
		{
			vgLoadIdentity();
			vgTranslate(650,535);
			vgDrawImage(img7);
		}
		if(sum2==8)
		{
			vgLoadIdentity();
			vgTranslate(650,535);
			vgDrawImage(img8);
		}
		if(sum2==9)
		{
			vgLoadIdentity();
			vgTranslate(650,535);
			vgDrawImage(img9);
		}
		if((sum2==0)&&sum>9999)
		{
			vgLoadIdentity();
			vgTranslate(650,535);
			vgDrawImage(img0);
		}
		if(sum1==1)
		{
			vgLoadIdentity();
			vgTranslate(620,535);
			vgDrawImage(img1);
		}

		if(sum1==2)
		{
			vgLoadIdentity();
			vgTranslate(620,535);
			vgDrawImage(img2);
		}
		if(sum1==3)
		{
			vgLoadIdentity();
			vgTranslate(620,535);
			vgDrawImage(img3);
		}
		if(sum1==4)
		{
			vgLoadIdentity();
			vgTranslate(620,535);
			vgDrawImage(img4);
		}
		if(sum1==5)
		{
			vgLoadIdentity();
			vgTranslate(620,535);
			vgDrawImage(img5);
		}
		if(sum1==6)
		{
			vgLoadIdentity();
			vgTranslate(620,535);
			vgDrawImage(img6);
		}
		if(sum1==7)
		{
			vgLoadIdentity();
			vgTranslate(620,535);
			vgDrawImage(img7);
		}
		if(sum1==8)
		{
			vgLoadIdentity();
			vgTranslate(620,535);
			vgDrawImage(img8);
		}
		if(sum1==9)
		{
			vgLoadIdentity();
			vgTranslate(620,535);
			vgDrawImage(img9);
		}
		if((sum1==0)&&sum>99999)
		{
			vgLoadIdentity();
			vgTranslate(620,535);
			vgDrawImage(img0);
		}



		if(round.show && round2)
		{
			vgLoadIdentity();
			vgTranslate(0,0);
			vgDrawImage(imground2);
			round1=FALSE;


		}



		//게임오버 보이기

		if(i>100&&sum<30000)
		{
			vgLoadIdentity();
			vgTranslate(0,0);
			vgDrawImage(imggameover);
			gameover=TRUE;
		}


		if(round2)
		{
			if(i>100&&sum<50000)
			{
				gameover=TRUE;
				vgLoadIdentity();
				vgTranslate(0,0);
				vgDrawImage(imggameover);
			}
		}//2라운드 실패-드로우


		if(gameend)
		{
			vgLoadIdentity();
			vgTranslate(0,0);
			vgDrawImage(imggameend);
		}


		eglSwapBuffers( display, surface );
}

void timerProc()
{

	//벌어들인 수입 자릿수 계산 -> 변수 저장
	sum1=sum/10000;
	sum2=(sum%10000)/1000;
	sum3=((sum%10000)%1000)/100;



	//스크롤 처리
	if(mug.x<=180*5)
	{
		cx=mug.x-(180*3);

		if(mug.x < 800)
		{
			if(cx<0) 
				cx=0;
		}
	}





	//라운드별 커피 주문 처리
	if(!coffee_show)
	{
		coffee_show=TRUE;

		if(round1==TRUE)
		{
			randnum=rand()%3+1;
		}
		if(round2==TRUE)
		{
			randnum=rand()%5+1;
		}
	}




	//커피의 주문을 받아 처리
	if(push)
	{
		if(gameplay)
		{
			if(coffee_show)
			{
				if(coffee_change == 0)
				{
					if( map[ (( (mug.y / 100) + 2) * mapw) + (mug.x / 180) ] =='m')
					{
						if(randnum == ESPRESSO || randnum == AMERICANO || randnum == ICEAMERICANO)
							coffee_change=1;

						else if(randnum == CAFELATTE || randnum == CAFEMOCCA)
							coffee_change=3;
					}


				}

				if(coffee_change == 1)
				{
					if( map[ (( (mug.y / 100) + 2) * mapw) + (mug.x / 180) ] =='p')
					{
						if(randnum == AMERICANO || randnum == ICEAMERICANO)
							coffee_change=2;


					}
				}


				if(coffee_change == 2)
				{
					if( map[ (( (mug.y / 100) + 2) * mapw) + (mug.x / 180) ] =='I')
					{
						if(randnum == ICEAMERICANO)
							coffee_change=3;
					}
				}


				if(coffee_change == 3)
				{
					if( map[ (( (mug.y / 100) + 2) * mapw) + (mug.x / 180) ] =='M')
					{
						if(randnum == CAFELATTE || randnum == CAFEMOCCA)
							coffee_change=4;
					}
				}


				if(coffee_change == 4)
				{
					if( map[ (( (mug.y / 100) + 2) * mapw) + (mug.x / 180) ] =='C')
					{
						if(randnum == CAFEMOCCA)
							coffee_change=5;
					}

					else if( map[ (( (mug.y / 100) + 2) * mapw) + (mug.x / 180) ] =='c')
					{
						if(randnum == CAFELATTE)
							coffee_change=5;
					}
				}

			}
		}
	}




	//시간 처리
	if(ex[14].visible)
	{
		gameplay=TRUE;

		if(gameplay)
		{
			time_count++;
		}


	}


	//라운드1에서 라운드 2로 넘어갈때 처리
	if((sum>30000) && (round2 == FALSE))
	{
		round2=TRUE;
		round.show=TRUE;

		sum=0;

		gameplay=FALSE;
		i=0;

		for(int i=0; i<1000; i++)
			timer[i].visible = FALSE;


		gameplay=TRUE;

	}


	//라운드 2에서 게임오버로 넘어갈때 처리
	if((sum>=50000) && (round2 == TRUE))
	{
		gameend=TRUE;
		gameplay=FALSE;
	}




	//1초마다 세서 i에 저장
	if(gameplay)
	{
		if(time_count==30)
		{

			timer[i].visible=TRUE;
			i++;
			time_count=0;
		}

		if(i==2)
		{			
			correct_show = FALSE;
			round.show = FALSE;
			
		}

	}

	draw();



}



// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                                MyRegisterClass(HINSTANCE hInstance);
BOOL                                InitInstance(HINSTANCE, int);
LRESULT CALLBACK        WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK        About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.
	MSG msg;
	HACCEL hAccelTable;

	// 전역 문자열을 초기화합니다.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY201221128, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY201221128));

	DWORD lastTime = GetTickCount();
	while (1)
	{
		if( PeekMessage(&msg, NULL, 0, 0, 1) )
		{
			if(!TranslateAccelerator(msg.hwnd, NULL, &msg))
			{ TranslateMessage(&msg);
			DispatchMessage(&msg); }
			if( msg.message == WM_QUIT ) break;
		}
		DWORD curTime = GetTickCount();
		if( curTime-lastTime>32 ) // 30 frame per second
		{
			lastTime = lastTime+33;
			timerProc();

		}
	}
	//기본 메시지 루프입니다.
	/*while (GetMessage(&msg, NULL, 0, 0))
	{
	if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
	{
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	}
	}*/

	return (int) msg.wParam;
}




//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
//  설명:
//
//    Windows 95에서 추가된 'RegisterClassEx' 함수보다 먼저
//    해당 코드가 Win32 시스템과 호환되도록
//    하려는 경우에만 이 함수를 사용합니다. 이 함수를 호출해야
//    해당 응용 프로그램에 연결된
//    '올바른 형식의' 작은 아이콘을 가져올 수 있습니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style                        = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc        = WndProc;
	wcex.cbClsExtra                = 0;
	wcex.cbWndExtra                = 0;
	wcex.hInstance                = hInstance;
	wcex.hIcon                        = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY201221128));
	wcex.hCursor                = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground        = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName        = MAKEINTRESOURCE(IDC_MY201221128);
	wcex.lpszClassName        = szWindowClass;
	wcex.hIconSm                = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 800,650, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND        - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT        - 주 창을 그립니다.
//  WM_DESTROY        - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 그리기 코드를 추가합니다.
		//TextOut(hdc, x, y, L"A",1);
		EndPaint(hWnd, &ps);
		break;
	case WM_CREATE:
		{

			display = eglGetDisplay( GetDC(hWnd));
			eglInitialize( display, NULL, NULL );
			eglBindAPI( EGL_OPENVG_API );
			EGLint conf_list[] = { EGL_RED_SIZE, 8,
				EGL_GREEN_SIZE, 8,
				EGL_BLUE_SIZE, 8,
				EGL_ALPHA_SIZE, 8,
				EGL_NONE };
			EGLConfig config;
			EGLint num_config;
			eglChooseConfig( display, conf_list, &config, 1, &num_config );
			surface = eglCreateWindowSurface( display, config, hWnd, NULL );
			context = eglCreateContext( display, 0, NULL, NULL );

			imgback=vgLoadImage(TEXT("back.png"));


			imgamericano1=vgLoadImage(TEXT("americano1.png"));
			imgamericano2=vgLoadImage(TEXT("americano2.png"));

			imgiceamericano=vgLoadImage(TEXT("iceamericano.png"));

			imgespresso1=vgLoadImage(TEXT("espresso1.png"));
			imgespresso2=vgLoadImage(TEXT("espresso2.png"));

			imgmorning1=vgLoadImage(TEXT("morning1.png"));
			imgmorning2=vgLoadImage(TEXT("morning2.png"));
			imglatte=vgLoadImage(TEXT("latte.png"));
			imgmocca=vgLoadImage(TEXT("mocca.png"));


			imgmachine=vgLoadImage(TEXT("machine.png"));
			imgmorning=vgLoadImage(TEXT("morning.png"));
			imgmug=vgLoadImage(TEXT("mug.png"));
			imgpot=vgLoadImage(TEXT("pot.png"));
			imgmilk=vgLoadImage(TEXT("milk.png"));

			imgui=vgLoadImage(TEXT("ui.png"));
			imgtimer=vgLoadImage(TEXT("timer.png"));

			imgsyrup_cm=vgLoadImage(TEXT("caramel syrup.png"));
			imgsyrup_cc=vgLoadImage(TEXT("choco syrup.png"));
			imgicepot=vgLoadImage(TEXT("ice pot.png"));

			imgEmoney=vgLoadImage(TEXT("Emoney.png"));
			imgEmenu=vgLoadImage(TEXT("Emenu.png"));
			imgEmachine=vgLoadImage(TEXT("Emachine.png"));
			imgEcup=vgLoadImage(TEXT("Ecup.png"));
			imgEtimer=vgLoadImage(TEXT("Etimer.png"));
			imgnext=vgLoadImage(TEXT("next.png"));
			imgox=vgLoadImage(TEXT("ox.png"));
			imgmade=vgLoadImage(TEXT("made.png"));

			imgrecipe1=vgLoadImage(TEXT("recipe1.png"));
			imgrecipe2=vgLoadImage(TEXT("recipe2.png"));
			imgrecipe3=vgLoadImage(TEXT("recipe3.png"));
			imgrecipe4=vgLoadImage(TEXT("recipe4.png"));
			imgrecipe5=vgLoadImage(TEXT("recipe5.png"));

			img0=vgLoadImage(TEXT("0.png"));
			img1=vgLoadImage(TEXT("1.png"));
			img2=vgLoadImage(TEXT("2.png"));
			img3=vgLoadImage(TEXT("3.png"));
			img4=vgLoadImage(TEXT("4.png"));
			img5=vgLoadImage(TEXT("5.png"));
			img6=vgLoadImage(TEXT("6.png"));
			img7=vgLoadImage(TEXT("7.png"));
			img8=vgLoadImage(TEXT("8.png"));
			img9=vgLoadImage(TEXT("9.png"));

			imgstart=vgLoadImage(TEXT("start.png"));
			imground1=vgLoadImage(TEXT("round1.png"));
			imground2=vgLoadImage(TEXT("round2.png"));
			imggameover=vgLoadImage(TEXT("gameover.png"));
			imggameend=vgLoadImage(TEXT("gameend.png"));

			imgmain=vgLoadImage(TEXT("main.png"));
			imgO=vgLoadImage(TEXT("O.png"));
			imgX=vgLoadImage(TEXT("X.png"));


			readMap(("map1.txt"),map,mapw,maph);

			srand(time(NULL));

			mug.x=0;
			mug.y=100;
			mug.show=TRUE;


			time_count=0;
			box[i].x=0;
			i=0;
			j=0;
			ex[j].visible=FALSE;

			for(int i=0;i<100;i++)
			{
				timer[i].visible=FALSE;
			}


			gameplay = FALSE;
			gameover=FALSE;
			gameend=FALSE;

			coffee_show=FALSE;
			coffee_change = 0;


			round1=TRUE;
			round2=FALSE;

			push = FALSE;
			rpush = FALSE;

			showo=FALSE;
			showx=FALSE;

			correct = FALSE;
			correct_show = FALSE;


			sm = new CSoundManager();
			sm->Initialize(hWnd,DSSCL_NORMAL);

			sm->Create(&ilove, TEXT("cappuccino.wav"));
			sm->Create(&fail, TEXT("fail.wav"));
			sm->Create(&success, TEXT("success.wav"));
			sm->Create(&drag, TEXT("drag.wav"));


			ilove->Play(0,1);
		}
		break;

	case WM_KEYDOWN:
		{
			push=0;
			rpush=0;

			if(wParam ==VK_RIGHT)	//오른쪽 방향키
			{
				
					if(mug.x < 180*5)
						mug.x+=180;

					drag->Play();
					if( drag->IsSoundPlaying() ) drag->Reset();
					else drag->Play();

				
			}


			if(wParam==VK_LEFT)		//왼쪽 방향키
			{

					drag->Play();
					if( drag->IsSoundPlaying() ) drag->Reset();
					else drag->Play();

					mug.x-=180;
					if(mug.x<=0)
						mug.x=0;
				
			}



			if(wParam==VK_SPACE)	//스페이스바
			{

				if(!push)
					push = TRUE;

			}



			if(wParam == VK_RETURN)		//엔터키
			{
				if(ex[j].visible==FALSE)
				{
					ex[j].visible=TRUE;
					j++;
				}


				rpush = TRUE;

				//엔터 입력시 커피 검사 수행
				if(gameplay || round2)
				{
					if(randnum == ESPRESSO)
					{
						if(coffee_change == 1)
						{
							coffee_count+=1;
							coffee_change = 0;
							coffee_show=FALSE;

							correct_show = TRUE;
							correct = TRUE;
							sum+=1500;

							success->Play();
							if( success->IsSoundPlaying() ) success->Reset();
							else success->Play();

						}

						else if(!(coffee_change == 1))
						{

							coffee_change = 0;
							coffee_show=FALSE;

							correct_show = TRUE;
							correct = FALSE;
							if(ex[15].visible)
							{
								fail->Play();
								if( fail->IsSoundPlaying() ) fail->Reset();
								else fail->Play();
							}
						}
					}

					else if(randnum == AMERICANO)
					{
						if(coffee_change == 2)
						{
							coffee_count+=1;
							coffee_change = 0;
							coffee_show=FALSE;

							correct_show = TRUE;
							correct = TRUE;
							sum+=3000;

							success->Play();
							if( success->IsSoundPlaying() ) success->Reset();
							else success->Play();
						}

						else if(!(coffee_change == 2))
						{

							coffee_change = 0;
							coffee_show=FALSE;

							correct_show = TRUE;
							correct = FALSE;
							if(ex[15].visible)
							{
								fail->Play();
								if( fail->IsSoundPlaying() ) fail->Reset();
								else fail->Play();
							}
						}
					}

					else if(randnum == ICEAMERICANO)
					{
						if(coffee_change == 3)
						{
							coffee_count+=1;
							coffee_change = 0;
							coffee_show=FALSE;

							correct_show = TRUE;
							correct = TRUE;
							sum+=3500;

							success->Play();
							if( success->IsSoundPlaying() ) success->Reset();
							else success->Play();
						}

						else if(!(coffee_change == 3))
						{

							coffee_change = 0;
							coffee_show=FALSE;

							correct_show = TRUE;
							correct = FALSE;
							if(ex[15].visible)
							{
								fail->Play();
								if( fail->IsSoundPlaying() ) fail->Reset();
								else fail->Play();
							}
						}
					}


					else if(randnum == CAFELATTE)
					{
						if(coffee_change == 5)
						{
							coffee_count+=1;
							coffee_change = 0;
							coffee_show=FALSE;

							correct_show = TRUE;
							correct = TRUE;
							sum+=4500;

							success->Play();
							if( success->IsSoundPlaying() ) success->Reset();
							else success->Play();
						}

						else if(!(coffee_change == 5))
						{

							coffee_change = 0;
							coffee_show=FALSE;

							correct_show = TRUE;
							correct = FALSE;
							if(ex[15].visible){
								fail->Play();
								if( fail->IsSoundPlaying() ) fail->Reset();
								else fail->Play();
							}
						}
					}

					else if(randnum == CAFEMOCCA)
					{
						if(coffee_change == 5)
						{
							coffee_count+=1;
							coffee_change = 0;
							coffee_show=FALSE;

							correct_show = TRUE;
							correct = TRUE;
							sum+=4500;

							success->Play();
							if( success->IsSoundPlaying() ) success->Reset();
							else success->Play();
						}

						else if(!(coffee_change == 5))
						{

							coffee_change = 0;
							coffee_show=FALSE;

							correct_show = TRUE;
							correct = FALSE;
							if(ex[15].visible){
								fail->Play();
								if( fail->IsSoundPlaying() ) fail->Reset();
								else fail->Play();
							}
						}
					}
				}

				//게임이 끝났을 시 처리
				if(gameover)
				{
					PostQuitMessage(0);
				}


				if(gameend)
				{
					PostQuitMessage(0);
				}

			}

		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
} 