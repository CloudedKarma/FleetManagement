#ifndef VEHICLE_AVL_TREE_H
#define VEHICLE_AVL_TREE_H

#include <string>
using namespace std;

// AVL Tree Node representing a vehicle
struct VehicleNode {
    int vehicle_id;
    string make;
    string model;
    int year;
    string registration_number;
    string fleet_number;
    string status; // "available", "rented", or "maintenance"
    string assigned_driver;
    string rental_date;

    VehicleNode* left;
    VehicleNode* right;
    int height;

    VehicleNode(int id, string mk, string mdl, int yr, string reg, string fleet, string stat);
};

// AVL Tree functions
int height(VehicleNode* node);
int getBalanceFactor(VehicleNode* node);
VehicleNode* rotateRight(VehicleNode* y);
VehicleNode* rotateLeft(VehicleNode* x);
VehicleNode* insertVehicle(VehicleNode* node, int id, string make, string model, int year, 
                           string reg, string fleet, string status);
VehicleNode* registerVehicle(VehicleNode* root, int id, string make, string model, int year, 
                             string reg, string fleet, string status = "available");
void checkAvailability(VehicleNode* node);

// Additional features
void markForMaintenance(VehicleNode* node, int vehicle_id);
void assignDriver(VehicleNode* node, int vehicle_id, const string& driver, const string& rental_date);
void generateConditionReport(VehicleNode* node);

// Crud Functions
VehicleNode* searchVehicle(VehicleNode* node, int vehicle_id);
bool updateVehicleStatus(VehicleNode* node, int vehicle_id, const string& new_status);
VehicleNode* deleteVehicle(VehicleNode* root, int vehicle_id);
void displayVehicle(VehicleNode* node);
#endif // VEHICLE_AVL_TREE_H
