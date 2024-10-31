// main.cpp
#include "VehicleAVLTree.h"
#include "VehicleAVLTree.cpp"
#include <iostream>
using namespace std;

// int main() {
//     VehicleNode* root = nullptr;

//     // Registering vehicles
//     root = registerVehicle(root, 1, "Toyota", "Camry", 2020, "ABC123", "FL123");
//     root = registerVehicle(root, 2, "Honda", "Accord", 2019, "XYZ789", "FL456");

//     // Marking a vehicle for maintenance
//     markForMaintenance(root, 1);

//     // Assigning a driver to a vehicle
//     assignDriver(root, 2, "John Doe", "2023-11-01");

//     // Generating condition report
//     cout << "\nCondition Report:" << endl;
//     generateConditionReport(root);

//     return 0;
// }

void displayMenu() {
    cout << "\n--- Fleet Management System ---\n";
    cout << "1. Register Vehicle\n";
    cout << "2. Search Vehicle\n";
    cout << "3. Update Vehicle Status\n";
    cout << "4. Delete Vehicle\n";
    cout << "5. Display All Vehicles\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    VehicleNode* root = nullptr;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        int id, year;
        string make, model, reg, fleet, status;

        switch (choice) {
            case 1: 
                cout << "Enter Vehicle ID, Make, Model, Year, Registration, Fleet Number, Status: ";
                cin >> id >> make >> model >> year >> reg >> fleet >> status;
                root = insertVehicle(root, id, make, model, year, reg, fleet, status);
                cout << "Vehicle registered successfully.\n";
                break;

            case 2:
                cout << "Enter Vehicle ID to search: ";
                cin >> id;
                if (VehicleNode* found = searchVehicle(root, id))
                    displayVehicle(found);
                else
                    cout << "Vehicle not found.\n";
                break;

            case 3:
                cout << "Enter Vehicle ID and new Status: ";
                cin >> id >> status;
                if (updateVehicleStatus(root, id, status))
                    cout << "Vehicle status updated.\n";
                else
                    cout << "Vehicle not found.\n";
                break;

            case 4:
                cout << "Enter Vehicle ID to delete: ";
                cin >> id;
                root = deleteVehicle(root, id);
                cout << "Vehicle deleted.\n";
                break;

            case 5:
                cout << "\n--- Vehicle List ---\n";
                displayVehicle(root);
                break;

            case 0:
                cout << "Exiting.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}