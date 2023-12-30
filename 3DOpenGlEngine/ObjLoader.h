#pragma once

#include "Polygonal.h"
#include <fstream>

class ObjLoader
{

private:

	static std::vector<float> getValues(std::string line)
	{
		std::vector<float> array;
		std::stringstream ss(line);
		float value;
		while (ss >> value)
			array.push_back(value);
		return array;
	}


	static void handleNewPoint(std::string line, std::shared_ptr<Polygonal> loadingFile)
	{
	

		//std::cout << "new point: " << array.at(0)<<", " << array.at(1) <<", "<< array.at(2) << std::endl;
		std::vector<float> array = getValues(line);
		loadingFile->addPoint(array.at(0), array.at(1), array.at(2),
			(float)rand() / RAND_MAX,
			(float)rand() / RAND_MAX,
			(float)rand() / RAND_MAX,
			(float)rand() / RAND_MAX * 50
		
		
		);




	}

	static void handleNewFace(std::string line, std::vector<Vector2f>* uvs, std::vector<Vector3f>* ns, std::shared_ptr<Polygonal> loadingFile)
	{
	//	std::cout << "face" <<line<< std::endl;


		std::vector<std::string> array;
		std::stringstream ss(line);
		std::string point;
		while (ss >> point)
			array.push_back(point);
		//std::cout << "uvssize: " << uvs->size() << std::endl;
		
		std::vector<int> poinIndexList;
		std::vector<Vector2f> uvList;
		std::vector<Vector3f> NList;
		for (std::string pointString: array)
		{
			//std::cout << "piont:" << pointString << std::endl;
			int ptNumbEnd= pointString.find('/');
			int ptNumber = stoi(pointString.substr(0, ptNumbEnd))-1;
			poinIndexList.push_back(ptNumber);

			pointString = pointString.substr(ptNumbEnd+1);

			//std::cout << "piont2:" << pointString << std::endl;
			ptNumbEnd = pointString.find('/');
			//std::cout << "pt: " << pointString.substr(0, ptNumbEnd) << std::endl;
			//	ptNumbEnd = pointString.find('/');
		     //	std::cout <<"pt: "<< pointString <<" ptned: "<< ptNumbEnd << " substr: "<< pointString.substr(0, ptNumbEnd)<<std::endl;
				int uvNumber = stoi(pointString.substr(0, ptNumbEnd)) - 1;
			//	std::cout << uvNumber << ", " << std::endl;;
			///	std::cout << "Adding uv: " << uvNumber << std::endl;
				uvList.push_back(uvs->at(uvNumber));
			//loadingFile->addFace()






				pointString = pointString.substr(ptNumbEnd + 1);

				//std::cout << "piont2:" << pointString << std::endl;
				ptNumbEnd = pointString.find('/');
				//std::cout << "pt: " << pointString.substr(0, ptNumbEnd) << std::endl;
				//	ptNumbEnd = pointString.find('/');
				//std::cout << "pt: " << pointString << " ptned: " << ptNumbEnd << " substr: " << pointString.substr(0, ptNumbEnd) << std::endl;
				int nNumber = stoi(pointString.substr(0, ptNumbEnd)) - 1;
				//std::cout << nNumber << ", " << std::endl;;
				///std::cout << "Adding n: " << nNumber << std::endl;
				NList.push_back(ns->at(nNumber));


		}

		loadingFile->addFullFace(poinIndexList, uvList, NList);


		//std::cout << std::endl;

	}
static 	void handleNewUV(std::string line, std::vector<Vector2f>* uvs)
	{

		//std::cout << "new point: " << array.at(0)<<", " << array.at(1) <<", "<< array.at(2) << std::endl;
		std::vector<float> array = getValues(line);
		Vector2f uv = Vector2f(array.at(0), array.at(1));
		uvs->push_back(uv);
		//std::cout << "uv: " << uv << std::endl;
	
	}
static 	void handleNewN(std::string line, std::vector<Vector3f>* ns)
{

	//std::cout << "new point: " << array.at(0)<<", " << array.at(1) <<", "<< array.at(2) << std::endl;
	std::vector<float> array = getValues(line);
	Vector3f N = Vector3f(array.at(0), array.at(1), array.at(2));
	ns->push_back(N);
	//std::cout << "uv: " << uv << std::endl;
}

	static void handleNeLine(std::string line, std::shared_ptr<Polygonal> loadingFile, std::vector<Vector2f>* uvs, std::vector<Vector3f>* ns)
	{
	
		int typeEnd = line.find(" ");
		
		std::string type = line.substr(0, typeEnd);
		
		
		if (type == "v")
			handleNewPoint(line.substr(typeEnd), loadingFile);
		if (type == "vt")
			handleNewUV(line.substr(typeEnd), uvs);
		if (type == "vn")
			handleNewN(line.substr(typeEnd), ns);


		
		if (type == "f") {
			handleNewFace(line.substr(typeEnd), uvs,ns,loadingFile);
		}
		
	
	 }




public:
	
	static std::shared_ptr<Polygonal> loadFromFile(std::string file)
	{
		//std::cout << "file: " << file;
		
		std::ifstream inputStream;
		inputStream.open(file);
		std::shared_ptr<Polygonal> loadingFile = std::make_shared<Polygonal>();


		std::vector<Vector2f>* uvs = new std::vector<Vector2f>();
		std::vector<Vector3f>* ns = new 	std::vector<Vector3f>();
		if (inputStream.is_open())
		{
			std::string line;
			while (std::getline(inputStream,line))
			{
				handleNeLine(line, loadingFile, uvs, ns);
			}
		}
		else
		{
			throw std::runtime_error("Couildnt open file");
		}
		


		delete(uvs);
		delete(ns);
		return loadingFile;

	  }

};

