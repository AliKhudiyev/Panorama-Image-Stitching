#include<iostream>
#include"chdrs.hpp"
#include"bmp.hpp"

using namespace std;

void check(int argc, const char** argv);

int main(int argc, char const *argv[])
{
    std::cout<<"Program started!\n";

    try{
        check(argc, argv);
        
        if(strcmp(argv[1], "-e")==0){
            Image image1(argv[2]);
            string iname(argv[2]);
            string final_name=iname.substr(iname.find_last_of('/', iname.size()-1)+1,iname.find('.', 0)-iname.find_last_of('/', iname.size()-1)-1)+"Resized";
            BMP image(final_name);

            vector<double>sf{1.75, 1.7, 1.5, 1.5, 1.3, 1.4, 1.4, 1.4, 1.1, 1.1, 1};
            image=BMP::elongate(sf, image1);
            image.create("syc/"+final_name);
        } else if(strcmp(argv[1], "-s")==0){
            try{
                BMP image1(argv[2]);
                BMP image2(argv[3]);
                BMP image;

                image=image1+image2;
                image.create();
            } catch(Exception& exception){
                cout<<exception.get()<<'\n';
            }
        }

    } catch(Exception& exception){
        cout<<exception.get()<<'\n';
    }

    std::cout<<"End of the program!\n";

    return 0;
}

void check(int argc, const char** argv){
    if(argc>4){
        throw Exception("\n\
Appropriate run syntax: \
./main -[option] [image_path/image_name]\
", INFO);
    } else if(argc==3 && strcmp(argv[1], "-e") &&
        access(argv[2], F_OK)==-1){
        throw Exception("File doesn't exist.", NFILE);
    } else if(argc==4 && strcmp(argv[1], "-s") &&
        (access(argv[2], F_OK)==-1 || access(argv[3], F_OK)==-1)){
        throw Exception("File doesn't exist.", NFILE);
    }
    if(argc<=2 || strcmp(argv[1], "--help")==0){
        throw Exception("\n\
Appropriate run syntax: \
./main [image_path/image_name]\
", INFO);
    }
}
