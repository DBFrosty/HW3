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

// Variable information to be printed on the test
std::string CLASS = "Arithmetic";
std::string TERM = "Fall 2025";
std::string EXAM = "925";
std::string TIME = "Day";
std::string TITLE = "Final Exam";
std::string FORM = "A";

// Source file for problem bank
std::string BANK = "arithmetic_problems.tex";

// Filename for the created test
std::string FILENAME = "fancy_test.tex";

// tex files to include in the test file
std::string TEX_HEADER = "fancy_tex_header.tex";
std::string CONTENT_HEADER = "fancy_content_header.tex";
int NUM_PROBLEMS = 20; // The test must have 20 problems.

// Constraints on the problem choice.
int MIN_TOPIC = 3; // Each topic must be covered 
int MAX_TOPIC = 7; // by 3-7 problems.
int MIN_DIFFICULTY = 65; // Total difficulty (using the difficulty defined 
int MAX_DIFFICULTY = 75; // in the problem bank) must be 65-75.




int main() {
  // Set config
  Config config;
  config.CLASS = CLASS;
  config.TERM = TERM;
  config.EXAM = EXAM;
  config.TIME = TIME;
  config.TITLE = TITLE;
  config.FORM = FORM;
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
  IExporter* exporter = new FancyExporter(config);

  // Write the header to the file
  exporter->writeHeader();

  // Write the problems to the file
  exporter->writeProblems(test);

  // End the file
  exporter->writeEnd();
  
  delete exporter;
}