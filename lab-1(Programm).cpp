#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <windows.h>

using namespace std;

//1: PUBLIC
class TrainPublic {
public:
    string destination;
    string trainNumber;
    int departureHour;
    int departureMinute;
    int travelHours;
    int travelMinutes;
    int totalSeats;
    int compartmentSeats;
    int reservedSeats;
    int arrivalHour;
    int arrivalMinute;

    TrainPublic(string dest, string num, int dHour, int dMin, int tHour, int tMin,
        int total, int comp, int reserv) {
        destination = dest;
        trainNumber = num;
        departureHour = dHour;
        departureMinute = dMin;
        travelHours = tHour;
        travelMinutes = tMin;
        totalSeats = total;
        compartmentSeats = comp;
        reservedSeats = reserv;

        // Расчет времени прибытия
        arrivalHour = departureHour + travelHours;
        arrivalMinute = departureMinute + travelMinutes;
        if (arrivalMinute >= 60) {
            arrivalHour += arrivalMinute / 60;
            arrivalMinute %= 60;
        }
        if (arrivalHour >= 24) arrivalHour %= 24;
    }

    void show() {
        cout << "------------------------" << endl;
        cout << "Поезд №" << trainNumber << endl;
        cout << "Назначение: " << destination << endl;
        cout << "Отправление: " << setw(2) << setfill('0') << departureHour << ":"
            << setw(2) << setfill('0') << departureMinute;
        cout << "  Прибытие: " << setw(2) << setfill('0') << arrivalHour << ":"
            << setw(2) << setfill('0') << arrivalMinute << endl;
        cout << "Время в пути: " << travelHours << "ч " << travelMinutes << "м" << endl;
        cout << "Места: общих " << totalSeats
            << ", купейных " << compartmentSeats
            << ", плацкартных " << reservedSeats << endl;
    }
};

//2: PRIVATE (ЧЕРЕЗ SET/GET)
class TrainPrivate {
private:
    string destination;
    string trainNumber;
    int departureHour;
    int departureMinute;
    int travelHours;
    int travelMinutes;
    int totalSeats;
    int compartmentSeats;
    int reservedSeats;
    int arrivalHour;
    int arrivalMinute;

    void calcArrival() {
        arrivalHour = departureHour + travelHours;
        arrivalMinute = departureMinute + travelMinutes;
        if (arrivalMinute >= 60) {
            arrivalHour += arrivalMinute / 60;
            arrivalMinute %= 60;
        }
        if (arrivalHour >= 24) arrivalHour %= 24;
    }

public:
    TrainPrivate(string dest, string num, int dHour, int dMin, int tHour, int tMin,
        int total, int comp, int reserv) {
        setDestination(dest);
        setTrainNumber(num);
        setDepartureHour(dHour);
        setDepartureMinute(dMin);
        setTravelHours(tHour);
        setTravelMinutes(tMin);
        setTotalSeats(total);
        setCompartmentSeats(comp);
        setReservedSeats(reserv);
        calcArrival();
    }

    // SET-методы
    void setDestination(string dest) { if (!dest.empty()) destination = dest; }
    void setTrainNumber(string num) { if (!num.empty()) trainNumber = num; }
    void setDepartureHour(int hour) { if (hour >= 0 && hour <= 23) departureHour = hour; calcArrival(); }
    void setDepartureMinute(int min) { if (min >= 0 && min <= 59) departureMinute = min; calcArrival(); }
    void setTravelHours(int hours) { if (hours >= 0) travelHours = hours; calcArrival(); }
    void setTravelMinutes(int min) { if (min >= 0 && min <= 59) travelMinutes = min; calcArrival(); }
    void setTotalSeats(int seats) { if (seats >= 0) totalSeats = seats; }
    void setCompartmentSeats(int seats) { if (seats >= 0) compartmentSeats = seats; }
    void setReservedSeats(int seats) { if (seats >= 0) reservedSeats = seats; }

    // GET-методы
    string getDestination() { return destination; }
    string getTrainNumber() { return trainNumber; }
    int getDepartureHour() { return departureHour; }
    int getDepartureMinute() { return departureMinute; }
    int getTotalSeats() { return totalSeats; }

    void show() {
        cout << "------------------------" << endl;
        cout << "Поезд №" << trainNumber << endl;
        cout << "Назначение: " << destination << endl;
        cout << "Отправление: " << setw(2) << setfill('0') << departureHour << ":"
            << setw(2) << setfill('0') << departureMinute;
        cout << "  Прибытие: " << setw(2) << setfill('0') << arrivalHour << ":"
            << setw(2) << setfill('0') << arrivalMinute << endl;
        cout << "Время в пути: " << travelHours << "ч " << travelMinutes << "м" << endl;
        cout << "Места: общих " << totalSeats
            << ", купейных " << compartmentSeats
            << ", плацкартных " << reservedSeats << endl;
    }
};

