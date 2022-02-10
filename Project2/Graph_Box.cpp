#include "Graph_Box.h"

// �����������
Graph_box::Graph_box(Fl_Boxtype b, int X, int Y, int W, int H,const char* l) :Fl_Box(b, X, Y, W, H, l) {
	this->pfun = testfunc1;
	// ������� �������� ���������� ������ 
	mouse_pos={ 0,0 };
	camera.left =X;
	camera.right = X + W;
	camera.top = Y;
	camera.bottom = Y + H;
	// ��������� ��������� ���� ��������� � ������ �������
	axelpos.x = (camera.right - camera.left )/ 2+ camera.left;
	axelpos.y = (camera.bottom - camera.top) / 2;
	// ������� ���� � ������������ ����
	mous_coord = new Fl_Output(10, 40, 280, 20);
	mous_coord->value("x = 0.0 y = 0.0");
	// ���� ������ �������
	choice = new Fl_Choice(10, 10, 280, 20);
	choice->add("3x^4-4x^3-12x^2+2");
	choice->add("x-x^3\\/6+x^5\\/120");
	choice->add("-x^3+12sin(3x)-5x");
	choice->add("sin(x)-x+0.15");
	choice->add("x^2-5sin(x)");
	choice->add("e^(-x)* cos(pi*x)");
	choice->value(0);
	choice->callback((Fl_Callback*) ChoiceCallback,this);
	// ����� ��������
	count = new Precis(10, 70, 280, 40,u8"����� ��������");
	count->callback((Fl_Callback*)CountCallback,this);
	// �������� ��� ������ �����
	interval = new Fl_Box(10, 130, 280, 20, (u8"�������� �� ������� ��� ������ ���������"));
	interval->labelsize(12);
	// ���� � "��������"
	dispbuf = new Fl_Text_Buffer();
	displ = new Fl_Text_Display(10,170,280,300);
	displ->buffer(dispbuf);
	displ->color(0xffffff00);
	displ->textsize(13);
};

//����������
Graph_box::~Graph_box() {
	delete displ;
	displ = nullptr;
	delete dispbuf;
	dispbuf = nullptr;
	delete interval;
	interval = nullptr;
	delete count;
	count = nullptr;
	delete choice;
	choice = nullptr;
	delete mous_coord;
}

// ���������������  draw 
void Graph_box::draw(){
	// ������ ������� 
	fl_draw_box(FL_FLAT_BOX, this->x(), this->y(), this->w(), this->h(), 255);
	// ������ ��� ���������
	Draw_Axels();
	// ������ ������ �������
	Draw_func();
	// ������ �������� ������, ��������� �������������
	if (draw_interv){ 
		Draw_interv();
	}
	// ������ ��������� ������
	if (this->draw_X) {
		Draw_root(root);
	}
}



// ������ ������������ �����
void Graph_box::Draw_Axels(){		
	fl_color(0x00000000); // ������ ���� ��� ���������
	fl_line_style(FL_SOLID, 3, 0);
	// ��� X
	if (axelpos.y > camera.top && axelpos.y < camera.bottom) {
		fl_line(camera.left, axelpos.y, camera.right, axelpos.y); 
	}
	// ��� Y
	if (axelpos.x > camera.left && axelpos.x < camera.right) {
		fl_line(axelpos.x, camera.top, axelpos.x, camera.bottom); 
	}
	fl_line_style(FL_SOLID, 1, 0);
	// ������ �� ���� ����� ��������� ������������ �����
	int start_X = (camera.left - axelpos.x) / scale;
	int start_Y = (axelpos.y-camera.top)/scale;
	char buffer[4];
	fl_color(0xd2d2d200);
	while (GetAbsY(start_Y) < camera.bottom) {
		for (int x = start_X; GetAbsX(x) < camera.right; x++) {
			if (x != 0) {
				// ������������ �����
				// ������� ���� �������, ���� ������� �������	
				fl_line(GetAbsX(x), camera.top, GetAbsX(x), camera.bottom);
				snprintf(buffer, sizeof(buffer), "%d", x);
				if (scale > 40) {
					fl_color(0x62626200);
					fl_draw(buffer, GetAbsX(x), GetAbsY(0) - 5);
					fl_color(0xd2d2d200);
				}
			}
		}
		if (start_Y != 0) {
			// �������������� �����
			fl_color(0xd2d2d200);
			fl_line(camera.left, GetAbsY(start_Y), camera.right, GetAbsY(start_Y));
			// ������� ���� �������, ���� ������� �������
			if (scale > 40) {
				snprintf(buffer, sizeof(buffer), "%d", start_Y);
				fl_color(0x62626200);
				fl_draw(buffer, GetAbsX(0) + 5, GetAbsY(start_Y));
				fl_color(0xd2d2d200);
			}
		}
		start_Y--;
	}
}


