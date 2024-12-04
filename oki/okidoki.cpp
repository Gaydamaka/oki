#include <iostream>  
#include <cstring>  
#include <typeinfo>  
using namespace std;
class Device {
protected:
    char manufacturer[50];
    char model[50];
    char name[50];
    int capacity; // � ��  
    int quantity;

public:
    Device(const char* man, const char* mod, const char* nam, int cap, int qty) {
        strncpy(manufacturer, man, 50);
        strncpy(model, mod, 50);
        strncpy(name, nam, 50);
        capacity = cap;
        quantity = qty;
    }

    virtual ~Device() {}

    virtual void print() const = 0;
    virtual void load() const { cout << "������ ���������\n"; }
    virtual void save() const { cout << "������ ���������\n"; }

    void setManufacturer(const char* man) { strncpy(manufacturer, man, 50); }
    void setModel(const char* mod) { strncpy(model, mod, 50); }
    void setName(const char* nam) { strncpy(name, nam, 50); }
    void setCapacity(int cap) { capacity = cap; }
    void setQuantity(int qty) { quantity = qty; }

    const char* getManufacturer() const { return manufacturer; }
    const char* getModel() const { return model; }
    const char* getName() const { return name; }
    int getCapacity() const { return capacity; }
    int getQuantity() const { return quantity; }
};

class PortableHardDrive : public Device {
public:
    PortableHardDrive(const char* man, const char* mod, const char* nam, int cap, int qty)
        : Device(man, mod, nam, cap, qty) {}

    void print() const  {
        cout << "����������� ������� ����: " << name
            << ", �������������: " << manufacturer
            << ", ������: " << model
            << ", �������: " << capacity
            << " ��, ����������: " << quantity << "\n";
    }
};

class Smartphone : public Device {
public:
    Smartphone(const char* man, const char* mod, const char* nam, int cap, int qty)
        : Device(man, mod, nam, cap, qty) {}

    void print() const  {
        cout << "��������: " << name
            << ", �������������: " << manufacturer
            << ", ������: " << model
            << ", �������: " << capacity
            << " ��, ����������: " << quantity << "\n";
    }
};

class Tablet : public Device {
public:
    Tablet(const char* man, const char* mod, const char* nam, int cap, int qty)
        : Device(man, mod, nam, cap, qty) {}

    void print() const  {
        cout << "�������: " << name
            << ", �������������: " << manufacturer
            << ", ������: " << model
            << ", �������: " << capacity
            << " ��, ����������: " << quantity << "\n";
    }
};

class Storage {
private:
    Device** devices;
    int count;
    int capacity;

public:
    Storage(int cap = 10) : count(0), capacity(cap) {
        devices = new Device * [capacity];
    }

    ~Storage() {
        for (int i = 0; i < count; ++i) {
            delete devices[i];
        }
        delete[] devices;
    }

    void addDevice(Device* device) {
        if (count >= capacity) {
            capacity *= 2;
            Device** newDevices = new Device * [capacity];
            for (int i = 0; i < count; ++i) {
                newDevices[i] = devices[i];
            }
            delete[] devices;
            devices = newDevices;
        }
        devices[count++] = device;
    }

    void removeDevice(int index) {
        if (index < 0 || index >= count) {
            cout << "�����c �� ��������� ���������.\n";
            return;
        }
        delete devices[index];
        for (int i = index; i < count - 1; ++i) {
            devices[i] = devices[i + 1];
        }
        --count;
    }

    void printDevices() const {
        for (int i = 0; i < count; ++i) {
            devices[i]->print();
        }
    }

    void saveDevices() const {
        for (int i = 0; i < count; ++i) {
            devices[i]->save();
        }
    }

    void loadDevices() const {
        for (int i = 0; i < count; ++i) {
            devices[i]->load();
        }
    }

    Device* findDevice(const char* name) const {
        for (int i = 0; i < count; ++i) {
            if (strcmp(devices[i]->getName(), name) == 0) {
                return devices[i];
            }
        }
        return nullptr;
    }

    void modifyDevice(int index, const char* man, const char* mod, const char* nam, int cap, int qty) {
        if (index < 0 || index >= count) {
            cout << "�����c �� ��������� ���������.\n";
            return;
        }
        devices[index]->setManufacturer(man);
        devices[index]->setModel(mod);
        devices[index]->setName(nam);
        devices[index]->setCapacity(cap);
        devices[index]->setQuantity(qty);
    }

    void identifyDevices() const {
        for (int i = 0; i < count; ++i) {
            cout << "��� ����������: " << typeid(*devices[i]).name() << "\n";
        }
    }
};

int main() {
    Storage storage;

    storage.addDevice(new PortableHardDrive("Seagate", "Expansion", "HDD", 500, 10));
    storage.addDevice(new Smartphone("Apple", "iPhone 13", "iPhone", 128, 5));
    storage.addDevice(new Tablet("Samsung", "Galaxy Tab", "Tablet", 256, 8));

    cout << "������ ���������:\n";
    storage.printDevices();

    cout << "���������� ���������:\n";
    storage.saveDevices();

    cout << "�������� ���������:\n";
    storage.loadDevices();

    cout << "��������� ������ ����������:\n";
    storage.modifyDevice(1, "Apple", "iPhone 14", "iPhone Pro", 256, 3);
    storage.printDevices();

    cout << "�������� ����������:\n";
    storage.removeDevice(0);
    storage.printDevices();
 
    const char* searchName = "iPhone Pro";
    Device* foundDevice = storage.findDevice(searchName);
    if (foundDevice) {
        cout << "������� ����������: ";
        foundDevice->print();
    }
    else {
        cout << "���������� � ������ " << searchName << " �� �������.\n";
    }
 
    cout << "������������� ���������:\n";
    storage.identifyDevices();

    return 0;
}