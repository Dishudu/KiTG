#include <iostream>
#include <vector>
#include <stdexcept>

// Класс для реализации максимальной кучи
class Heap {
private:
    std::vector<int> data; // Хранилище элементов кучи

    // Просеивание вверх для восстановления свойства кучи
    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (data[parent] >= data[index]) break;
            std::swap(data[parent], data[index]);
            index = parent;
        }
    }

    // Просеивание вниз для восстановления свойства кучи
    void siftDown(int index) {
        int size = data.size();
        while (2 * index + 1 < size) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int largest = index;

            if (data[leftChild] > data[largest])
                largest = leftChild;
            if (rightChild < size && data[rightChild] > data[largest])
                largest = rightChild;

            if (largest == index) break;

            std::swap(data[index], data[largest]);
            index = largest;
        }
    }

public:
    // Конструктор по умолчанию
    Heap() {}

    // Добавление элемента в кучу
    void insert(int value) {
        data.push_back(value);
        siftUp(data.size() - 1);
    }

    // Извлечение максимального элемента из кучи
    int extractMax() {
        if (data.empty())
            throw std::runtime_error("Heap is empty!");

        int max = data[0];
        data[0] = data.back();
        data.pop_back();
        siftDown(0);
        return max;
    }

    // Построение кучи из массива
    void buildHeap(const std::vector<int>& input) {
        data = input;
        for (int i = data.size() / 2 - 1; i >= 0; --i)
            siftDown(i);
    }

    // Печать текущего состояния кучи
    void printHeap() const {
        for (int val : data)
            std::cout << val << " ";
        std::cout << std::endl;
    }
};

// Точка входа в программу
int main() {
    Heap heap;

    // Тест добавления элементов
    std::cout << "Inserting elements into the heap:\n";
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(30);
    heap.insert(15);

    std::cout << "Heap after inserts: ";
    heap.printHeap();

    // Тест извлечения максимального элемента
    std::cout << "\nExtracting max:\n";
    std::cout << "Max: " << heap.extractMax() << std::endl;

    std::cout << "Heap after extraction: ";
    heap.printHeap();

    // Тест построения кучи из массива
    std::cout << "\nBuilding heap from array:\n";
    std::vector<int> inputArray = {3, 1, 6, 5, 2, 4};
    heap.buildHeap(inputArray);

    std::cout << "Heap after buildHeap: ";
    heap.printHeap();

    return 0;
}
