#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <chrono>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int ARRAY_SIZE = 100;
const int BAR_WIDTH = WINDOW_WIDTH / ARRAY_SIZE;
const int DELAY = 10;

void drawBars(sf::RenderWindow& window, const std::vector<int>& arr, int minIdx = -1, int i = -1) {
    window.clear();

    for (int j = 0; j < ARRAY_SIZE; j++) {
        sf::RectangleShape bar(sf::Vector2f(BAR_WIDTH, arr[j]));
        bar.setPosition(j * BAR_WIDTH, WINDOW_HEIGHT - arr[j]);

        if (j == minIdx) {
            bar.setFillColor(sf::Color::Red); // Highlight the minimum element
        } else if (j == i) {
            bar.setFillColor(sf::Color::Green); // Highlight the current element being compared
        } else {
            bar.setFillColor(sf::Color::Blue);
        }

        window.draw(bar);
    }

    window.display();
}

void selectionSort(std::vector<int>& arr, sf::RenderWindow& window) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }

        std::swap(arr[i], arr[minIdx]);
        drawBars(window, arr, -1, -1); // Remove highlighting after the swap
        sf::sleep(sf::milliseconds(DELAY));
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

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Selection Sort Visualization");

    selectionSort(arr, window);

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
