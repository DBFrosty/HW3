#include <ranges>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>
#include <map>
#include <set>
#include "problem.h"
#include "test_validate.h"
#include "test_generator.h"

// ****************************************************************************
// Configuration details

// Title to be printed at the beginning of the test
std::string TITLE = "Arithmetic Test";

// Source file for problem bank
std::string BANK = "arithmetic_problems.tex";

// Filename for the created test
std::string FILENAME = "simple_test.tex";

// Constraints on the problem choice.
int NUM_PROBLEMS = 20; // The test must have 20 problems.
int MIN_TOPIC = 3; // Each topic must be covered 
int MAX_TOPIC = 7; // by 3-7 problems.
int MIN_DIFFICULTY = 65; // Total difficulty (using the difficulty defined 
int MAX_DIFFICULTY = 75; // in the problem bank) must be 65-75.

// tex files to include in the test file
std::string TEX_HEADER = "simple_tex_header.tex";
std::string CONTENT_HEADER = "simple_content_header.tex";

// ****************************************************************************


int main() {
  ProblemLoader* loader = new ProblemV1Loader();
  Validate* validator = new Validate();
  SelectionMethod* selectionAlgo = new RandomSelection();
  TestGenerator* generator = new TestGenerator(validator, selectionAlgo);
  std::vector<Constraint> constraints;
  constraints.push_back(Constraint(MIN_TOPIC, MAX_TOPIC, new CTopic("Addition")));
  constraints.push_back(Constraint(MIN_DIFFICULTY, MAX_DIFFICULTY, new CDifficulty()));
  
  // Read in problem list and convert to Problem objects, using loader
  std::vector<Problem*> bank = loader->problemList(BANK);
  
  // Generate test from bank using validator within generator
  std::vector<Problem*> test = generator->generateTest(bank, constraints, NUM_PROBLEMS);

  // Open the file to write the test to
  std::ofstream outputFile(FILENAME); 
  if (!outputFile.is_open()) {
      std::cerr << "Unable to open file." << std::endl;
      return 1;
  }

  // Write the header to the file
  outputFile << "\\input{" << TEX_HEADER << "}\n";
  outputFile << "\\newcommand{\\testtitle}{" << TITLE << "}\n";
  outputFile << "\\input{" << CONTENT_HEADER << "}\n";

  // Write the problems to the file
  for (Problem* problem : test) {
      outputFile << "\\item " << problem->getQuestion() << "\n";
  }

  // End the file
  outputFile << "\\end{enumerate}\n\\end{document}";
  outputFile.close();
}