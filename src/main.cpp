#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <chrono>

const int WINDOW_WIDTH = 300;
const int WINDOW_HEIGHT = 300;
const int ARRAY_SIZE = 100;
const int BAR_WIDTH = WINDOW_WIDTH / ARRAY_SIZE;
const int DELAY = 40;

void drawBars(sf::RenderWindow& window, const std::vector<int>& arr) {
    window.clear();

    for (int i = 0; i < ARRAY_SIZE; i++) {
        sf::RectangleShape bar(sf::Vector2f(BAR_WIDTH, arr[i]));
        bar.setPosition(i * BAR_WIDTH, WINDOW_HEIGHT - arr[i]);
        bar.setFillColor(sf::Color::Blue);
        window.draw(bar);
    }

    window.display();
}

void bubbleSort(std::vector<int>& arr, sf::RenderWindow& window) {
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        drawBars(window, arr);
        sf::sleep(sf::milliseconds(DELAY));

        // If no two elements were swapped, the array is already sorted
        if (!swapped) {
            break;
        }
    }
}

int main() {
    std::vector<int> arr(ARRAY_SIZE);

    // Generate a random unsorted array
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(50, WINDOW_HEIGHT - 50);

    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = distribution(generator);
    }

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bubble Sort Visualization");

    bubbleSort(arr, window);

    // Keep the window open until it's closed
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    return 0;
}
