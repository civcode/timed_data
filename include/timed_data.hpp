#ifndef TIMED_DATA_HPP_
#define TIMED_DATA_HPP_

#include <chrono>
#include <optional>

template<typename T>
class TimedData {
public:
  TimedData(std::chrono::milliseconds expiration_time)
  : has_been_written_(false), 
    expiration_duration(expiration_time) 
  {}

  // Read function for the underlying data type
  std::optional<T> read()
  {
    if (has_been_written_) {
      has_been_written_ = false;       
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
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_write_time);
    return elapsed < expiration_duration;
  }

  // Function to check if data is currently written (for external checking)
  bool is_written() const
  {
    return has_been_written_;
  }

  // Access the underlying data directly (for containers)
  T& get_data() {
    if (!data.has_value()) {
      data = T(); 
    }
    has_been_written_ = true;
    last_write_time = std::chrono::steady_clock::now();  
    return *data;
  }

private:
  bool has_been_written_;     
  std::optional<T> data;   
  std::chrono::steady_clock::time_point last_write_time;    
  std::chrono::milliseconds expiration_duration;   
};

#endif // TIMED_DATA_HPP_
