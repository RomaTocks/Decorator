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
    { "close", "Goldenrod" },
    { "push_back", "Goldenrod" },
    { "insert", "Goldenrod" },
    { "find", "Goldenrod" },
    { "istream", "Goldenrod" },
    { "iostream", "Goldenrod" },
    { "fstream", "Goldenrod" },
    { "vector", "Goldenrod" },
    { "cout", "Goldenrod" },
    { "cin", "Goldenrod" },
    { "endl", "Goldenrod" },
    { "map", "Goldenrod" },
    { "out", "Goldenrod" },
    { "int", "blue" },
    { "class", "blue" },
    { "public", "blue" },
    { "virtual", "blue" },
    { "override", "blue" },
    { "protected", "blue" },
    { "new", "blue" },
    { "delete", "blue" },
    { "ios", "green" },
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
        std::fstream fs("Y:\TrueDecoratorLab.cpp", std::ios::in);
        if (fs.is_open())
        {
            std::string line;
            std::cout << "\nReading in progress ... " << std::endl;
            while (getline(fs, line))
            {
                for (auto d : line)
			{
				if (d == '<')
				{
					line.insert(line.find(d), "&lt");				
				}
				if (d == '<')
				{
					line.erase(line.find(d), 1);
				}
			}
			for (auto d : line)
			{
				if (d == '>')
				{
					line.insert(line.find(d), "&gt");					
				}
				if (d == '>')
				{
					line.erase(line.find(d), 1);
				}
			}
                strings.push_back(line);
            }
        }
        else
        {
            std::cout << "Something going wrong!";
        }
        fs.close();        
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
    Decorator(FileInterface* file) :file_(file) {}
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
    LineDecorator(FileInterface* file) :Decorator(file) {}
    void Output() override
    {
        Decorator::Output();
    }
    void Input() override
    {    
        Decorator::Input();
        strings.clear();
        std::fstream fs("Y:\code.html", std::ios::in);
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
        std::fstream fn("Y:\code.html", std::ios::out);
        if (fn.is_open())
        {
            int count = 0;
            std::string countline;
            for (auto p : strings)
            {
                count++;
                countline = "\<font color = \"blue\">" + std::to_string(count) + "\t|" + "<\/font>";
                p.insert(0, countline);
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
class HTMLDecorator :public Decorator
{
public:
    HTMLDecorator(FileInterface* file) :Decorator(file) {}
    void Output() override
    {
        Decorator::Output();
    }
    void Input() override
    {   
        /*std::string first = strings.front();
        strings.front() = first.insert(0, "\<html\>\n\<body\>\n\<pre\>");*/
        Decorator::Input();
        strings.clear();
        std::fstream fs("Y:\code.html", std::ios::in);
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
        std::fstream fv("Y:\code.html", std::ios::out);
        if (fv.is_open())
        {
            fv << "<html>" << std::endl << "<body>" << std::endl << "<pre>" << std::endl;
            std::cout << "Recording completed! " << std::endl;
        }
        fv.close();
        std::fstream fn("Y:\code.html", std::ios::app);
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
        std::fstream fd("Y:\code.html", std::ios::app);
        if (fd.is_open())
        {
            fd << "<\/pre>" << std::endl << "<\/body>" << std::endl << "<\/html>" << std::endl;
            std::cout << "Recording completed! " << std::endl;
        }
        else
        {
            std::cout << "Something going wrong!";
        }
        fd.close();
    }
};
class ColorDecorator :public Decorator
{
public:
    ColorDecorator(FileInterface* file) :Decorator(file) {}
    void Output() override
    {   
        Decorator::Output();
    }
    void Input() override
    {  
        Decorator::Input();
        strings.clear();
        std::fstream fs("Y:\code.html", std::ios::in);
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
        std::fstream fn("Y:\code.html", std::ios::out);
        if (fn.is_open())
        {
            int count = 0;
            std::string countline;
            for (auto p : strings)
            {
                p=FindKeywords(p);            
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
    std::string FindKeywords(std::string line)
    {
        for (auto p : myFirstMap)
        {
            std::size_t  found = line.find(p.first);
            if (found != std::string::npos)
            {
                line.replace(line.find(p.first), p.first.length(), "\<font color = \"" + p.second + "\">" + p.first + "<\/font>");
            }
        }
        return line;
    }
};
void ResultFile(FileInterface* file)
{
    file->Output();
    file->Input();
}
void Choice(FileInterface* file)
{
    int n;
    std::cout << "Do you want a code lines in your file?\n1. Yes\n2. No" << std::endl;
    std::cin >> n;
    if (n == 1)
    {
        file = new LineDecorator(file);
    } 
    std::cout << "Do you want a file with HTML tags?\n1. Yes\n2. No" << std::endl;
    std::cin >> n;
    if (n == 1)
    {
        file = new HTMLDecorator(file);
    }    
    std::cout << "Do you want a set color to keywords in your file?\n1. Yes\n2. No" << std::endl;
    std::cin >> n;
    if (n == 1)
    {
        file = new ColorDecorator(file);
    }   
    ResultFile(file);
    std::cout << "Check your file in browser!" << std::endl;
    system("Y:\code.html");
    delete file;
}
int main()
{
    FileInterface* file = new File;
    Choice(file);
    /*FileInterface* file = new File;
    FileInterface* linedecorator = new LineDecorator(file);
    FileInterface* colordecorator = new ColorDecorator(linedecorator);
    FileInterface* htmldecorator = new HTMLDecorator(colordecorator);
    std::cout << "File: Decorator writing!";
    ResultFile(htmldecorator);
    system("Y:\code.html");
    delete file;
    delete linedecorator;
    delete htmldecorator;
    delete colordecorator;*/
}