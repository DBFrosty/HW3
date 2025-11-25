#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include "config.h"
#include "problem.h"

class IExporter {
  public:
    virtual void writeHeader() = 0;
    virtual void writeProblems(const std::vector<Problem*>& problems) = 0;
    virtual void writeEnd() = 0;
    virtual ~IExporter() = default;
  protected:
    std::ofstream outFile;
    Config config;
};

class SimpleExporter : public IExporter {
  public:
    SimpleExporter(const Config& cfg);
    ~SimpleExporter();
    
    void writeHeader() override;
    void writeProblems(const std::vector<Problem*>& problems) override;
    void writeEnd() override;
};

class SimpleExporterWithKeySupport : public SimpleExporter {
  public:
    SimpleExporterWithKeySupport(const Config& cfg) : SimpleExporter(cfg) {}//pass construction to parent constructor
    
    void writeProblems(const std::vector<Problem*>& problems) override;
};

class FancyExporter : public IExporter {
  public:
    FancyExporter(const Config& cfg);
    ~FancyExporter();
    
    void writeHeader() override;
    void writeProblems(const std::vector<Problem*>& problems) override;
    void writeEnd() override;
};