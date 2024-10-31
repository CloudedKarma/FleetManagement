// VehicleAVLTree.cpp
#include "VehicleAVLTree.h"
#include <iostream>

VehicleNode::VehicleNode(int id, string mk, string mdl, int yr, string reg, string fleet, string stat)
    : vehicle_id(id), make(mk), model(mdl), year(yr), registration_number(reg),
      fleet_number(fleet), status(stat), left(nullptr), right(nullptr), height(1) {}

int height(VehicleNode* node) {
    return node ? node->height : 0;
}

int getBalanceFactor(VehicleNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

VehicleNode* rotateRight(VehicleNode* y) {
    VehicleNode* x = y->left;
    VehicleNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

VehicleNode* rotateLeft(VehicleNode* x) {
    VehicleNode* y = x->right;
    VehicleNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// This adds a new vechical to the fleet
VehicleNode* insertVehicle(VehicleNode* node, int id, string make, string model, int year, 
                           string reg, string fleet, string status) {
    if (!node) return new VehicleNode(id, make, model, year, reg, fleet, status);

    if (id < node->vehicle_id)
        node->left = insertVehicle(node->left, id, make, model, year, reg, fleet, status);
    else if (id > node->vehicle_id)
        node->right = insertVehicle(node->right, id, make, model, year, reg, fleet, status);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalanceFactor(node);

    if (balance > 1 && id < node->left->vehicle_id)
        return rotateRight(node);

    if (balance < -1 && id > node->right->vehicle_id)
        return rotateLeft(node);

    if (balance > 1 && id > node->left->vehicle_id) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && id < node->right->vehicle_id) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// This registers a new vechical to the fleet
VehicleNode* registerVehicle(VehicleNode* root, int id, string make, string model, int year, 
                             string reg, string fleet, string status) {
    return insertVehicle(root, id, make, model, year, reg, fleet, status);
}

// This checks the availability of the vehical
void checkAvailability(VehicleNode* node) {
    if (!node) return;

    checkAvailability(node->left);

    if (node->status == "available") {
        cout << "Vehicle ID: " << node->vehicle_id << ", Make: " << node->make 
             << ", Model: " << node->model << ", Year: " << node->year 
             << ", Fleet Number: " << node->fleet_number << endl;
    }

    checkAvailability(node->right);
}

// This function finds the vehical that are marked for maintence
void markForMaintenance(VehicleNode* node, int vehicle_id) {
    if (!node) return;

    if (vehicle_id < node->vehicle_id) {
        markForMaintenance(node->left, vehicle_id);
    } else if (vehicle_id > node->vehicle_id) {
        markForMaintenance(node->right, vehicle_id);
    } else {
        node->status = "maintenance";
        cout << "Vehicle ID " << vehicle_id << " marked for maintenance." << endl;
    }
}

// This is the function to assign a driver to a vehical
void assignDriver(VehicleNode* node, int vehicle_id, const string& driver, const string& rental_date) {
    if (!node) return;

    if (vehicle_id < node->vehicle_id) {
        assignDriver(node->left, vehicle_id, driver, rental_date);
    } else if (vehicle_id > node->vehicle_id) {
        assignDriver(node->right, vehicle_id, driver, rental_date);
    } else {
        if (node->status == "available") {
            node->status = "rented";
            node->assigned_driver = driver;
            node->rental_date = rental_date;
            cout << "Vehicle ID " << vehicle_id << " assigned to driver " << driver << " for rental on " << rental_date << "." << endl;
        } else {
            cout << "Vehicle ID " << vehicle_id << " is currently unavailable." << endl;
        }
    }
}

// This is function to return the Condition of the vehical
void generateConditionReport(VehicleNode* node) {
    if (!node) return;

    generateConditionReport(node->left);

    cout << "Vehicle ID: " << node->vehicle_id << ", Make: " << node->make 
         << ", Model: " << node->model << ", Year: " << node->year 
         << ", Status: " << node->status;

    if (node->status == "rented") {
        cout << ", Driver: " << node->assigned_driver 
             << ", Rental Date: " << node->rental_date;
    }
    cout << endl;

    generateConditionReport(node->right);
}

// This is the search Function
VehicleNode* searchVehicle(VehicleNode* node, int vehicle_id) {
    if (!node || node->vehicle_id == vehicle_id)
        return node;
    if (vehicle_id < node->vehicle_id)
        return searchVehicle(node->left, vehicle_id);
    return searchVehicle(node->right, vehicle_id);
}

// The update Function
bool updateVehicleStatus(VehicleNode* node, int vehicle_id, const string& new_status) {
    VehicleNode* target = searchVehicle(node, vehicle_id);
    if (target) {
        target->status = new_status;
        return true;
    }
    return false;
}

// The delete function
VehicleNode* deleteVehicle(VehicleNode* root, int vehicle_id) {
    if (!root) return root;

    if (vehicle_id < root->vehicle_id)
        root->left = deleteVehicle(root->left, vehicle_id);
    else if (vehicle_id > root->vehicle_id)
        root->right = deleteVehicle(root->right, vehicle_id);
    else {
        if (!root->left || !root->right) {
            VehicleNode* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        } else {
            VehicleNode* temp = root->right;
            while (temp && temp->left) temp = temp->left;
            root->vehicle_id = temp->vehicle_id;
            root->make = temp->make;
            root->model = temp->model;
            root->year = temp->year;
            root->registration_number = temp->registration_number;
            root->fleet_number = temp->fleet_number;
            root->status = temp->status;
            root->right = deleteVehicle(root->right, temp->vehicle_id);
        }
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalanceFactor(root);

    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rotateRight(root);
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return rotateLeft(root);
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// This funcrion find the vehicals and display them
void displayVehicle(VehicleNode* node) {
    if (node) {
        cout << "Vehicle ID: " << node->vehicle_id << endl;
        cout << "Make: " << node->make << endl;
        cout << "Model: " << node->model << endl;
        cout << "Year: " << node->year << endl;
        cout << "Registration Number: " << node->registration_number << endl;
        cout << "Fleet Number: " << node->fleet_number << endl;
        cout << "Status: " << node->status << endl;
        cout << "-------------------------" << endl;
    }
}