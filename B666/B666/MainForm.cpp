#include "MainForm.h"

namespace ATSProject {
    namespace Forms {

        MainForm::MainForm() {
            InitializeComponent();
            LoadData();
        }

        MainForm::~MainForm() {
            if (components) {
                delete components;
            }
        }

        void MainForm::InitializeComponent() {
            this->Text = L"АТС - Управление звонками";
            this->Size = System::Drawing::Size(1000, 700);
            this->StartPosition = FormStartPosition::CenterScreen;

            // Создание TabControl
            tabControl = gcnew TabControl();
            tabControl->Dock = DockStyle::Fill;

            // Вкладки
            tabPageClients = gcnew TabPage(L"Клиенты");
            CreateClientsTab();

            tabPageTariffs = gcnew TabPage(L"Тарифы");
            CreateTariffsTab();

            tabPageCalls = gcnew TabPage(L"Звонки");
            CreateCallsTab();

            tabPageInfo = gcnew TabPage(L"Информация");
            CreateInfoTab();

            tabControl->TabPages->Add(tabPageClients);
            tabControl->TabPages->Add(tabPageTariffs);
            tabControl->TabPages->Add(tabPageCalls);
            tabControl->TabPages->Add(tabPageInfo);

            // Панель с кнопками внизу
            Panel^ bottomPanel = gcnew Panel();
            bottomPanel->Dock = DockStyle::Bottom;
            bottomPanel->Height = 60;
            bottomPanel->BackColor = Color::LightGray;

            btnSaveToFile = CreateButton(L"Сохранить в файл", 10, 15, 130, 30);
            btnSaveToFile->Click += gcnew EventHandler(this, &MainForm::OnSaveToFile);
            bottomPanel->Controls->Add(btnSaveToFile);

            btnLoadFromFile = CreateButton(L"Загрузить из файла", 150, 15, 130, 30);
            btnLoadFromFile->Click += gcnew EventHandler(this, &MainForm::OnLoadFromFile);
            bottomPanel->Controls->Add(btnLoadFromFile);

            btnRefresh = CreateButton(L"Обновить", 290, 15, 100, 30);
            btnRefresh->Click += gcnew EventHandler(this, &MainForm::OnRefresh);
            bottomPanel->Controls->Add(btnRefresh);

            btnClearAll = CreateButton(L"Очистить всё", 400, 15, 100, 30);
            btnClearAll->Click += gcnew EventHandler(this, &MainForm::OnClearAll);
            bottomPanel->Controls->Add(btnClearAll);

            // Метка времени
            lblUpdateTime = gcnew Label();
            lblUpdateTime->Dock = DockStyle::Bottom;
            lblUpdateTime->TextAlign = ContentAlignment::MiddleRight;
            lblUpdateTime->Height = 25;
            lblUpdateTime->BackColor = Color::WhiteSmoke;
            lblUpdateTime->Padding = System::Windows::Forms::Padding(0, 0, 10, 0);

            this->Controls->Add(tabControl);
            this->Controls->Add(bottomPanel);
            this->Controls->Add(lblUpdateTime);

            // Диалоги для файлов
            openFileDialog = gcnew OpenFileDialog();
            openFileDialog->Filter = L"ATS Data Files (*.ats)|*.ats|All Files (*.*)|*.*";
            openFileDialog->Title = L"Загрузить данные";

            saveFileDialog = gcnew SaveFileDialog();
            saveFileDialog->Filter = L"ATS Data Files (*.ats)|*.ats|All Files (*.*)|*.*";
            saveFileDialog->Title = L"Сохранить данные";
            saveFileDialog->DefaultExt = L"ats";

            UpdateTimestamp();
        }

