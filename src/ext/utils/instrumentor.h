/*
A performance instrumentor, based on TheCherno's one
https://www.youtube.com/watch?v=xlAH4dbMVnU
*/

#ifndef HG_INSTRUMENTOR_H
#define HG_INSTRUMENTOR_H
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
    /*
    @brief Construct a timer with a name, and start it.
    */
    InstrumentationTimer(const std::string& name);

    /*
    @brief Timer destructor. Calls stop.
    */
    ~InstrumentationTimer();

    /*
    @brief Stop the timer. This function gets called by the destructor, but can also be called to forcefully stop a timer.
    Also writes to the profiler.
    */
    void Stop();
};

#define HG_ENABLE_PROFILE 1

#if HG_ENABLE_PROFILE
#define HG_PROFILE_START(name, file) Instrumentor::Get().BeginSession(name, file)
#define HG_PROFILE_END() Instrumentor::Get().EndSession()
#define HG_TIMER_INTERNAL(name, line) InstrumentationTimer timer##name##line(name)
#define HG_NAMED_TIMER(name) InstrumentationTimer timer##name(#name)
#define HG_PROFILE_FUNCTION() HG_TIMER_INTERNAL(__func__, __LINE__)

#else
#define HG_PROFILE_START(name, file)
#define HG_PROFILE_END()
#define HG_TIMER_INTERNAL(name, line)
#define HG_PROFILE_FUNCTION()
#endif

#endif