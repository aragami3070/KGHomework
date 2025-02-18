#pragma once

namespace Smirnov251HW2 {
	float lines[] = {
		// ������
		0.5f,3.f,1.f,4.5f, // �� ����� ���� ����� �� ���
		1.f,4.5f,0.5f,6.f, // ����� ��� ����� ����� �����
		0.5f,6.f,0.5f, 7.5f, // ����� ��� �����
		0.5f, 7.5f,1.f,8.f, // ����� ��� ���� �����
		1.f,8.f,1.5f,8.f, // ����� ��� ���� ��������
		1.5f,8.f,2.f,7.5f, // ����� ��� ���� ������
		2.f,7.5f,1.5f, 6.f, // ����� ��� ������ ������ ����
		1.5f, 6.f,1.5f,4.5f, // ����� ��� ������ �� �������
		1.5f,4.5f,3.f,4.5f, // �������
		3.f,4.5f,3.f,6.f, // ������ ��� ����� ����� �����
		3.f,6.f,2.5f,7.5f, // ������ ��� �����
		2.5f,7.5f,3.f,8.f, // ������ ��� ���� �����
		3.f,8.f,3.5f,8.f, // ������ ��� ���� ��������
		3.5f,8.f,4.f,7.5f, // ������ ��� ���� ������
		4.f,7.5f,4.f,6.f, // ������ ��� ������ ����
		4.f,6.f,3.5f,4.5f, // ������ ��� ������
		3.5f,4.5f,4.f,3.f, // �� ������� ��� ���� �� ����
		4.f,3.f,3.5f,1.5f, // ������ �����
		3.5f,1.5f,2.5f,1.f, // ���������� ������
		2.5f,1.f,2.f,1.f, // ���������� �����
		2.f,1.f,1.f,1.5f, // ���������� �����
		1.f,1.5f,0.5f,3.f, // ����� �����
		// ��������
		4.f,3.f,5.5f,3.5f, // ����� �� ������ ������
		5.5f,3.5f,7.f,3.5f, // ����� ����
		7.f,3.5f,7.5f,2.5f, // ����� ������ �� ������
		7.5f,2.5f,8.f,2.5f, // ����� ������
		8.f,2.5f,8.f,2.f, // ����� ������
		8.f,2.f,7.5f,2.f, // ����� ��� ������ ������
		7.5f,2.f,7.5f,0.5f, // ������ ���� ������ ������ ����
		7.5f,0.5f,6.5f,0.5f, // ������ ���� ���
		6.5f,0.5f,6.5f,1.f, // ������ ���� �����
		6.5f,1.f,6.f,1.f, // ����� ������ ���
		6.f,1.f,6.f,0.5f, // ����� ������ ���� ������
		6.f,0.5f,5.f,0.5f, // ����� ������ ���� ���
		5.f,0.5f,5.f,1.f, // ����� ������ ���� �����
		5.f,1.f,4.f,1.f, // ����� ������� � ��������� ������
		4.f,1.f,4.f,0.5f, // ������ �������� ���� ������
		4.f,0.5f,3.f,0.5f, // ������ �������� ���� ���
		3.f,0.5f,3.f,1.f, // ������ �������� ���� �����
		3.f,1.f,2.5f,1.f, // ����� �������� ���
		2.5f,1.f,2.5f,0.5f, // �������� ���� ������
		2.5f,0.5f,1.5f,0.5f, // �������� ���� ���
		1.5f,0.5f,1.5f,1.25f, // �������� ���� �����
		// ����� ����
		1.5f,3.5f,1.5f,3.f, // ����� ���� ����� ������ ����
		1.5f,3.f,2.f,3.f, // ����� ���� ���
		2.f, 3.f,2.f,3.5f, // ����� ���� ������
		2.f,3.5f,1.5f,3.5f, // ����� ���� ����
		// ������ ����
		2.5f,3.5f,2.5f,3.f, // ������ ���� �����
		2.5f,3.f,3.f, 3.f, // ������ ���� �����
		3.f,3.f,3.f,3.5f, // ������ ���� ������
		3.f,3.5f,2.5f,3.5f, // ������ ���� ������
		// ����� ��������
		1.f,5.5f,1.f,7.f, // ����� ����� ��������
		3.5f,5.5f,3.5f,7.f, // ������ ����� ��������
		// ���
		2.f,2.5f,2.5f,2.5f, // ��� ������
		2.5f,2.5f,2.25f,2.f, // ��� ������
		2.25f,2.f,2.f,2.5f // ��� �����
	};
	// Number of lines
	unsigned int arrayLength = sizeof(lines) / sizeof(float);

