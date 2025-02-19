#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class Item {
public:
    int value;
    Item(int v) : value(v) {}
};

// Comparator function for sorting
bool compare(const std::shared_ptr<Item>& a, const std::shared_ptr<Item>& b) {
    return a->value < b->value; // Sort in ascending order
}

int main() {
    // Create a vector of smart pointers to Item
    std::vector<std::shared_ptr<Item>> items;
    items.push_back(std::make_shared<Item>(5));
    items.push_back(std::make_shared<Item>(2));
    items.push_back(std::make_shared<Item>(8));
    items.push_back(std::make_shared<Item>(1));

    // Sort the vector using std::sort and the custom comparator
    std::sort(items.begin(), items.end(), compare);

    // Output the sorted values
    std::cout << "Sorted values: ";
    for (const auto& item : items) {
        std::cout << item->value << " ";
    }
    std::cout << std::endl;

    return 0;
}
