#include <iostream>
#include <chrono>
#include <thread>
#include <string>

class Timer
{
private:
	std::chrono::high_resolution_clock::time_point m_time;
	std::chrono::duration<float> duration;

	std::string m_name;
public:
	Timer(const std::string& TimerName)
	{
		m_name = TimerName;
	};

	inline void start()
	{
		m_time = std::chrono::high_resolution_clock::now();
	};

	inline void end()
	{
		duration = std::chrono::high_resolution_clock::now() - m_time;

		float ms = duration.count() * 1000;
		std::cout << "[" << m_name << "] Program Duration: " << ms << " ms" << "\n";
	};
};