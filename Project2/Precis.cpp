#include "Precis.h"
#include <cmath>

// �����������
Precis::Precis(int X, int Y, int W, int H, const char* L):Fl_Simple_Counter(X, Y, W, H, L)
{
	// ������������� �������� �� ���������
	prec = 2;
	this->precision(prec);
	// ������������ �������� ������� �� ����+ ���� ���
	this->value(this->increment(0,1));
};



// �������� ��������
void  Precis::change() {
	// ������ ������ ������
	if (this->value() > this->previous_value()) {
			if (prec < 9) {
				prec++;
				this->precision(prec);
				this->value(this->previous_value() / 10);
			}
			else this->value(this->previous_value());
	}
	// ������ ����� ������ 
	else if (this->value() < this->previous_value()) {
		if (prec > 1) {
			prec--;
			this->precision(prec);
			this->value(this->previous_value() * 10);
		}
		else this->value(this->previous_value());
	}
}

// ������ �������� ( � ���� 0.01) ��� ������� �����
double  Precis::getPrec() {
	return 1 / (pow(10, prec));
}