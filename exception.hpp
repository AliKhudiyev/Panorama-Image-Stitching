/*
 * Exception header file is for handling exceptions in my own way.
 * There are a few types of errors to be able to control a flow of the program better,
 * and to help user to understand what is he/she doing wrong while using my header files.
 * For detailed information, visit my github: https://github.com/AliKhudiyev/Panorama-Image-Stitching
*/

#pragma once

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
    Exception(const std::string& msg, const ERROR& error=DEFAULT){
        switch(error){
            case DEFAULT:
                msg_=msg;
                break;
            case LIGHT:
                msg_="LIGHT ERROR: "+msg;
                msg_+="\tInitializing default parameters to continue..";
                break;
            case NFILE:
                msg_="FILE ERROR: "+msg;
                break;
            case FATAL:
                msg_="FATAL ERROR: "+msg;
                break;
            case MEMORY:
                msg_="MEMORY ERROR: "+msg;
                break;
            case LOGIC:
                msg_="LOGIC ERROR: "+msg;
                break;
            case INFO:
                msg_="INFO: "+msg;
                break;
            default:
                msg_="Undefined: "+msg;
                break;
        }
    }
    const std::string& get() const{
        return msg_;
    }
    ~Exception(){}
};