        void MainForm::CreateClientsTab() {
            dgvClients = gcnew DataGridView();
            dgvClients->Dock = DockStyle::Fill;
            dgvClients->AllowUserToAddRows = false;
            dgvClients->AllowUserToDeleteRows = false;
            dgvClients->ReadOnly = true;
            dgvClients->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            dgvClients->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            dgvClients->MultiSelect = false;

            Panel^ buttonPanel = gcnew Panel();
            buttonPanel->Dock = DockStyle::Bottom;
            buttonPanel->Height = 50;

            btnAddClient = CreateButton(L"Добавить", 10, 10, 100, 30);
            btnEditClient = CreateButton(L"Изменить", 120, 10, 100, 30);
            btnDeleteClient = CreateButton(L"Удалить", 230, 10, 100, 30);
            btnMakeCall = CreateButton(L"Совершить звонок", 340, 10, 140, 30);
            btnSortClients = CreateButton(L"Сортировать", 490, 10, 110, 30);

            btnAddClient->Click += gcnew EventHandler(this, &MainForm::OnAddClient);
            btnEditClient->Click += gcnew EventHandler(this, &MainForm::OnEditClient);
            btnDeleteClient->Click += gcnew EventHandler(this, &MainForm::OnDeleteClient);
            btnMakeCall->Click += gcnew EventHandler(this, &MainForm::OnMakeCall);
            btnSortClients->Click += gcnew EventHandler(this, &MainForm::OnSortClients);

            buttonPanel->Controls->Add(btnAddClient);
            buttonPanel->Controls->Add(btnEditClient);
            buttonPanel->Controls->Add(btnDeleteClient);
            buttonPanel->Controls->Add(btnMakeCall);
            buttonPanel->Controls->Add(btnSortClients);

            tabPageClients->Controls->Add(dgvClients);
            tabPageClients->Controls->Add(buttonPanel);
        }

        void MainForm::CreateTariffsTab() {
            dgvTariffs = gcnew DataGridView();
            dgvTariffs->Dock = DockStyle::Fill;
            dgvTariffs->AllowUserToAddRows = false;
            dgvTariffs->AllowUserToDeleteRows = false;
            dgvTariffs->ReadOnly = true;
            dgvTariffs->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            dgvTariffs->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            dgvTariffs->MultiSelect = false;

            Panel^ buttonPanel = gcnew Panel();
            buttonPanel->Dock = DockStyle::Bottom;
            buttonPanel->Height = 50;

            btnAddTariff = CreateButton(L"Добавить", 10, 10, 100, 30);
            btnEditTariff = CreateButton(L"Изменить", 120, 10, 100, 30);
            btnDeleteTariff = CreateButton(L"Удалить", 230, 10, 100, 30);
            btnSortTariffs = CreateButton(L"Сортировать", 340, 10, 110, 30);

            btnAddTariff->Click += gcnew EventHandler(this, &MainForm::OnAddTariff);
            btnEditTariff->Click += gcnew EventHandler(this, &MainForm::OnEditTariff);
            btnDeleteTariff->Click += gcnew EventHandler(this, &MainForm::OnDeleteTariff);
            btnSortTariffs->Click += gcnew EventHandler(this, &MainForm::OnSortTariffs);

            buttonPanel->Controls->Add(btnAddTariff);
            buttonPanel->Controls->Add(btnEditTariff);
            buttonPanel->Controls->Add(btnDeleteTariff);
            buttonPanel->Controls->Add(btnSortTariffs);

            tabPageTariffs->Controls->Add(dgvTariffs);
            tabPageTariffs->Controls->Add(buttonPanel);
        }

        void MainForm::CreateCallsTab() {
            dgvCalls = gcnew DataGridView();
            dgvCalls->Dock = DockStyle::Fill;
            dgvCalls->AllowUserToAddRows = false;
            dgvCalls->AllowUserToDeleteRows = false;
            dgvCalls->ReadOnly = true;
            dgvCalls->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            dgvCalls->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            dgvCalls->MultiSelect = false;

            Panel^ buttonPanel = gcnew Panel();
            buttonPanel->Dock = DockStyle::Bottom;
            buttonPanel->Height = 50;

            btnDeleteCall = CreateButton(L"Удалить звонок", 10, 10, 130, 30);
            btnViewClientCalls = CreateButton(L"Звонки клиента", 150, 10, 130, 30);

            btnDeleteCall->Click += gcnew EventHandler(this, &MainForm::OnDeleteCall);
            btnViewClientCalls->Click += gcnew EventHandler(this, &MainForm::OnViewClientCalls);

            buttonPanel->Controls->Add(btnDeleteCall);
            buttonPanel->Controls->Add(btnViewClientCalls);

            tabPageCalls->Controls->Add(dgvCalls);
            tabPageCalls->Controls->Add(buttonPanel);
        }

