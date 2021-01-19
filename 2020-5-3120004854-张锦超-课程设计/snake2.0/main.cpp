#include<graphics.h>//图形界面的头文件
#include<stdio.h>
#include<mmsystem.h>//多媒体接口
#pragma comment(lib, "WINMM.LIB")
#include<conio.h>//getch()在这个头文件里
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

//坐标
typedef struct Coor {
	int x;
	int y;
}coor;

//方向,键值
typedef enum CH {
	up = 72,
	down = 80,
	left = 75,
	right = 77
}ch;

//蛇的信息
struct Snake {
	struct Coor scr[100];//包含100节蛇的坐标信息
	int n=0;//蛇的节数
	ch CH;//蛇的方向
	//int speed = 3;//蛇的速度
}snake;

//食物的信息
struct Food {
	coor fcr;//食物坐标
	int flag;//食物是否被吃
	int eatgrade=0;
}food;

//绘制n节彩色蛇身
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

//计算有多少节蛇
int Snakebody() {
	int i;
	i = snake.n;
	return i;
}

//计算蛇运动后的坐标
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
	Sleep(100);//蛇的速度
}

//改变蛇的方向
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

//判断蛇的状态
int Snakestatus() {
	if (snake.scr[0].x <= 9 || snake.scr[0].x >= 591 || snake.scr[0].y <= 9 || snake.scr[0].y >= 466){//撞墙结束
		return 0;
	}
	else{
		for (int i = 1; i <= snake.n; ++i){//咬到自己结束
			if (snake.scr[0].x == snake.scr[i].x && snake.scr[0].y == snake.scr[i].y){
				return 0;
			}
		}
		return 1;
	}
}

//计算食物的随机坐标
void Createfood() {
	srand(unsigned int(time(NULL)));

	food.fcr.x = 10 + (rand() % ((590 - 10) / 10)) * 10;//CreateRectRgn(10, 10, 590, 470)
	food.fcr.y = 10 + (rand() % ((470 - 10) / 10)) * 10;
	food.flag = 1;//没被吃
}

//蛇和食物出现位置夹在一起
void Eatflag() {
	for (int i = 1; i < snake.n; i++)
	{
		if (food.fcr.x == snake.scr[i].x && food.fcr.y == snake.scr[i].y)
		{
			food.flag = 0;//有重合
			Createfood();
			break;
		}
	}
}

//绘制食物
void Drawfood(){
	setlinecolor(RED);
	roundrect(food.fcr.x, food.fcr.y, food.fcr.x + 10, food.fcr.y + 10, 10, 10);
}

//建口字墙
void Buildwall() {
	setfillcolor(BROWN);//设置填充颜色
	HRGN rgn4 = CreateRectRgn(10, 470, 590, 480);//创建一块矩形区域
	setcliprgn(rgn4);//矩形区域剪裁
	DeleteObject(rgn4);//不要占用系统内存
	solidrectangle(10, 470, 590, 480);//实心的矩形区域
	//上边的墙壁
	HRGN rgn3 = CreateRectRgn(10, 0, 590, 10);//创建一块矩形区域
	setcliprgn(rgn3);//矩形区域剪裁
	DeleteObject(rgn3);//不要占用系统内存
	solidrectangle(10, 0, 590, 10);//实心的矩形区域
	//左边的墙壁
	HRGN rgn2 = CreateRectRgn(0, 0, 10, 480);//创建一块矩形区域
	setcliprgn(rgn2);//矩形区域剪裁
	DeleteObject(rgn2);//不要占用系统内存
	solidrectangle(0, 0, 10, 480);//实心的矩形区域
	//右边的墙壁
	HRGN rgn1 = CreateRectRgn(590, 0, 600, 480);//创建一块矩形区域
	setcliprgn(rgn1);//矩形区域剪裁
	DeleteObject(rgn1);//不要占用系统内存
	solidrectangle(590, 0, 600, 480);//实心的矩形区域
}

//建立游戏区
void Gamearea() {
	HRGN rgn = CreateRectRgn(10, 10, 590, 470);//创建一块矩形区域
	setcliprgn(rgn);//矩形区域剪裁
	DeleteObject(rgn);//不要占用系统内存
	solidrectangle(10, 10, 590, 470);//实心的矩形区域
	setbkcolor(RGB(220, 220, 220));
	clearcliprgn();
}

