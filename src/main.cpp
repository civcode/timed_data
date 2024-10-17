#include <iostream>
#include <thread>
#include <vector>     // Including STL containers
#include <map>
#include <list>

#include "timed_data.hpp"

int main()
{
  TimedData<int> timedInt(std::chrono::milliseconds(100));
  TimedData<std::vector<int>> timedVector(std::chrono::milliseconds(100));
  TimedData<std::map<std::string, int>> timedMap(std::chrono::milliseconds(100));

  // Write data for int
  timedInt.get_data() = 43;
  std::cout << "Is alive after int write: " << timedInt.alive() << "\n";

  // Access the vector and add elements using push_back
  timedVector.get_data().push_back(1);
  timedVector.get_data().push_back(2);
  timedVector.get_data().push_back(3);
  std::cout << "Is alive after vector push_back: " << timedVector.alive() << "\n";

  // Access the map and insert elements using insert
  timedMap.get_data().insert({"apple", 1});
  timedMap.get_data().insert({"banana", 2});
  timedMap.get_data().insert({"cherry", 3});
  std::cout << "Is alive after map insert: " << timedMap.alive() << "\n";

  // Read and display int data
  auto intData = timedInt.read();
  if (intData) {
    std::cout << "Read int data: " << *intData << "\n";
  }

  // Read and display vector data
  auto vectorData = timedVector.read();
  if (vectorData) {
    std::cout << "Read vector data: ";
    for (int v : *vectorData) {
      std::cout << v << " ";
    }
    std::cout << "\n";
  }

  // Read and display map data
  auto mapData = timedMap.read();
  if (mapData) {
    std::cout << "Read map data: ";
    for (const auto & [key, value] : *mapData) {
      std::cout << "{" << key << ": " << value << "} ";
    }
    std::cout << "\n";
  }

  // Simulate waiting longer than expiration (for testing purpose)
  std::this_thread::sleep_for(std::chrono::milliseconds(90));

  std::cout << "Is int alive after 90 milliseconds: " << timedInt.alive() << "\n";
  std::cout << "Is vector alive after 90 milliseconds: " << timedVector.alive() << "\n";
  std::cout << "Is map alive after 90 milliseconds: " << timedMap.alive() << "\n";

  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  std::cout << "Is int alive after more than 100 milliseconds: " << timedInt.alive() << "\n";
  std::cout << "Is vector alive after more than 100 milliseconds: " << timedVector.alive() << "\n";
  std::cout << "Is map alive after more than 100 milliseconds: " << timedMap.alive() << "\n";

  return 0;
}
