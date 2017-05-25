// 2012211mapw.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
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

int coffee_show;   //true or false , Ŀ�� ���� (���ʹ����� �����)
int coffee_change;   //Ŀ�� ����� ���� �̹�����ȯ (�����̽� ������)
int coffee_count;   //���� Ŀ�� ���� ����

int time_count;
int i, j;

int correct;
int correct_show;
int showo, showx; //o�̹��� x�̹���

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

// ���� ����:
HINSTANCE hInst;                                                                // ���� �ν��Ͻ��Դϴ�.
TCHAR szTitle[MAX_LOADSTRING];                                        // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];                        // �⺻ â Ŭ���� �̸��Դϴ�.
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
	// transform�� image�� ����ǰ� ��
	vgSeti( VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
	// ȭ���� ��Ȳ������ �����.
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
				if(randnum==ESPRESSO) //���������� �÷���
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

				else if(randnum==AMERICANO)   //�Ƹ޸�ī�� �÷���
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


				else if(randnum==ICEAMERICANO)   //���̽��Ƹ޸�ī�� �÷���
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

				else if(randnum==CAFELATTE)   //ī��� �÷���
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


				else if(randnum==CAFEMOCCA)   //ī���ī �÷���
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


		//UI ����
		vgLoadIdentity();
		vgTranslate(0,0);
		vgDrawImage(imgui);



		//UI ��� �ڽ��ȿ� �� �ֹ� ����
		if(gameplay)
		{
			if(coffee_show)
			{
				if(randnum==ESPRESSO)   //���������� �ֹ�
				{

					vgLoadIdentity();
					vgTranslate(5,490);
					vgScale(0.7, 0.7);
					vgDrawImage(imgespresso2);
				}

				else if(randnum==AMERICANO)   //�Ƹ޸�ī�� �ֹ�
				{
					vgLoadIdentity();
					vgTranslate(5,490);
					vgScale(0.7, 0.7);
					vgDrawImage(imgamericano2);
				}

				else if(randnum==ICEAMERICANO)   //�Ƹ޸�ī�� �ֹ�
				{
					vgLoadIdentity();
					vgTranslate(5,490);
					vgScale(0.7, 0.7);
					vgDrawImage(imgiceamericano);
				}

				else if(randnum==CAFELATTE)   //ī��� �ֹ�
				{
					vgLoadIdentity();
					vgTranslate(5,490);
					vgScale(0.7, 0.7);
					vgDrawImage(imglatte);
				}

				else if(randnum==CAFEMOCCA)   //ī���ī �ֹ�
				{
					vgLoadIdentity();
					vgTranslate(5,490);
					vgScale(0.7, 0.7);
					vgDrawImage(imgmocca);
				}
			}
		}


		//TIMER ó��
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

		//���� ��� �����ֱ�

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



		// O, X �̹��� �����ֱ�

		if(rpush)
		{
			if(round1 || round2)
			{
				if(correct_show)
				{
					if(correct) //o�̹���
					{   
						vgLoadIdentity();
						vgTranslate(0,0);
						vgDrawImage(imgO);
					}

					if(!correct) //x�̹���
					{
						if(ex[15].visible)//���ӹ�� �����ĺ��� ����
						{
							vgLoadIdentity();
							vgTranslate(0,0);
							vgDrawImage(imgX);
						}
					}
				}
			}
		}



		//������� ���� ���

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



		//���ӿ��� ���̱�

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
		}//2���� ����-��ο�


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

	//������� ���� �ڸ��� ��� -> ���� ����
	sum1=sum/10000;
	sum2=(sum%10000)/1000;
	sum3=((sum%10000)%1000)/100;



	//��ũ�� ó��
	if(mug.x<=180*5)
	{
		cx=mug.x-(180*3);

		if(mug.x < 800)
		{
			if(cx<0) 
				cx=0;
		}
	}





	//���庰 Ŀ�� �ֹ� ó��
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




	//Ŀ���� �ֹ��� �޾� ó��
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




	//�ð� ó��
	if(ex[14].visible)
	{
		gameplay=TRUE;

		if(gameplay)
		{
			time_count++;
		}


	}


	//����1���� ���� 2�� �Ѿ�� ó��
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


	//���� 2���� ���ӿ����� �Ѿ�� ó��
	if((sum>=50000) && (round2 == TRUE))
	{
		gameend=TRUE;
		gameplay=FALSE;
	}




	//1�ʸ��� ���� i�� ����
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



// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
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

	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	MSG msg;
	HACCEL hAccelTable;

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY201221128, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
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
	//�⺻ �޽��� �����Դϴ�.
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
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
//  ����:
//
//    Windows 95���� �߰��� 'RegisterClassEx' �Լ����� ����
//    �ش� �ڵ尡 Win32 �ý��۰� ȣȯ�ǵ���
//    �Ϸ��� ��쿡�� �� �Լ��� ����մϴ�. �� �Լ��� ȣ���ؾ�
//    �ش� ���� ���α׷��� �����
//    '�ùٸ� ������' ���� �������� ������ �� �ֽ��ϴ�.
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
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

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
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND        - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT        - �� â�� �׸��ϴ�.
//  WM_DESTROY        - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
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
		// �޴� ������ ���� �м��մϴ�.
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
		// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
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

			if(wParam ==VK_RIGHT)	//������ ����Ű
			{
				
					if(mug.x < 180*5)
						mug.x+=180;

					drag->Play();
					if( drag->IsSoundPlaying() ) drag->Reset();
					else drag->Play();

				
			}


			if(wParam==VK_LEFT)		//���� ����Ű
			{

					drag->Play();
					if( drag->IsSoundPlaying() ) drag->Reset();
					else drag->Play();

					mug.x-=180;
					if(mug.x<=0)
						mug.x=0;
				
			}



			if(wParam==VK_SPACE)	//�����̽���
			{

				if(!push)
					push = TRUE;

			}



			if(wParam == VK_RETURN)		//����Ű
			{
				if(ex[j].visible==FALSE)
				{
					ex[j].visible=TRUE;
					j++;
				}


				rpush = TRUE;

				//���� �Է½� Ŀ�� �˻� ����
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

				//������ ������ �� ó��
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

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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