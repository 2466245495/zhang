#include<graphics.h>//ͼ�ν����ͷ�ļ�
#include<stdio.h>
#include<mmsystem.h>//��ý��ӿ�
#pragma comment(lib, "WINMM.LIB")
#include<conio.h>//getch()�����ͷ�ļ���
#include<time.h>
void Startgame();
void Musicaffection();
void Drawmeun();
void Drawmeun();
void gameinita();
void Drawsnake();
void ChangesnakeCH();
void Createfood();
void Eatflag();
void Drawfood();
void Buildwall();
void Gamearea();
void Gameover();
void Hight_Score_in(int Hight_Score);
int Hight_out();
void Second_Score_in(int Second_Score);
int Second_out();
void Third_Score_in(int Third_Score);
int Third_out();
void playthegrand(int c);

//����
typedef struct Coor {
	int x;
	int y;
}coor;

//����,��ֵ
typedef enum CH {
	up = 72,
	down = 80,
	left = 75,
	right = 77
}ch;

//�ߵ���Ϣ
struct Snake {
	struct Coor scr[100];//����100���ߵ�������Ϣ
	int n=0;//�ߵĽ���
	ch CH;//�ߵķ���
	//int speed = 3;//�ߵ��ٶ�
}snake;

//ʳ�����Ϣ
struct Food {
	coor fcr;//ʳ������
	int flag;//ʳ���Ƿ񱻳�
	int eatgrade=0;
}food;

//����n�ڲ�ɫ����
void Drawsnake() {
	for (int i = snake.n; i >= 0; i--) {
		fillrectangle(snake.scr[i].x, snake.scr[i].y, snake.scr[i].x + 10, snake.scr[i].y + 10);
		setfillcolor(RED);
		int k;
		k = (i + 4) % 4;
		switch (k) {
		case 0:
			fillrectangle(snake.scr[i].x, snake.scr[i].y, snake.scr[i].x + 10, snake.scr[i].y + 10);
			k = 1;
			break;
		case 1:
			setfillcolor(CYAN);
			fillrectangle(snake.scr[i].x, snake.scr[i].y, snake.scr[i].x + 10, snake.scr[i].y + 10);
			k = 2;
			break;
		case 2:
			setfillcolor(BLUE);
			fillrectangle(snake.scr[i].x, snake.scr[i].y, snake.scr[i].x + 10, snake.scr[i].y + 10);
			k = 3;
			break;
		case 3:
			setfillcolor(GREEN);
			fillrectangle(snake.scr[i].x, snake.scr[i].y, snake.scr[i].x + 10, snake.scr[i].y + 10);
			k = 4;
			break;
		case 4:
			setfillcolor(MAGENTA);
			fillrectangle(snake.scr[i].x, snake.scr[i].y, snake.scr[i].x + 10, snake.scr[i].y + 10);
			k = 0;
			break;
		}
	}
	
}

//�����ж��ٽ���
int Snakebody() {
	int i;
	i = snake.n;
	return i;
}

//�������˶��������
void Snakemove() {
	for (int i = snake.n; i > 0; i--) {
		snake.scr[i].x = snake.scr[i - 1].x;
		snake.scr[i].y = snake.scr[i - 1].y;
	}
	switch (snake.CH) {
	case up:
		snake.scr[0].y -= 10;
		break;
	case down:
		snake.scr[0].y += 10;
		break;
	case left:
		snake.scr[0].x -= 10;
		break;
	case right:
		snake.scr[0].x += 10;
		break;
	}

	Drawsnake();
	Sleep(100);//�ߵ��ٶ�
}

//�ı��ߵķ���
void ChangesnakeCH() {
	int input;
	input = _getch();
	switch (input) {
	case up:
		if (snake.CH != down) {
			snake.CH = up;
		}
		break;
	case down:
		if (snake.CH != up) {
			snake.CH = down;
		}
		break;
	case left:
		if (snake.CH != right) {
			snake.CH = left;
		}
		break;
	case right:
		if (snake.CH != left) {
			snake.CH = right;
		}
		break;
	}

}

