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
    int numXsect = 5, numYsect = 5;

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
        return tan(x);
    }

  private:
    bool f_exists(float x, float delta) {
        return fabs(2.f * std::acos(std::cos(x)) - Math::PI) > delta;
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

        Pen ^ gridPen = gcnew Pen(Color::Black, 1);
        SolidBrush ^ drawBrush = gcnew SolidBrush(Color::Black);
        System::Drawing::Font ^ drawFont =
            gcnew System::Drawing::Font("Arial", 8);

        float gridStep_x = Wx / numXsect; // расстояние между линиями сетки по x
        float grid_dX = V_work.x / numXsect; // расстояние между линиями сетки
                                             // по x в мировых координатах

        float tick_x = Vc_work.x; // значение соответствующее первой линии сетки
        for (int i = 0; i <= numXsect; i++) { // цикл по количеству линий

            float tmpXCoord_v =
                Wcx + i * gridStep_x; // координата x i-й вертикальной линии
            // i-я вертикальная линия
            g->DrawLine(gridPen, tmpXCoord_v, Wcy, tmpXCoord_v, minY);
            if (i > 0 && i < numXsect) // если линия не крайняя
                // выводим текст в нижней точке диагональной линии
                g->DrawString(tick_x.ToString("F4"), drawFont, drawBrush,
                              tmpXCoord_v, Wcy);
            tick_x +=
                grid_dX; // вычисляем значение, соответствующее следующей линии
        }
        float gridStep_y = Wy / numYsect;
        float grid_dY = V_work.y / numYsect;
        float tick_y = Vc_work.y;
        for (int i = 0; i <= numYsect; i++) { // цикл по количеству линий
            float tmpYCoord_g =
                Wcy + i * gridStep_y; // координата y горизонтальных линий

            // i-я горизонтальная линия
            g->DrawLine(gridPen, Wcx, tmpYCoord_g - Wy, Wcx + Wx,
                        tmpYCoord_g - Wy);

            if (i > 0 && i < numYsect) // если линия не крайняя
                // выводим текст в правой точке горизонтальной линии
                g->DrawString(tick_y.ToString("F4"), drawFont, drawBrush, maxX,
                              tmpYCoord_g - Wy);
            tick_y +=
                grid_dY; // вычисляем значение, соответствующее следующей линии
        }
        // Перо для графика
        Pen ^ pen = gcnew Pen(Color::Blue, 3);
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

        bool hasStart = f_exists(x, deltaX);
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

            // Высота точки в прямоугольнике (доля общей высоты)
            float deltaY;
            // Компоненты цвета отрезка
            float red, green, blue;

            bool hasEnd = f_exists(x, deltaX);
            // Если функция определена в этой точке, то
            if (hasEnd) {

                // координата y конечной точки в мировых координатах
                y = f(x);
                deltaY = (y - Vc_work.y) / V_work.y;
                // вычисляем соответствующее значение в координатах экрана
                end.y = Wcy - (y - Vc_work.y) / V_work.y * Wy;
            }

            // Отсечение отрезка относительно области видимости на форме,
            // предворительно сохранив координаты конца отрезка
            vec2 tmpEnd = end;
            bool visible =
                hasStart && hasEnd && clip(start, end, minX, minY, maxX, maxY);
            // если отрезок видим
            if (visible) {
                // после отсечения, start и end - концы видимой части отрезка
                // Нормализуем значение высоты точки на случай, если отрезок
                // отсекался
                if (deltaY > 1.f) {
                    deltaY = 1.f;
                }
                if (deltaY < 0.f) {
                    deltaY = 0.f;
                }
                // предварительное вычисление произведения
                green = 510.f * deltaY;
                // если точка ниже середины области видимости
                if (deltaY < 0.5) {
                    // компонента зеленого уже вычислена
                    // синий дополняет зеленый
                    blue = 255.f - green;
                    // красный равен нулю
                    red = 0.f;
                }
                // если точка не ниже середины
                else {
                    // синий равен нулю
                    blue = 0.f;
                    // вычисляем красный и зеленый
                    red = green - 255.f;
                    // с использованием вычисленного произведения
                    green = 510.f - green;
                }
                // меняем цвет пера
                pen->Color = Color::FromArgb(red, green, blue);
                // отрисовка видимых частей
                g->DrawLine(pen, start.x, start.y, end.x, end.y);
            }
            // конечная точка неотсеченного отрезка становится начальной точкой
            // следующего
            start = tmpEnd;
            hasStart = hasEnd;
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
        case Keys::D:
            // сдвиг графика вправо на один пиксел
            T = translate(V_work.x / Wx, 0.f) * T;
            break;
        case Keys::S:
            // сдвиг графика вправо на один пиксел
            T = translate(0.f, -V_work.y / Wy) * T;
            break;
        case Keys::W:
            // сдвиг графика вправо на один пиксел
            T = translate(0.f, V_work.y / Wy) * T;
            break;
        case Keys::Z:
            // перенос начала координат в центр
            T = translate(-centerX, -centerY) * T;
            // масштабирование относительно начала координат
            T = scale(1.1) * T;
            // возврат позиции начала координат
            T = translate(centerX, centerY) * T;
            break;
        case Keys::X:
            // перенос начала координат в центр
            T = translate(-centerX, -centerY) * T;

            T = scale(1 / 1.1) *
                T; // масштабирование относительно начала координат

            T = translate(centerX, centerY) *
                T; // возврат позиции начала координат
            break;
        case Keys::T:

            T = translate(-centerX, -centerY) *
                T; // перенос начала координат в центр

            T = scale(1.1, 1) *
                T; // масштабирование относительно начала координат

            T = translate(centerX, centerY) *
                T; // возврат позиции начала координат
            break;
        case Keys::G:

            T = translate(-centerX, -centerY) *
                T; // перенос начала координат в центр

            T = scale(1 / 1.1, 1) *
                T; // масштабирование относительно начала координат

            T = translate(centerX, centerY) *
                T; // возврат позиции начала координат
            break;
        case Keys::Y:

            T = translate(-centerX, -centerY) *
                T; // перенос начала координат в центр

            T = scale(1, 1.1) *
                T; // масштабирование относительно начала координат

            T = translate(centerX, centerY) *
                T; // возврат позиции начала координат
            break;
        case Keys::H:

            T = translate(-centerX, -centerY) *
                T; // перенос начала координат в центр

            T = scale(1, 1 / 1.1) *
                T; // масштабирование относительно начала координат

            T = translate(centerX, centerY) *
                T; // возврат позиции начала координат
            break;
        case Keys::D1:
            numXsect++;
            break;
        case Keys::D2:
            numXsect = std::max(2, numXsect - 1);
            break;
        case Keys::D3:
            numYsect++;
            break;
        case Keys::D4:
            numYsect = std::max(2, numYsect - 1);
        case Keys::Q:
            T = translate(-centerX, -centerY) *
                T; // перенос начала координат в центр
            T = rotate(0.1f) * T;
            T = translate(centerX, centerY) *
                T; // возврат позиции начала координат
            break;
        case Keys::E:
            T = translate(-centerX, -centerY) *
                T; // перенос начала координат в центр
            T = rotate(-0.1f) * T;
            T = translate(centerX, centerY) *
                T; // возврат позиции начала координат
            break;
        case Keys::U:
            T = translate(-centerX, -centerY) *
                T; // перенос начала координат в центр
            T = scale(-1.f, 1.f) *
                T; // масштабирование относительно начала координат
            T = translate(centerX, centerY) *
                T; // возврат позиции начала координат
            break;
        case Keys::J:
            T = translate(-centerX, -centerY) *
                T; // перенос начала координат в центр
            T = scale(1.f, -1.f) *
                T; // масштабирование относительно начала координат
            T = translate(centerX, centerY) *
                T; // возврат позиции начала координат
        default:
            break;
        }
        Refresh();
        worldRectCalc();
    }
};
} // namespace Smirnov251HW2
