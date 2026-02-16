#pragma once
#include "Tariff.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace ATSProject {
    namespace Forms {
        public ref class TariffForm : public Form {
        public:
            // Режимы работы формы
            enum class FormMode {
                Add,    // Добавление
                Edit    // Редактирование
            };

        private:
            TextBox^ txtCity;
            TextBox^ txtBaseCost;
            ComboBox^ cmbStrategyType;
            TextBox^ txtDiscountRate;
            Button^ btnOK;
            Button^ btnCancel;
            Label^ lblCity;
            Label^ lblBaseCost;
            Label^ lblStrategyType;
            Label^ lblDiscountRate;
            Label^ lblTitle;

            FormMode mode;
            Models::Tariff^ editingTariff;

        public:
            Models::Tariff^ ResultTariff;

            // Конструктор для добавления нового тарифа
            TariffForm();

            // ПЕРЕГРУЗКА КОНСТРУКТОРА для редактирования существующего
            TariffForm(Models::Tariff^ tariff);

        private:
            void InitializeComponent();
            void InitializeForMode();
            void OnPriceKeyPress(Object^ sender, KeyPressEventArgs^ e);
            void OnDiscountKeyPress(Object^ sender, KeyPressEventArgs^ e);
            void OnStrategyTypeChanged(Object^ sender, EventArgs^ e);
            bool ValidateCity(String^ city);
            bool ValidatePrice(String^ priceText, [System::Runtime::InteropServices::Out] double% price);
            bool ValidateDiscount(String^ discountText, [System::Runtime::InteropServices::Out] double% discount);
            void OnOKClick(Object^ sender, EventArgs^ e);
        };
    }
}
