#include <jni.h>
#include <string>
#include <dlfcn.h>    // dlopen, dlerror, dlsym, dlclose

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_cppcalltest_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    void* handle = dlopen( "libthird-lib.so", RTLD_LAZY );


    std::string hello = "Hello from C++";

    if(!handle)
    {
        hello = "Load fail.";
    } else
    {
        hello = "Load success.";
    }

    typedef int(*fun)();

    fun tsetcfun = (fun)dlsym(handle,"TestC");

    if(tsetcfun)
    {
        char* chs = new char[4096];
        sprintf(chs,"load testc %d",tsetcfun());
        hello += chs;
    } else
    {
        hello+=" load testC fail.";
    }

    fun tsetfun = (fun)dlsym(handle,"Test");
    if(tsetfun)
    {
        hello += printf("load test %d",666);
    } else
    {
        hello +=" load test fail.";
    }

    return env->NewStringUTF(hello.c_str());
}
