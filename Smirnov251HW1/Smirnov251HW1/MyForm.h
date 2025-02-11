#pragma once

namespace Smirnov251HW1 {

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
			this->ClientSize = System::Drawing::Size(284, 261);
			this->DoubleBuffered = true;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ g = e->Graphics;
		// Fill form Aquamarine
		g->Clear(Color::Aquamarine);

		// Create Pen with red color
		Pen^ redPen = gcnew Pen(Color::Red);
		// Set Pen width = 6
		redPen->Width = 6;
		g->DrawLine(redPen,
			0, 0, 
			this->ClientRectangle.Width, this->ClientRectangle.Height
		);

		// Create Pen with blue color and width = 10
		Pen^ bluePen = gcnew Pen(Color::Blue, 10);
		g->DrawLine(bluePen,
			90, 50,
			this->ClientRectangle.Width, 80
		);

		// Create Brush black color
		SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);
		// Set font family and font size
		System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 10);
		// Write text
		g->DrawString("Надпись на форме", drawFont, drawBrush, 40, 100);

		// Create Pen with green color and width = 5
		Pen^ greenPen = gcnew Pen(Color::Green, 5);
		// Connect the sides of form in 2 to 1
		g->DrawLine(greenPen,
			0, this->ClientRectangle.Height / 3,
			2 * this->ClientRectangle.Width / 3, 0
		);
		g->DrawLine(greenPen,
			2 * this->ClientRectangle.Width / 3, 0,
			this->ClientRectangle.Width, 2 * this->ClientRectangle.Height / 3
		);
		g->DrawLine(greenPen,
			0, this->ClientRectangle.Height / 3,
			this->ClientRectangle.Width / 3, this->ClientRectangle.Height
		);
		g->DrawLine(greenPen,
			this->ClientRectangle.Width / 3, this->ClientRectangle.Height,
			this->ClientRectangle.Width, 2 * this->ClientRectangle.Height / 3
		);

	}
	private: System::Void MyForm_Resize(System::Object^ sender, System::EventArgs^ e) {
		Refresh();
	}
	};
}
