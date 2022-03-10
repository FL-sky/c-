#include <iostream>
#include <thread>
#include <ctime>

#include <chrono>
using namespace std::chrono;
using namespace std;
class CELLTimestamp
{
public:
    CELLTimestamp()
    {
        //QueryPerformanceFrequency(&_frequency);
        //QueryPerformanceCounter(&_startCount);
        update();
    }
    ~CELLTimestamp()
    {
    }

    void update()
    {
        //QueryPerformanceCounter(&_startCount);
        _begin = high_resolution_clock::now();
    }
    /**
    *   获取当前秒
    */
    double getElapsedSecond()
    {
        return getElapsedTimeInMicroSec() * 0.000001;
    }
    /**
    *   获取毫秒
    */
    double getElapsedTimeInMilliSec()
    {
        return this->getElapsedTimeInMicroSec() * 0.001;
    }
    /**
    *   获取微妙
    */
    long long getElapsedTimeInMicroSec()
    {
        /*
        LARGE_INTEGER endCount;
        QueryPerformanceCounter(&endCount);
        double  startTimeInMicroSec =   _startCount.QuadPart * (1000000.0 / _frequency.QuadPart);
        double  endTimeInMicroSec   =   endCount.QuadPart * (1000000.0 / _frequency.QuadPart);
        return  endTimeInMicroSec - startTimeInMicroSec;
		*/

        return duration_cast<microseconds>(high_resolution_clock::now() - _begin).count();
    }

protected:
    //LARGE_INTEGER   _frequency;
    //LARGE_INTEGER   _startCount;
    time_point<high_resolution_clock> _begin;
};

int g_nData = 0;

void foo()
{
    for (int i = 0; i < 10000000; i++)
    {
        g_nData++;
    }
}

int main()
{
    //clock_t startTime, endTime;
    //startTime = clock(); //计时开始
    CELLTimestamp st;
    double start = st.getElapsedTimeInMicroSec();
    std::thread t(foo);

    for (int i = 0; i < 100000; i++)
    {
        g_nData++;
    }

    t.join();
    //endTime = clock(); //计时结束
    //cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    double end = st.getElapsedTimeInMicroSec();
    cout << "The run time is: " << end - start << " us" << endl;
    std::cout << g_nData << std::endl;

    return 0;
}