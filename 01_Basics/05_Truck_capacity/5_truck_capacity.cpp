#include <iostream>
using namespace std;

int main( ) {
    float max_load_capacity;
    int num_boxes;
    float avg_box_weight;
    int boxes;

    cout << "Enter the truck's maximum load capacity (in metric tons):";
    cin >> max_load_capacity;
    cout << "Enter the number of boxes the truck is carrying:";
    cin >> num_boxes;
    cout << "Enter the average weight of a box (in kilos):";
    cin >> avg_box_weight;

    avg_box_weight /= 1000.0;
    float total_weight = static_cast<float>(num_boxes) * avg_box_weight;

    if (max_load_capacity >= total_weight) {
        boxes = static_cast<int>((max_load_capacity-total_weight) / (avg_box_weight));
        cout << "The truck can legally carry all boxes.\n"
             << "Additional boxes that can be added: " << boxes << endl;
    }
    else {
        float excess = (total_weight - max_load_capacity)/avg_box_weight;
        boxes = static_cast<int>(excess);
        if (excess > static_cast<float>(boxes))     // comparison needs to be done in float
            boxes += 1;

        cout << "The truck is overloaded.\n"
             << "Boxes that must be removed: " << boxes << endl;
    }

    return 0;
}
