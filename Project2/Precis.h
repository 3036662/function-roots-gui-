#pragma once
#include <FL/Fl_Simple_Counter.H>

// ����� ��� ������ �������� ���������
// ���������� FL_Simple_Counter,�� ������ ������� �� ������� �������
class Precis :public Fl_Simple_Counter {
private:
	int prec;// �������� ������ ����� �������
public:
	// �����������
	Precis(int X, int Y, int W, int H, const char* L = 0);

	void change(); // �������� �������� �� ������� �����
	double getPrec(); // ������ �������� ( � ���� 0.01) ��� ������� �����	
};