//�ж��ߵ�״̬
int Snakestatus() {
	if (snake.scr[0].x <= 9 || snake.scr[0].x >= 591 || snake.scr[0].y <= 9 || snake.scr[0].y >= 466){//ײǽ����
		return 0;
	}
	else{
		for (int i = 1; i <= snake.n; ++i){//ҧ���Լ�����
			if (snake.scr[0].x == snake.scr[i].x && snake.scr[0].y == snake.scr[i].y){
				return 0;
			}
		}
		return 1;
	}
}

//����ʳ����������
void Createfood() {
	srand(unsigned int(time(NULL)));

	food.fcr.x = 10 + (rand() % ((590 - 10) / 10)) * 10;//CreateRectRgn(10, 10, 590, 470)
	food.fcr.y = 10 + (rand() % ((470 - 10) / 10)) * 10;
	food.flag = 1;//û����
}

//�ߺ�ʳ�����λ�ü���һ��
void Eatflag() {
	for (int i = 1; i < snake.n; i++)
	{
		if (food.fcr.x == snake.scr[i].x && food.fcr.y == snake.scr[i].y)
		{
			food.flag = 0;//���غ�
			Createfood();
			break;
		}
	}
}

//����ʳ��
void Drawfood(){
	setlinecolor(RED);
	roundrect(food.fcr.x, food.fcr.y, food.fcr.x + 10, food.fcr.y + 10, 10, 10);
}

//������ǽ
void Buildwall() {
	setfillcolor(BROWN);//���������ɫ
	HRGN rgn4 = CreateRectRgn(10, 470, 590, 480);//����һ���������
	setcliprgn(rgn4);//�����������
	DeleteObject(rgn4);//��Ҫռ��ϵͳ�ڴ�
	solidrectangle(10, 470, 590, 480);//ʵ�ĵľ�������
	//�ϱߵ�ǽ��
	HRGN rgn3 = CreateRectRgn(10, 0, 590, 10);//����һ���������
	setcliprgn(rgn3);//�����������
	DeleteObject(rgn3);//��Ҫռ��ϵͳ�ڴ�
	solidrectangle(10, 0, 590, 10);//ʵ�ĵľ�������
	//��ߵ�ǽ��
	HRGN rgn2 = CreateRectRgn(0, 0, 10, 480);//����һ���������
	setcliprgn(rgn2);//�����������
	DeleteObject(rgn2);//��Ҫռ��ϵͳ�ڴ�
	solidrectangle(0, 0, 10, 480);//ʵ�ĵľ�������
	//�ұߵ�ǽ��
	HRGN rgn1 = CreateRectRgn(590, 0, 600, 480);//����һ���������
	setcliprgn(rgn1);//�����������
	DeleteObject(rgn1);//��Ҫռ��ϵͳ�ڴ�
	solidrectangle(590, 0, 600, 480);//ʵ�ĵľ�������
}

//������Ϸ��
void Gamearea() {
	HRGN rgn = CreateRectRgn(10, 10, 590, 470);//����һ���������
	setcliprgn(rgn);//�����������
	DeleteObject(rgn);//��Ҫռ��ϵͳ�ڴ�
	solidrectangle(10, 10, 590, 470);//ʵ�ĵľ�������
	setbkcolor(RGB(220, 220, 220));
	clearcliprgn();
}

//�����ͻ���
void Clientarea() {
	int g = Snakebody();
	setfillcolor(YELLOW);//���������ɫ
	HRGN rgn = CreateRectRgn(600, 0, 800, 480);//����һ���������
	setcliprgn(rgn);//�����������
	DeleteObject(rgn);//��Ҫռ��ϵͳ�ڴ�
	solidrectangle(600, 0, 800, 480);//ʵ�ĵľ�������
	setcolor(RED);//������ɫ
	settextstyle(25, 0, L"����");//�������� 
	setbkmode(TRANSPARENT);//͸���ı�����
	outtextxy(650, 50, L"̰����");
	settextstyle(15, 0, L"����");//�������� 
	outtextxy(650, 150, L"[��Ϸ˵��]");
	outtextxy(650, 250, L"�����:���Ʒ���");
}

