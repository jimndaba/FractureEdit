#pragma once
#ifndef FRACTUREPROJECT_H
#define FRACTUREPROJECT_H

namespace Fracture
{
	struct ProjectParams
	{
		std::string Name;
		std::string path;
	};


	struct FractureProject
	{
		FractureProject();
		UUID ID;
		std::string Name = "Untitled";
		std::string Directory;
		std::string ContentDirectory;
		std::string AssetsFileDirectory;
		std::string ProjectsDirectory;
		
		std::string ActiveScene;
		std::string ActiveRendergraph;
		std::string ActiveScenePath;

		std::string EditorScreenshotFolderPath;


		UUID ActiveGraphID;
		UUID ActiveSceneID;
		UUID DefaultMatID;

		bool IsDirty = false;
	};




}
#endif