// ��������� ���������� ������������ ���� ������� , ���������� �������� � ��������
inline int  Graph_box::GetAbsX(double x) {
	return static_cast<int> (scale * x + axelpos.x);
}
inline int Graph_box::GetAbsY(double y) {
	return static_cast<int> (axelpos.y - scale*y);
}

// ��������� �������
int Graph_box::handle(int event) {
	char buffer[50];
	switch (event){
		// �����, ����� ����������� �� keydown
		case FL_FOCUS:
			return 1;
			break;
		// �����, ����� ����������� �� keydown
		case FL_UNFOCUS:
			return 1;
			break;
		// ��������� ������� ������� ����� � ����
		case FL_KEYDOWN:
			switch (Fl::event_key()) {
			case 0xFF52:				
				scale += 4;					
				break;
			case 0xFF54:
				if (scale > 10) {
					scale -= 4;				
				}
				break;
			}
			redraw();
			return 1;
			break;
		// ��������� ������ ���� ������ �������
		case FL_MOUSEWHEEL:
			if (Fl::event_dy() > 0 && scale>10) {
				scale-=4;				
			}
			else {
				scale+=4;
			}
			redraw();			
			return 1;
			break;
		// �������������� ���� ������� ��� ������� ���������
		case FL_PUSH:
			mouse_pos.x=(Fl::event_x());
			mouse_pos.y=(Fl::event_y());
			return 1;
			break;
		case FL_DRAG:
			axelpos.x += Fl::event_x() - mouse_pos.x;
			axelpos.y += Fl::event_y() - mouse_pos.y;
			mouse_pos.x = Fl::event_x();
			mouse_pos.y= Fl::event_y();
			redraw();
			return 1;
			break;
		case FL_ENTER: // ����� ����� �����������  �� FL_MOVE
			return 1;
		case FL_MOVE:
			mouse_hover_pos.x = Fl::event_x();
			mouse_hover_pos.y = Fl::event_y();
			mouseX = (static_cast<double> (mouse_hover_pos.x) - axelpos.x) / scale;
			mouseY= (static_cast<double> ( axelpos.y)- mouse_hover_pos.y) / scale;
			snprintf(buffer, sizeof(buffer), "x= %f  y= %f", mouseX,mouseY);
			mous_coord->value(buffer);
			return 1;
			break;
		case FL_RELEASE:
			//  ������ �������� ������, �� ��� ������ , ��� ������ ������� 
			interv_L = (static_cast<double> (Fl::event_x()) - axelpos.x - 30) / scale ;
			interv_R = (static_cast<double> (Fl::event_x()) - axelpos.x + 30) / scale ;
			snprintf(buffer, sizeof(buffer), "�������� �� %1.2f �� %1.2f", interv_L,interv_R);
			interval->label(fl_locale_to_utf8(buffer, sizeof(buffer), 1251));
			interval->redraw_label();
			dispbuf->remove(0, dispbuf->length());
			this->Displ_calc(count->getPrec());
			draw_interv = TRUE;
			take_focus();
			redraw();
			return 1;
			break;
		default:
			return 0;
			break;
	}
}

