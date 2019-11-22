
#ifndef __INI_FILE_H_
#define __INI_FILE_H_

#if defined(__WINDOWS__)

namespace ArkLight {
    namespace Config {
        class IniFile
        {
        private:
            /* data */
        public:
            IniFile(/* args */);
            virtual ~IniFile();
        };
        
        IniFile::IniFile(/* args */)
        {
        }
        
        IniFile::~IniFile()
        {
        }     
    }
}

#elif defined(__LINUX__)



#elif defined(__ANDROID__)



#elif defined(__APPLE__)

#else 

#endif

#endif
