/*
 * Exception header file is for handling exceptions in my own way.
 * There are a few types of errors to be able to control a flow of the program better,
 * and to help user to understand what is he/she doing wrong while using my header files.
 * For detailed information, visit my github: https://github.com/AliKhudiyev/Panorama-Image-Stitching
*/

#pragma once

#include<exception>
#include<string>

enum ERROR { 
    DEFAULT=0,
    LIGHT,
    NFILE,
    FATAL,
    MEMORY,
    LOGIC,
    INFO
};

class Exception{
    private:
    std::string msg_;

    public:
    explicit Exception(const char* msg, const ERROR& error=DEFAULT){
        switch(error){
            case DEFAULT:
                msg_=msg;
                break;
            case LIGHT:
                msg_="LIGHT ERROR: "+std::string(msg);
                msg_+="\tInitializing default parameters to continue..";
                break;
            case NFILE:
                msg_="FILE ERROR: "+std::string(msg);
                break;
            case FATAL:
                msg_="FATAL ERROR: "+std::string(msg);
                break;
            case MEMORY:
                msg_="MEMORY ERROR: "+std::string(msg);
                break;
            case LOGIC:
                msg_="LOGIC ERROR: "+std::string(msg);
                break;
            case INFO:
                msg_="INFO: "+std::string(msg);
                break;
            default:
                msg_="Undefined: "+std::string(msg);
                break;
        }
    }
    explicit Exception(const std::string& msg, const ERROR& error=DEFAULT): 
        Exception(msg.c_str(), error) {}
    const std::string& get() const{
        return msg_;
    }
    ~Exception(){}
};
