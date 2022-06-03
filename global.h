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

#define BLANK				-1		//�ж��Ƿ�Ϊ��
#define MAX_ROW				16		//��ʼ����
#define MAX_COL				15		//��ʼ����
#define MAX_VERTEX_NUM      240		//������
#define MAX_PIC_NUM         15		//ͼƬ��ɫ
#define REPEAT_NUM          16		//ÿ�ֻ�ɫͼƬ����
#define MAP_TOP             50		//��Ϸ��ͼ���Ͻ�������
#define MAP_LETF            50		//��Ϸ��ͼ���ϽǺ�����
#define PIC_HEIGHT          40		//��Ϸ��ͼ�߶�
#define PIC_WIDTH           40		//��Ϸ��ͼ���
#define MAX_TIME			300
//���ò�ͬ����Ϸ����
#define LEISURE_MODE		10
#define BASIC_MODE			20
#define BREAKTHROUGH_MODE	30
