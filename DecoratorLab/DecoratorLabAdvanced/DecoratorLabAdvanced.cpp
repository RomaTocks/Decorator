
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <istream>
#include <map> 

std::map<std::string, std::string> myFirstMap =
{
    { "include", "purple" },
    { "else", "purple" },
    { "return", "purple" },
    { "for", "purple" },
    { "if", "purple" },
    { "auto", "blue" },
    { "void", "blue" },
    { "istream", "Goldenrod" },
    { "iostream", "Goldenrod" },
    { "fstream", "Goldenrod" },
    { "vector", "Goldenrod" },
    { "map", "Goldenrod" },
    { "int", "blue" },
    { "string", "green" },
    { "main", "Goldenrod" },
    { "while", "purple" },
    { "system", "Goldenrod" }
};
std::vector<std::string> strings;
std::vector<std::string> htmlstrings;
class FileInterface
{
public: 
    virtual ~FileInterface() {}
    virtual void Output() {};
    virtual void Input() {};
};
class File : public FileInterface
{
public:
    
    void Output() override
    {
        std::fstream fs("Y:\DecoratorLabAdvanced.cpp", std::ios::in);
        if (fs.is_open())
        {
            std::string line;
            std::cout << "\nReading in progress ... " << std::endl;
            while (getline(fs, line))
            {
                strings.push_back(line);              
            }
        }
        else
        {
            std::cout << "Something going wrong!";
        }
        fs.close();
        Input();
    }
    void Input() override
    {
        std::fstream fn("Y:\code.html", std::ios::out);
        if (fn.is_open())
        {
            for (auto p : strings)
            {
                fn << p << std::endl;
            }
            std::cout << "Recording completed! " << std::endl;
        }
        else
        {
            std::cout << "Something going wrong!";
        }
        fn.close();
    }
};
class Decorator : public FileInterface
{
protected:
    FileInterface* file_;
public:
    Decorator(FileInterface* file):file_(file){}
    void Output() override
    {
        return this->file_->Output();
    }
    void Input() override
    {
       return this->file_->Input();
    }
};
class LineDecorator :public Decorator
{
public:
    LineDecorator(FileInterface* file):Decorator(file) {}
    void Output() override
    {        
        Decorator::Output();
    }
    void Input() override
    {
        std::fstream fn("Y:\code.html", std::ios::out);
        if (fn.is_open())
        {
            int count = 0;
            std::string countline;
            for (auto p : strings)
            {
                count++;
                countline = "\<font color = \"blue\">" + std::to_string(count) + "\t|" + "<\/font>";          
                fn << p.insert(0, countline) << std::endl;
            }
            std::cout << "Recording completed! " << std::endl;
        }
        else
        {
            std::cout << "Something going wrong!";
        }
        fn.close();
    }
};
class HTMLDecorator :public Decorator
{
public:
    HTMLDecorator(FileInterface* file):Decorator(file){}
    void Output() override
    {   
        //Decorator::Output();
       /* std::fstream fs("Y:\code.html", std::ios::in);
        if (fs.is_open())
        {
            std::string line;
            std::cout << "\nReading in progress ... " << std::endl;
            while (getline(fs, line))
            {
                strings.push_back(line);             
            }
        }
        else
        {
            std::cout << "Something going wrong!";
        }
        fs.close();*/
    }
    void Input() override
    {
        //Decorator::Input();


        std::fstream fn("Y:\code.html", std::ios::out);
        if (fn.is_open())
        {
            fn << "<\html>" << std::endl << "<body style=\"background-color:White	; \">" << std::endl << "<\pre>" << std::endl;
            for (auto p : strings)
            {                
                fn << p << std::endl;
            }
            fn << "<\/pre>" << std::endl << "<\/body>" << std::endl << "<\/html>" << std::endl;
            std::cout << "Recording completed! " << std::endl;
        }
        else
        {
            std::cout << "Something going wrong!";
        }
        fn.close();
    }
};
void ResultFile(FileInterface* file)
{
    file->Output();
    file->Input();
}

int main()
{
 
    FileInterface* file = new File;
    //FileInterface* linedecorator = new LineDecorator(file);
    //FileInterface* htmldecorator = new HTMLDecorator(linedecorator);
   
    std::cout << "File: simple writing!";
    //ResultFile(file);
    //ResultFile(linedecorator);
    ResultFile(htmldecorator);
    std::cout << "File: Decorator writing!";
    system("Y:\code.html");
    delete file;
    delete linedecorator;
    delete htmldecorator;

}
