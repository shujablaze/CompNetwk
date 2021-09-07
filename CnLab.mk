##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=CnLab
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=E:/oopsLab/oopsLab
ProjectPath            :=E:/oopsLab/CnLab/CnLab
IntermediateDirectory  :=../../oopsLab/build-$(ConfigurationName)/__/CnLab/CnLab
OutDir                 :=../../oopsLab/build-$(ConfigurationName)/__/CnLab/CnLab
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=shuja
Date                   :=02/09/2021
CodeLitePath           :="E:/Program Files/CodeLite"
LinkerName             :=C:/MinGW/bin/g++.exe
SharedObjectLinkerName :=C:/MinGW/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=..\..\oopsLab\build-$(ConfigurationName)\bin\$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
RcCmpOptions           := 
RcCompilerName         :=C:/MinGW/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/MinGW/bin/ar.exe rcu
CXX      := C:/MinGW/bin/g++.exe
CC       := C:/MinGW/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/MinGW/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=E:\Program Files\CodeLite
Objects0=../../oopsLab/build-$(ConfigurationName)/__/CnLab/CnLab/Hill_Cipher.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../../oopsLab/build-$(ConfigurationName)/__/CnLab/CnLab/.d $(Objects) 
	@if not exist "..\..\oopsLab\build-$(ConfigurationName)\__\CnLab\CnLab" mkdir "..\..\oopsLab\build-$(ConfigurationName)\__\CnLab\CnLab"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@if not exist "..\..\oopsLab\build-$(ConfigurationName)\__\CnLab\CnLab" mkdir "..\..\oopsLab\build-$(ConfigurationName)\__\CnLab\CnLab"
	@if not exist ""..\..\oopsLab\build-$(ConfigurationName)\bin"" mkdir ""..\..\oopsLab\build-$(ConfigurationName)\bin""

../../oopsLab/build-$(ConfigurationName)/__/CnLab/CnLab/.d:
	@if not exist "..\..\oopsLab\build-$(ConfigurationName)\__\CnLab\CnLab" mkdir "..\..\oopsLab\build-$(ConfigurationName)\__\CnLab\CnLab"

PreBuild:


##
## Objects
##
../../oopsLab/build-$(ConfigurationName)/__/CnLab/CnLab/Hill_Cipher.cpp$(ObjectSuffix): Hill_Cipher.cpp ../../oopsLab/build-$(ConfigurationName)/__/CnLab/CnLab/Hill_Cipher.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/oopsLab/CnLab/CnLab/Hill_Cipher.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hill_Cipher.cpp$(ObjectSuffix) $(IncludePath)
../../oopsLab/build-$(ConfigurationName)/__/CnLab/CnLab/Hill_Cipher.cpp$(DependSuffix): Hill_Cipher.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../../oopsLab/build-$(ConfigurationName)/__/CnLab/CnLab/Hill_Cipher.cpp$(ObjectSuffix) -MF../../oopsLab/build-$(ConfigurationName)/__/CnLab/CnLab/Hill_Cipher.cpp$(DependSuffix) -MM Hill_Cipher.cpp

../../oopsLab/build-$(ConfigurationName)/__/CnLab/CnLab/Hill_Cipher.cpp$(PreprocessSuffix): Hill_Cipher.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../../oopsLab/build-$(ConfigurationName)/__/CnLab/CnLab/Hill_Cipher.cpp$(PreprocessSuffix) Hill_Cipher.cpp


-include ../../oopsLab/build-$(ConfigurationName)/__/CnLab/CnLab//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