	float ejik[] = {
		// ���
		0.5f, 4.f, 0.5f, 3.8f, // ��� ����
		0.5f, 3.8f, 0.3f, 3.6f, // ��� ����� ����
		0.3f, 3.6f, 0.1f, 4.f, // ��� ����� ����
		0.1f, 4.f, 0.5f, 4.f, // ��� ����
		// ������
		0.5f, 4.f, 1.1f, 4.2f, // ������ �� ���� ������ ����� 
		// ������: ����: ������
		1.1f, 4.2f, 1.3f, 4.2f, // ������ ������
		1.3f, 4.2f, 1.5f, 4.6f, // ������ ������ �����
		// ������: ����
		1.1f, 4.2f, 1.5f, 4.f, // ���� ������ ����
		1.5f, 4.f, 1.7f, 4.6f, // ���� ������ �����
		1.7f, 4.6f, 1.3f, 4.6f, // ���� �����

		// ������
		1.1f, 4.2f, 1.3f, 4.6f, // ������ �� ������ ����� ������ ����� 
		1.3f, 4.6f, 1.7f, 5.f, // ������ �� ����� ����� ������ ����� 
		// ������:������� ������ �����
		1.7f, 5.f, 2.1f, 5.2f, //  �. ������� ������ �����
		2.1f, 5.2f, 1.9f, 4.6f, //  �. ������� ����� ����
		1.9f, 4.6f, 2.3f, 5.f, //  �. ������� ������ �����
		2.3f, 5.f, 2.1f, 4.2f, //  �. ������� ����� ����
		2.1f, 4.2f, 2.5f, 4.4f, //  �. ������� ������ �����
		2.5f, 4.4f, 2.3f, 3.8f, //  �. ������� ����� ����
		2.3f, 3.8f, 2.7f, 4.f, //  �. ������� ������ �����
		2.7f, 4.f, 2.5f, 3.6f, //  �. ������� ����� ����
		// ������
		2.5f, 3.6f, 2.3f, 3.4f, //  ������ �� �������/�������� ����� ����
		2.3f, 3.4f, 1.9f, 3.2f, //  ������ ����� � ����� ����� ����
		1.9f, 3.2f, 1.3f, 3.4f, //  ������ �� ���� ����� �����
		// ������: ���
		1.3f, 3.4f, 1.9f, 3.8f, //  ��� ������ �����
		1.9f, 3.8f, 1.9f, 4.f, //  ��� �����
		
		// ������
		1.3f, 3.4f, 0.5f, 3.8f, //  ������ �� ��� � ���� ����� �����


		// ������� ������� �����
		1.7f, 5.f, 1.3f, 4.8f, //  �. ������� ����� ����
		1.3f, 4.8f, 1.5f, 5.2f, //  �. ������� ������ �����
		1.5f, 5.2f, 0.9f, 5.f, //  �. ������� ����� ����
		0.9f, 5.f, 1.5f, 5.6f, //  �. ������� ������ �����
		1.5f, 5.6f, 1.1f, 6.f, //  �. ������� ����� �����
		1.1f, 6.f, 1.7f, 5.8f, //  �. ������� ������ ����
		1.7f, 5.8f, 1.9f, 6.2f, //  �. ������� ������ �����
		1.9f, 6.2f, 2.1f, 5.8f, //  �. ������� ������ ����
		2.1f, 5.8f, 2.7f, 6.2f, //  �. ������� ������ �����
		2.7f, 6.2f, 2.7f, 5.8f, //  �. ������� ������ ����
		2.7f, 5.8f, 3.3f, 6.f, //  �. ������� ������ �����
		3.3f, 6.f, 3.1f, 5.6f, //  �. ������� ����� ����
		3.1f, 5.6f, 3.7f, 5.4f, //  �. ������� ������ ����
		3.7f, 5.4f, 3.3f, 5.2f, //  �. ������� ����� ����
		3.3f, 5.2f, 3.9f, 4.8f, //  �. ������� ������ ����
		3.9f, 4.8f, 4.f, 4.6f, //  �. ������� ������ ����
		4.f, 4.6f, 3.7f, 4.6f, //  �. ������� �����
		3.7f, 4.6f, 3.9f, 4.f, //  �. ������� ������ ����
		3.9f, 4.f, 3.5f, 4.f, //  �. ������� �����
		3.5f, 4.f, 3.9f, 3.8f, //  �. ������� ������ ����
		3.9f, 3.8f, 3.5f, 3.6f, //  �. ������� ����� ����
		3.5f, 3.6f, 3.9f, 3.4f, //  �. ������� ������ ����
		3.9f, 3.4f, 3.5f, 3.2f, //  �. ������� ����� ����
		3.5f, 3.2f, 3.9f, 2.8f, //  �. ������� ������ ����
		3.9f, 2.8f, 3.3f, 2.6f, //  �. ������� ����� ����
		3.3f, 2.6f, 3.9f, 2.4f, //  �. ������� ������ ����
		3.9f, 2.4f, 3.5f, 2.2f, //  �. ������� ����� ����
		3.5f, 2.2f, 3.9f, 1.8f, //  �. ������� ������ ����
		3.9f, 1.8f, 3.5f, 1.6f, //  �. ������� ����� ����
		3.5f, 1.6f, 3.9f, 1.4f, //  �. ������� ������ ����
		3.9f, 1.4f, 3.5f, 1.162f, //  �. ������� ����� ����

		// �����
		2.9f, 1.6f, 3.7f, 1.0f, //  ����� � �. �������� ������ ����
		2.9f, 1.6f, 2.7f, 1.4f, //  ����� ����� � ����� ����� ����
		2.7f, 1.4f, 2.7f, 1.2f, //  ����� ����� � ����� ����
		2.7f, 1.2f, 3.7f, 1.0f, //  ����� � �. �������� ������ ����



		// ����
		2.5f, 3.6f, 2.9f, 3.2f, // ���� �� �������/������ ������ ����
		2.9f, 3.2f, 3.1f, 2.4f, // ���� ������ ����
		3.1f, 2.4f, 2.9f, 1.6f, // ���� ����� ����

	};
	unsigned int ejikLinesLength = sizeof(ejik) / sizeof(float);


	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// ������ ��� MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
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
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
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
	private: bool keepAspectRatio; // �������� - ��������� �� ����������� ������ �������? 
	private: bool choosePicture; // true - �������, false - ������

	private: System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ g = e->Graphics;
		// ��������� ����� �����������
		g->Clear(Color::Aquamarine);

		// ������� black Pen � �������� = 2
		Pen^ blackPen = gcnew Pen(Color::Black, 2);

		float Vx = 8.5f; // ������ ������� �� �����������
		float Vy = 8.5f; // ������ ������� �� ���������

		float Wx = ClientRectangle.Width; // ������ ���� �� �����������
		float Wy = ClientRectangle.Height; // ������ ���� �� ���������
		float aspectFig = Vx / Vy; // ����������� ������ �������
		float aspectForm = Wx / Wy; // ����������� ������ ���� ���������

		float ZoomX, ZoomY;
		if (keepAspectRatio) {
			// ������������ ���������� ��� ���������� ��������� ����������� ������
			ZoomX = ZoomY = aspectFig < aspectForm ? Wy / Vy : Wx / Vx;
		}
		else {
			ZoomX = Wx / Vx; // ����������� ���������� �� ��� Ox
			ZoomY = Wy / Vy; // ����������� ���������� �� ��� Oy
		}

		// �������� � ������������� ������� �� ��� Oy ����� ����� �����
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
		// ��������� ��������: ��������� ����������� ������ �������
		keepAspectRatio = true;
		
		choosePicture = true;
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		// ���� ������ M, �� ������ keepAspectRatio �� ��������������� ��������
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