//����Ϸ���г�ʼ��
void gameinita() {
	initgraph(800, 480);
	//ǽ����
	Buildwall();
	//�ͻ���
	Clientarea();
	//��Ϸ��
	Gamearea();
	
	//���ߵĳ�ʼ��
	snake.scr[0].x = 290;
	snake.scr[0].y = 230;
	snake.CH = down;
}

//����
void Grand() {
	TCHAR grade[1000];
	_stprintf(grade, _T("������%d"), snake.n);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(500, 30, grade);
}

//�й����а�
//д�� ���� ��߷�
void Hight_Score_in(int Hight_Score) {
	FILE* fp = fopen("Hight_Score.txt", "w");
	if (NULL != fp) {
		fprintf(fp, "%d", Hight_Score);
	}

	fclose(fp);
}
int Hight_out() {
	int h = 0;
	FILE* fp = fopen("Hight_Score.txt", "r");
	if (NULL != fp) {
		fscanf(fp, "%d", &h);
	}
	fclose(fp);
	return h;
}

//д�� ����  �ڶ��߷�
void Second_Score_in(int Second_Score) {
	FILE* fp = fopen("Second_Score.txt", "w");
	if (NULL != fp) {
		fprintf(fp, "%d", Second_Score);
	}

	fclose(fp);
}
int Second_out() {
	int s = 0;
	FILE* fp = fopen("Second_Score.txt", "r");
	if (NULL != fp) {
		fscanf(fp, "%d", &s);
	}
	fclose(fp);
	return s;
}

//д�� ����  �����߷�
void Third_Score_in(int Third_Score) {
	FILE* fp = fopen("Third_Score.txt", "w");
	if (NULL != fp) {
		fprintf(fp, "%d", Third_Score);
	}

	fclose(fp);
}
int Third_out() {
	int t = 0;
	FILE* fp = fopen("Third_Score.txt", "r");
	if (NULL != fp) {
		fscanf(fp, "%d", &t);
	}
	fclose(fp);
	return t;
}

//��¼�ĵ�ǰ����
void fourth_Score_in(int fourth_Score) {
	FILE* fp = fopen("fourth_Score.txt", "w");
	if (NULL != fp) {
		fprintf(fp, "%d", fourth_Score);
	}

	fclose(fp);
}
int fourth_out() {
	int t = 0;
	FILE* fp = fopen("fourth_Score.txt", "r");
	if (NULL != fp) {
		fscanf(fp, "%d", &t);
	}
	fclose(fp);
	return t;
}

//�Է�����������
void playthegrand(int c) {
	int d, e, f,g, o;
	fourth_Score_in(c);
	d = Hight_out();
	e = Second_out();
	f = Third_out();
	g = fourth_out();
	if (d < e) {
		o = d;
		d = e;
		e = o;
	}
	if (d < f) {
		o = d;
		d = f;
		f = o;
	}
	if (d < g) {
		o = d;
		d = g;
		g = o;
	}
	if (e < f) {
		o = e;
		e = f;
		f = o;
	}
	if (e < g) {
		o = e;
		e = g;
		g = o;
	}
	if (f < g) {
		o = f;
		f = g;
		g = o;
	}
	Hight_Score_in(d);
	Second_Score_in(e);
	Third_Score_in(f);
	fourth_Score_in(g);
}

//��Ϸ����ʱ
void playing() {
	int flag = 0, d = 1;
	while (1) {
		while (!_kbhit()) {
			if (flag == 0) {//��ʾʳ�ﱻ���ˣ�������ʳ������
				Createfood();
				Eatflag();
			}
			Drawfood();
			//��ʳ�ﱻ��ʱ
			if (snake.scr[0].x == food.fcr.x && snake.scr[0].y == food.fcr.y) {
				snake.n++;
				food.flag = 0;
			}
			else {
				food.flag = 1;
			}
			flag = food.flag;
			Snakemove();
			clearcliprgn();
			d = Snakestatus();
			Grand();
		}
		ChangesnakeCH();
		if (d == 0) {
			system("pause");
			Gameover();
			
			clearcliprgn();
			break;
		}
		//ChangesnakeCH();
	}
}

