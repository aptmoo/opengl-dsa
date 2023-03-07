#include "instrumentor.h"
// std include
#include <algorithm>
#include <thread>

void Instrumentor::BeginSession(const std::string& name, const std::string& path)
{
    m_OutputFileStream.open(path);
    WriteHeader();
    m_Session = new InstrumentationSession{ name };
}

void Instrumentor::EndSession()
{
    WriteFooter();
    m_OutputFileStream.close();
    delete m_Session;
    m_Session = nullptr;
    m_ProfileCount = 0;
}

void Instrumentor::WriteProfile(const ProfileResult& profile)
{
    if(m_ProfileCount++ > 0)
        m_OutputFileStream << ',';

    std::string name = profile.m_Name;
    std::replace(name.begin(), name.end(), '"', '\'');

    m_OutputFileStream << "{";
    m_OutputFileStream << "\"cat\":\"function\",";
    m_OutputFileStream << "\"dur\":" << (profile.m_End - profile.m_Start) << ',';
    m_OutputFileStream << "\"name\":\"" << name << "\",";
    m_OutputFileStream << "\"ph\":\"X\",";
    m_OutputFileStream << "\"pid\":0,";
    m_OutputFileStream << "\"tid\":" << profile.m_ThreadID << ",";
    m_OutputFileStream << "\"ts\":" << profile.m_Start;
    m_OutputFileStream << "}";

    m_OutputFileStream.flush();
}

void Instrumentor::WriteHeader()
{
    m_OutputFileStream << "{\"otherData\": {},\"traceEvents\":[";
    m_OutputFileStream.flush();
}

void Instrumentor::WriteFooter()
{
    m_OutputFileStream << "]}";
    m_OutputFileStream.flush();
}

Instrumentor& Instrumentor::Get()
{
    static Instrumentor instance;
    return instance;
}

InstrumentationTimer::InstrumentationTimer(const std::string& name)
    : m_Name(name), m_Stopped(false)
{   
    m_StartTimePoint = std::chrono::high_resolution_clock::now();
}

InstrumentationTimer::~InstrumentationTimer()
{
    // avoid stopping twice
    if(!m_Stopped)
        Stop();
}

void InstrumentationTimer::Stop()
{
    auto endTimePoint = std::chrono::high_resolution_clock::now();

    int64_t start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
    int64_t end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

    uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
    Instrumentor::Get().WriteProfile({ m_Name, start, end, threadID });

    m_Stopped = true;
}