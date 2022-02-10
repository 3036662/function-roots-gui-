#pragma once
#include <FL/Fl_Simple_Counter.H>

// класс для выборы точности рассчетов
// наследуюет FL_Simple_Counter,но меняет реакцию на нажатие стрелок
class Precis :public Fl_Simple_Counter {
private:
	int prec;// точность знаков после запятой
public:
	// конструктор
	Precis(int X, int Y, int W, int H, const char* L = 0);

	void change(); // изменить точность по нажатию мышки
	double getPrec(); // вернет точность ( в виде 0.01) для расчета корня	
};
