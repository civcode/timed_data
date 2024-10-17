#include <iostream>
#include <thread>
#include <vector>     // Including STL containers
#include <map>
#include <list>

#include "timed_data.hpp"

int main()
{
  TimedData<int> timed_int(std::chrono::milliseconds(100));
  TimedData<std::vector<int>> timed_vector(std::chrono::milliseconds(100));
  TimedData<std::map<std::string, int>> timed_map(std::chrono::milliseconds(100));

  // Write data for int
  timed_int.get_data() = 43;
  std::cout << "Is alive after int write: " << timed_int.alive() << "\n";

  // Access the vector and add elements using push_back
  timed_vector.get_data().push_back(1);
  timed_vector.get_data().push_back(2);
  timed_vector.get_data().push_back(3);
  std::cout << "Is alive after vec push_back: " << timed_vector.alive() << "\n";

  // Access the map and insert elements using insert
  timed_map.get_data().insert({"apple", 1});
  timed_map.get_data().insert({"banana", 2});
  timed_map.get_data().insert({"cherry", 3});
  std::cout << "Is alive after map insert: " << timed_map.alive() << "\n";

  // Read and display int data
  auto int_data = timed_int.read();
  if (int_data) {
    std::cout << "Read int data: " << *int_data << "\n";
  }

  // Read and display vector data
  auto vector_data = timed_vector.read();
  if (vector_data) {
    std::cout << "Read vec data: ";
    for (int v : *vector_data) {
      std::cout << v << " ";
    }
    std::cout << "\n";
  }

  // Read and display map data
  auto map_data = timed_map.read();
  if (map_data) {
    std::cout << "Read map data: ";
    for (const auto & [key, value] : *map_data) {
      std::cout << "{" << key << ": " << value << "} ";
    }
    std::cout << "\n";
  }

  // Simulate waiting longer than expiration (for testing purpose)
  std::this_thread::sleep_for(std::chrono::milliseconds(90));

  std::cout << "Is int alive after 90 ms: " << timed_int.alive() << "\n";
  std::cout << "Is vec alive after 90 ms: " << timed_vector.alive() << "\n";
  std::cout << "Is map alive after 90 ms: " << timed_map.alive() << "\n";

  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  std::cout << "Is int alive after more than 100 ms: " << timed_int.alive() << "\n";
  std::cout << "Is vec alive after more than 100 ms: " << timed_vector.alive() << "\n";
  std::cout << "Is map alive after more than 100 ms: " << timed_map.alive() << "\n";

  return 0;
}
