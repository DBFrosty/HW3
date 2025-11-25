#include <ranges>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>
#include <map>
#include <set>
#include "problem.h"
#include "loader.h"
#include "validate.h"
#include "test_generator.h"
#include "constraint.h"
#include "config.h"
#include "exporter.h"

// ****************************************************************************
// Configuration details

// Title to be printed at the beginning of the test
std::string TITLE = "Arithmetic Test";

// Source file for problem bank
std::string BANK = "arithmetic_problems.tex";

// Filename for the created test
std::string FILENAME = "simple_test.tex";

// tex files to include in the test file
std::string TEX_HEADER = "questions_tex_header.tex";
std::string CONTENT_HEADER = "simple_content_header.tex";
int NUM_PROBLEMS = 20; // The test must have 20 problems.

// Constraints on the problem choice.
int MIN_TOPIC = 3; // Each topic must be covered 
int MAX_TOPIC = 7; // by 3-7 problems.
int MIN_DIFFICULTY = 65; // Total difficulty (using the difficulty defined 
int MAX_DIFFICULTY = 75; // in the problem bank) must be 65-75.


// ****************************************************************************



int main() {
  // Set config
  Config config;
  config.TITLE = TITLE;
  config.BANK = BANK;
  config.FILENAME = FILENAME;
  config.TEX_HEADER = TEX_HEADER;
  config.CONTENT_HEADER = CONTENT_HEADER;
  config.NUM_PROBLEMS = NUM_PROBLEMS;
  
  // Load problems and create generator
  ProblemLoader* loader = new ProblemV1Loader();
  
  Validate* validator = new Validate();
  SelectionMethod* selectionAlgo = new RandomSelection();
  TestGenerator* generator = new TestGenerator(validator, selectionAlgo);
  
  // Add constraints
  std::vector<Constraint*> constraints;
  constraints.push_back(new CAddition(MIN_TOPIC, MAX_TOPIC));
  constraints.push_back(new CSubtraction(MIN_TOPIC, MAX_TOPIC));
  constraints.push_back(new CMultiplication(MIN_TOPIC, MAX_TOPIC));
  constraints.push_back(new CDivision(MIN_TOPIC, MAX_TOPIC));
  constraints.push_back(new CDifficulty(MIN_DIFFICULTY, MAX_DIFFICULTY));
  
  // Read in problem list and convert to Problem objects, using loader
  std::vector<Problem*> bank = loader->problemList(config.BANK);
  
  // Generate test from bank using validator within generator
  std::vector<Problem*> test = generator->generateTest(bank, constraints, config.NUM_PROBLEMS);

  // Open the file to write the test to
  //IExporter* exporter = new SimpleExporter(config);
  IExporter* exporter = new SimpleExporterWithKeySupport(config);

  // Write the header to the file
  exporter->writeHeader();

  // Write the problems to the file
  exporter->writeProblems(test);

  // End the file
  exporter->writeEnd();
  
  // Clean up
  delete exporter;
}