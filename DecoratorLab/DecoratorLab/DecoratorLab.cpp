#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <istream>
#include <map> 
std::vector<std::string> strings;
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
class Component 
{
public:
	virtual ~Component(){}
	virtual std::string Operation() const = 0;
};
class ConcreteComponent : public Component
{
public:
	std::string Operation() const override
	{
		return "ConcreteComponent";
	}
};
class Decorator : public Component
{
protected:
	Component* component_;
public:
	Decorator(Component* component):component_(component){}
	std::string Operation() const override
	{
		return this->component_->Operation();
	}
};
class ConcreteDecoratorA : public Decorator
{
public:
	ConcreteDecoratorA(Component* component):Decorator(component){}
	std::string Operation() const override
	{
		return "ConcreteDecoratorA(" + Decorator::Operation() + ")";
	}
};
class ConcreteDecoratorB : public Decorator
{
public:
	ConcreteDecoratorB(Component* component):Decorator(component){}
	std::string Operation() const override
	{
		return"ConcreteDecoratorB(" + Decorator::Operation() + ")";
	}
};
void ClientCode(Component* component)
{
	std::cout << "Result:" << component->Operation();
}
std::string FindKeywords(std::string line)
{
	for (auto p : myFirstMap)
	{		
		std::size_t  found = line.find(p.first);
		if (found != std::string::npos)
		{
			line.replace(line.find(p.first), p.first.length(), "\<font color = \"" + p.second + "\">"+p.first+"<\/font>");
		}		
	}	
	return line;
}
void InputStream()
{
	std::fstream fs("E:\code.html", std::ios::out);
	if (fs.is_open())
	{
		fs << "<\html>" << std::endl<<"<\body style=\"background-color:black;\">"<< std::endl << "<\pre>" << std::endl;
		std::cout << "Recording in progress ... " << std::endl;
		for(auto p:strings)
		{
			fs << p << std::endl;
		}
		std::cout << "Recording completed! " << std::endl;
	}
	else
	{
		std::cout << "Something going wrong!";
	}
	fs << "<\/pre>" << std::endl << "<\/body>" << std::endl << "<\/html>" << std::endl;
	fs.close();
}
void OutputStream()
{
	int count=0;
	std::fstream fs("E:\Decoratorlab.cpp", std::ios::in);
	if (fs.is_open())
	{
		std::string line;	
		std::string countline;
		std::cout << "\nReading in progress ... " << std::endl;
		while (getline(fs, line))
		{
			count++;
			std::cout << line << std::endl;
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
			std::string sline = FindKeywords(line);
			line.replace(0, sline.length(), sline);
			countline = "\<font color = \"blue\">"+std::to_string(count)+"\t|"+"<\/font>" ;
			line.insert(0,countline);
			strings.push_back(line);
		}
		std::cout << "\nReading completed! " << std::endl;
	}
	else
	{
		std::cout << "Something going wrong!";
	}
	fs.close();
	InputStream();
}
int main()
{

	Component* simple = new ConcreteComponent;
	std::cout << "Client: I've got a simple component:\n";
	//ClientCode(simple);
	std::cout << "\n\n";
	Component* decoratorfirst = new ConcreteDecoratorA(simple);
	Component* decoratorsecond = new ConcreteDecoratorB(decoratorfirst);
	std::cout << "Client: I've got a simple component:\n";
	ClientCode(decoratorsecond);
	std::cout << "\n";
	delete simple;
	delete decoratorfirst;
	delete decoratorsecond;
	return 0;















	std::string sol=FindKeywords("ifinelsecludeifinclude");
	std::cout << sol;
	OutputStream();
    std::cout << "Hello World!\n";
	system("Y:\code.html");
}