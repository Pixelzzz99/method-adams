#include "pbPlots.hpp"
#include "supportLib.hpp"
#include <string>
#include <sstream>

bool plots(std::vector<double> xs, std::vector<double> ys, std::string name_file)
{
    bool success;
    StringReference *errorMessage = new StringReference();
	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

	success = DrawScatterPlot(imageReference, 1600, 900, &xs, &ys, errorMessage);

    if(success){
        std::vector<double> *pngdata = ConvertToPNG(imageReference->image);
        WriteToFile(pngdata, name_file);
        DeleteImage(imageReference->image);
	}else{
	    std::cerr << "Error: ";
        for(wchar_t c : *errorMessage->string){
            std::wcerr << c;
        }
        std::cerr << std::endl;
	}

	return success ? 0 : 1;
}

int main(){

    //open file
    std::fstream file("./results.txt", std::ios::in | std::ios::out );
    if(!file.is_open()){
        std::cout << "Error opening file" << std::endl;
        return 1;
    }
    //read file
    std::vector<double> t;
    std::vector<double> y;
    std::vector<double> solution;
    

    //number1 number2 number3 in file
    while(!file.eof()){
        double temp;
        file >> temp;
        t.push_back(temp);
        temp = 0;
        file >> temp;
        y.push_back(temp);
        temp = 0;
        file >> temp;
        solution.push_back(temp);
        temp = 0;
    }
    file.close();
    t.pop_back();
    y.pop_back();
    solution.pop_back();
    plots(t, y, "AdamsMoulton.png");
    plots(t, solution, "solution.png");
    return 0;
}