//ФУНКЦИЯ ЗАГРУЗКИ ДЛЯ PUBLIC
vector<TrainPublic> loadTrainsPublic(string filename) {
    vector<TrainPublic> trains;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return trains;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string dest, num, timeStr, travelStr;
        string totalStr, compStr, reservStr;

        getline(ss, dest, ',');
        getline(ss, num, ',');
        getline(ss, timeStr, ',');
        getline(ss, travelStr, ',');
        getline(ss, totalStr, ',');
        getline(ss, compStr, ',');
        getline(ss, reservStr, ',');

        int dHour, dMin, tHour, tMin;
        char colon;

        stringstream(timeStr) >> dHour >> colon >> dMin;
        stringstream(travelStr) >> tHour >> colon >> tMin;

        trains.push_back(TrainPublic(dest, num, dHour, dMin, tHour, tMin,
            stoi(totalStr), stoi(compStr), stoi(reservStr)));
    }

    file.close();
    return trains;
}

//Функция загрузки для privat
vector<TrainPrivate> loadTrainsPrivate(string filename) {
    vector<TrainPrivate> trains;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return trains;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string dest, num, timeStr, travelStr;
        string totalStr, compStr, reservStr;

        getline(ss, dest, ',');
        getline(ss, num, ',');
        getline(ss, timeStr, ',');
        getline(ss, travelStr, ',');
        getline(ss, totalStr, ',');
        getline(ss, compStr, ',');
        getline(ss, reservStr, ',');

        int dHour, dMin, tHour, tMin;
        char colon;

        stringstream(timeStr) >> dHour >> colon >> dMin;
        stringstream(travelStr) >> tHour >> colon >> tMin;

        trains.push_back(TrainPrivate(dest, num, dHour, dMin, tHour, tMin,
            stoi(totalStr), stoi(compStr), stoi(reservStr)));
    }

    file.close();
    return trains;
}

//ГЛАВНАЯ ФУНКЦИЯ
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string filename = "C:\\Users\\Жагочка\\Documents\\Программирование\\файл\\poezda1.txt";
    string dest;
    int hour;
    cout << "Введите пункт назначения: ";
    cin >> dest;
    cout << "Введите час: ";
    cin >> hour;

    //1: PUBLIC
    cout << "\n========== 1: PUBLIC ==========\n";
    vector<TrainPublic> trainsPublic = loadTrainsPublic(filename);

    if (!trainsPublic.empty()) {
        // а) Поезда до заданного пункта
        cout << "\n=== а) Поезда до " << dest << " ===\n";
        bool found = false;
        for (auto& t : trainsPublic) {
            if (t.destination == dest) {
                t.show();
                found = true;
            }
        }
        if (!found) cout << "Поездов не найдено.\n";

        // б) Поезда после заданного часа
        cout << "\n=== б) Поезда до " << dest << " после " << hour << ":00 ===\n";
        found = false;
        for (auto& t : trainsPublic) {
            if (t.destination == dest && t.departureHour > hour) {
                t.show();
                found = true;
            }
        }
        if (!found) cout << "Поездов не найдено.\n";

        // в) Поезда с общими местами
        cout << "\n=== в) Поезда до " << dest << " с общими местами ===\n";
        found = false;
        for (auto& t : trainsPublic) {
            if (t.destination == dest && t.totalSeats > 0) {
                t.show();
                found = true;
            }
        }
        if (!found) cout << "Поездов не найдено.\n";
    }
    else {
        cout << "Нет данных для public реализации\n";
    }

    //2: PRIVATE
    cout << "\n==========2: PRIVATE (ЧЕРЕЗ SET/GET) ==========\n";
    vector<TrainPrivate> trainsPrivate = loadTrainsPrivate(filename);

    if (!trainsPrivate.empty()) {
        // а) Поезда до заданного пункта
        cout << "\n=== а) Поезда до " << dest << " ===\n";
        bool found = false;
        for (auto& t : trainsPrivate) {
            if (t.getDestination() == dest) {
                t.show();
                found = true;
            }
        }
        if (!found) cout << "Поездов не найдено.\n";

        // б) Поезда после заданного часа
        cout << "\n=== б) Поезда до " << dest << " после " << hour << ":00 ===\n";
        found = false;
        for (auto& t : trainsPrivate) {
            if (t.getDestination() == dest && t.getDepartureHour() > hour) {
                t.show();
                found = true;
            }
        }
        if (!found) cout << "Поездов не найдено.\n";

        // в) Поезда с общими местами
        cout << "\n=== в) Поезда до " << dest << " с общими местами ===\n";
        found = false;
        for (auto& t : trainsPrivate) {
            if (t.getDestination() == dest && t.getTotalSeats() > 0) {
                t.show();
                found = true;
            }
        }
        if (!found) cout << "Поездов не найдено.\n";
    }
    else {
        cout << "Нет данных для private реализации\n";
    }

    system("pause");
    return 0;
}