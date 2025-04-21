#pragma once
#include "src/Clip.h"
#include "src/Matrix.h"
#include "src/Transform.h"
#include <cmath>
#include <vector>

namespace Smirnov251HW2 {

// ��� ��������� ��������
vec2 Vc; // ���������� ������ ������� ����
vec2 V;  // ������� ������������� � ������������ �������
// ��� ������� ��������
vec2 Vc_work; // ���������� ������ ������� ����
vec2 V_work;  // ������� ������������� � ������������ �������

// �������, � ������� ������������� ��� ��������������
// ������������� ��������� �������
mat3 T = mat3(1.f);
// ������� ���������� ��������������
mat3 initT;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// ������ ��� MyForm
/// </summary>
public
ref class MyForm : public System::Windows::Forms::Form {
  public:
    MyForm(void) {
        InitializeComponent();
        //
        // TODO: �������� ��� ������������
        //
    }

  protected:
    /// <summary>
    /// ���������� ��� ������������ �������.
    /// </summary>
    ~MyForm() {
        if (components) {
            delete components;
        }
    }

  private:
    System::Windows::Forms::OpenFileDialog ^ openFileDialog;

  protected:
  private:
    /// <summary>
    /// ������������ ���������� ������������.
    /// </summary>
    System::ComponentModel::Container ^ components;

#pragma region Windows Form Designer generated code
    /// <summary>
    /// ��������� ����� ��� ��������� ������������ � �� ���������
    /// ���������� ����� ������ � ������� ��������� ����.
    /// </summary>
    void InitializeComponent(void) {
        this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
        this->SuspendLayout();
        //
        // openFileDialog
        //
        this->openFileDialog->Filter =
            L"��������� ����� (*.txt)|*.txt|��� ����� (*.*)|*.*";
        this->openFileDialog->Title = L"������� ����";
        //
        // MyForm
        //
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(1149, 956);
        this->DoubleBuffered = true;
        this->KeyPreview = true;
        this->MinimumSize = System::Drawing::Size(155, 120);
        this->Name = L"MyForm";
        this->Text = L"MyForm";
        this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
        this->Paint += gcnew System::Windows::Forms::PaintEventHandler(
            this, &MyForm::MyForm_Paint);
        this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(
            this, &MyForm::MyForm_KeyDown);
        this->Resize +=
            gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
        this->ResumeLayout(false);
    }
#pragma endregion
    // ���������� �� ������ ����
  private:
    float left = 30;
    float right = 100;
    float top = 20;
    float bottom = 50;
    // �������� ��������� ��������� x, ������� ��������� x
    float minX = left, maxX;
    // �������� ��������� ��������� y, ������� ��������� y
    float minY = top, maxY;
    // ���������� ������ ������� ���� ��������������
    float Wcx = left, Wcy;
    // ������ � ������ ��������������
    float Wx, Wy;

  private:
    System::Void rectCalc() {
        // �������� ��������� ��������� x, ������� ��������� x
        maxX = ClientRectangle.Width - right;
        // �������� ��������� ��������� y, ������� ��������� y
        maxY = ClientRectangle.Height - bottom;
        // ���������� ������ ������� ���� ��������������
        Wcy = maxY;
        // ������ ��������������
        Wx = maxX - left;
        // ������ ��������������
        Wy = maxY - top;
    }

  private:
    System::Void worldRectCalc() {
        // ������������� �������� Vc_work
        Vc_work = normalize(T * vec3(Vc, 1.f));
        // ������������� �������� V_work
        V_work = mat2(T) * V;
    }

  private:
    float f(float x) {
        return x * sin(std::log(x));
    }

  private:
    bool f_exists(float x) {
        return x > 0;
    }

  private:
    System::Void MyForm_Paint(System::Object ^ sender,
                              System::Windows::Forms::PaintEventArgs ^ e) {
        Graphics ^ g = e->Graphics;
        // ��������� ����� �����������
        g->Clear(Color::Aquamarine);

        Pen ^ rectPen = gcnew Pen(Color::Black, 2);
        g->DrawRectangle(rectPen,
                         left, // �� ������
                         top,  // �������� ���� �������� ���� � ������
                         Wx,   // ������
                         Wy    // ������
        );

        // ���� ��� �������
        Pen ^ pen = gcnew Pen(Color::Blue, 1);
        // ��� �� x � ������� ������� ���������
        float deltaX = V_work.x / Wx;
        // ����� ������ ������� � ����������� ������
        vec2 start;
        // ���������� ��� ��������� ����� � ������� ��
        float x, y;
        // ��� ��������� ����� ������� ������� �������������
        // ���������� x
        start.x = Wcx;
        // ���������� x ��������� ����� ������� ������� � �������
        // �����������
        x = Vc_work.x;

        bool hasStart = f_exists(x);
        // ���� ������� ���������� � ���� �����, ��
        if (hasStart) {

            // ���������� y ��������� ����� � ������� �����������
            y = f(x);
            // ��������� ��������������� �������� � ����������� ������
            start.y = Wcy - (y - Vc_work.y) / V_work.y * Wy;
        }

        // ���� x ����� ������ ������� �� ��������� ������� �������� �������� �
        // �������������� �� ����� - maxX
        while (start.x < maxX) {
            // ����� ����� ������� � ����������� ������
            vec2 end;
            // ���������� x ���������� �� �������
            end.x = start.x + 1.f;
            // ���������� x �������� ����� ������� � �������
            // �����������
            x += deltaX;
            bool hasEnd = f_exists(x);
            // ���� ������� ���������� � ���� �����, ��
            if (hasEnd) {

                // ���������� y �������� ����� � ������� �����������
                y = f(x);
                // ��������� ��������������� �������� � ����������� ������
                end.y = Wcy - (y - Vc_work.y) / V_work.y * Wy;
            }

            // ��������� ������� ������������ ������� ��������� �� �����,
            // �������������� �������� ���������� ����� �������
            vec2 tmpEnd = end;
            bool visible = hasStart && hasEnd && clip(start, end, minX, minY, maxX, maxY);
            hasStart = hasEnd;
            // ���� ������� �����
            if (visible) {
                // ����� ���������, start � end - ����� ������� ����� �������
                // ��������� ������� ������
                g->DrawLine(pen, start.x, start.y, end.x, end.y);
            }
            // �������� ����� ������������� ������� ���������� ��������� ������
            // ����������
            start = tmpEnd;
        }
    }

  private:
    System::Void MyForm_Resize(System::Object ^ sender, System::EventArgs ^ e) {
        rectCalc();
        Refresh();
    }

  private:
    System::Void MyForm_Load(System::Object ^ sender, System::EventArgs ^ e) {
        // ������ ������� �� �������� 4, � ������� � ������ ���������
        Vc = vec2(-2.f, -2.f);
        V = vec2(4.f, 4.f);

        initT = mat3(1.f);
        T = initT;

        rectCalc();
        worldRectCalc();
    }

  private:
    System::Void MyForm_KeyDown(System::Object ^ sender,
                                System::Windows::Forms::KeyEventArgs ^ e) {
        // ���������� ������ ��������������
        float centerX = Vc_work.x + V_work.x / 2;
        // � ������� ������� ���������
        float centerY = Vc_work.y + V_work.y / 2;
        switch (e->KeyCode) {
        // ����� ���� ��������� ��������������
        case Keys::Escape:
            T = initT;
            break;
        case Keys::A:
            // ����� ������� ������ �� ���� ������
            T = translate(-V_work.x / Wx, 0.f) * T;
            break;
        case Keys::Z:
            // ������� ������ ��������� � �����
            T = translate(-centerX, -centerY) * T;
            // ��������������� ������������ ������ ���������
            T = scale(1.1) * T;
            // ������� ������� ������ ���������
            T = translate(centerX, centerY) * T;
            break;
        default:
            break;
        }
        worldRectCalc();
        Refresh();
    }
};
} // namespace Smirnov251HW2
