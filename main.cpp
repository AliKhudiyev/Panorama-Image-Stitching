#include<iostream>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include"bmp.hpp"

using namespace std;

void check(int argc, const char** argv);

int main(int argc, char const *argv[])
{
    std::cout<<"Program started!\n";
    
    /*
    unsigned char adv;
    char r, g, b;
    cout<<"Do you want to switch to advanced mode? (y/n) ";
    cin>>adv;
    if(adv==y){
        cout<<"Enter background color : (r, g, b) ";
        cin>>r>>g>>b;
        Panorama panorama;
        panorama.background_color_.set(r, g, b);
    } else{
        ;
    }
    */

    try{
        // check(argc, argv);

        Image image1(argv[1]);
        // Image image2(argv[2]);

        try{
            image1.set("copy25");
        } catch(Exception& exception){
            cout<<exception.get()<<'\n';
        }
        image1.Info();
        image1.create();

        // image1.vertical_stitch(image);
        BMP image(iName("elongated25"));
        vector<double>sf{1.8, 1.6, 1.4, 1.2, 1};
        image=BMP::elongate(sf, image1);
        image.create();
    } catch(Exception& exception){
        cout<<exception.get()<<'\n';
    }

    std::cout<<"End of the program!\n";

    return 0;
}

void check(int argc, const char** argv){
    if(argc!=2 || strcmp(argv[1], "--help")==0){
        throw Exception("\n\
Appropriate run syntax: \
./main [image_path/image_name]\
            ", INFO);
    }
    if(access(argv[1], F_OK)==-1){
        throw Exception("File doesn't exist.", NFILE);
    }
}
