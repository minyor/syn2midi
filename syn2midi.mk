##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=syn2midi
ConfigurationName      :=Release
WorkspacePath          :=C:/Data/Workspace/Workspace
ProjectPath            :=C:/Data/Workspace/Workspace/syn2midi
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Vasya Pupkin
Date                   :=17/03/2019
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/mingw32/bin/g++.exe
SharedObjectLinkerName :=C:/mingw32/bin/g++.exe -shared -fPIC
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
OutputFile             :=$(IntermediateDirectory)/../bin/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="syn2midi.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/mingw32/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)ffmpeg\ffmpeg-dev\include $(IncludeSwitch)midifile-master\include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)avcodec $(LibrarySwitch)avformat $(LibrarySwitch)avutil $(LibrarySwitch)swscale $(LibrarySwitch)gdi32 
ArLibs                 :=  "avcodec" "avformat" "avutil" "swscale" "gdi32" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)ffmpeg\ffmpeg-dev\lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/mingw32/bin/ar.exe rcu
CXX      := C:/mingw32/bin/g++.exe
CC       := C:/mingw32/bin/gcc.exe
CXXFLAGS :=  -O2 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/mingw32/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/midi.cpp$(ObjectSuffix) $(IntermediateDirectory)/midifile-master_src-library_Binasc.cpp$(ObjectSuffix) $(IntermediateDirectory)/midifile-master_src-library_MidiEvent.cpp$(ObjectSuffix) $(IntermediateDirectory)/midifile-master_src-library_MidiEventList.cpp$(ObjectSuffix) $(IntermediateDirectory)/midifile-master_src-library_MidiFile.cpp$(ObjectSuffix) $(IntermediateDirectory)/midifile-master_src-library_MidiMessage.cpp$(ObjectSuffix) $(IntermediateDirectory)/midifile-master_src-library_Options.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Release"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Release"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Data/Workspace/Workspace/syn2midi/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix)main.cpp

$(IntermediateDirectory)/midi.cpp$(ObjectSuffix): midi.cpp $(IntermediateDirectory)/midi.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Data/Workspace/Workspace/syn2midi/midi.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/midi.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/midi.cpp$(DependSuffix): midi.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/midi.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/midi.cpp$(DependSuffix) -MM midi.cpp

$(IntermediateDirectory)/midi.cpp$(PreprocessSuffix): midi.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/midi.cpp$(PreprocessSuffix)midi.cpp

$(IntermediateDirectory)/midifile-master_src-library_Binasc.cpp$(ObjectSuffix): midifile-master/src-library/Binasc.cpp $(IntermediateDirectory)/midifile-master_src-library_Binasc.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Data/Workspace/Workspace/syn2midi/midifile-master/src-library/Binasc.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/midifile-master_src-library_Binasc.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/midifile-master_src-library_Binasc.cpp$(DependSuffix): midifile-master/src-library/Binasc.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/midifile-master_src-library_Binasc.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/midifile-master_src-library_Binasc.cpp$(DependSuffix) -MM midifile-master/src-library/Binasc.cpp

$(IntermediateDirectory)/midifile-master_src-library_Binasc.cpp$(PreprocessSuffix): midifile-master/src-library/Binasc.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/midifile-master_src-library_Binasc.cpp$(PreprocessSuffix)midifile-master/src-library/Binasc.cpp

$(IntermediateDirectory)/midifile-master_src-library_MidiEvent.cpp$(ObjectSuffix): midifile-master/src-library/MidiEvent.cpp $(IntermediateDirectory)/midifile-master_src-library_MidiEvent.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Data/Workspace/Workspace/syn2midi/midifile-master/src-library/MidiEvent.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/midifile-master_src-library_MidiEvent.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/midifile-master_src-library_MidiEvent.cpp$(DependSuffix): midifile-master/src-library/MidiEvent.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/midifile-master_src-library_MidiEvent.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/midifile-master_src-library_MidiEvent.cpp$(DependSuffix) -MM midifile-master/src-library/MidiEvent.cpp

