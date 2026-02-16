#pragma once
#include "Client.h"
#include "Tariff.h"
#include "Call.h"

using namespace System;
using namespace System::Collections::Generic;

namespace ATSProject {
    namespace Data {
        // Класс для управления данными (вместо DatabaseManager)
        public ref class DataManager {
        private:
            List<Models::Client^>^ clients;
            List<Models::Tariff^>^ tariffs;
            List<Models::Call^>^ calls;

            int nextClientId;
            int nextTariffId;
            int nextCallId;

            static DataManager^ instance;

            DataManager();

        public:
            static DataManager^ GetInstance();

            // Методы для клиентов
            void AddClient(Models::Client^ client);
            void UpdateClient(Models::Client^ client);
            void DeleteClient(int clientId);
            Models::Client^ FindClient(int clientId);
            List<Models::Client^>^ GetAllClients();
            void SortClientsByName();

            // Методы для тарифов
            void AddTariff(Models::Tariff^ tariff);
            void UpdateTariff(Models::Tariff^ tariff);
            void DeleteTariff(int tariffId);
            Models::Tariff^ FindTariff(int tariffId);
            List<Models::Tariff^>^ GetAllTariffs();
            void SortTariffsByCity();

            // Методы для звонков
            void AddCall(Models::Call^ call);
            void DeleteCall(int callId);
            List<Models::Call^>^ GetAllCalls();
            List<Models::Call^>^ GetCallsByClient(int clientId);

            // Методы для работы с файлами
            void SaveToFile(String^ filename);
            void LoadFromFile(String^ filename);
            void ClearAllData();

            // Статистика
            int GetTotalClients();
            int GetTotalTariffs();
            int GetTotalCalls();
        };
    }
}