// ������ ������ �������
// ����� ������� ������� �� 1000 ����� � ��������� �� ������
void Graph_box::Draw_func() {
	fl_color(0xFF000000);
	fl_line_style(FL_SOLID, 2, 0);
	double start_x = (static_cast<double> (camera.left) - axelpos.x) / scale;
	double end_x =  (static_cast<double>(camera.right) - axelpos.x) / scale;
	double y, y_next, x_next, length, step;
	double maxlenght;
	if (scale<this->h()){
		maxlenght =(static_cast<double> (this->h()) / scale)*2;
	}
	else {
		maxlenght = 2;
	}
	x_next = start_x;
	step = (end_x - start_x) / 1000;
	for (double x = start_x; x < end_x; x=x_next) {
		y = func(x);
		x_next += step;
		y_next = func(x_next);		
		// ������������ ������� ���������
		length = abs(y_next-y);
		fl_push_clip(camera.left, camera.top, this->w(), this->h());
		if (length >maxlenght && y*y_next<0) {		
			// ������
			fl_line(GetAbsX(x), camera.top, GetAbsX(x_next), camera.bottom);
		}
		if (length < maxlenght) {
			// ������
			fl_line(GetAbsX(x), GetAbsY(y), GetAbsX(x_next), GetAbsY(y_next));			
		}
		fl_pop_clip();
	}
}

// ������ ������������ ����� � ����� � 
// �������� ��������� ������ �� ������� ������������ ����� ������
void Graph_box::Draw_root(double x) {
		fl_color(0x000fFF00); //  ���� ��� ���������
		fl_line_style(FL_SOLID, 3, 0);
		fl_push_clip(camera.left, camera.top, this->w(), this->h());
		fl_line(GetAbsX(x), camera.top, GetAbsX(x), camera.bottom);
		fl_pop_clip();
	Fl_Window* ptrwind;
	ptrwind=this->window();
	ptrwind->make_current();
}


// ���������� �� ������� ������� ���������� ���������
// ����� �������� �������
void Graph_box::Draw_interv() {
	fl_color(0x00ff0000); //  ���� ��� ���������
	fl_line(GetAbsX(interv_L), camera.top, GetAbsX(interv_L), camera.bottom);
	fl_line(GetAbsX(interv_R), camera.top, GetAbsX(interv_R), camera.bottom);
	Fl_Window* ptrwind;
	ptrwind = this->window();
	ptrwind->make_current();
}


// ���������� �������� ������� �� �
double Graph_box::func(double x) {
	return pfun(x);
}

// ���������� ����������� �������, ������ ������� - �����������
// ������������ ��� �������������� ������� � ����, �������� ��� ��������
double Graph_box::func_maxder() {	
	double step =abs(interv_L-interv_R)/1000;
	double x = this->interv_L;
	double max = ((func(x + step) - func(x - step)) / (2 * step));
	double min = max;
	x += step;
	double der;
	while (x <= interv_R) {
		der= ((func(x + step) - func(x - step)) /( 2 * step));
		if (max < der) {
			max = der;
		}
		if (min > der) {
			min = der;
		}
		x += step;
	}
	if (abs(min) > abs(max)) { return min; }
	else return max;
}


