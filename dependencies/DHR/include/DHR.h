#pragma  once

#ifdef DHR_EXPORT_SYMBOL
#define DYNALO_EXPORT_SYMBOLS
#define DHR_EXPORT DYNALO_EXPORT
#define DHR_CALL DYNALO_CALL
#include "dynalo/symbol_helper.hpp"
#else

#ifndef DHR_DLL_COPIES_DIR
#define DHR_DLL_COPIES_DIR "./DHRDllCopies/"
#endif
#ifndef DHR_RELOAD_DELEY
#define DHR_RELOAD_DELEY 100ms
#endif

#include "dynalo/dynalo.hpp"
#include <unordered_map>
#include <type_traits>
#include <filesystem>
#include <functional>
#include <thread>
namespace fs = std::filesystem;
using namespace std::chrono_literals;


struct DLLHotReloader
{
    dynalo::library* mLibrary;
    std::string mInputPath;
    fs::file_time_type mLastUpdateTime;
    std::function<void()> mOnCloseFunction;

    // output path 
    int dll_counter = 0;
    std::string mName;

    typedef void (*DefFunctionPointer)(void);
    mutable std::unordered_map<std::string, DefFunctionPointer> mFunctionCache;

    std::string GetOutputPath()
    {
		return dynalo::to_native_name(DHR_DLL_COPIES_DIR + mName + std::to_string(dll_counter++));
    }

    /*
    *  Name without extension
    *  @throw If dll can't be loaded
    */
    inline DLLHotReloader(const std::string& path)
        : mLibrary(nullptr)
    {
        if (fs::exists(DHR_DLL_COPIES_DIR))
            fs::remove_all(DHR_DLL_COPIES_DIR);
        fs::create_directory(DHR_DLL_COPIES_DIR);

        std::string input_dir;
        int pos = path.find_last_of('/') + 1;
        if (pos != std::string::npos)
        {
			mName = path.substr(pos);
            input_dir = path.substr(0, pos);
        }
        else
            mName = path;

        mInputPath = dynalo::to_native_name(input_dir + mName);
        CheckForUpdate();
    }

    inline ~DLLHotReloader()
    {
        if (mOnCloseFunction)
            mOnCloseFunction();
        delete mLibrary;
    }

    /*
    *  @throw If dll can't be reloaded
    */
    inline bool CheckForUpdate()
    {
        fs::file_time_type lib_update_time = mLastUpdateTime;
        try
        {
            lib_update_time = fs::last_write_time(mInputPath);
        }
        catch (const std::exception& e)
        {}

        if (mLastUpdateTime != lib_update_time || mLibrary == nullptr)
        {
            if (mOnCloseFunction)
                mOnCloseFunction();

            for (int i = 0; i < 10; i++)
            {
                std::this_thread::sleep_for(DHR_RELOAD_DELEY);

                try {
                    delete mLibrary;
                    mLibrary = nullptr;
                    std::string output_path = GetOutputPath();
                    fs::copy(mInputPath, output_path);
                    mLibrary = new dynalo::library(output_path);

                    mLastUpdateTime = lib_update_time;
                    mFunctionCache.clear();
                    return true;
                }
                catch(std::exception& exception)
                {
                    if (i == 9)
                        throw exception;
                }
            }
        }
        return false;
    }

    /*
    *  @throw If no function with such signature
    */
    template <typename FunctionSignature, typename ...Args>
    auto Call(const std::string& name, Args... args)
    {
        if (mFunctionCache.count(name))
        {
            auto func = reinterpret_cast<FunctionSignature*>(mFunctionCache[name]);
            return func(args...);
        }
        else {
            auto func = mLibrary->get_function<FunctionSignature>(name);
            mFunctionCache[name] = reinterpret_cast<DefFunctionPointer>(func);
            return func(args...);
        }
    }

    /* Will be called at dll detaching and program closing
    *  @throw If no function with such signature
    */
    template <typename FunctionSignature, typename ...Args>
    auto SetOnCloseFunction(const std::string& name, Args... args)
    {
        auto func = mLibrary->get_function<FunctionSignature>(name);
        mOnCloseFunction = std::function<void()>(std::bind(func, args...));
    }

    /*
    *  After hot reloading function pointers may be invalid
    *  @throw If no function with such signature
    */
    template <typename FunctionSignature>
    FunctionSignature* Get(const std::string& name)
    {
        return mLibrary->get_function<FunctionSignature>(name);
    }

};

#endif