//建立客户区
void Clientarea() {
	int g = Snakebody();
	setfillcolor(YELLOW);//设置填充颜色
	HRGN rgn = CreateRectRgn(600, 0, 800, 480);//创建一块矩形区域
	setcliprgn(rgn);//矩形区域剪裁
	DeleteObject(rgn);//不要占用系统内存
	solidrectangle(600, 0, 800, 480);//实心的矩形区域
	setcolor(RED);//设置颜色
	settextstyle(25, 0, L"楷体");//设置字体 
	setbkmode(TRANSPARENT);//透明的背景风
	outtextxy(650, 50, L"贪吃蛇");
	settextstyle(15, 0, L"楷体");//设置字体 
	outtextxy(650, 150, L"[游戏说明]");
	outtextxy(650, 250, L"方向键:控制方向");
}

//对游戏进行初始化
void gameinita() {
	initgraph(800, 480);
	//墙壁区
	Buildwall();
	//客户区
	Clientarea();
	//游戏区
	Gamearea();
	
	//对蛇的初始化
	snake.scr[0].x = 290;
	snake.scr[0].y = 230;
	snake.CH = down;
}

//分数
void Grand() {
	TCHAR grade[1000];
	_stprintf(grade, _T("分数：%d"), snake.n);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(500, 30, grade);
}

//有关排行榜
//写入 读出 最高分
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

//写入 读出  第二高分
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

//写入 读出  第三高分
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

//记录的当前分数
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

//对分数进行排序
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

