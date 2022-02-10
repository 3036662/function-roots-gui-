#include "Precis.h"
#include <cmath>

// конструктор
Precis::Precis(int X, int Y, int W, int H, const char* L):Fl_Simple_Counter(X, Y, W, H, L)
{
	// устанавливаем точность по умолчанию
	prec = 2;
	this->precision(prec);
	// устанавиваем значения счетика на ноль+ один шаг
	this->value(this->increment(0,1));
};



// Изменить точность
void  Precis::change() {
	// кнопка вправо нажата
	if (this->value() > this->previous_value()) {
			if (prec < 9) {
				prec++;
				this->precision(prec);
				this->value(this->previous_value() / 10);
			}
			else this->value(this->previous_value());
	}
	// кнопка влево нажата 
	else if (this->value() < this->previous_value()) {
		if (prec > 1) {
			prec--;
			this->precision(prec);
			this->value(this->previous_value() * 10);
		}
		else this->value(this->previous_value());
	}
}

// вернет точность ( в виде 0.01) для расчета корня
double  Precis::getPrec() {
	return 1 / (pow(10, prec));
}