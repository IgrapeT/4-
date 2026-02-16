#include "ClientForm.h"

namespace ATSProject {
    namespace Forms {

        // Конструктор для ДОБАВЛЕНИЯ
        ClientForm::ClientForm() {
            mode = FormMode::Add;
            editingClient = nullptr;
            ResultClient = nullptr;
            InitializeComponent();
            InitializeForMode();
        }

        // Конструктор для РЕДАКТИРОВАНИЯ (ПЕРЕГРУЗКА)
        ClientForm::ClientForm(Models::Client^ client) {
            mode = FormMode::Edit;
            editingClient = client;
            ResultClient = nullptr;
            InitializeComponent();
            InitializeForMode();
        }

        void ClientForm::InitializeComponent() {
            this->Size = System::Drawing::Size(400, 280);
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
            lblLastName = gcnew Label();
            lblLastName->Text = L"Фамилия:";
            lblLastName->Location = Point(20, 50);
            lblLastName->Size = System::Drawing::Size(100, 20);

            lblFirstName = gcnew Label();
            lblFirstName->Text = L"Имя:";
            lblFirstName->Location = Point(20, 90);
            lblFirstName->Size = System::Drawing::Size(100, 20);

            lblPhone = gcnew Label();
            lblPhone->Text = L"Телефон:";
            lblPhone->Location = Point(20, 130);
            lblPhone->Size = System::Drawing::Size(100, 20);

            // TextBoxes
            txtLastName = gcnew TextBox();
            txtLastName->Location = Point(130, 50);
            txtLastName->Size = System::Drawing::Size(230, 20);
            txtLastName->MaxLength = 50;

            txtFirstName = gcnew TextBox();
            txtFirstName->Location = Point(130, 90);
            txtFirstName->Size = System::Drawing::Size(230, 20);
            txtFirstName->MaxLength = 50;

            txtPhone = gcnew TextBox();
            txtPhone->Location = Point(130, 130);
            txtPhone->Size = System::Drawing::Size(230, 20);
            txtPhone->MaxLength = 20;
            txtPhone->KeyPress += gcnew KeyPressEventHandler(this, &ClientForm::OnPhoneKeyPress);

            // Buttons
            btnOK = gcnew Button();
            btnOK->Location = Point(180, 180);
            btnOK->Size = System::Drawing::Size(80, 30);
            btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
            btnOK->Click += gcnew EventHandler(this, &ClientForm::OnOKClick);

            btnCancel = gcnew Button();
            btnCancel->Text = L"Отмена";
            btnCancel->Location = Point(280, 180);
            btnCancel->Size = System::Drawing::Size(80, 30);
            btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;

            // Add controls
            this->Controls->Add(lblTitle);
            this->Controls->Add(lblLastName);
            this->Controls->Add(lblFirstName);
            this->Controls->Add(lblPhone);
            this->Controls->Add(txtLastName);
            this->Controls->Add(txtFirstName);
            this->Controls->Add(txtPhone);
            this->Controls->Add(btnOK);
            this->Controls->Add(btnCancel);

            this->AcceptButton = btnOK;
            this->CancelButton = btnCancel;
        }

        void ClientForm::InitializeForMode() {
            // Настраиваем интерфейс в зависимости от режима
            if (mode == FormMode::Add) {
                this->Text = L"Добавить клиента";
                lblTitle->Text = L"ДОБАВЛЕНИЕ НОВОГО КЛИЕНТА";
                lblTitle->ForeColor = Color::Green;
                btnOK->Text = L"Добавить";
            }
            else if (mode == FormMode::Edit) {
                this->Text = L"Редактировать клиента";
                lblTitle->Text = L"РЕДАКТИРОВАНИЕ КЛИЕНТА";
                lblTitle->ForeColor = Color::Blue;
                btnOK->Text = L"Сохранить";

                // Заполняем поля данными
                if (editingClient != nullptr) {
                    txtLastName->Text = editingClient->LastName;
                    txtFirstName->Text = editingClient->FirstName;
                    txtPhone->Text = editingClient->PhoneNumber;
                }
            }
        }

        void ClientForm::OnPhoneKeyPress(Object^ sender, KeyPressEventArgs^ e) {
            if (!Char::IsDigit(e->KeyChar) &&
                e->KeyChar != '+' &&
                e->KeyChar != '-' &&
                e->KeyChar != '(' &&
                e->KeyChar != ')' &&
                e->KeyChar != ' ' &&
                e->KeyChar != (char)Keys::Back) {
                e->Handled = true;
            }
        }

        bool ClientForm::ValidateName(String^ name, String^ fieldName) {
            if (String::IsNullOrWhiteSpace(name)) {
                MessageBox::Show(String::Format(L"Введите {0}!", fieldName),
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            if (name->Length < 2) {
                MessageBox::Show(String::Format(L"{0} должно содержать минимум 2 символа!", fieldName),
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            if (name->Length > 50) {
                MessageBox::Show(String::Format(L"{0} слишком длинное (макс 50 символов)!", fieldName),
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            for each (Char c in name) {
                if (!Char::IsLetter(c) && c != ' ' && c != '-') {
                    MessageBox::Show(String::Format(L"{0} должно содержать только буквы!", fieldName),
                        L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return false;
                }
            }

            return true;
        }

        bool ClientForm::ValidatePhone(String^ phone) {
            if (String::IsNullOrWhiteSpace(phone)) {
                MessageBox::Show(L"Введите номер телефона!",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            String^ digitsOnly = Regex::Replace(phone, "[^0-9]", "");

            if (digitsOnly->Length < 10) {
                MessageBox::Show(L"Номер телефона должен содержать минимум 10 цифр!",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            if (digitsOnly->Length > 15) {
                MessageBox::Show(L"Номер телефона слишком длинный (макс 15 цифр)!",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            return true;
        }

        void ClientForm::OnOKClick(Object^ sender, EventArgs^ e) {
            String^ lastName = txtLastName->Text->Trim();
            String^ firstName = txtFirstName->Text->Trim();
            String^ phone = txtPhone->Text->Trim();

            if (!ValidateName(lastName, L"Фамилия")) {
                this->DialogResult = System::Windows::Forms::DialogResult::None;
                txtLastName->Focus();
                return;
            }

            if (!ValidateName(firstName, L"Имя")) {
                this->DialogResult = System::Windows::Forms::DialogResult::None;
                txtFirstName->Focus();
                return;
            }

            if (!ValidatePhone(phone)) {
                this->DialogResult = System::Windows::Forms::DialogResult::None;
                txtPhone->Focus();
                return;
            }

            // Создаем или обновляем клиента
            if (mode == FormMode::Add) {
                ResultClient = gcnew Models::Client(0, lastName, firstName, phone);
            }
            else {
                ResultClient = gcnew Models::Client(editingClient->Id, lastName, firstName, phone);
            }
        }
    }
}