//游戏进行时
void playing() {
	int flag = 0, d = 1;
	while (1) {
		while (!_kbhit()) {
			if (flag == 0) {//表示食物被吃了，计算新食物坐标
				Createfood();
				Eatflag();
			}
			Drawfood();
			//当食物被吃时
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

//游戏结束效果
void Gameover() {
gmor:;
	int t;
	MOUSEMSG m;
	IMAGE img1;//定义变量 存放图片
	loadimage(&img1, L"背景3.jpg", 800, 480);//加载图片
	initgraph(800, 480);
	cleardevice();//刷屏
	putimage(0, 0, &img1);//将图片作为背景
	setcolor(BLACK);
	settextstyle(30, 0, L"楷体");//设置文字格式
	setbkmode(TRANSPARENT);// 去掉文字背景
	outtextxy(360, 140, L"你挂了");
	TCHAR grade[1000];
	_stprintf(grade, _T("最终得分：%d"), snake.n);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(330, 400, grade);
	t = Third_out();
	playthegrand(snake.n);
	snake.n = 0; 
	setfillcolor(LIGHTBLUE);
	fillrectangle(300, 300, 500, 320);
	settextstyle(15, 0, L"楷体");//设置文字格式
	outtextxy(360, 305, L"返回主菜单");
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 500 && m.y >= 300 && m.y <= 320) {
			setlinecolor(RED);
			rectangle(299, 299, 501, 321);
			//点击了返回菜单
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

//开始游戏
void Startgame() {
	int flag = 0, d=1;
	gameinita();
	playing();
	clearcliprgn();
}

//音乐效果
void Musicaffection() {
maft:;
	MOUSEMSG m;
	IMAGE img1;//定义变量 存放图片
	loadimage(&img1, L"背景2.jpg", 800, 480);//加载图片
	initgraph(800, 480);
	cleardevice();//刷屏
	putimage(0, 0, &img1);//将图片作为背景
	
	setfillcolor(LIGHTBLUE);
	fillrectangle(300, 100, 500, 120);
	fillrectangle(300, 200, 500, 220);
	fillrectangle(300, 300, 500, 320);
	settextstyle(15, 0, L"楷体");//设置文字格式
	setbkmode(TRANSPARENT);// 去掉文字背景
	outtextxy(370, 105, L"开启音乐");
	outtextxy(370, 205, L"关闭音乐");
	outtextxy(370, 305, L"返回主菜单");
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 500 && m.y >= 100 && m.y <= 120) {
			setlinecolor(RED);
			rectangle(299, 99, 501, 121);
			//如果点击开启音乐
			if (m.uMsg == WM_LBUTTONDOWN) {
				mciSendString(L"open YELLOW.mp3 alias asd", NULL, 0, NULL);
				mciSendString(L"play asd  repeat", NULL, 0, NULL);
				goto maft;
			}
		}
		else if (m.x >= 300 && m.x <= 500 && m.y >= 200 && m.y <= 220) {//
			setlinecolor(RED);
			rectangle(299, 199, 501, 221);
			//点击了关闭音乐
			if (m.uMsg == WM_LBUTTONDOWN) {
				mciSendString(L"stop asd ", NULL, 0, NULL);
				goto maft;
			}
		}
		else if (m.x >= 300 && m.x <= 500 && m.y >= 300 && m.y <= 320) {
			setlinecolor(RED);
			rectangle(299, 299, 501, 321);
			//点击了返回菜单
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

//排行榜
void Rankinglist() {
rkl:;
	int a, b, c;
	a = Hight_out();
	b = Second_out();
	c = Third_out();
	MOUSEMSG m;
	IMAGE img1;//定义变量 存放图片
	loadimage(&img1, L"背景4.jpg", 800, 480);//加载图片
	initgraph(800, 480);
	cleardevice();//刷屏
	putimage(0, 0, &img1);//将图片作为背景
	setfillcolor(LIGHTBLUE);
	fillrectangle(300, 400, 500, 420);
	settextstyle(15, 0, L"楷体");//设置文字格式
	setbkmode(TRANSPARENT);// 去掉文字背景
	outtextxy(370, 405, L"返回主菜单");
	settextstyle(20, 0, L"楷体");//设置文字格式
	TCHAR grade1[1000],grade2[1000],grade3[1000];
	_stprintf(grade1, _T("第一名：%d"), a);
	_stprintf(grade2, _T("第二名：%d"), b);
	_stprintf(grade3, _T("第三名：%d"), c);
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
			//点击了返回菜单
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

//主菜单
void Drawmeun() {
dmu:;
	MOUSEMSG m;
	IMAGE img;//定义变量 存放图片
	loadimage(&img, L"背景.jpg", 800, 480);//加载图片
	initgraph(800, 480);//初始化一个800*480的窗口
	
	//setbkcolor(WHITE);
	cleardevice();//清屏
	putimage(0, 0, &img);//将图片作为背景
	setfillcolor(LIGHTBLUE);
	fillrectangle(300, 100, 500, 120);
	fillrectangle(300, 200, 500, 220);
	fillrectangle(300, 300, 500, 320);
	fillrectangle(300, 400, 500, 420);

	settextstyle(15, 0, L"楷体");//设置文字格式
	setbkmode(TRANSPARENT);// 去掉文字背景
	outtextxy(370, 105, L"开始游戏");
	outtextxy(370, 205, L"音乐效果");
	outtextxy(377, 305, L"排行榜");
	outtextxy(370, 405, L"退出游戏");
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 500 && m.y >= 100 && m.y <= 120) {
			setlinecolor(RED);
			rectangle(299, 99, 501, 121);
			//如果点击开始游戏
			if (m.uMsg == WM_LBUTTONDOWN) {
				Startgame();
				goto dmu;
			}
		}
		else if (m.x >= 300 && m.x <= 500 && m.y >= 200 && m.y <= 220) {//
			setlinecolor(RED);
			rectangle(299, 199, 501, 221);
			//点击了音乐效果
			if (m.uMsg == WM_LBUTTONDOWN) {
				Musicaffection();
				goto dmu;
			}
		}
		else if (m.x >= 300 && m.x <= 500 && m.y >= 300 && m.y <= 320) {
			setlinecolor(RED);
			rectangle(299, 299, 501, 321);
			//点击了排行榜
			if (m.uMsg == WM_LBUTTONDOWN) {
				Rankinglist();
				goto dmu;
			}
		}
		else if (m.x >= 300 && m.x <= 500 && m.y >= 400 && m.y <= 420) {
			setlinecolor(RED);
			rectangle(299, 399, 501, 421);
			//点击了退出游戏
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





