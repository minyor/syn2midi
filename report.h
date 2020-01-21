#include <map>

using namespace std;

class BaseReport {
public:
    virtual void print(BufferRGBA colors[], int colorSize) = 0;
    virtual void recordUnfitColor(BufferRGBA &color) = 0;
    virtual void recordMatchedColor(BufferRGBA &fittestColor, BufferRGBA &color) = 0;
};

class DummyReport : public BaseReport {
public:
    DummyReport() {}
    void print(BufferRGBA colors[], int colorSize) {}
    void recordUnfitColor(BufferRGBA &color) {}
    void recordMatchedColor(BufferRGBA &fittestColor, BufferRGBA &color) {}
};

class Report : public BaseReport {
private:
    map<BufferRGBA, int> unfitColorMap;
    map<BufferRGBA, map<BufferRGBA, int>> fittestColorMap;
public:
    Report();
    void print(BufferRGBA colors[], int colorSize);
    void recordUnfitColor(BufferRGBA &color);
    void recordMatchedColor(BufferRGBA &fittestColor, BufferRGBA &color);

};
