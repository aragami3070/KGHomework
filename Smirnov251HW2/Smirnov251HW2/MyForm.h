#pragma once

namespace Smirnov251HW2 {
	float lines[] = {
		// голова
		0.5f,3.f,1.f,4.5f, // от левой щеки вверх до уха
		1.f,4.5f,0.5f,6.f, // левое ухо слева снизу вверх
		0.5f,6.f,0.5f, 7.5f, // левое ухо слева
		0.5f, 7.5f,1.f,8.f, // левое ухо верх слева
		1.f,8.f,1.5f,8.f, // левое ухо верх середина
		1.5f,8.f,2.f,7.5f, // левое ухо верх справа
		2.f,7.5f,1.5f, 6.f, // левое ухо справа сверху вниз
		1.5f, 6.f,1.5f,4.5f, // левое ухо справа до макушки
		1.5f,4.5f,3.f,4.5f, // макушка
		3.f,4.5f,3.f,6.f, // правое ухо слева снизу вверх
		3.f,6.f,2.5f,7.5f, // правое ухо слева
		2.5f,7.5f,3.f,8.f, // правое ухо верх слева
		3.f,8.f,3.5f,8.f, // правое ухо верх середина
		3.5f,8.f,4.f,7.5f, // правое ухо верх справа
		4.f,7.5f,4.f,6.f, // правое ухо сверху вниз
		4.f,6.f,3.5f,4.5f, // правое ухо справа
		3.5f,4.5f,4.f,3.f, // от правого уха вниз до щеки
		4.f,3.f,3.5f,1.5f, // правая скула
		3.5f,1.5f,2.5f,1.f, // подбородок справа
		2.5f,1.f,2.f,1.f, // подбородок снизу
		2.f,1.f,1.f,1.5f, // подбородок слева
		1.f,1.5f,0.5f,3.f, // левая скула
		// туловище
		4.f,3.f,5.5f,3.5f, // спина от головы вправо
		5.5f,3.5f,7.f,3.5f, // спина верх
		7.f,3.5f,7.5f,2.5f, // спина сверху до хвоста
		7.5f,2.5f,8.f,2.5f, // хвост сверху
		8.f,2.5f,8.f,2.f, // хвост справа
		8.f,2.f,7.5f,2.f, // хвост низ справа налево
		7.5f,2.f,7.5f,0.5f, // задняя нога справа сверху вниз
		7.5f,0.5f,6.5f,0.5f, // задняя нога низ
		6.5f,0.5f,6.5f,1.f, // задняя нога слева
		6.5f,1.f,6.f,1.f, // между задних ног
		6.f,1.f,6.f,0.5f, // левая задняя нога справа
		6.f,0.5f,5.f,0.5f, // левая задняя нога низ
		5.f,0.5f,5.f,1.f, // левая задняя нога слева
		5.f,1.f,4.f,1.f, // между задними и передними ногами
		4.f,1.f,4.f,0.5f, // правая передняя нога справа
		4.f,0.5f,3.f,0.5f, // правая передняя нога низ
		3.f,0.5f,3.f,1.f, // правая передняя нога слева
		3.f,1.f,2.5f,1.f, // между передних ног
		2.5f,1.f,2.5f,0.5f, // передняя нога справа
		2.5f,0.5f,1.5f,0.5f, // передняя нога низ
		1.5f,0.5f,1.5f,1.25f, // передняя нога слева
		// левый глаз
		1.5f,3.5f,1.5f,3.f, // левый глаз слева сверху вниз
		1.5f,3.f,2.f,3.f, // левый глаз низ
		2.f, 3.f,2.f,3.5f, // левый глаз справа
		2.f,3.5f,1.5f,3.5f, // левый глаз верх
		// правый глаз
		2.5f,3.5f,2.5f,3.f, // правый глаз слева
		2.5f,3.f,3.f, 3.f, // правый глаз снизу
		3.f,3.f,3.f,3.5f, // правый глаз справа
		3.f,3.5f,2.5f,3.5f, // правый глаз сверху
		// ушные раковины
		1.f,5.5f,1.f,7.f, // левая ушная раковина
		3.5f,5.5f,3.5f,7.f, // правая ушная раковина
		// нос
		2.f,2.5f,2.5f,2.5f, // нос сверху
		2.5f,2.5f,2.25f,2.f, // нос справа
		2.25f,2.f,2.f,2.5f // нос слева
	};
	// Number of lines
	unsigned int arrayLength = sizeof(lines) / sizeof(float);

