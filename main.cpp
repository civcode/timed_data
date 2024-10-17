#include <iostream>
#include <chrono>
#include <optional>
#include <thread>
#include <vector>     // Including STL containers
#include <map>
#include <list>

template<typename T>
class TimedData {
public:
  TimedData(std::chrono::milliseconds expirationTime)
  : hasBeenWritten(false), 
    expirationDuration(expirationTime) 
  {}

  // Write function for the underlying data type
  void write(const T & value)
  {
    data = value;
    hasBeenWritten = true;
    lastWriteTime = std::chrono::steady_clock::now();     
  }

  // Read function for the underlying data type
  std::optional<T> read()
  {
    if (hasBeenWritten) {
      hasBeenWritten = false;       
      return data;
    }
    return std::nullopt;    
  }

  // Alive function to check if the data was written within the last x milliseconds
  bool alive() const
  {
    if (!data.has_value()) {
      return false;       
    }
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastWriteTime);
    return elapsed < expirationDuration;
  }

  // Function to check if data is currently written (for external checking)
  bool isWritten() const
  {
    return hasBeenWritten;
  }

private:
  std::optional<T> data;   
  bool hasBeenWritten;     
  std::chrono::steady_clock::time_point lastWriteTime;    
  std::chrono::milliseconds expirationDuration;   

};

int main()
{
  TimedData<int> timedInt(std::chrono::milliseconds(5));
  TimedData<std::vector<int>> timedVector(std::chrono::milliseconds(5));
  TimedData<std::map<std::string, int>> timedMap(std::chrono::milliseconds(5));

    // Write data for int
  timedInt.write(42);
  std::cout << "Is alive after int write: " << timedInt.alive() << "\n";

    // Write data for vector
  timedVector.write({1, 2, 3, 4, 5});
  std::cout << "Is alive after vector write: " << timedVector.alive() << "\n";

    // Write data for map
  timedMap.write({{"apple", 1}, {"banana", 2}, {"cherry", 3}});
  std::cout << "Is alive after map write: " << timedMap.alive() << "\n";

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
  std::this_thread::sleep_for(std::chrono::milliseconds(4));

  std::cout << "Is int alive after 6 milliseconds: " << timedInt.alive() << "\n";
  std::cout << "Is vector alive after 6 milliseconds: " << timedVector.alive() << "\n";
  std::cout << "Is map alive after 6 milliseconds: " << timedMap.alive() << "\n";

  return 0;
}