// ���������� ��� ���������� ����� � ���� "�������"
void Graph_box::Displ_calc(double eps) {
	char buffer[50];
	dispbuf->text("");
	// ���� �� ������ �������� ��� ������
	if (interv_L == interv_R) {
		displ->insert(u8"�������� �������� ��� ������...\n");
		return;
	}
	displ->insert(u8"�������...\n");
	snprintf(buffer, sizeof(buffer), "F(%1.2f)= %1.4f \n", interv_L,func(interv_L));
	displ->insert(buffer);
	snprintf(buffer, sizeof(buffer), "F(%1.2f)= %1.4f \n", interv_R, func(interv_R));
	displ->insert(buffer);
	// �������� ������ �� ���� �������
	if (func(interv_L) * func(interv_R) >= 0) {
		displ->insert(u8"�� ������ ��������� ������ �� ������ ����,\n����� �� �������\n");
		displ->insert(u8"��������� ������� ��� ������� ������ ���������\n");
		this->draw_X = false;
		return;
	}

	snprintf(buffer, sizeof(buffer), u8"������� �������� %0.10f\n", eps);
	displ->insert(buffer);
	//  ���� ����� ������ ���� �� ���������, ����� ������ �������
	displ->insert(u8"������ ���������� �� ������\n�������� �����������\n");
	snprintf(buffer, sizeof(buffer), "max|F'(x)|= |%1.4f| \n",  func_maxder());
	displ->insert(buffer);
	double lambda = 1 / func_maxder();
	snprintf(buffer, sizeof(buffer), "a= 1/max|F'(x)| = %1.4f\nx=x- %1.4ff(x)\n", lambda,lambda);
	displ->insert(buffer);	
	displ->insert(u8"������ ��������...\n");
	
	// ����� ��������
	double x = interv_L;
	snprintf(buffer, sizeof(buffer), "x0 = %1.4f f(x)= %f\n",x,func(x));
	displ->insert(buffer);
	double x_prev=x;
	double a;
	double x_prevprev=x;
	int i = 0;
	// ������� �� 1000 �����,����� ��������� ����������� ������������ �����
	// ���� ������� ����� ����� ������������� � ������ �������� eps
	while ((abs(x - x_prev) >eps || i==0)&&i<1000){
		i++;
		x_prevprev = x_prev;
		x_prev = x;
		x = x-lambda*(func(x));	
		snprintf(buffer, sizeof(buffer), "x%d = %.10f f(x)=%f \n", i, x, func(x));
		displ->insert(buffer);			
	} 
	// ����� ���������� ����� ����������� ����� ����� ������� ��'(x) 
	// � ������� ������������� �������� ���������
	if (abs(x - x_prev) < eps) {
		displ->insert(u8"���������� ����� ����������� �����\n");		
		a = (x - x_prev) / (x_prev - x_prevprev);
		snprintf(buffer, sizeof(buffer), "f'(x) ~  %f\n", a);
		displ->insert(buffer);
		while  ((x - x_prev > abs((1 - a) / a) * eps)&&i<1000) {
			i++;
			x_prevprev = x_prev;
			x_prev = x;
			x = x - lambda * (func(x));		
			snprintf(buffer, sizeof(buffer), "x%d = %.10f f(x)=%.10f \n", i, x, func(x));
			displ->insert(buffer);
		}		
		// ���� �������� ��������� ��������� 
		// ���������� ������ ���������
		if (x - x_prev < abs((1 - a) / a) * eps) {			
			displ->insert(u8"���������� �������� ��������\n");
		}
		else {
			displ->insert(u8"���������� ����������� �� ����� ��������\n");
		}
		// �������� �� ������� ����� ������ 
		x = round(x/eps)*eps;
		snprintf(buffer, sizeof(buffer), "x = %.10f\n",  x);
		displ->insert(buffer);
		snprintf(buffer, sizeof(buffer), "f(x) = %.10f\n", func(x));
		displ->insert(buffer);
		this->draw_X = true;
		this->root = x;
	}	
}


// ������������� ������� ��� ������������ , ����������� ����� ������������ �������� ������� 
void Graph_box::SetFunc(int funcnumb) {
	switch (funcnumb)
	{
	case 0:
		pfun = testfunc1;
		break;
	case 1:
		pfun = testfunc2;
		break;
	case 2:
		pfun = testfunc3;
		break;
	case 3:
		pfun = testfunc4;
		break;
	case 4:
		pfun = testfunc5;
		break;
	case 5:
		pfun = testfunc6;
		break;
	default:
		pfun = testfunc1;
		break;
	}
	// ������� ��� ��� � ���� � �������� �� ���������
	axelpos.x = (camera.right - camera.left) / 2 + camera.left;
	axelpos.y = (camera.bottom - camera.top) / 2;
	scale = 50;
	draw_X = false;
	interv_L = 0;
	interv_R = 0;
	draw_interv = false;
	dispbuf->text(u8"�������� �������� ��� ������");
	redraw();
}


// CallBack  ��� ���� ������ �������
void ChoiceCallback(Fl_Choice* choise, Graph_box* graph){
	if (choise->changed()) {
		graph->SetFunc(choise->value());
		Fl::focus(graph);
	}
};

// callback ��� ������ ��������
void CountCallback(Precis* counter, Graph_box* graph) {
	counter->change();
	graph->Displ_calc(counter->getPrec());
	Fl::focus(graph);
}
