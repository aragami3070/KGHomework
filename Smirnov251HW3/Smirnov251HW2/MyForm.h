#pragma once

namespace Smirnov251HW2 {
	// Number of lines
	float Vx; // размер рисунка по горизонтали
	float Vy; // размер рисунка по вертикали
	float aspectFig; // соотношение сторон рисунка

	float ejik[] = {
		// нос
		0.5f, 3.5f, 0.5f, 3.3f, // нос вниз
		0.5f, 3.3f, 0.3f, 3.1f, // нос влево вниз
		0.3f, 3.1f, 0.1f, 3.5f, // нос влево вниз
		0.1f, 3.5f, 0.5f, 3.5f, // нос вниз

		// голова
		0.5f, 3.5f, 1.1f, 3.7f, // голова от носа вправо вверх 
		// голова: глаз: зрачок
		1.1f, 3.7f, 1.3f, 3.7f, // зрачок вправо
		1.3f, 3.7f, 1.5f, 4.1f, // зрачок вправо вверх
		// голова: глаз
		1.1f, 3.7f, 1.5f, 3.5f, // глаз вправо вниз
		1.5f, 3.5f, 1.7f, 4.1f, // глаз вправо вверх
		1.7f, 4.1f, 1.3f, 4.1f, // глаз влево
		// голова
		1.1f, 3.7f, 1.3f, 4.1f, // голова от начала глаза вправо вверх 
		1.3f, 4.1f, 1.7f, 4.5f, // голова от конца глаза вправо вверх 
		// голова:колючки нижняя часть
		1.7f, 4.5f, 2.1f, 4.7f, //  н. колючки вправо вверх
		2.1f, 4.7f, 1.9f, 4.1f, //  н. колючки влево вниз
		1.9f, 4.1f, 2.3f, 4.5f, //  н. колючки вправо вверх
		2.3f, 4.5f, 2.1f, 3.7f, //  н. колючки влево вниз
		2.1f, 3.7f, 2.5f, 3.9f, //  н. колючки вправо вверх
		2.5f, 3.9f, 2.3f, 3.3f, //  н. колючки влево вниз
		2.3f, 3.3f, 2.7f, 3.5f, //  н. колючки вправо вверх
		2.7f, 3.5f, 2.5f, 3.1f, //  н. колючки влево вниз
		// голова
		2.5f, 3.1f, 2.3f, 2.9f, //  голова от колючек/туловища влево вниз
		2.3f, 2.9f, 1.9f, 2.7f, //  голова рядом с телом влево вниз
		1.9f, 2.7f, 1.3f, 2.9f, //  голова от тела влево вверх
		// голова: рот
		1.3f, 2.9f, 1.9f, 3.3f, //  рот вправо вверх
		1.9f, 3.3f, 1.9f, 3.5f, //  рот вверх
		// голова
		1.3f, 2.9f, 0.5f, 3.3f, //  голова от рта к носу влево вверх


		// колючки верхняя часть
		1.7f, 4.5f, 1.3f, 4.3f, //  в. колючки влево вниз
		1.3f, 4.3f, 1.5f, 4.7f, //  в. колючки вправо вверх
		1.5f, 4.7f, 0.9f, 4.5f, //  в. колючки влево вниз
		0.9f, 4.5f, 1.5f, 5.1f, //  в. колючки вправо вверх
		1.5f, 5.1f, 1.1f, 5.5f, //  в. колючки влево вверх
		1.1f, 5.5f, 1.7f, 5.3f, //  в. колючки вправо вниз
		1.7f, 5.3f, 1.9f, 5.7f, //  в. колючки вправо вверх
		1.9f, 5.7f, 2.1f, 5.3f, //  в. колючки вправо вниз
		2.1f, 5.3f, 2.7f, 5.7f, //  в. колючки вправо вверх
		2.7f, 5.7f, 2.7f, 5.3f, //  в. колючки вправо вниз
		2.7f, 5.3f, 3.3f, 5.5f, //  в. колючки вправо вверх
		3.3f, 5.5f, 3.1f, 5.1f, //  в. колючки влево вниз
		3.1f, 5.1f, 3.7f, 4.9f, //  в. колючки вправо вниз
		3.7f, 4.9f, 3.3f, 4.7f, //  в. колючки влево вниз
		3.3f, 4.7f, 3.9f, 4.3f, //  в. колючки вправо вниз
		3.9f, 4.3f, 4.f, 4.1f, //  в. колючки вправо вниз
		4.f, 4.1f, 3.7f, 4.1f, //  в. колючки влево
		3.7f, 4.1f, 3.9f, 3.5f, //  в. колючки вправо вниз
		3.9f, 3.5f, 3.5f, 3.5f, //  в. колючки влево
		3.5f, 3.5f, 3.9f, 3.3f, //  в. колючки вправо вниз
		3.9f, 3.3f, 3.5f, 3.1f, //  в. колючки влево вниз
		3.5f, 3.1f, 3.9f, 2.9f, //  в. колючки вправо вниз
		3.9f, 2.9f, 3.5f, 2.7f, //  в. колючки влево вниз
		3.5f, 2.7f, 3.9f, 2.3f, //  в. колючки вправо вниз
		3.9f, 2.3f, 3.3f, 2.1f, //  в. колючки влево вниз
		3.3f, 2.1f, 3.9f, 1.9f, //  в. колючки вправо вниз
		3.9f, 1.9f, 3.5f, 1.7f, //  в. колючки влево вниз
		3.5f, 1.7f, 3.9f, 1.3f, //  в. колючки вправо вниз
		3.9f, 1.3f, 3.5f, 1.1f, //  в. колючки влево вниз
		3.5f, 1.1f, 3.9f, 0.9f, //  в. колючки вправо вниз
		3.9f, 0.9f, 3.5f, 0.662f, //  в. колючки влево вниз

		// хвост
		2.9f, 1.1f, 3.7f, 0.5f, //  хвост к в. колючкам вправо вниз
		2.9f, 1.1f, 2.7f, 0.9f, //  хвост рядом с телом влево вниз
		2.7f, 0.9f, 2.7f, 0.7f, //  хвост рядом с телом вниз
		2.7f, 0.7f, 3.7f, 0.5f, //  хвост к в. колючкам вправо вниз



		// тело
		2.5f, 3.1f, 2.9f, 2.7f, // тело от колючек/головы вправо вниз
		2.9f, 2.7f, 3.1f, 1.9f, // тело вправо вниз
		3.1f, 1.9f, 2.9f, 1.1f, // тело влево вниз
		2.7f, 0.7f, 1.9f, 0.5f,  // тело влево вниз
		// тело: нога
		1.9f, 0.5f, 1.1f, 0.3f,  // нога влево вниз
		1.1f, 0.3f, 0.7f, 0.9f,  // нога влево вверх
		0.7f, 0.9f, 0.9f, 1.5f,  // нога вправо вверх
		0.9f, 1.5f, 1.3f, 1.7f,  // нога вправо вверх
		1.3f, 1.7f, 1.9f, 0.5f,  // нога вправо вниз
		// тело
		1.5f, 1.3f, 1.9f, 1.5f,  // тело вправо вверх
		// тело: пояс
		1.8f, 1.7f, 3.05f, 1.7f,  // тело влево вверх
		// тело
		1.9f, 1.5f, 1.7f, 1.9f,  // тело влево вверх
		// тело: рука
		1.7f, 1.9f, 2.5f, 1.9f,  // рука вправо
		2.1f, 1.9f, 2.1f, 2.4f,  // рука вверх
		1.7f, 2.3f, 2.5f, 2.5f,  // рука вправо
		1.7f, 2.3f, 1.5f, 2.5f,  // рука влево вверх
		1.5f, 2.5f, 1.1f, 2.1f,  // рука влево вниз
		1.1f, 2.1f, 1.5f, 1.7f,  // рука вправо вниз
		1.5f, 1.7f, 1.7f, 1.9f,  // рука вправо вверх
		1.9f, 2.7f, 1.1f, 2.3f,  // рука влево вниз
		// тело
		1.7f, 2.3f, 1.9f, 2.7f,  // тело влево вверх

		// яблоко
		1.3f, 2.3f, 1.04f, 2.3f,  // яблоко влево
		1.1f, 2.1f, 0.9f, 2.7f,  // яблоко влево вверх
		0.9f, 2.7f, 0.7f, 2.5f,  // яблоко влево вниз
		0.7f, 2.5f, 1.1f, 2.1f,  // яблоко вправо вниз
		0.9f, 2.3f, 0.5f, 2.3f,  // яблоко влево
		0.5f, 2.3f, 0.5f, 2.1f,  // яблоко вниз
		0.5f, 2.1f, 0.1f, 1.5f,  // яблоко влево вниз
		0.1f, 1.5f, 0.1f, 1.1f,  // яблоко вниз
		0.1f, 1.1f, 0.5f, 0.5f,  // яблоко вправо вниз
		0.5f, 0.5f, 0.95f, 0.5f,  // яблоко вправо
		0.5f, 2.1f, 0.7f, 1.9f,  // яблоко вправо вниз
		0.7f, 1.9f, 0.7f, 2.2f,  // яблоко вверх
		0.7f, 2.2f, 0.9f, 2.3f,  // яблоко вправо вверх
		0.7f, 2.1f, 0.9f, 1.9f,  // яблоко вправо вниз
		0.9f, 1.9f, 1.3f, 1.9f,  // яблоко вправо вниз

	};
	unsigned int ejikLinesLength = sizeof(ejik) / sizeof(float);
	float ejikVx = 4.f; // размер рисунка по горизонтали
	float ejikVy = 5.9f; // размер рисунка по вертикали
	float ejikaspectFig = ejikVx / ejikVy; // соотношение сторон рисунка

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
			this->SuspendLayout();
			// 
			// openFileDialog
			// 
			this->openFileDialog->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
			this->openFileDialog->Title = L"Открыть файл";
			// 
			// btnOpen
			// 
			this->btnOpen->Location = System::Drawing::Point(284, 24);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(75, 23);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = L"Открыть";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &MyForm::btnOpen_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(402, 578);
			this->Controls->Add(this->btnOpen);
			this->DoubleBuffered = true;
			this->KeyPreview = true;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: bool keepAspectRatio; // значение - сохранять ли соотношение сторон рисунка? 
	private: bool choosePicture; // true - Задание, false - пример