//��Ϸ����Ч��
void Gameover() {
gmor:;
	int t;
	MOUSEMSG m;
	IMAGE img1;//������� ���ͼƬ
	loadimage(&img1, L"����3.jpg", 800, 480);//����ͼƬ
	initgraph(800, 480);
	cleardevice();//ˢ��
	putimage(0, 0, &img1);//��ͼƬ��Ϊ����
	setcolor(BLACK);
	settextstyle(30, 0, L"����");//�������ָ�ʽ
	setbkmode(TRANSPARENT);// ȥ�����ֱ���
	outtextxy(360, 140, L"�����");
	TCHAR grade[1000];
	_stprintf(grade, _T("���յ÷֣�%d"), snake.n);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(330, 400, grade);
	t = Third_out();
	playthegrand(snake.n);
	snake.n = 0; 
	setfillcolor(LIGHTBLUE);
	fillrectangle(300, 300, 500, 320);
	settextstyle(15, 0, L"����");//�������ָ�ʽ
	outtextxy(360, 305, L"�������˵�");
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 500 && m.y >= 300 && m.y <= 320) {
			setlinecolor(RED);
			rectangle(299, 299, 501, 321);
			//����˷��ز˵�
			if (m.uMsg == WM_LBUTTONDOWN) {
				goto cgmor;
			}
			else {
				setlinecolor(WHITE);
				rectangle(299, 299, 501, 321);
			}
		}
	}
cgmor:;
}

//��ʼ��Ϸ
void Startgame() {
	int flag = 0, d=1;
	gameinita();
	playing();
	clearcliprgn();
}

//����Ч��
void Musicaffection() {
maft:;
	MOUSEMSG m;
	IMAGE img1;//������� ���ͼƬ
	loadimage(&img1, L"����2.jpg", 800, 480);//����ͼƬ
	initgraph(800, 480);
	cleardevice();//ˢ��
	putimage(0, 0, &img1);//��ͼƬ��Ϊ����
	
	setfillcolor(LIGHTBLUE);
	fillrectangle(300, 100, 500, 120);
	fillrectangle(300, 200, 500, 220);
	fillrectangle(300, 300, 500, 320);
	settextstyle(15, 0, L"����");//�������ָ�ʽ
	setbkmode(TRANSPARENT);// ȥ�����ֱ���
	outtextxy(370, 105, L"��������");
	outtextxy(370, 205, L"�ر�����");
	outtextxy(370, 305, L"�������˵�");
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 500 && m.y >= 100 && m.y <= 120) {
			setlinecolor(RED);
			rectangle(299, 99, 501, 121);
			//��������������
			if (m.uMsg == WM_LBUTTONDOWN) {
				mciSendString(L"open YELLOW.mp3 alias asd", NULL, 0, NULL);
				mciSendString(L"play asd  repeat", NULL, 0, NULL);
				goto maft;
			}
		}
		else if (m.x >= 300 && m.x <= 500 && m.y >= 200 && m.y <= 220) {//
			setlinecolor(RED);
			rectangle(299, 199, 501, 221);
			//����˹ر�����
			if (m.uMsg == WM_LBUTTONDOWN) {
				mciSendString(L"stop asd ", NULL, 0, NULL);
				goto maft;
			}
		}
		else if (m.x >= 300 && m.x <= 500 && m.y >= 300 && m.y <= 320) {
			setlinecolor(RED);
			rectangle(299, 299, 501, 321);
			//����˷��ز˵�
			if (m.uMsg == WM_LBUTTONDOWN) {
				goto cmaft;
			}
		}
		else {
			setlinecolor(WHITE);
			rectangle(299, 99, 501, 121);
			rectangle(299, 199, 501, 221);
			rectangle(299, 299, 501, 321);
		}
	}
cmaft:;
}

