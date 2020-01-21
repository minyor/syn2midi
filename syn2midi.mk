##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=syn2midi
ConfigurationName      :=Debug
WorkspacePath          :=C:/Users/daniel.latimer/Documents/codelite3
ProjectPath            :=C:/Users/daniel.latimer/src/syn2midi
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=daniel.latimer
Date                   :=02/01/2020
CodeLitePath           :="C:/Program Files/CodeLite"
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
OutputFile             :=$(IntermediateDirectory)/../bin/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="syn2midi.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/MinGW/bin/windres.exe
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
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/midifile-master_src-library_MidiMessage.cpp$(ObjectSuffix) $(IntermediateDirectory)/midifile-master_src-library_Options.cpp$(ObjectSuffix) $(IntermediateDirectory)/midifile-master_src-library_MidiEventList.cpp$(ObjectSuffix) $(IntermediateDirectory)/midifile-master_src-library_MidiEvent.cpp$(ObjectSuffix) $(IntermediateDirectory)/midi.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/report.cpp$(ObjectSuffix) $(IntermediateDirectory)/midifile-master_src-library_MidiFile.cpp$(ObjectSuffix) $(IntermediateDirectory)/midifile-master_src-library_Binasc.cpp$(ObjectSuffix) 



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
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/midifile-master_src-library_MidiMessage.cpp$(ObjectSuffix): midifile-master/src-library/MidiMessage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/midifile-master_src-library_MidiMessage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/midifile-master_src-library_MidiMessage.cpp$(DependSuffix) -MM midifile-master/src-library/MidiMessage.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/daniel.latimer/src/syn2midi/midifile-master/src-library/MidiMessage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/midifile-master_src-library_MidiMessage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/midifile-master_src-library_MidiMessage.cpp$(PreprocessSuffix): midifile-master/src-library/MidiMessage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/midifile-master_src-library_MidiMessage.cpp$(PreprocessSuffix) midifile-master/src-library/MidiMessage.cpp

$(IntermediateDirectory)/midifile-master_src-library_Options.cpp$(ObjectSuffix): midifile-master/src-library/Options.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/midifile-master_src-library_Options.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/midifile-master_src-library_Options.cpp$(DependSuffix) -MM midifile-master/src-library/Options.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/daniel.latimer/src/syn2midi/midifile-master/src-library/Options.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/midifile-master_src-library_Options.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/midifile-master_src-library_Options.cpp$(PreprocessSuffix): midifile-master/src-library/Options.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/midifile-master_src-library_Options.cpp$(PreprocessSuffix) midifile-master/src-library/Options.cpp

$(IntermediateDirectory)/midifile-master_src-library_MidiEventList.cpp$(ObjectSuffix): midifile-master/src-library/MidiEventList.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/midifile-master_src-library_MidiEventList.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/midifile-master_src-library_MidiEventList.cpp$(DependSuffix) -MM midifile-master/src-library/MidiEventList.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/daniel.latimer/src/syn2midi/midifile-master/src-library/MidiEventList.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/midifile-master_src-library_MidiEventList.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/midifile-master_src-library_MidiEventList.cpp$(PreprocessSuffix): midifile-master/src-library/MidiEventList.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/midifile-master_src-library_MidiEventList.cpp$(PreprocessSuffix) midifile-master/src-library/MidiEventList.cpp

$(IntermediateDirectory)/midifile-master_src-library_MidiEvent.cpp$(ObjectSuffix): midifile-master/src-library/MidiEvent.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/midifile-master_src-library_MidiEvent.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/midifile-master_src-library_MidiEvent.cpp$(DependSuffix) -MM midifile-master/src-library/MidiEvent.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/daniel.latimer/src/syn2midi/midifile-master/src-library/MidiEvent.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/midifile-master_src-library_MidiEvent.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/midifile-master_src-library_MidiEvent.cpp$(PreprocessSuffix): midifile-master/src-library/MidiEvent.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/midifile-master_src-library_MidiEvent.cpp$(PreprocessSuffix) midifile-master/src-library/MidiEvent.cpp

$(IntermediateDirectory)/midi.cpp$(ObjectSuffix): midi.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/midi.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/midi.cpp$(DependSuffix) -MM midi.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/daniel.latimer/src/syn2midi/midi.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/midi.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/midi.cpp$(PreprocessSuffix): midi.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/midi.cpp$(PreprocessSuffix) midi.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/daniel.latimer/src/syn2midi/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/report.cpp$(ObjectSuffix): report.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/report.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/report.cpp$(DependSuffix) -MM report.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/daniel.latimer/src/syn2midi/report.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/report.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/report.cpp$(PreprocessSuffix): report.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/report.cpp$(PreprocessSuffix) report.cpp

$(IntermediateDirectory)/midifile-master_src-library_MidiFile.cpp$(ObjectSuffix): midifile-master/src-library/MidiFile.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/midifile-master_src-library_MidiFile.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/midifile-master_src-library_MidiFile.cpp$(DependSuffix) -MM midifile-master/src-library/MidiFile.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/daniel.latimer/src/syn2midi/midifile-master/src-library/MidiFile.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/midifile-master_src-library_MidiFile.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/midifile-master_src-library_MidiFile.cpp$(PreprocessSuffix): midifile-master/src-library/MidiFile.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/midifile-master_src-library_MidiFile.cpp$(PreprocessSuffix) midifile-master/src-library/MidiFile.cpp

$(IntermediateDirectory)/midifile-master_src-library_Binasc.cpp$(ObjectSuffix): midifile-master/src-library/Binasc.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/midifile-master_src-library_Binasc.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/midifile-master_src-library_Binasc.cpp$(DependSuffix) -MM midifile-master/src-library/Binasc.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/daniel.latimer/src/syn2midi/midifile-master/src-library/Binasc.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/midifile-master_src-library_Binasc.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/midifile-master_src-library_Binasc.cpp$(PreprocessSuffix): midifile-master/src-library/Binasc.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/midifile-master_src-library_Binasc.cpp$(PreprocessSuffix) midifile-master/src-library/Binasc.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


