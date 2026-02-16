#include "DataManager.h"

using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Globalization;

namespace ATSProject {
    namespace Data {

        DataManager::DataManager() {
            clients = gcnew System::Collections::Generic::List<Models::Client^>();
            tariffs = gcnew System::Collections::Generic::List<Models::Tariff^>();
            calls = gcnew System::Collections::Generic::List<Models::Call^>();
            nextClientId = 1;
            nextTariffId = 1;
            nextCallId = 1;
        }

        DataManager^ DataManager::GetInstance() {
            if (instance == nullptr) {
                instance = gcnew DataManager();
            }
            return instance;
        }

        void DataManager::AddClient(Models::Client^ client) {
            client->Id = nextClientId++;
            clients->Add(client);
        }

        void DataManager::UpdateClient(Models::Client^ client) {
            for (int i = 0; i < clients->Count; i++) {
                if (clients[i]->Id == client->Id) {
                    clients[i] = client;
                    return;
                }
            }
        }

        void DataManager::DeleteClient(int clientId) {
            for (int i = calls->Count - 1; i >= 0; i--) {
                if (calls[i]->ClientId == clientId) {
                    calls->RemoveAt(i);
                }
            }
            for (int i = 0; i < clients->Count; i++) {
                if (clients[i]->Id == clientId) {
                    clients->RemoveAt(i);
                    return;
                }
            }
        }

        Models::Client^ DataManager::FindClient(int clientId) {
            for (int i = 0; i < clients->Count; i++) {
                if (clients[i]->Id == clientId) {
                    return clients[i];
                }
            }
            return nullptr;
        }

        System::Collections::Generic::List<Models::Client^>^ DataManager::GetAllClients() {
            return clients;
        }

        void DataManager::SortClientsByName() {
            // Простая сортировка пузырьком
            for (int i = 0; i < clients->Count - 1; i++) {
                for (int j = 0; j < clients->Count - i - 1; j++) {
                    if (String::Compare(clients[j]->LastName, clients[j + 1]->LastName) > 0) {
                        Models::Client^ temp = clients[j];
                        clients[j] = clients[j + 1];
                        clients[j + 1] = temp;
                    }
                }
            }
        }

        void DataManager::AddTariff(Models::Tariff^ tariff) {
            tariff->Id = nextTariffId++;
            tariffs->Add(tariff);
        }

        void DataManager::UpdateTariff(Models::Tariff^ tariff) {
            for (int i = 0; i < tariffs->Count; i++) {
                if (tariffs[i]->Id == tariff->Id) {
                    tariffs[i] = tariff;
                    return;
                }
            }
        }

        void DataManager::DeleteTariff(int tariffId) {
            for (int i = calls->Count - 1; i >= 0; i--) {
                if (calls[i]->TariffId == tariffId) {
                    calls->RemoveAt(i);
                }
            }
            for (int i = 0; i < tariffs->Count; i++) {
                if (tariffs[i]->Id == tariffId) {
                    tariffs->RemoveAt(i);
                    return;
                }
            }
        }

        Models::Tariff^ DataManager::FindTariff(int tariffId) {
            for (int i = 0; i < tariffs->Count; i++) {
                if (tariffs[i]->Id == tariffId) {
                    return tariffs[i];
                }
            }
            return nullptr;
        }

        System::Collections::Generic::List<Models::Tariff^>^ DataManager::GetAllTariffs() {
            return tariffs;
        }

        void DataManager::SortTariffsByCity() {
            // Простая сортировка пузырьком
            for (int i = 0; i < tariffs->Count - 1; i++) {
                for (int j = 0; j < tariffs->Count - i - 1; j++) {
                    if (String::Compare(tariffs[j]->City, tariffs[j + 1]->City) > 0) {
                        Models::Tariff^ temp = tariffs[j];
                        tariffs[j] = tariffs[j + 1];
                        tariffs[j + 1] = temp;
                    }
                }
            }
        }

        void DataManager::AddCall(Models::Call^ call) {
            call->Id = nextCallId++;
            calls->Add(call);
        }

        void DataManager::DeleteCall(int callId) {
            for (int i = 0; i < calls->Count; i++) {
                if (calls[i]->Id == callId) {
                    calls->RemoveAt(i);
                    return;
                }
            }
        }

