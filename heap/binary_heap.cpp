#include <iostream>
#include <vector>
#include <chrono> // Для замера времени
#include <algorithm> // Для генерации случайных чисел
#include <random> // Генератор случайных чисел

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

int main() {
    Heap heap;
    std::vector<int> testSizes = {100000, 1000000, 5000000, 10000000}; // Количество элементов для тестов
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 1000000);

    for (int size : testSizes) {
        std::vector<int> inputArray(size);

        // Генерация случайных чисел
        std::generate(inputArray.begin(), inputArray.end(), [&]() { return dist(gen); });

        // Тест: Построение кучи из массива
        std::cout << "\nTest buildHeap with " << size << " elements:\n";
        auto start = std::chrono::high_resolution_clock::now();
        heap.buildHeap(inputArray);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Time taken: " << std::chrono::duration<double>(end - start).count() << " seconds\n";

        // Тест: Вставка всех элементов по одному
        std::cout << "Test insert with " << size << " elements:\n";
        Heap heapForInsert;
        start = std::chrono::high_resolution_clock::now();
        for (int value : inputArray) {
            heapForInsert.insert(value);
        }
        end = std::chrono::high_resolution_clock::now();
        std::cout << "Time taken: " << std::chrono::duration<double>(end - start).count() << " seconds\n";

        // Тест: Извлечение всех элементов
        std::cout << "Test extractMax with " << size << " elements:\n";
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < size; ++i) {
            heap.extractMax();
        }
        end = std::chrono::high_resolution_clock::now();
        std::cout << "Time taken: " << std::chrono::duration<double>(end - start).count() << " seconds\n";
    }

    return 0;
}