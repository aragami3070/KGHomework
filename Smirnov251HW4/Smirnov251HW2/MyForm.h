#pragma once
#include "src/Matrix.h"
#include "src/Transform.h"
#include "src/Figure.h"
#include "src/Clip.h"
#include <vector>
#include <fstream>
#include <sstream>

namespace Smirnov251HW2 {
	// Number of lines
	float Vx; // размер рисунка по горизонтали
	float Vy; // размер рисунка по вертикали
	float aspectFig; // соотношение сторон рисунка
	// Матрица, в которой накапливаются все преобразования 
	// Первоначально единичная матрица
	mat3 T = mat3(1.f);
	// Матрица начального преобразования
	mat3 initT;
	std::vector<path> figure;

	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog;
	private: System::Windows::Forms::Button^ btnOpen;
	private: System::Windows::Forms::Button^ button1;
	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->btnOpen = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// openFileDialog
			// 
			this->openFileDialog->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
			this->openFileDialog->Title = L"Открыть файл";
			// 
			// btnOpen
			// 
			this->btnOpen->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnOpen->Location = System::Drawing::Point(315, 26);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(75, 23);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = L"Открыть";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &MyForm::btnOpen_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(203, 37);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(0, 0);
			this->button1->TabIndex = 1;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(402, 578);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->btnOpen);
			this->DoubleBuffered = true;
			this->KeyPreview = true;
			this->MinimumSize = System::Drawing::Size(155, 120);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	// Расстояния до границ окна
	private: float left = 30;
		   float right = 100;
		   float top = 20; 
		   float bottom = 50;
		   // Диапазон изменения координат x, пределы изменения x
		   float minX = left, maxX;
		   // Диапазон изменения координат y, пределы изменения y
		   float minY = top, maxY;
		   // Координаты левого нижнего угла прямоугольника
		   float Wcx = left, Wcy;
		   // Ширина и высота прямоугольника
		   float Wx, Wy;

	private: System::Void rectCalc() {
		// Диапазон изменения координат x, пределы изменения x
		maxX = ClientRectangle.Width - right;
		// Диапазон изменения координат y, пределы изменения y
		maxY = ClientRectangle.Height - bottom;
		// Координаты левого нижнего угла прямоугольника
		Wcy = maxY;
		// Ширина прямоугольника
		Wx = maxX - left;
		// Высота прямоугольника
		Wy = maxY - top;
	}


	private: System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ g = e->Graphics;
		// Заполнить форму аквамарином
		g->Clear(Color::Aquamarine);

		Pen^ rectPen = gcnew Pen(Color::Black, 2);
		g->DrawRectangle(rectPen,
			left, // От левого
			top, // верхнего угла отмеряем вниз и вправо
			Wx, // Ширина
			Wy // Высота
		);

		for (int i = 0; i < figure.size(); i++) {
			// lines - очередная ломаная линяя
			path lines = figure[i];
			// Создать pen с толщиной = 2
			Pen^ pen = gcnew Pen(Color::FromArgb(
					lines.color.x,
					lines.color.y,
					lines.color.z )
			);
			pen->Width = lines.thickness;
			//Начальная точка первого отрезка
			vec2 start = normalize(T * vec3(lines.vertices[0], 1.0));
			// цикл по конечным точкам (от единицы)
			for (int j = 1; j < lines.vertices.size(); j++) {
				// конечная точка
				vec2 end = normalize(T * vec3(lines.vertices[j], 1.0));
				// Продублировали координаты точки для будущего использования
				vec2 tempEnd = end;
				// Если видим отрезок
				if (clip(start, end, minX, minY, maxX, maxY)) { 
					// после отсечения start и end - концы видимой части отрезка
					// Отрисовка видимой части отрезка 
					g->DrawLine(pen, 
						start.x, start.y,
						end.x, end.y 
					);
				}
				// Конечная точка текущего отрезка становится начальной точкой следующего
				start = tempEnd;
			}
		}
	}
	private: System::Void MyForm_Resize(System::Object^ sender, System::EventArgs^ e) {
		rectCalc();
		Refresh();
	}

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		rectCalc();
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		// Координаты центра текущего окна
		float Wcx = ClientRectangle.Width / 2.f; 
		float Wcy = ClientRectangle.Height / 2.f;
		switch (e->KeyCode) {
		// Поворот рисунка на 0.01 радиан против часовой стрелке относительно нового центра
		case Keys::Q:
			// Перенос начала координат в (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// Поворот на 0.01 радиан против часовой стрелке относительно нового центра
			T = rotate(0.01f) * T;
			// Перенос начала координат обратно
			T = translate(Wcx, Wcy) * T;
			break;
		// Поворот рисунка на 0.01 радиан по часовой стрелке относительно нового центра
		case Keys::E:
			// Перенос начала координат в (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// Поворот на 0.01 радиан по часовой стрелке относительно нового центра
			T = rotate(-0.01f) * T;
			// Перенос начала координат обратно
			T = translate(Wcx, Wcy) * T;
			break;
		// Поворот рисунка на 0.05 радиан по часовой стрелке относительно нового центра
		case Keys::R:
			// Перенос начала координат в (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// Поворот на 0.05 радиан по часовой стрелке относительно нового центра
			T = rotate(-0.05f) * T;
			// Перенос начала координат обратно
			T = translate(Wcx, Wcy) * T;
			break;
		// Поворот рисунка на 0.05 радиан против часовой стрелке относительно нового центра
		case Keys::Y:
			// Перенос начала координат в (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// Поворот на 0.05 радиан против часовой стрелке относительно нового центра
			T = rotate(0.05f) * T;
			// Перенос начала координат обратно
			T = translate(Wcx, Wcy) * T;
			break;
		// Сдвиг изображения вверх на 1 пиксель
		case Keys::W:
			// Сдвиг вверх на один пиксель
			T = translate(0.f, -1.f) * T;
			break;
		// Сдвиг изображения влево на 1 пиксель
		case Keys::A:
			// Сдвиг влево на один пиксель
			T = translate(-1.f, 0.f) * T;
			break;
		// Сдвиг изображения вниз на 1 пиксель
		case Keys::S:
			// Сдвиг вниз на один пиксель
			T = translate(0.f, 1.f) * T;
			break;
		// Сдвиг изображения вправо на 1 пиксель
		case Keys::D:
			// Сдвиг вправо на один пиксель
			T = translate(1.f, 0.f) * T;
			break;
		// Сдвиг изображения вверх на 1 пиксель
		case Keys::T:
			// Сдвиг вверх на один пиксель
			T = translate(0.f, -10.f) * T;
			break;
		// Сдвиг изображения влево на 1 пиксель
		case Keys::F:
			// Сдвиг влево на один пиксель
			T = translate(-10.f, 0.f) * T;
			break;
		// Сдвиг изображения вниз на 1 пиксель
		case Keys::G:
			// Сдвиг вниз на один пиксель
			T = translate(0.f, 10.f) * T;
			break;
		// Сдвиг изображения вправо на 1 пиксель
		case Keys::H:
			// Сдвиг вправо на один пиксель
			T = translate(10.f, 0.f) * T;
			break;
		// Увеличение в 1.1 раз
		case Keys::Z:
			// Перенос начала координат в (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// Увеличение в 1.1 раз
			T = scale(1.1f) * T;
			// Перенос начала координат обратно
			T = translate(Wcx, Wcy) * T;
			break;
		// Функция обратная увеличению в 1.1 раз
		case Keys::X:
			// Перенос начала координат в (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// Функция обратная увеличению в 1.1 раз
			T = scale(1.f / 1.1f) * T;
			// Перенос начала координат обратно
			T = translate(Wcx, Wcy) * T;
			break;
		// Увеличение в 1.1 раз по Ox
		case Keys::I:
			// Перенос начала координат в (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// Увеличение в 1.1 раз по Ox
			T = scale(1.1f, 1.f) * T;
			// Перенос начала координат обратно
			T = translate(Wcx, Wcy) * T;
			break;
		// Функция обратная увеличению в 1.1 раз по Ox
		case Keys::K:
			// Перенос начала координат в (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// Функция обратная увеличению в 1.1 раз по Ox
			T = scale(1.f / 1.1f, 1.f) * T;
			// Перенос начала координат обратно
			T = translate(Wcx, Wcy) * T;
			break;
		// Увеличение в 1.1 раз по Oy
		case Keys::O:
			// Перенос начала координат в (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// Увеличение в 1.1 раз по Oy
			T = scale(1.f, 1.1f) * T;
			// Перенос начала координат обратно
			T = translate(Wcx, Wcy) * T;
			break;
		// Функция обратная увеличению в 1.1 раз по Oy
		case Keys::L:
			// Перенос начала координат в (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// Функция обратная увеличению в 1.1  раз по Oy
			T = scale(1.f, 1.f / 1.1f) * T;
			// Перенос начала координат обратно
			T = translate(Wcx, Wcy) * T;
			break;
		// Зеркальное отражение относительно Ox
		case Keys::U:
			// Перенос начала координат в (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// Зеркальное отражение относительно Ox
			T = mirrorX() * T;
			// Перенос начала координат обратно
			T = translate(Wcx, Wcy) * T;
			break;
		// Зеркальное отражение относительно Oy
		case Keys::J:
			// Перенос начала координат в (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// Зеркальное отражение относительно Oy
			T = mirrorY() * T;
			// Перенос начала координат обратно
			T = translate(Wcx, Wcy) * T;
			break;


		// Сброс всех сделанных преобразований
		case Keys::Escape:
			T = initT;
			break;
		default:
			break;
		}
		Refresh();
	}
	private: System::Void btnOpen_Click(System::Object^ sender, System::EventArgs^ e) {
		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			// Перезапись имени файла из openFileDialog->FileName в fileName
			wchar_t fileName[1024]; // Переменная, в которой посимвольно сохраним имя файла
			for (int i = 0; i < openFileDialog->FileName->Length; i++) {
				fileName[i] = openFileDialog->FileName[i];
			}
			fileName[openFileDialog->FileName->Length] = '\0';
			// Объявление и открытие файла
			std::ifstream in;
			in.open(fileName);
			if (in.is_open()) {
				// Файл успешно открыт
				// очищаем имеющийся список ломаных
				figure.clear(); 
				// временные переменные для чтения из файла
				// толщина со значением по умолчанию 2
				float thickness = 2; 
				// составляющие цвета
				float r, g, b; 
				// значение составляющих цвета по умолчанию (черный)
				r = g = b = 0;
				std::string cmd; // строка для считывания имени команды
				// непосредственно работа с файлом
				std::string str; // строка, в которую считываем строки файла
				std::getline(in, str); // считываем из входного файла первую строку
				while (in) { // если очередная строка считана успешно
					// обрабатываем строку
					if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) {
						// прочитанная строка не пуста и не комментарий
						std::stringstream s(str); // строковый поток из строки str
						s >> cmd;
						if (cmd == "frame") { // размеры изображения
							s >> Vx >> Vy; // считываем глобальные значение Vx и Vy
							aspectFig = Vx / Vy; // обновление соотношение сторон рисунка
							float Wx = ClientRectangle.Width - left - right; // размер окна по горизонтали
							float Wy = ClientRectangle.Height - top - bottom; // размер окна по вертикали
							float aspectForm = Wx / Wy; // соотношение сторон окна рисования
							// Коэффициент увеличения при сохранении исходного соотношения сторон
							mat3 T1 = translate(-Vx / 2, -Vy / 2);
							// Масштабирование остается прежним, меняется только привязка
							// коэффициент увеличения при сохранении исходного соотношения сторон
							float S = aspectFig < aspectForm ? Wy / Vy : Wx / Vx;
							mat3 S1 = scale(S, -S);
							// Сдвиг точки привязки из начала координат в нужную позицию
							mat3 T2 = translate(Wx / 2 + Wcx, Wcy - Wy / 2);
							// Преобразования применяются справа налево, сначала масштабирование, а потом перенос
							// В initT совмещаем эти два преобразования
							initT = T2 * (S1 * T1);
							T = initT;
						}
						else if (cmd == "color") { // цвет линии
							s >> r >> g >> b; // считываем три составляющие цвета
						}
						else if (cmd == "thickness") { // толщина линии
							s >> thickness; // считываем значение толщины
						}
						else if (cmd == "path") { // набор точек
							std::vector<vec2> vertices; // список точек ломаной
							int N; // количество точек
							s >> N;
							std::string str1; // дополнительная строка для чтения из файла
							while (N > 0) { // пока не все точки считали
								getline(in, str1); // считываем в str1 из входного файла очередную строку
								// так как файл корректный, то на конец файла проверять не нужно
									if ((str1.find_first_not_of(" \t\r\n") != std::string::npos) && (str1[0] != '#')) {
										// прочитанная строка не пуста и не комментарий
										// значит в ней пара координат
										float x, y; // переменные для считывания
										std::stringstream s1(str1); // еще один строковый поток из строки str1
										s1 >> x >> y;
										vertices.push_back(vec2(x, y)); // добавляем точку в список
										N--; // уменьшаем счетчик после успешного считывания точки
								}
							}
							// все точки считаны, генерируем ломаную (path) и кладем ее в список figure
							figure.push_back(path(vertices, vec3(r, g, b), thickness));
						}
					}
					// считываем очередную строку
					getline(in, str);
				}
				Refresh();
			}
		}
	}
};
}
