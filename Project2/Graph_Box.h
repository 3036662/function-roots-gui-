#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>
#include <FL/fl_utf8.h>
#include <FL/Fl_Text_Display.h>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Simple_Counter.H>
#include <cmath>
#include "test_functions.h"
#include "Precis.h"


// ��������� ��� �������� ��������� � ��������
struct  Coord {
	int x;
	int y;
};

// ��������� ��� �������� ��������� ����� ������ 
struct Camera {
	int left;
	int right;
	int top;
	int bottom;
};


//  ������� � ������� ����� ���������� ������
class Graph_box : public Fl_Box{
public:
	Graph_box(Fl_Boxtype b, int X, int Y, int W, int H, const char* l = 0);
	~Graph_box(void);
	void draw();
	int handle(int event); // ���������� ���������� �������
	void Draw_func(); // ��������� ������� �������
	void SetFunc(int); // ����� ������� ��� ������������
	void Displ_calc(double eps); // ��������� �������� � displ

private:
	double (*pfun)(double) = NULL; // ��������� �� �������
	Coord axelpos{ 300,300 }; // ���������� ���� ���� � ��������
	Camera camera{ 0,0,0,0 }; // ���������� ���� ��� ������� � ��������
	int scale = 50; // ������� �������� �� ������� �����
	Coord mouse_pos{ 0,0 }; // ������� ���� (��� Drag)
	Coord mouse_hover_pos{ 0,0 }; //������� � ��������, ��� ������� ����� �����
	double mouseX{ 0 }, mouseY{ 0 }; // ���������� ���� �� �����
	double interv_L{ 0 }, interv_R{ 0 }; // �������� ��� ������ �����
	bool draw_X{ FALSE }; // ����� �� �������� ������
	bool draw_interv{ FALSE };// ����� �� �������� �������� (����)
	double root{0};// ������ ���������
	double epsilon{ 0.01 }; // �������� ��� ������ �����

	Fl_Text_Buffer* dispbuf; // ��������� ����� ��� ���� displ

	// �������� ����������
	Fl_Output* mous_coord; //����� ��������� ����
	Fl_Box* interval; // �������� ��� ������ �����
	Fl_Text_Display* displ; // "�������" ���������
	Fl_Choice* choice; // ����� �������
	Precis* count; // ����� ��������

	// ������ ������
	int GetAbsX(double x); // ������������� ���������� � ��������� ����� � ��������
	int GetAbsY(double y);
	void Draw_Axels(); // ������ ������������ �����
	void Draw_root(double x); // ������ ������������ ����� � ����� �
	void Draw_interv(); // ������ ��������
	
	double func(double x); // ��������� �������� ��������� �������
	// ��������� ������������ �������� ����������� �� ������� ����� intev_L � interv_R
	double func_maxder(); 
};

// callback , ������������ �������� �������
void ChoiceCallback(Fl_Choice*, Graph_box*);
// callback, ������������ ������ ��������
void CountCallback(Precis*, Graph_box*);