        void MainForm::CreateInfoTab() {
            dgvInfo = gcnew DataGridView();
            dgvInfo->Dock = DockStyle::Fill;
            dgvInfo->AllowUserToAddRows = false;
            dgvInfo->AllowUserToDeleteRows = false;
            dgvInfo->ReadOnly = true;
            dgvInfo->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;

            tabPageInfo->Controls->Add(dgvInfo);
        }

        Button^ MainForm::CreateButton(String^ text, int x, int y, int width, int height) {
            Button^ btn = gcnew Button();
            btn->Text = text;
            btn->Location = Point(x, y);
            btn->Size = System::Drawing::Size(width, height);
            return btn;
        }

        void MainForm::UpdateTimestamp() {
            lblUpdateTime->Text = L"Обновлено: " + DateTime::Now.ToString(L"dd.MM.yyyy HH:mm:ss");
        }
        // === ЗАГРУЗКА ДАННЫХ ===

        void MainForm::LoadData() {
            LoadClients();
            LoadTariffs();
            LoadCalls();
            LoadInfo();
        }

        void MainForm::LoadClients() {
            try {
                auto dm = Data::DataManager::GetInstance();
                auto clients = dm->GetAllClients();

                DataTable^ dt = gcnew DataTable();
                dt->Columns->Add("ID", int::typeid);
                dt->Columns->Add(L"Фамилия", String::typeid);
                dt->Columns->Add(L"Имя", String::typeid);
                dt->Columns->Add(L"Телефон", String::typeid);

                for each (auto client in clients) {
                    DataRow^ row = dt->NewRow();
                    row["ID"] = client->Id;
                    row[L"Фамилия"] = client->LastName;
                    row[L"Имя"] = client->FirstName;
                    row[L"Телефон"] = client->PhoneNumber;
                    dt->Rows->Add(row);
                }

                dgvClients->DataSource = dt;
            }
            catch (Exception^ ex) {
                MessageBox::Show(L"Ошибка загрузки клиентов: " + ex->Message);
            }
        }

        void MainForm::LoadTariffs() {
            try {
                auto dm = Data::DataManager::GetInstance();
                auto tariffs = dm->GetAllTariffs();

                DataTable^ dt = gcnew DataTable();
                dt->Columns->Add("ID", int::typeid);
                dt->Columns->Add(L"Город", String::typeid);
                dt->Columns->Add(L"Цена/мин", double::typeid);
                dt->Columns->Add(L"Тип", String::typeid);
                dt->Columns->Add(L"Скидка %", String::typeid);

                for each (auto tariff in tariffs) {
                    DataRow^ row = dt->NewRow();
                    row["ID"] = tariff->Id;
                    row[L"Город"] = tariff->City;
                    row[L"Цена/мин"] = tariff->BaseCostPerMinute;
                    row[L"Тип"] = tariff->StrategyType;
                    row[L"Скидка %"] = tariff->DiscountRate.HasValue ?
                        tariff->DiscountRate.Value.ToString("F2") : "-";
                    dt->Rows->Add(row);
                }

                dgvTariffs->DataSource = dt;
            }
            catch (Exception^ ex) {
                MessageBox::Show(L"Ошибка загрузки тарифов: " + ex->Message);
            }
        }

        void MainForm::LoadCalls() {
            try {
                auto dm = Data::DataManager::GetInstance();
                auto calls = dm->GetAllCalls();

                DataTable^ dt = gcnew DataTable();
                dt->Columns->Add("ID", int::typeid);
                dt->Columns->Add(L"ID Клиента", int::typeid);
                dt->Columns->Add(L"ID Тарифа", int::typeid);
                dt->Columns->Add(L"Город", String::typeid);
                dt->Columns->Add(L"Длительность (мин)", int::typeid);
                dt->Columns->Add(L"Стоимость", double::typeid);

                for each (auto call in calls) {
                    DataRow^ row = dt->NewRow();
                    row["ID"] = call->Id;
                    row[L"ID Клиента"] = call->ClientId;
                    row[L"ID Тарифа"] = call->TariffId;
                    row[L"Город"] = call->City;
                    row[L"Длительность (мин)"] = call->Duration;
                    row[L"Стоимость"] = call->Cost;
                    dt->Rows->Add(row);
                }

                dgvCalls->DataSource = dt;
            }
            catch (Exception^ ex) {
                MessageBox::Show(L"Ошибка загрузки звонков: " + ex->Message);
            }
        }