	private: System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ g = e->Graphics;
		// Заполнить форму аквамарином
		g->Clear(Color::Aquamarine);

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
				// Отрисовка отрезка 
				g->DrawLine(pen, 
					start.x, start.y,
					end.x, end.y 
				);
				// Конечная точка текущего отрезка становится начальной точкой следующего
				start = end;
			}
		}
	}
	private: System::Void MyForm_Resize(System::Object^ sender, System::EventArgs^ e) {
		Refresh();
	}

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		// Координаты центра текущего окна
		float Wcx = ClientRectangle.Width / 2.f; 
		float Wcy = ClientRectangle.Height / 2.f;
		switch (e->KeyCode) {
		// Поворот рисунка на 0.01 радиан относительно нового центра
		case Keys::Q:
			// Перенос начала координат в (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// Поворот на 0.01 радиан относительно нового центра
			T = rotate(0.01f) * T;
			// Перенос начала координат обратно
			T = translate(Wcx, Wcy) * T;
			break;
		// Сдвиг изображения вверх на 1 пиксель
		case Keys::W:
			// Сдвиг вверх на один пиксель
			T = translate(0.f, -1.f) * T;
			break;
		// Сброс всех сделанных преобразований
		case Keys::Escape:
			// Присвоили T единичную матрицу
			T = mat3(1.f);
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
							float Wx = ClientRectangle.Width; // размер окна по горизонтали
							float Wy = ClientRectangle.Height; // размер окна по вертикали
							float aspectForm = Wx / Wy; // соотношение сторон окна рисования
							// коэффициент увеличения при сохранении исходного соотношения сторон
							float S = aspectFig < aspectForm ? Wy / Vy : Wx / Vx;
							// смещение в положительную сторону по оси Oy после смены знака
							float Ty = S * Vy;
							// Преобразования применяются справа налево, сначала масштабирование, а потом перенос
							// В initT совмещаем эти два преобразования
							initT = translate(0.f, Ty) * scale(S, -S);
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
