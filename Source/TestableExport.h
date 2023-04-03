#ifndef TESTABLEEXPORT_H
#define TESTABLEEXPORT_H


#ifdef _WIN32
#ifdef TEST_RUNNER
#define TESTABLE __declspec(dllimport)
#else
#define TESTABLE __declspec(dllexport)
#endif
#else
#define TESTABLE __attribute__((visibility("default")))
#endif



#endif