        void MainForm::LoadInfo() {
            try {
                auto dm = Data::DataManager::GetInstance();

                DataTable^ dt = gcnew DataTable();
                dt->Columns->Add(L"Параметр", String::typeid);
                dt->Columns->Add(L"Значение", String::typeid);

                DataRow^ row1 = dt->NewRow();
                row1[L"Параметр"] = L"Всего клиентов";
                row1[L"Значение"] = dm->GetTotalClients().ToString();
                dt->Rows->Add(row1);

                DataRow^ row2 = dt->NewRow();
                row2[L"Параметр"] = L"Всего тарифов";
                row2[L"Значение"] = dm->GetTotalTariffs().ToString();
                dt->Rows->Add(row2);

                DataRow^ row3 = dt->NewRow();
                row3[L"Параметр"] = L"Всего звонков";
                row3[L"Значение"] = dm->GetTotalCalls().ToString();
                dt->Rows->Add(row3);

                dgvInfo->DataSource = dt;
            }
            catch (Exception^ ex) {
                MessageBox::Show(L"Ошибка загрузки информации: " + ex->Message);
            }
        }
        // === ОБРАБОТЧИКИ КЛИЕНТОВ ===

        void MainForm::OnAddClient(Object^ sender, EventArgs^ e) {
            ClientForm^ form = gcnew ClientForm(); // Конструктор для ДОБАВЛЕНИЯ
            if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                auto dm = Data::DataManager::GetInstance();
                dm->AddClient(form->ResultClient);
                LoadClients();
                LoadInfo();
                UpdateTimestamp();
                MessageBox::Show(L"Клиент добавлен!", L"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        void MainForm::OnEditClient(Object^ sender, EventArgs^ e) {
            if (dgvClients->SelectedRows->Count == 0) {
                MessageBox::Show(L"Выберите клиента для редактирования!");
                return;
            }

            int clientId = Convert::ToInt32(dgvClients->SelectedRows[0]->Cells["ID"]->Value);
            auto dm = Data::DataManager::GetInstance();
            auto client = dm->FindClient(clientId);

            if (client != nullptr) {
                ClientForm^ form = gcnew ClientForm(client); // Конструктор для РЕДАКТИРОВАНИЯ (перегрузка)
                if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                    dm->UpdateClient(form->ResultClient);
                    LoadClients();
                    UpdateTimestamp();
                    MessageBox::Show(L"Клиент обновлен!", L"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
            }
        }

        void MainForm::OnDeleteClient(Object^ sender, EventArgs^ e) {
            if (dgvClients->SelectedRows->Count == 0) {
                MessageBox::Show(L"Выберите клиента для удаления!");
                return;
            }

            auto result = MessageBox::Show(L"Удалить выбранного клиента?\n\nВсе его звонки также будут удалены!",
                L"Подтверждение", MessageBoxButtons::YesNo, MessageBoxIcon::Question);

            if (result == System::Windows::Forms::DialogResult::Yes) {
                int clientId = Convert::ToInt32(dgvClients->SelectedRows[0]->Cells["ID"]->Value);
                auto dm = Data::DataManager::GetInstance();
                dm->DeleteClient(clientId);
                LoadClients();
                LoadCalls();
                LoadInfo();
                UpdateTimestamp();
                MessageBox::Show(L"Клиент удален!", L"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        void MainForm::OnSortClients(Object^ sender, EventArgs^ e) {
            auto dm = Data::DataManager::GetInstance();
            dm->SortClientsByName();
            LoadClients();
            UpdateTimestamp();
            MessageBox::Show(L"Клиенты отсортированы по фамилии!", L"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        // === ОБРАБОТЧИКИ ТАРИФОВ ===

        void MainForm::OnAddTariff(Object^ sender, EventArgs^ e) {
            TariffForm^ form = gcnew TariffForm(); // Конструктор для ДОБАВЛЕНИЯ
            if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                auto dm = Data::DataManager::GetInstance();
                dm->AddTariff(form->ResultTariff);
                LoadTariffs();
                LoadInfo();
                UpdateTimestamp();
                MessageBox::Show(L"Тариф добавлен!", L"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        void MainForm::OnEditTariff(Object^ sender, EventArgs^ e) {
            if (dgvTariffs->SelectedRows->Count == 0) {
                MessageBox::Show(L"Выберите тариф для редактирования!");
                return;
            }

            int tariffId = Convert::ToInt32(dgvTariffs->SelectedRows[0]->Cells["ID"]->Value);
            auto dm = Data::DataManager::GetInstance();
            auto tariff = dm->FindTariff(tariffId);

            if (tariff != nullptr) {
                TariffForm^ form = gcnew TariffForm(tariff); // Конструктор для РЕДАКТИРОВАНИЯ (перегрузка)
                if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                    dm->UpdateTariff(form->ResultTariff);
                    LoadTariffs();
                    UpdateTimestamp();
                    MessageBox::Show(L"Тариф обновлен!", L"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
            }
        }

        void MainForm::OnDeleteTariff(Object^ sender, EventArgs^ e) {
            if (dgvTariffs->SelectedRows->Count == 0) {
                MessageBox::Show(L"Выберите тариф для удаления!");
                return;
            }

            auto result = MessageBox::Show(L"Удалить выбранный тариф?\n\nВсе звонки с этим тарифом также будут удалены!",
                L"Подтверждение", MessageBoxButtons::YesNo, MessageBoxIcon::Question);

            if (result == System::Windows::Forms::DialogResult::Yes) {
                int tariffId = Convert::ToInt32(dgvTariffs->SelectedRows[0]->Cells["ID"]->Value);
                auto dm = Data::DataManager::GetInstance();
                dm->DeleteTariff(tariffId);
                LoadTariffs();
                LoadCalls();
                LoadInfo();
                UpdateTimestamp();
                MessageBox::Show(L"Тариф удален!", L"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        void MainForm::OnSortTariffs(Object^ sender, EventArgs^ e) {
            auto dm = Data::DataManager::GetInstance();
            dm->SortTariffsByCity();
            LoadTariffs();
            UpdateTimestamp();
            MessageBox::Show(L"Тарифы отсортированы по городу!", L"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
        // === ОБРАБОТЧИКИ ЗВОНКОВ ===

        void MainForm::OnMakeCall(Object^ sender, EventArgs^ e) {
            if (dgvClients->SelectedRows->Count == 0) {
                MessageBox::Show(L"Выберите клиента!");
                return;
            }

            auto dm = Data::DataManager::GetInstance();
            auto tariffs = dm->GetAllTariffs();

            if (tariffs->Count == 0) {
                MessageBox::Show(L"Сначала добавьте тарифы!");
                return;
            }

            int clientId = Convert::ToInt32(dgvClients->SelectedRows[0]->Cells["ID"]->Value);

            // Создаем форму для звонка
            Form^ callForm = gcnew Form();
            callForm->Text = L"Совершить звонок";
            callForm->Size = System::Drawing::Size(400, 250);
            callForm->StartPosition = FormStartPosition::CenterParent;
            callForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            callForm->MaximizeBox = false;
            callForm->MinimizeBox = false;

            Label^ lblTariff = gcnew Label();
            lblTariff->Text = L"Выберите тариф:";
            lblTariff->Location = Point(20, 20);
            lblTariff->Size = System::Drawing::Size(120, 20);

            ComboBox^ cmbTariff = gcnew ComboBox();
            cmbTariff->Location = Point(150, 20);
            cmbTariff->Size = System::Drawing::Size(210, 20);
            cmbTariff->DropDownStyle = ComboBoxStyle::DropDownList;

            for each (auto tariff in tariffs) {
                String^ item = String::Format(L"{0} - {1} руб/мин ({2})",
                    tariff->City, tariff->BaseCostPerMinute, tariff->StrategyType);
                cmbTariff->Items->Add(item);
            }
            if (cmbTariff->Items->Count > 0) {
                cmbTariff->SelectedIndex = 0;
            }

            Label^ lblDuration = gcnew Label();
            lblDuration->Text = L"Длительность (мин):";
            lblDuration->Location = Point(20, 60);
            lblDuration->Size = System::Drawing::Size(120, 20);

            TextBox^ txtDuration = gcnew TextBox();
            txtDuration->Location = Point(150, 60);
            txtDuration->Size = System::Drawing::Size(210, 20);
            txtDuration->Text = L"10";
            txtDuration->MaxLength = 6;
            txtDuration->KeyPress += gcnew KeyPressEventHandler(this, &MainForm::OnDurationKeyPress);

            Label^ lblCost = gcnew Label();
            lblCost->Text = L"Стоимость: 0.00 руб";
            lblCost->Location = Point(20, 100);
            lblCost->Size = System::Drawing::Size(340, 20);
            lblCost->Font = gcnew System::Drawing::Font(lblCost->Font->FontFamily, 10, FontStyle::Bold);

            // Сохраняем ссылки
            array<Object^>^ controls = gcnew array<Object^>(4);
            controls[0] = cmbTariff;
            controls[1] = txtDuration;
            controls[2] = lblCost;
            controls[3] = tariffs;
            callForm->Tag = controls;

            cmbTariff->SelectedIndexChanged += gcnew EventHandler(this, &MainForm::OnCallFormDataChanged);
            txtDuration->TextChanged += gcnew EventHandler(this, &MainForm::OnCallFormDataChanged);

            UpdateCallCost(cmbTariff, txtDuration, lblCost, tariffs);

            Button^ btnOK = gcnew Button();
            btnOK->Text = L"Совершить";
            btnOK->Location = Point(180, 140);
            btnOK->Size = System::Drawing::Size(80, 30);
            btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;

            Button^ btnCancel = gcnew Button();
            btnCancel->Text = L"Отмена";
            btnCancel->Location = Point(280, 140);
            btnCancel->Size = System::Drawing::Size(80, 30);
            btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;

            callForm->Controls->Add(lblTariff);
            callForm->Controls->Add(cmbTariff);
            callForm->Controls->Add(lblDuration);
            callForm->Controls->Add(txtDuration);
            callForm->Controls->Add(lblCost);
            callForm->Controls->Add(btnOK);
            callForm->Controls->Add(btnCancel);
            callForm->AcceptButton = btnOK;
            callForm->CancelButton = btnCancel;

            if (callForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                try {
                    int duration;
                    if (!ValidateCallDuration(txtDuration->Text, duration)) {
                        return;
                    }

                    int tariffIndex = cmbTariff->SelectedIndex;
                    auto tariff = tariffs[tariffIndex];
                    double cost = tariff->CalculateCost(duration);

                    Models::Call^ call = gcnew Models::Call(0, clientId, tariff->Id, tariff->City, duration, cost);
                    dm->AddCall(call);
                    LoadCalls();
                    LoadInfo();
                    UpdateTimestamp();
                    MessageBox::Show(String::Format(L"Звонок добавлен!\n\nСтоимость: {0:F2} руб", cost),
                        L"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
                catch (Exception^ ex) {
                    MessageBox::Show(L"Ошибка: " + ex->Message);
                }
            }
        }

        void MainForm::OnDeleteCall(Object^ sender, EventArgs^ e) {
            if (dgvCalls->SelectedRows->Count == 0) {
                MessageBox::Show(L"Выберите звонок для удаления!");
                return;
            }

            auto result = MessageBox::Show(L"Удалить выбранный звонок?", L"Подтверждение",
                MessageBoxButtons::YesNo, MessageBoxIcon::Question);

            if (result == System::Windows::Forms::DialogResult::Yes) {
                int callId = Convert::ToInt32(dgvCalls->SelectedRows[0]->Cells["ID"]->Value);
                auto dm = Data::DataManager::GetInstance();
                dm->DeleteCall(callId);
                LoadCalls();
                LoadInfo();
                UpdateTimestamp();
                MessageBox::Show(L"Звонок удален!", L"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        void MainForm::OnViewClientCalls(Object^ sender, EventArgs^ e) {
            if (dgvCalls->SelectedRows->Count == 0) {
                MessageBox::Show(L"Выберите звонок!");
                return;
            }

            int clientId = Convert::ToInt32(dgvCalls->SelectedRows[0]->Cells[L"ID Клиента"]->Value);
            auto dm = Data::DataManager::GetInstance();
            auto client = dm->FindClient(clientId);
            auto calls = dm->GetCallsByClient(clientId);

            if (client != nullptr) {
                String^ message = String::Format(L"Клиент: {0}\n\nВсего звонков: {1}\n\n",
                    client->GetFullName(), calls->Count);

                double totalCost = 0;
                int totalDuration = 0;

                for each (auto call in calls) {
                    message += String::Format(L"• Город: {0}, Длительность: {1} мин, Стоимость: {2:F2} руб\n",
                        call->City, call->Duration, call->Cost);
                    totalCost += call->Cost;
                    totalDuration += call->Duration;
                }

                message += String::Format(L"\nОбщая длительность: {0} мин\nОбщая стоимость: {1:F2} руб",
                    totalDuration, totalCost);

                MessageBox::Show(message, L"Звонки клиента", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        // === РАБОТА С ФАЙЛАМИ ===

        void MainForm::OnSaveToFile(Object^ sender, EventArgs^ e) {
            if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                try {
                    auto dm = Data::DataManager::GetInstance();
                    dm->SaveToFile(saveFileDialog->FileName);
                    MessageBox::Show(L"Данные успешно сохранены!", L"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
                catch (Exception^ ex) {
                    MessageBox::Show(L"Ошибка сохранения: " + ex->Message, L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
        }

        void MainForm::OnLoadFromFile(Object^ sender, EventArgs^ e) {
            if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                auto result = MessageBox::Show(L"Загрузка заменит текущие данные. Продолжить?",
                    L"Предупреждение", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);

                if (result == System::Windows::Forms::DialogResult::Yes) {
                    try {
                        auto dm = Data::DataManager::GetInstance();
                        dm->LoadFromFile(openFileDialog->FileName);
                        LoadData();
                        UpdateTimestamp();
                        MessageBox::Show(L"Данные успешно загружены!", L"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    }
                    catch (Exception^ ex) {
                        MessageBox::Show(L"Ошибка загрузки: " + ex->Message, L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    }
                }
            }
        }

        void MainForm::OnClearAll(Object^ sender, EventArgs^ e) {
            auto result = MessageBox::Show(L"Очистить все данные?\n\nЭто действие необратимо!",
                L"Подтверждение", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);

            if (result == System::Windows::Forms::DialogResult::Yes) {
                auto dm = Data::DataManager::GetInstance();
                dm->ClearAllData();
                LoadData();
                UpdateTimestamp();
                MessageBox::Show(L"Все данные очищены!", L"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        void MainForm::OnRefresh(Object^ sender, EventArgs^ e) {
            LoadData();
            UpdateTimestamp();
        }

        // === ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ===

        void MainForm::OnDurationKeyPress(Object^ sender, KeyPressEventArgs^ e) {
            if (!Char::IsDigit(e->KeyChar) && e->KeyChar != (char)Keys::Back) {
                e->Handled = true;
            }
        }

        bool MainForm::ValidateCallDuration(String^ durationText, int% duration) {
            if (String::IsNullOrWhiteSpace(durationText)) {
                MessageBox::Show(L"Введите длительность звонка!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            if (!Int32::TryParse(durationText, duration)) {
                MessageBox::Show(L"Длительность должна быть целым числом!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            if (duration <= 0) {
                MessageBox::Show(L"Длительность должна быть больше 0 минут!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            if (duration > 10000) {
                MessageBox::Show(L"Длительность слишком большая (максимум 10000 минут)!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            return true;
        }

        void MainForm::OnCallFormDataChanged(Object^ sender, EventArgs^ e) {
            Form^ form = safe_cast<Form^>(safe_cast<Control^>(sender)->FindForm());
            if (form != nullptr && form->Tag != nullptr) {
                array<Object^>^ controls = safe_cast<array<Object^>^>(form->Tag);
                ComboBox^ cmbTariff = safe_cast<ComboBox^>(controls[0]);
                TextBox^ txtDuration = safe_cast<TextBox^>(controls[1]);
                Label^ lblCost = safe_cast<Label^>(controls[2]);
                List<Models::Tariff^>^ tariffs = safe_cast<List<Models::Tariff^>^>(controls[3]);

                UpdateCallCost(cmbTariff, txtDuration, lblCost, tariffs);
            }
        }

        void MainForm::UpdateCallCost(ComboBox^ cmbTariff, TextBox^ txtDuration, Label^ lblCost, List<Models::Tariff^>^ tariffs) {
            try {
                int duration = Int32::Parse(txtDuration->Text);
                int tariffIndex = cmbTariff->SelectedIndex;

                if (tariffIndex >= 0 && tariffIndex < tariffs->Count) {
                    auto tariff = tariffs[tariffIndex];
                    double cost = tariff->CalculateCost(duration);
                    lblCost->Text = String::Format(L"Стоимость: {0:F2} руб", cost);
                }
            }
            catch (...) {
                lblCost->Text = L"Стоимость: 0.00 руб";
            }
        }
    }
}
