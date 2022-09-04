#!/bin/bash

cur_dir=$(cd $(dirname $0);pwd)/
base_dir=$(cd $(dirname $0);pwd)/XBase/

read -p "please enter new Project's name:"  projectName
echo "projectName: $projectName"

read -p "please enter $projectName 's path(according to the current path)(empty is cur path):" newProjectPath
echo "projectPath: $cur_dir$newProjectPath"

project_dir="$cur_dir$newProjectPath/$projectName"

if [ ! -d "$project_dir" ]; then
    echo "createProject $projectName in $cur_dir$newProjectPath"
    mkdir $project_dir

    cd $project_dir
    ln -s $base_dir/include include
    ln -s $base_dir/lib lib
    ln -s $base_dir/third third

    filePath=readme.md
    echo "" > $filePath

    cp $base_dir/CMakeLists.txt CMakeLists.txt
    cp $base_dir/Config.h.in Config.h.in
    
    mkdir src
    cd src

    cp $base_dir/src/CMakeLists.txt CMakeLists.txt
    ln -s $base_dir/src/XPublic XPublic
    filePath=main.cpp
    echo "#include \"XLog/XLog.h\"
int main(int argc, char* argv[])
{
	if (!XLOG->init(\""$projectName"Log.txt\", 0))
	{
		return 0;
	}

    XLOG_INFO(\"Hello $projectName\");

	return 0;
}" > $filePath

    mkdir $projectName
    cd $projectName
    cp $base_dir/src/test/CMakeLists.txt CMakeLists.txt
else
    echo "$projectName is exist."
fi


