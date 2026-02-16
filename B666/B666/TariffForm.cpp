#include "TariffForm.h"

using namespace System::Globalization;

namespace ATSProject {
    namespace Forms {

        // Конструктор для ДОБАВЛЕНИЯ
        TariffForm::TariffForm() {
            mode = TariffForm::FormMode::Add;
            editingTariff = nullptr;
            ResultTariff = nullptr;
            InitializeComponent();
            InitializeForMode();
        }

        // Конструктор для РЕДАКТИРОВАНИЯ (ПЕРЕГРУЗКА)
        TariffForm::TariffForm(Models::Tariff^ tariff) {
            mode = TariffForm::FormMode::Edit;
            editingTariff = tariff;
            ResultTariff = nullptr;
            InitializeComponent();
            InitializeForMode();
        }

        void TariffForm::InitializeComponent() {
            this->Size = System::Drawing::Size(400, 310);
            this->StartPosition = FormStartPosition::CenterParent;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;

            // Заголовок формы
            lblTitle = gcnew Label();
            lblTitle->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
            lblTitle->Location = Point(20, 10);
            lblTitle->Size = System::Drawing::Size(350, 25);
            lblTitle->TextAlign = ContentAlignment::MiddleCenter;

            // Labels
            lblCity = gcnew Label();
            lblCity->Text = L"Город:";
            lblCity->Location = Point(20, 50);
            lblCity->Size = System::Drawing::Size(120, 20);

            lblBaseCost = gcnew Label();
            lblBaseCost->Text = L"Цена за минуту:";
            lblBaseCost->Location = Point(20, 90);
            lblBaseCost->Size = System::Drawing::Size(120, 20);

            lblStrategyType = gcnew Label();
            lblStrategyType->Text = L"Тип тарифа:";
            lblStrategyType->Location = Point(20, 130);
            lblStrategyType->Size = System::Drawing::Size(120, 20);

            lblDiscountRate = gcnew Label();
            lblDiscountRate->Text = L"Скидка (%):";
            lblDiscountRate->Location = Point(20, 170);
            lblDiscountRate->Size = System::Drawing::Size(120, 20);

            // TextBoxes
            txtCity = gcnew TextBox();
            txtCity->Location = Point(150, 50);
            txtCity->Size = System::Drawing::Size(210, 20);
            txtCity->MaxLength = 100;

            txtBaseCost = gcnew TextBox();
            txtBaseCost->Location = Point(150, 90);
            txtBaseCost->Size = System::Drawing::Size(210, 20);
            txtBaseCost->KeyPress += gcnew KeyPressEventHandler(this, &TariffForm::OnPriceKeyPress);

            // ComboBox
            cmbStrategyType = gcnew ComboBox();
            cmbStrategyType->Location = Point(150, 130);
            cmbStrategyType->Size = System::Drawing::Size(210, 20);
            cmbStrategyType->DropDownStyle = ComboBoxStyle::DropDownList;
            cmbStrategyType->Items->Add(L"Regular");
            cmbStrategyType->Items->Add(L"Discounted");
            cmbStrategyType->SelectedIndex = 0;
            cmbStrategyType->SelectedIndexChanged += gcnew EventHandler(this, &TariffForm::OnStrategyTypeChanged);

            txtDiscountRate = gcnew TextBox();
            txtDiscountRate->Location = Point(150, 170);
            txtDiscountRate->Size = System::Drawing::Size(210, 20);
            txtDiscountRate->Enabled = false;
            txtDiscountRate->Text = L"0";
            txtDiscountRate->KeyPress += gcnew KeyPressEventHandler(this, &TariffForm::OnDiscountKeyPress);

            // Buttons
            btnOK = gcnew Button();
            btnOK->Location = Point(180, 220);
            btnOK->Size = System::Drawing::Size(80, 30);
            btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
            btnOK->Click += gcnew EventHandler(this, &TariffForm::OnOKClick);

            btnCancel = gcnew Button();
            btnCancel->Text = L"Отмена";
            btnCancel->Location = Point(280, 220);
            btnCancel->Size = System::Drawing::Size(80, 30);
            btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;

            // Add controls
            this->Controls->Add(lblTitle);
            this->Controls->Add(lblCity);
            this->Controls->Add(lblBaseCost);
            this->Controls->Add(lblStrategyType);
            this->Controls->Add(lblDiscountRate);
            this->Controls->Add(txtCity);
            this->Controls->Add(txtBaseCost);
            this->Controls->Add(cmbStrategyType);
            this->Controls->Add(txtDiscountRate);
            this->Controls->Add(btnOK);
            this->Controls->Add(btnCancel);

            this->AcceptButton = btnOK;
            this->CancelButton = btnCancel;
        }

        void TariffForm::InitializeForMode() {
            if (mode == TariffForm::FormMode::Add) {
                this->Text = L"Добавить тариф";
                lblTitle->Text = L"ДОБАВЛЕНИЕ НОВОГО ТАРИФА";
                lblTitle->ForeColor = Color::Green;
                btnOK->Text = L"Добавить";
            }
            else if (mode == TariffForm::FormMode::Edit) {
                this->Text = L"Редактировать тариф";
                lblTitle->Text = L"РЕДАКТИРОВАНИЕ ТАРИФА";
                lblTitle->ForeColor = Color::Blue;
                btnOK->Text = L"Сохранить";

                if (editingTariff != nullptr) {
                    txtCity->Text = editingTariff->City;
                    txtBaseCost->Text = editingTariff->BaseCostPerMinute.ToString("F2");

                    if (editingTariff->StrategyType == "Regular") {
                        cmbStrategyType->SelectedIndex = 0;
                    }
                    else {
                        cmbStrategyType->SelectedIndex = 1;
                        if (editingTariff->DiscountRate.HasValue) {
                            txtDiscountRate->Text = editingTariff->DiscountRate.Value.ToString("F2");
                        }
                    }
                }
            }
        }