        System::Collections::Generic::List<Models::Call^>^ DataManager::GetAllCalls() {
            return calls;
        }

        System::Collections::Generic::List<Models::Call^>^ DataManager::GetCallsByClient(int clientId) {
            System::Collections::Generic::List<Models::Call^>^ result =
                gcnew System::Collections::Generic::List<Models::Call^>();
            for (int i = 0; i < calls->Count; i++) {
                if (calls[i]->ClientId == clientId) {
                    result->Add(calls[i]);
                }
            }
            return result;
        }

        void DataManager::SaveToFile(String^ filename) {
            try {
                StreamWriter^ writer = gcnew StreamWriter(filename, false, System::Text::Encoding::UTF8);

                writer->WriteLine("[CLIENTS]");
                for (int i = 0; i < clients->Count; i++) {
                    writer->WriteLine(clients[i]->ToString());
                }

                writer->WriteLine("[TARIFFS]");
                for (int i = 0; i < tariffs->Count; i++) {
                    writer->WriteLine(tariffs[i]->ToString());
                }

                writer->WriteLine("[CALLS]");
                for (int i = 0; i < calls->Count; i++) {
                    writer->WriteLine(calls[i]->ToString());
                }

                writer->Close();
            }
            catch (Exception^ ex) {
                throw gcnew Exception("Save error: " + ex->Message);
            }
        }

        void DataManager::LoadFromFile(String^ filename) {
            try {
                if (!File::Exists(filename)) {
                    throw gcnew Exception("File not found!");
                }

                StreamReader^ reader = gcnew StreamReader(filename, System::Text::Encoding::UTF8);
                ClearAllData();

                String^ section = "";
                String^ line;

                while ((line = reader->ReadLine()) != nullptr) {
                    if (line->StartsWith("[") && line->EndsWith("]")) {
                        section = line;
                        continue;
                    }

                    if (String::IsNullOrWhiteSpace(line)) continue;

                    array<String^>^ parts = line->Split(';');

                    if (section == "[CLIENTS]" && parts->Length >= 4) {
                        Models::Client^ client = gcnew Models::Client();
                        client->Id = Int32::Parse(parts[0]);
                        client->LastName = parts[1];
                        client->FirstName = parts[2];
                        client->PhoneNumber = parts[3];
                        clients->Add(client);
                        if (client->Id >= nextClientId) nextClientId = client->Id + 1;
                    }
                    else if (section == "[TARIFFS]" && parts->Length >= 4) {
                        Models::Tariff^ tariff = gcnew Models::Tariff();
                        tariff->Id = Int32::Parse(parts[0]);
                        tariff->City = parts[1];
                        tariff->BaseCostPerMinute = Double::Parse(parts[2], CultureInfo::InvariantCulture);
                        tariff->StrategyType = parts[3];
                        if (parts->Length >= 5 && !String::IsNullOrWhiteSpace(parts[4])) {
                            tariff->DiscountRate = Double::Parse(parts[4], CultureInfo::InvariantCulture);
                        }
                        tariffs->Add(tariff);
                        if (tariff->Id >= nextTariffId) nextTariffId = tariff->Id + 1;
                    }
                    else if (section == "[CALLS]" && parts->Length >= 6) {
                        Models::Call^ call = gcnew Models::Call();
                        call->Id = Int32::Parse(parts[0]);
                        call->ClientId = Int32::Parse(parts[1]);
                        call->TariffId = Int32::Parse(parts[2]);
                        call->City = parts[3];
                        call->Duration = Int32::Parse(parts[4]);
                        call->Cost = Double::Parse(parts[5], CultureInfo::InvariantCulture);
                        calls->Add(call);
                        if (call->Id >= nextCallId) nextCallId = call->Id + 1;
                    }
                }
                reader->Close();
            }
            catch (Exception^ ex) {
                throw gcnew Exception("Load error: " + ex->Message);
            }
        }

        void DataManager::ClearAllData() {
            clients->Clear();
            tariffs->Clear();
            calls->Clear();
            nextClientId = 1;
            nextTariffId = 1;
            nextCallId = 1;
        }

        int DataManager::GetTotalClients() {
            return clients->Count;
        }

        int DataManager::GetTotalTariffs() {
            return tariffs->Count;
        }

        int DataManager::GetTotalCalls() {
            return calls->Count;
        }
    }
}
