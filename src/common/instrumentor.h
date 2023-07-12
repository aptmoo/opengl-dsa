/*
A performance instrumentor, based on TheCherno's one
https://www.youtube.com/watch?v=xlAH4dbMVnU
*/

#ifndef INSTRUMENTOR_H
#define INSTRUMENTOR_H
// std includes
#include <fstream>
#include <string>
#include <chrono>

struct ProfileResult
{
    std::string m_Name;
    int64_t m_Start, m_End;
    uint32_t m_ThreadID;
};

struct InstrumentationSession
{
    std::string m_Name;
};

class Instrumentor
{
private:
    InstrumentationSession* m_Session;
    std::ofstream m_OutputFileStream;
    int m_ProfileCount;
public:
    /*
    @brief Instrumentor constructor. Does nothing exept setting some values to 0.
    */
    Instrumentor()
        : m_Session(nullptr), m_ProfileCount(0) {};
    
    void BeginSession(const std::string& name, const std::string& path = "performance.json");

    void EndSession();

    void WriteProfile(const ProfileResult& profile);

    void WriteHeader();
    void WriteFooter();

    static Instrumentor& Get();
};

class InstrumentationTimer
{
private:
    std::string m_Name;
    bool m_Stopped;

    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;

public:
   /**
    * @brief Construct a timer with a name, and start it.
    * 
    * @param name The name of the timer.
    */
    InstrumentationTimer(const std::string& name);
   /**
    * @brief Timer destructor. Calls stop()
    * 
    */
    ~InstrumentationTimer();

   /**
    * @brief Stop the timer. This function gets called by the destructor, but can also be called to forcefully stop a timer.
    * Also writes to the profiler.
    * 
    */
    void Stop();
};

#define ENABLE_PROFILE 1

#if ENABLE_PROFILE
#define PROFILE_START(name, file) Instrumentor::Get().BeginSession(name, file)
#define PROFILE_END() Instrumentor::Get().EndSession()
#define PROFILE_INTERNAL(name, line) InstrumentationTimer timer##name##line(name)
#define PROFILE_NAMED(name) InstrumentationTimer timer##name(#name)
#define PROFILE_FUNCTION() PROFILE_INTERNAL(__func__, __LINE__)

#else
#define PROFILE_START(name, file)
#define PROFILE_END()
#define PROFILE_INTERNAL(name, line)
#define PROFILE_FUNCTION()
#endif

#endif