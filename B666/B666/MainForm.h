#pragma once
#include "DataManager.h"
#include "ClientForm.h"
#include "TariffForm.h"

namespace ATSProject {
    namespace Forms {
        using namespace System;
        using namespace System::ComponentModel;
        using namespace System::Collections::Generic;
        using namespace System::Windows::Forms;
        using namespace System::Data;
        using namespace System::Drawing;

        public ref class MainForm : public Form {
        private:
            // Таблицы
            DataGridView^ dgvClients;
            DataGridView^ dgvTariffs;
            DataGridView^ dgvCalls;
            DataGridView^ dgvInfo;

            // Кнопки для клиентов
            Button^ btnAddClient;
            Button^ btnEditClient;
            Button^ btnDeleteClient;
            Button^ btnMakeCall;
            Button^ btnSortClients;

            // Кнопки для тарифов
            Button^ btnAddTariff;
            Button^ btnEditTariff;
            Button^ btnDeleteTariff;
            Button^ btnSortTariffs;

            // Кнопки для звонков
            Button^ btnDeleteCall;
            Button^ btnViewClientCalls;

            // Кнопки для файлов
            Button^ btnSaveToFile;
            Button^ btnLoadFromFile;
            Button^ btnClearAll;
            Button^ btnRefresh;

            // TabControl
            TabControl^ tabControl;
            TabPage^ tabPageClients;
            TabPage^ tabPageTariffs;
            TabPage^ tabPageCalls;
            TabPage^ tabPageInfo;

            // Метка времени
            Label^ lblUpdateTime;

            // OpenFileDialog и SaveFileDialog
            OpenFileDialog^ openFileDialog;
            SaveFileDialog^ saveFileDialog;

        public:
            MainForm();

        protected:
            ~MainForm();

        private:
            System::ComponentModel::Container^ components;

            void InitializeComponent();
            void CreateClientsTab();
            void CreateTariffsTab();
            void CreateCallsTab();
            void CreateInfoTab();

            Button^ CreateButton(String^ text, int x, int y, int width, int height);
            void UpdateTimestamp();

            void LoadData();
            void LoadClients();
            void LoadTariffs();
            void LoadCalls();
            void LoadInfo();

            // Обработчики для клиентов
            void OnAddClient(Object^ sender, EventArgs^ e);
            void OnEditClient(Object^ sender, EventArgs^ e);
            void OnDeleteClient(Object^ sender, EventArgs^ e);
            void OnMakeCall(Object^ sender, EventArgs^ e);
            void OnSortClients(Object^ sender, EventArgs^ e);

            // Обработчики для тарифов
            void OnAddTariff(Object^ sender, EventArgs^ e);
            void OnEditTariff(Object^ sender, EventArgs^ e);
            void OnDeleteTariff(Object^ sender, EventArgs^ e);
            void OnSortTariffs(Object^ sender, EventArgs^ e);

            // Обработчики для звонков
            void OnDeleteCall(Object^ sender, EventArgs^ e);
            void OnViewClientCalls(Object^ sender, EventArgs^ e);

            // Обработчики для файлов
            void OnSaveToFile(Object^ sender, EventArgs^ e);
            void OnLoadFromFile(Object^ sender, EventArgs^ e);
            void OnClearAll(Object^ sender, EventArgs^ e);
            void OnRefresh(Object^ sender, EventArgs^ e);

            // Вспомогательные методы для звонка
            void OnDurationKeyPress(Object^ sender, KeyPressEventArgs^ e);
            bool ValidateCallDuration(String^ durationText, [System::Runtime::InteropServices::Out] int% duration);
            void OnCallFormDataChanged(Object^ sender, EventArgs^ e);
            void UpdateCallCost(ComboBox^ cmbTariff, TextBox^ txtDuration, Label^ lblCost, List<Models::Tariff^>^ tariffs);
        };
    }
}