//���а�
void Rankinglist() {
rkl:;
	int a, b, c;
	a = Hight_out();
	b = Second_out();
	c = Third_out();
	MOUSEMSG m;
	IMAGE img1;//������� ���ͼƬ
	loadimage(&img1, L"����4.jpg", 800, 480);//����ͼƬ
	initgraph(800, 480);
	cleardevice();//ˢ��
	putimage(0, 0, &img1);//��ͼƬ��Ϊ����
	setfillcolor(LIGHTBLUE);
	fillrectangle(300, 400, 500, 420);
	settextstyle(15, 0, L"����");//�������ָ�ʽ
	setbkmode(TRANSPARENT);// ȥ�����ֱ���
	outtextxy(370, 405, L"�������˵�");
	settextstyle(20, 0, L"����");//�������ָ�ʽ
	TCHAR grade1[1000],grade2[1000],grade3[1000];
	_stprintf(grade1, _T("��һ����%d"), a);
	_stprintf(grade2, _T("�ڶ�����%d"), b);
	_stprintf(grade3, _T("��������%d"), c);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(360, 105, grade1);
	outtextxy(360, 205, grade2);
	outtextxy(360, 305, grade3);
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 500 && m.y >= 400 && m.y <= 420) {
			setlinecolor(RED);
			rectangle(299, 399, 501, 421);
			//����˷��ز˵�
			if (m.uMsg == WM_LBUTTONDOWN) {
				goto crkl;
			}
		}
		else {
			setlinecolor(WHITE);
			rectangle(299, 399, 501, 421);
		}
	}
crkl:;
}

//���˵�
void Drawmeun() {
dmu:;
	MOUSEMSG m;
	IMAGE img;//������� ���ͼƬ
	loadimage(&img, L"����.jpg", 800, 480);//����ͼƬ
	initgraph(800, 480);//��ʼ��һ��800*480�Ĵ���
	
	//setbkcolor(WHITE);
	cleardevice();//����
	putimage(0, 0, &img);//��ͼƬ��Ϊ����
	setfillcolor(LIGHTBLUE);
	fillrectangle(300, 100, 500, 120);
	fillrectangle(300, 200, 500, 220);
	fillrectangle(300, 300, 500, 320);
	fillrectangle(300, 400, 500, 420);

	settextstyle(15, 0, L"����");//�������ָ�ʽ
	setbkmode(TRANSPARENT);// ȥ�����ֱ���
	outtextxy(370, 105, L"��ʼ��Ϸ");
	outtextxy(370, 205, L"����Ч��");
	outtextxy(377, 305, L"���а�");
	outtextxy(370, 405, L"�˳���Ϸ");
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 500 && m.y >= 100 && m.y <= 120) {
			setlinecolor(RED);
			rectangle(299, 99, 501, 121);
			//��������ʼ��Ϸ
			if (m.uMsg == WM_LBUTTONDOWN) {
				Startgame();
				goto dmu;
			}
		}
		else if (m.x >= 300 && m.x <= 500 && m.y >= 200 && m.y <= 220) {//
			setlinecolor(RED);
			rectangle(299, 199, 501, 221);
			//���������Ч��
			if (m.uMsg == WM_LBUTTONDOWN) {
				Musicaffection();
				goto dmu;
			}
		}
		else if (m.x >= 300 && m.x <= 500 && m.y >= 300 && m.y <= 320) {
			setlinecolor(RED);
			rectangle(299, 299, 501, 321);
			//��������а�
			if (m.uMsg == WM_LBUTTONDOWN) {
				Rankinglist();
				goto dmu;
			}
		}
		else if (m.x >= 300 && m.x <= 500 && m.y >= 400 && m.y <= 420) {
			setlinecolor(RED);
			rectangle(299, 399, 501, 421);
			//������˳���Ϸ
			if (m.uMsg == WM_LBUTTONDOWN) {
				break;
			}
		}
		else {
			setlinecolor(WHITE);
			rectangle(299, 99, 501, 121);
			rectangle(299, 199, 501, 221);
			rectangle(299, 299, 501, 321);
			rectangle(299, 399, 501, 421);
		}
	}
	closegraph();
}

int main() {
	Drawmeun();
	return 0;
}





