#include "exporter.h"

//SimpleExporter implementation
//constructor
SimpleExporter::SimpleExporter(const Config& cfg) {
  config = cfg;
  outFile.open(config.FILENAME);
  if (!outFile.is_open()) {
    std::cerr << "Unable to open file: " << config.FILENAME << std::endl;
  }
}
//destructor
SimpleExporter::~SimpleExporter() {
  if (outFile.is_open()) {
    outFile.close();
  }
}
//methods
void SimpleExporter::writeHeader() {
  outFile << "\\input{" << config.TEX_HEADER << "}\n";
  outFile << "\\newcommand{\\testtitle}{" << config.TITLE << "}\n";
  outFile << "\\input{" << config.CONTENT_HEADER << "}\n";
}
void SimpleExporter::writeProblems(const std::vector<Problem*>& problems) {
  for (Problem* problem : problems) {
    outFile << "\\item " << problem->getQuestion() << "\n";
  }
}
void SimpleExporter::writeEnd() {
  outFile << "\\end{enumerate}\n\\end{document}";
  outFile.flush();//make sure content is written
}

////////////////////////////////////////////////

void SimpleExporterWithKeySupport::writeProblems(const std::vector<Problem*>& problems) {
  for (Problem* problem : problems) {
    outFile << "\\item \\question{" << problem->getQuestion() << "}\n";
    outFile << "\\answer{" << problem->getAnswer() << "}\n";
  }
}

////////////////////////////////////////////////

//FancyExporter implementation
//constructor
FancyExporter::FancyExporter(const Config& cfg) {
  config = cfg;
  outFile.open(config.FILENAME);
  if (!outFile.is_open()) {
    std::cerr << "Unable to open file: " << config.FILENAME << std::endl;
  }
}
//destructor
FancyExporter::~FancyExporter() {
  if (outFile.is_open()) {
    outFile.close();
  }
}
//methods
void FancyExporter::writeHeader() {
  outFile << "\\input{" << config.TEX_HEADER << "}\n";
  // Include the manually-entered information
  outFile << "\\newcommand{\\class}{" << config.CLASS << "}\n";
  outFile << "\\newcommand{\\term}{" << config.TERM << "}\n";
  outFile << "\\newcommand{\\examno}{" << config.EXAM << "}\n";
  outFile << "\\newcommand{\\dayeve}{" << config.TIME << "}\n";
  outFile << "\\newcommand{\\formletter}{" << config.FORM << "}\n";
  outFile << "\\newcommand{\\numproblems}{" << config.NUM_PROBLEMS << " }\n";
  outFile << "\\newcommand{\\testtitle}{" << config.TITLE << "}\n";

  // Write the content header to the file
  outFile << "\\input{" << config.CONTENT_HEADER << "}\n";
}
void FancyExporter::writeProblems(const std::vector<Problem*>& problems) {
  int problem_number = 1;
  for (Problem* problem : problems) {
    if (problem_number % 2 == 1) {       // Start a new page before 
      outFile << "\\pagebreak\n\n";      // each odd-numbered problem
    } else {                             // Insert blank space before
      outFile << "\\vspace{350pt}\n\n";  // each even-numbered problem
    }
    outFile << "\\item\\begin{tabular}[t]{p{5in} p{.3in} p{.8in}}\n";
    outFile << problem->getQuestion();
    outFile << "& & \\arabic{enumi}.\\hrulefill\n\\end{tabular}\n";
    problem_number += 1;
  }
}
void FancyExporter::writeEnd() {
  outFile << "\\end{enumerate}\n\\end{document}";
  outFile.flush();
}
