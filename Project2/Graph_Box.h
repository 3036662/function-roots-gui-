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


// структура для хранения координат в пикселях
struct  Coord {
	int x;
	int y;
};

// структура для хранения координат краев камеры 
struct Camera {
	int left;
	int right;
	int top;
	int bottom;
};


//  область в которой будет рисоваться график
class Graph_box : public Fl_Box{
public:
	Graph_box(Fl_Boxtype b, int X, int Y, int W, int H, const char* l = 0);
	~Graph_box(void);
	void draw();
	int handle(int event); // определяем обработчик событий
	void Draw_func(); // рисование графика функции
	void SetFunc(int); // выбор функции для тестирования
	void Displ_calc(double eps); // отобразит рассчеты в displ

private:
	double (*pfun)(double) = NULL; // указатель на функцию
	Coord axelpos{ 300,300 }; // координаты нуля осей в пикселях
	Camera camera{ 0,0,0,0 }; // координаты окна для графика в пикселях
	int scale = 50; // масштаб пикселей на единицу шкалы
	Coord mouse_pos{ 0,0 }; // позиция мыши (для Drag)
	Coord mouse_hover_pos{ 0,0 }; //позиция в пикселях, над которой стоит мышка
	double mouseX{ 0 }, mouseY{ 0 }; // координаты мыши на сетке
	double interv_L{ 0 }, interv_R{ 0 }; // интервал для поиска корня
	bool draw_X{ FALSE }; // нужно ли рисовать корень
	bool draw_interv{ FALSE };// нужно ли рисовать интервал (флаг)
	double root{0};// корень уравнения
	double epsilon{ 0.01 }; // точность для поиска корня

	Fl_Text_Buffer* dispbuf; // текстовый буфер для окна displ

	// элементы интерфейса
	Fl_Output* mous_coord; //вывод координат мыши
	Fl_Box* interval; // интервал для поиска корня
	Fl_Text_Display* displ; // "консоль" программы
	Fl_Choice* choice; // выбор функции
	Precis* count; // выбор точности

	// Методы Класса
	int GetAbsX(double x); // пересчитывает координаты в экраанные коорд в пикселях
	int GetAbsY(double y);
	void Draw_Axels(); // рисует координатную сетку
	void Draw_root(double x); // рисует вертикальную линию в точке х
	void Draw_interv(); // рисует интервал
	
	double func(double x); // вычисляет значения изучаемой функции
	// вычисляет максимальное значение производной на отрезке между intev_L и interv_R
	double func_maxder(); 
};

// callback , пользователь выбирает функцию
void ChoiceCallback(Fl_Choice*, Graph_box*);
// callback, пользователь меняет точность
void CountCallback(Precis*, Graph_box*);