	float ejik[] = {
		// нос
		0.5f, 4.f, 0.5f, 3.8f, // нос вниз
		0.5f, 3.8f, 0.3f, 3.6f, // нос влево вниз
		0.3f, 3.6f, 0.1f, 4.f, // нос влево вниз
		0.1f, 4.f, 0.5f, 4.f, // нос вниз
		// голова
		0.5f, 4.f, 1.1f, 4.2f, // голова от носа вправо вверх 
		// голова: глаз: зрачок
		1.1f, 4.2f, 1.3f, 4.2f, // зрачок вправо
		1.3f, 4.2f, 1.5f, 4.6f, // зрачок вправо вверх
		// голова: глаз
		1.1f, 4.2f, 1.5f, 4.f, // глаз вправо вниз
		1.5f, 4.f, 1.7f, 4.6f, // глаз вправо вверх
		1.7f, 4.6f, 1.3f, 4.6f, // глаз влево

		// голова
		1.1f, 4.2f, 1.3f, 4.6f, // голова от начала глаза вправо вверх 
		1.3f, 4.6f, 1.7f, 5.f, // голова от конца глаза вправо вверх 
		// голова:колючки нижняя часть
		1.7f, 5.f, 2.1f, 5.2f, //  н. колючки вправо вверх
		2.1f, 5.2f, 1.9f, 4.6f, //  н. колючки влево вниз
		1.9f, 4.6f, 2.3f, 5.f, //  н. колючки вправо вверх
		2.3f, 5.f, 2.1f, 4.2f, //  н. колючки влево вниз
		2.1f, 4.2f, 2.5f, 4.4f, //  н. колючки вправо вверх
		2.5f, 4.4f, 2.3f, 3.8f, //  н. колючки влево вниз
		2.3f, 3.8f, 2.7f, 4.f, //  н. колючки вправо вверх
		2.7f, 4.f, 2.5f, 3.6f, //  н. колючки влево вниз
		// голова
		2.5f, 3.6f, 2.3f, 3.4f, //  голова от колючек/туловища влево вниз
		2.3f, 3.4f, 1.9f, 3.2f, //  голова рядом с телом влево вниз
		1.9f, 3.2f, 1.3f, 3.4f, //  голова от тела влево вверх
		// голова: рот
		1.3f, 3.4f, 1.9f, 3.8f, //  рот вправо вверх
		1.9f, 3.8f, 1.9f, 4.f, //  рот вверх
		
		// голова
		1.3f, 3.4f, 0.5f, 3.8f, //  голова от рта к носу влево вверх


		// колючки верхняя часть
		1.7f, 5.f, 1.3f, 4.8f, //  в. колючки влево вниз
		1.3f, 4.8f, 1.5f, 5.2f, //  в. колючки вправо вверх
		1.5f, 5.2f, 0.9f, 5.f, //  в. колючки влево вниз
		0.9f, 5.f, 1.5f, 5.6f, //  в. колючки вправо вверх
		1.5f, 5.6f, 1.1f, 6.f, //  в. колючки влево вверх
		1.1f, 6.f, 1.7f, 5.8f, //  в. колючки вправо вниз
		1.7f, 5.8f, 1.9f, 6.2f, //  в. колючки вправо вверх
		1.9f, 6.2f, 2.1f, 5.8f, //  в. колючки вправо вниз
		2.1f, 5.8f, 2.7f, 6.2f, //  в. колючки вправо вверх
		2.7f, 6.2f, 2.7f, 5.8f, //  в. колючки вправо вниз
		2.7f, 5.8f, 3.3f, 6.f, //  в. колючки вправо вверх
		3.3f, 6.f, 3.1f, 5.6f, //  в. колючки влево вниз
		3.1f, 5.6f, 3.7f, 5.4f, //  в. колючки вправо вниз
		3.7f, 5.4f, 3.3f, 5.2f, //  в. колючки влево вниз
		3.3f, 5.2f, 3.9f, 4.8f, //  в. колючки вправо вниз
		3.9f, 4.8f, 4.f, 4.6f, //  в. колючки вправо вниз
		4.f, 4.6f, 3.7f, 4.6f, //  в. колючки влево
		3.7f, 4.6f, 3.9f, 4.f, //  в. колючки вправо вниз
		3.9f, 4.f, 3.5f, 4.f, //  в. колючки влево
		3.5f, 4.f, 3.9f, 3.8f, //  в. колючки вправо вниз
		3.9f, 3.8f, 3.5f, 3.6f, //  в. колючки влево вниз
		3.5f, 3.6f, 3.9f, 3.4f, //  в. колючки вправо вниз
		3.9f, 3.4f, 3.5f, 3.2f, //  в. колючки влево вниз
		3.5f, 3.2f, 3.9f, 2.8f, //  в. колючки вправо вниз
		3.9f, 2.8f, 3.3f, 2.6f, //  в. колючки влево вниз
		3.3f, 2.6f, 3.9f, 2.4f, //  в. колючки вправо вниз
		3.9f, 2.4f, 3.5f, 2.2f, //  в. колючки влево вниз
		3.5f, 2.2f, 3.9f, 1.8f, //  в. колючки вправо вниз
		3.9f, 1.8f, 3.5f, 1.6f, //  в. колючки влево вниз
		3.5f, 1.6f, 3.9f, 1.4f, //  в. колючки вправо вниз
		3.9f, 1.4f, 3.5f, 1.162f, //  в. колючки влево вниз

		// хвост
		2.9f, 1.6f, 3.7f, 1.0f, //  хвост к в. колючкам вправо вниз
		2.9f, 1.6f, 2.7f, 1.4f, //  хвост рядом с телом влево вниз
		2.7f, 1.4f, 2.7f, 1.2f, //  хвост рядом с телом вниз
		2.7f, 1.2f, 3.7f, 1.0f, //  хвост к в. колючкам вправо вниз



		// тело
		2.5f, 3.6f, 2.9f, 3.2f, // тело от колючек/головы вправо вниз
		2.9f, 3.2f, 3.1f, 2.4f, // тело вправо вниз
		3.1f, 2.4f, 2.9f, 1.6f, // тело влево вниз

	};
	unsigned int ejikLinesLength = sizeof(ejik) / sizeof(float);


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
			this->SuspendLayout();
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1166, 838);
			this->DoubleBuffered = true;
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

		// Создать black Pen с толщиной = 2
		Pen^ blackPen = gcnew Pen(Color::Black, 2);

		float Vx = 8.5f; // размер рисунка по горизонтали
		float Vy = 8.5f; // размер рисунка по вертикали

		float Wx = ClientRectangle.Width; // размер окна по горизонтали
		float Wy = ClientRectangle.Height; // размер окна по вертикали
		float aspectFig = Vx / Vy; // соотношение сторон рисунка
		float aspectForm = Wx / Wy; // соотношение сторон окна рисования

		float ZoomX, ZoomY;
		if (keepAspectRatio) {
			// коэффициенты увеличения при сохранении исходного соотношения сторон
			ZoomX = ZoomY = aspectFig < aspectForm ? Wy / Vy : Wx / Vx;
		}
		else {
			ZoomX = Wx / Vx; // коэффициент увеличения по оси Ox
			ZoomY = Wy / Vy; // коэффициент увеличения по оси Oy
		}

		// смещение в положительную сторону по оси Oy после смены знака
		float OffsetY = ZoomY * Vy;
		if (choosePicture) {
			for (int i = 0; i < ejikLinesLength; i += 4) {
				g->DrawLine(blackPen,
					ZoomX * ejik[i], OffsetY - ZoomY * (ejik[i + 1] + 1.f),
					ZoomX * ejik[i + 2], OffsetY - ZoomY * (ejik[i + 3] + 1.f)
				);
			}

		}
		else {
			for (int i = 0; i < arrayLength; i += 4) {
				g->DrawLine(blackPen,
					ZoomX * lines[i], OffsetY - ZoomY * lines[i + 1],
					ZoomX * lines[i + 2], OffsetY - ZoomY * lines[i + 3]
				);
			}
		}
	}
	private: System::Void MyForm_Resize(System::Object^ sender, System::EventArgs^ e) {
		Refresh();
	}

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		// начальное значение: сохранять соотношение сторон рисунка
		keepAspectRatio = true;
		
		choosePicture = true;
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		// Если нажата M, то меняем keepAspectRatio на противоположное значение
		switch (e->KeyCode) {
		case Keys::M:
			keepAspectRatio = !keepAspectRatio;
			break;

		case Keys::N:
			choosePicture = !choosePicture;
			break;
		default:
			break;
		}
		Refresh();
	}
	};
}
