#ifndef TIMED_DATA_HPP
#define TIMED_DATA_HPP

#include <chrono>
#include <optional>

template<typename T>
class TimedData {
public:
  TimedData(std::chrono::milliseconds expirationTime)
  : hasBeenWritten(false), 
    expirationDuration(expirationTime) 
  {}

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

  // Access the underlying data directly (for containers)
  T& get_data() {
    if (!data.has_value()) {
      data = T();  // Initialize the data if it hasn't been written
    }
    hasBeenWritten = true;
    lastWriteTime = std::chrono::steady_clock::now();  // Update last write time
    return *data;
  }

private:
  std::optional<T> data;   
  bool hasBeenWritten;     
  std::chrono::steady_clock::time_point lastWriteTime;    
  std::chrono::milliseconds expirationDuration;   
};

#endif // TIMED_DATA_HPP
