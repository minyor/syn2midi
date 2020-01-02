
#include "buffer.h"
#include <fstream>

#include "report.h"

using namespace std;

void printColor(ofstream &reportFile, BufferRGBA &color, int size) {
    reportFile << "<div class=\"color-report-item\"><span class=\"color-square\" style=\"background-color: #"
    << color.toWebColor() 
    << "\"></span> 0x" << color.toWebColor()
    << " - " << size << " matched pixel shades"
    << "</div>" << endl;
}

void printPixel(ofstream &reportFile, BufferRGBA &color, int &count) {
    reportFile << "<div class=\"color-report-item pixel\"><span class=\"color-square\" style=\"background-color: #"
    << color.toWebColor() 
    << "\"></span> 0x" << color.toWebColor()
    << " - " << count << " pixels"
    << "</div>" << endl;
}

void printPixelGroupSubHeading(ofstream &reportFile, string subHeading) {
    reportFile << "<h3 class=\"report-subheader\">Pixels Matched To " << subHeading << " Note Colors:</h3>" << endl;
}

Report::Report() {
    
}

void Report::recordUnfitColor(BufferRGBA &color) {
    unfitColorMap[color] = (unfitColorMap.count(color) == 0 ? 0 : unfitColorMap[color]) + 1;
}
    
void Report::recordMatchedColor(BufferRGBA &fittestColor, BufferRGBA &color) {
    fittestColorMap[fittestColor][color] = (fittestColorMap[fittestColor].count(color) == 0 ? 0 : fittestColorMap[fittestColor][color]) + 1;
}
    
void Report::print(BufferRGBA colors[], int colorSize) {
    ofstream reportFile;
    reportFile.open("report.html");
    reportFile << "<html>" << endl;
    reportFile << "<head>" << endl;
    reportFile << "<style>" << endl;
    reportFile << "* {" << endl;
    reportFile << "	font-family: Arial, Helvetica, sans-serif;" << endl;
    reportFile << "}" << endl;
    reportFile << "" << endl;
    reportFile << "body {" << endl;
    reportFile << "	display: flex;" << endl;
    reportFile << "	align-items: stretch;" << endl;
    reportFile << "	justify-content: center;" << endl;
    reportFile << "}" << endl;
    reportFile << "" << endl;
    reportFile << ".report {" << endl;
    reportFile << "	background-color: 66ff66;" << endl;
    reportFile << "	margin: 30 30;" << endl;
    reportFile << "	padding: 30 30;" << endl;
    reportFile << "	width: 70%;" << endl;
    reportFile << " display: flex;" << endl;
    reportFile << " flex-direction: column;" << endl;
    reportFile << "}" << endl;
    reportFile << "" << endl;
    
    reportFile << ".pixel-container {" << endl;
    reportFile << "	display: flex;" << endl;
    reportFile << "	flex-wrap: wrap;" << endl;
    reportFile << " margin-bottom: 20px;" << endl;
    reportFile << "}" << endl;
    
    reportFile << "" << endl;
    reportFile << ".report-header {" << endl;
    reportFile << "	align-self: center;" << endl;
    reportFile << "	margin: 0 0 30 0;" << endl;
    reportFile << "}" << endl;
    reportFile << "" << endl;
    reportFile << ".report-subheader {" << endl;
    reportFile << "	margin: 0 0 10 0;" << endl;
    reportFile << "}" << endl;
    reportFile << "" << endl;
    reportFile << ".color-report-item {" << endl;
    reportFile << "	font-family: \"Courier New\", Courier, monospace;" << endl;
    reportFile << "	height: 25px;" << endl;
    reportFile << "	display: flex;" << endl;
    reportFile << "	align-items: center;" << endl;
    reportFile << "}" << endl;
    reportFile << "" << endl;
    reportFile << ".pixel {" << endl;
    reportFile << "	background-color: white;" << endl;
    reportFile << "	margin: 5px 5px 0 0;" << endl;
    reportFile << "	padding: 5px 10px;" << endl;
    reportFile << "	border-radius: 10px;" << endl;
    reportFile << "}" << endl;
    reportFile << "" << endl;
    reportFile << ".color-square {" << endl;
    reportFile << "	width: 15px; " << endl;
    reportFile << "	height: 15px; " << endl;
    reportFile << "	display: inline-block;" << endl;
    reportFile << "	margin-right: 5px;" << endl;
    reportFile << "}" << endl;
    reportFile << "</style>" << endl;
    reportFile << "</head>" << endl;
    reportFile << "<body>" << endl;
    reportFile << "<div class=\"report\">" << endl;
    reportFile << "<h1 class=\"report-header\">SynToMidi Report</h1>" << endl;
    printPixelGroupSubHeading(reportFile, "Left Hand");
    
    
    for(int i = 0; i < colorSize; i++) {
        if (i == 4)
            printPixelGroupSubHeading(reportFile, "Right Hand");
        if (i == 8) {
            printPixelGroupSubHeading(reportFile, "Unpressed");
        }
        
        BufferRGBA color = colors[i];
        map<BufferRGBA, int> matchedPixelShades = fittestColorMap[color];
        if (matchedPixelShades.size() == 0) {
            continue;
        }
        
        printColor(reportFile, color, matchedPixelShades.size());
        reportFile << "<div class=\"pixel-container\">" << endl;
        for (pair<BufferRGBA, int> pixel : matchedPixelShades)
        {
            printPixel(reportFile, pixel.first, pixel.second);
        }
        reportFile << "</div>" << endl;
    }
    
    reportFile << "<h3 class=\"report-subheader\">Unknown Colors:</h3>" << endl;        
    for (pair<BufferRGBA, int> element : unfitColorMap)
    {
        printPixel(reportFile, element.first, element.second);
    }
    
    reportFile << "</div>" << endl;
    reportFile << "</body>" << endl;
    reportFile << "</html>" << endl;
    reportFile << "" << endl;
    reportFile.close();        
}