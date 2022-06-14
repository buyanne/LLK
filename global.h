#pragma once
class Vertex {
public:
	
	int row, col, info;

public:
	Vertex() {
		row = col = info = 0;
	}
	Vertex(int a, int b, int c) {
		row = a;
		col = b;
		info = c;
	}

	bool operator== (const Vertex & node) {
		return row == node.row && col == node.col && info == node.info;
	}
};


#define BLANK				-1		//判断是否为空
#define MAX_ROW				14		//初始行数
#define MAX_COL				15		//初始列数
#define MAX_VERTEX_NUM      210		//顶点数
#define MAX_PIC_NUM         15		//图片花色
#define REPEAT_NUM          14		//每种花色图片个数
#define MAP_TOP             50		//游戏地图左上角纵坐标
#define MAP_LETF            50		//游戏地图左上角横坐标
#define PIC_HEIGHT          40		//游戏地图高度
#define PIC_WIDTH           40		//游戏地图宽度
#define MAX_TIME			300
//设置不同的游戏界面
#define LEISURE_MODE		10
#define BASIC_MODE			20
#define BREAKTHROUGH_MODE	30