$(IntermediateDirectory)/midifile-master_src-library_MidiEvent.cpp$(PreprocessSuffix): midifile-master/src-library/MidiEvent.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/midifile-master_src-library_MidiEvent.cpp$(PreprocessSuffix)midifile-master/src-library/MidiEvent.cpp

$(IntermediateDirectory)/midifile-master_src-library_MidiEventList.cpp$(ObjectSuffix): midifile-master/src-library/MidiEventList.cpp $(IntermediateDirectory)/midifile-master_src-library_MidiEventList.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Data/Workspace/Workspace/syn2midi/midifile-master/src-library/MidiEventList.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/midifile-master_src-library_MidiEventList.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/midifile-master_src-library_MidiEventList.cpp$(DependSuffix): midifile-master/src-library/MidiEventList.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/midifile-master_src-library_MidiEventList.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/midifile-master_src-library_MidiEventList.cpp$(DependSuffix) -MM midifile-master/src-library/MidiEventList.cpp

$(IntermediateDirectory)/midifile-master_src-library_MidiEventList.cpp$(PreprocessSuffix): midifile-master/src-library/MidiEventList.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/midifile-master_src-library_MidiEventList.cpp$(PreprocessSuffix)midifile-master/src-library/MidiEventList.cpp

$(IntermediateDirectory)/midifile-master_src-library_MidiFile.cpp$(ObjectSuffix): midifile-master/src-library/MidiFile.cpp $(IntermediateDirectory)/midifile-master_src-library_MidiFile.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Data/Workspace/Workspace/syn2midi/midifile-master/src-library/MidiFile.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/midifile-master_src-library_MidiFile.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/midifile-master_src-library_MidiFile.cpp$(DependSuffix): midifile-master/src-library/MidiFile.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/midifile-master_src-library_MidiFile.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/midifile-master_src-library_MidiFile.cpp$(DependSuffix) -MM midifile-master/src-library/MidiFile.cpp

$(IntermediateDirectory)/midifile-master_src-library_MidiFile.cpp$(PreprocessSuffix): midifile-master/src-library/MidiFile.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/midifile-master_src-library_MidiFile.cpp$(PreprocessSuffix)midifile-master/src-library/MidiFile.cpp

$(IntermediateDirectory)/midifile-master_src-library_MidiMessage.cpp$(ObjectSuffix): midifile-master/src-library/MidiMessage.cpp $(IntermediateDirectory)/midifile-master_src-library_MidiMessage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Data/Workspace/Workspace/syn2midi/midifile-master/src-library/MidiMessage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/midifile-master_src-library_MidiMessage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/midifile-master_src-library_MidiMessage.cpp$(DependSuffix): midifile-master/src-library/MidiMessage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/midifile-master_src-library_MidiMessage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/midifile-master_src-library_MidiMessage.cpp$(DependSuffix) -MM midifile-master/src-library/MidiMessage.cpp

$(IntermediateDirectory)/midifile-master_src-library_MidiMessage.cpp$(PreprocessSuffix): midifile-master/src-library/MidiMessage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/midifile-master_src-library_MidiMessage.cpp$(PreprocessSuffix)midifile-master/src-library/MidiMessage.cpp

$(IntermediateDirectory)/midifile-master_src-library_Options.cpp$(ObjectSuffix): midifile-master/src-library/Options.cpp $(IntermediateDirectory)/midifile-master_src-library_Options.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Data/Workspace/Workspace/syn2midi/midifile-master/src-library/Options.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/midifile-master_src-library_Options.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/midifile-master_src-library_Options.cpp$(DependSuffix): midifile-master/src-library/Options.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/midifile-master_src-library_Options.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/midifile-master_src-library_Options.cpp$(DependSuffix) -MM midifile-master/src-library/Options.cpp

$(IntermediateDirectory)/midifile-master_src-library_Options.cpp$(PreprocessSuffix): midifile-master/src-library/Options.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/midifile-master_src-library_Options.cpp$(PreprocessSuffix)midifile-master/src-library/Options.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


