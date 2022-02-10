#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "Graph_Box.h"


int main(int argc, char** argv) {
	// создает окно windows
	Fl_Window* window = new Fl_Window(1024, 600, u8"Метод итераций"); // Создаем окно
	// создает область для графика
	Graph_box* graph = new  Graph_box(FL_FLAT_BOX, 312, 10, 700, 580);
	window->end();
	window->make_current();
	window->show(argc, argv);
	return Fl::run();
}