        void TariffForm::OnPriceKeyPress(Object^ sender, KeyPressEventArgs^ e) {
            TextBox^ txt = safe_cast<TextBox^>(sender);

            if (!Char::IsDigit(e->KeyChar) &&
                e->KeyChar != '.' &&
                e->KeyChar != ',' &&
                e->KeyChar != (char)Keys::Back) {
                e->Handled = true;
                return;
            }

            if ((e->KeyChar == '.' || e->KeyChar == ',') &&
                (txt->Text->Contains(".") || txt->Text->Contains(","))) {
                e->Handled = true;
            }
        }

        void TariffForm::OnDiscountKeyPress(Object^ sender, KeyPressEventArgs^ e) {
            TextBox^ txt = safe_cast<TextBox^>(sender);

            if (!Char::IsDigit(e->KeyChar) &&
                e->KeyChar != '.' &&
                e->KeyChar != ',' &&
                e->KeyChar != (char)Keys::Back) {
                e->Handled = true;
                return;
            }

            if ((e->KeyChar == '.' || e->KeyChar == ',') &&
                (txt->Text->Contains(".") || txt->Text->Contains(","))) {
                e->Handled = true;
            }
        }

        void TariffForm::OnStrategyTypeChanged(Object^ sender, EventArgs^ e) {
            if (cmbStrategyType->SelectedItem->ToString() == L"Discounted") {
                txtDiscountRate->Enabled = true;
            }
            else {
                txtDiscountRate->Enabled = false;
                txtDiscountRate->Text = L"0";
            }
        }

        bool TariffForm::ValidateCity(String^ city) {
            if (String::IsNullOrWhiteSpace(city)) {
                MessageBox::Show(L"Введите название города!",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            if (city->Length < 2) {
                MessageBox::Show(L"Название города должно содержать минимум 2 символа!",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            if (city->Length > 100) {
                MessageBox::Show(L"Название города слишком длинное (макс 100 символов)!",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            for each (Char c in city) {
                if (!Char::IsLetter(c) && c != ' ' && c != '-') {
                    MessageBox::Show(L"Название города должно содержать только буквы!",
                        L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return false;
                }
            }

            return true;
        }

        bool TariffForm::ValidatePrice(String^ priceText, double% price) {
            if (String::IsNullOrWhiteSpace(priceText)) {
                MessageBox::Show(L"Введите цену за минуту!",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            String^ normalizedPrice = priceText->Replace(',', '.');

            if (!Double::TryParse(normalizedPrice, System::Globalization::NumberStyles::Float,
                System::Globalization::CultureInfo::InvariantCulture, price)) {
                MessageBox::Show(L"Введите корректную цену (например: 2.5 или 10.00)!",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            if (price <= 0) {
                MessageBox::Show(L"Цена должна быть больше 0!",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            if (price > 1000000) {
                MessageBox::Show(L"Цена слишком большая (максимум 1,000,000)!",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            return true;
        }

        bool TariffForm::ValidateDiscount(String^ discountText, double% discount) {
            if (String::IsNullOrWhiteSpace(discountText)) {
                discount = 0;
                return true;
            }

            String^ normalizedDiscount = discountText->Replace(',', '.');

            if (!Double::TryParse(normalizedDiscount, System::Globalization::NumberStyles::Float,
                System::Globalization::CultureInfo::InvariantCulture, discount)) {
                MessageBox::Show(L"Введите корректную скидку (например: 10 или 15.5)!",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            if (discount < 0) {
                MessageBox::Show(L"Скидка не может быть отрицательной!",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            if (discount > 100) {
                MessageBox::Show(L"Скидка не может быть больше 100%!",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            return true;
        }

        void TariffForm::OnOKClick(Object^ sender, EventArgs^ e) {
            String^ city = txtCity->Text->Trim();
            String^ priceText = txtBaseCost->Text->Trim();
            String^ strategyType = cmbStrategyType->SelectedItem->ToString();
            String^ discountText = txtDiscountRate->Text->Trim();

            if (!ValidateCity(city)) {
                this->DialogResult = System::Windows::Forms::DialogResult::None;
                txtCity->Focus();
                return;
            }

            double price;
            if (!ValidatePrice(priceText, price)) {
                this->DialogResult = System::Windows::Forms::DialogResult::None;
                txtBaseCost->Focus();
                return;
            }

            if (strategyType == L"Discounted") {
                double discount;
                if (!ValidateDiscount(discountText, discount)) {
                    this->DialogResult = System::Windows::Forms::DialogResult::None;
                    txtDiscountRate->Focus();
                    return;
                }

                if (mode == TariffForm::FormMode::Add) {
                    ResultTariff = gcnew Models::Tariff(0, city, price, strategyType, discount);
                }
                else {
                    ResultTariff = gcnew Models::Tariff(editingTariff->Id, city, price, strategyType, discount);
                }
            }
            else {
                if (mode == TariffForm::FormMode::Add) {
                    ResultTariff = gcnew Models::Tariff(0, city, price, strategyType);
                }
                else {
                    ResultTariff = gcnew Models::Tariff(editingTariff->Id, city, price, strategyType);
                }
            }
        }
    }
}
