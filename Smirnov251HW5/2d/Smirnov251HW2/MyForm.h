#pragma once
#include "src/Clip.h"
#include "src/Matrix.h"
#include "src/Transform.h"
#include <cmath>
#include <vector>

namespace Smirnov251HW2 {

// Под начальные значения
vec2 Vc; // Координаты левого нижнего угла
vec2 V;  // Размеры прямогульника в пространстве гарфика
// Под рабочие значения
vec2 Vc_work; // Координаты левого нижнего угла
vec2 V_work;  // Размеры прямогульника в пространстве гарфика

// Матрица, в которой накапливаются все преобразования
// Первоначально единичная матрица
mat3 T = mat3(1.f);
// Матрица начального преобразования
mat3 initT;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Сводка для MyForm
/// </summary>
public
ref class MyForm : public System::Windows::Forms::Form {
  public:
    MyForm(void) {
        InitializeComponent();
        //
        // TODO: добавьте код конструктора
        //
    }

  protected:
    /// <summary>
    /// Освободить все используемые ресурсы.
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
    /// Обязательная переменная конструктора.
    /// </summary>
    System::ComponentModel::Container ^ components;

#pragma region Windows Form Designer generated code
    /// <summary>
    /// Требуемый метод для поддержки конструктора — не изменяйте
    /// содержимое этого метода с помощью редактора кода.
    /// </summary>
    void InitializeComponent(void) {
        this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
        this->SuspendLayout();
        //
        // openFileDialog
        //
        this->openFileDialog->Filter =
            L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
        this->openFileDialog->Title = L"Открыть файл";
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
    // Расстояния до границ окна
  private:
    float left = 30;
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

  private:
    System::Void rectCalc() {
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

  private:
    System::Void worldRectCalc() {
        // Пересчитываем значение Vc_work
        Vc_work = normalize(T * vec3(Vc, 1.f));
        // Пересчитываем значение V_work
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
        // Заполнить форму аквамарином
        g->Clear(Color::Aquamarine);

        Pen ^ rectPen = gcnew Pen(Color::Black, 2);
        g->DrawRectangle(rectPen,
                         left, // От левого
                         top,  // верхнего угла отмеряем вниз и вправо
                         Wx,   // Ширина
                         Wy    // Высота
        );

        // Перо для графика
        Pen ^ pen = gcnew Pen(Color::Blue, 1);
        // Шаг по x в мировой системе координат
        float deltaX = V_work.x / Wx;
        // точка начала отрезка в координатах экрана
        vec2 start;
        // переменные для координат точки в мировой СК
        float x, y;
        // для начальной точки первого отрезка устанавливаем
        // координату x
        start.x = Wcx;
        // координата x начальной точки первого отрезка в мировых
        // координатах
        x = Vc_work.x;

        bool hasStart = f_exists(x);
        // Если функция определена в этой точке, то
        if (hasStart) {

            // координата y начальной точки в мировых координатах
            y = f(x);
            // вычисляем соответствующее значение в координатах экрана
            start.y = Wcy - (y - Vc_work.y) / V_work.y * Wy;
        }

        // Пока x точки начала отрезка не достигнет правого крайнего значения в
        // прямоугольнике на форме - maxX
        while (start.x < maxX) {
            // точка конца отрезка в координатах экрана
            vec2 end;
            // координата x отличается на единицу
            end.x = start.x + 1.f;
            // координата x конечной точки отрезка в мировых
            // координатах
            x += deltaX;
            bool hasEnd = f_exists(x);
            // Если функция определена в этой точке, то
            if (hasEnd) {

                // координата y конечной точки в мировых координатах
                y = f(x);
                // вычисляем соответствующее значение в координатах экрана
                end.y = Wcy - (y - Vc_work.y) / V_work.y * Wy;
            }

            // Отсечение отрезка относительно области видимости на форме,
            // предворительно сохранив координаты конца отрезка
            vec2 tmpEnd = end;
            bool visible = hasStart && hasEnd && clip(start, end, minX, minY, maxX, maxY);
            hasStart = hasEnd;
            // если отрезок видим
            if (visible) {
                // после отсечения, start и end - концы видимой части отрезка
                // отрисовка видимых частей
                g->DrawLine(pen, start.x, start.y, end.x, end.y);
            }
            // конечная точка неотсеченного отрезка становится начальной точкой
            // следующего
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
        // Задаем квадрат со стороной 4, с центром в начале координат
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
        // координаты центра прямоугольника
        float centerX = Vc_work.x + V_work.x / 2;
        // в мировой системе координат
        float centerY = Vc_work.y + V_work.y / 2;
        switch (e->KeyCode) {
        // Сброс всех сделанных преобразований
        case Keys::Escape:
            T = initT;
            break;
        case Keys::A:
            // сдвиг графика вправо на один пиксел
            T = translate(-V_work.x / Wx, 0.f) * T;
            break;
        case Keys::Z:
            // перенос начала координат в центр
            T = translate(-centerX, -centerY) * T;
            // масштабирование относительно начала координат
            T = scale(1.1) * T;
            // возврат позиции начала координат
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
