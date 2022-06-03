# C++ compiler and linker
CXX = g++

# Flags to pass to the C++ compiler
CXXFLAGS = -g -Werror -Wall -Wextra -pthread -c

# List of external libraries for testing
TESTLIBS = -lgtest_main -lgtest

# Flags to pass to the C++ linker for testing
TESTLDFLAGS = $(TESTLIBS) -pthread

# Directory for the source files
SRCDIR = .

# Output directories for the build process
BUILDDIR = $(SRCDIR)/build
BINDIR = $(BUILDDIR)/bin
OBJDIR = $(BUILDDIR)/obj

# Testing directory for the test files
TESTINGDIR = $(SRCDIR)/../testing

# Name of the executable to create
EXEFILE = $(BINDIR)/voting-system

# Name of the executable to create for testing
TESTEXEFILE = $(BINDIR)/unittest

# Google Test includes its own main() function
# Do not compile the project's main() function into the unit tests
MAINFILE = $(SRCDIR)/main.cpp $(SRCDIR)/main.cc

# List of unit test files to compile
TESTSRCFILES = $(wildcard $(SRCDIR)/*_unittest.cpp) $(wildcard $(SRCDIR)/*_unittest.cc)

# List of source files to compile
SRCFILES = $(filter-out $(MAINFILE) $(TESTSRCFILES), $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*.cc))

# List of object files to create
OBJFILES = $(notdir $(patsubst %.cpp,%.o,$(patsubst %.cc,%.o,$(SRCFILES)))) main.o

# List of object files to create for testing
TESTOBJFILES = $(notdir $(patsubst %.cpp,%.o,$(patsubst %.cc,%.o,$(SRCFILES)))) $(notdir $(patsubst %.cpp,%.o,$(patsubst %.cc,%.o,$(TESTSRCFILES))))

# List of phony targets
.PHONY: all clean docs $(OBJDIR) $(BINDIR)

# Default make target
all: $(EXEFILE) $(TESTEXEFILE)

# Each object file in $(OBJDIR)/ depends on the presence of the $(OBJDIR)/ directory
$(addprefix $(OBJDIR)/, $(TESTOBJFILES)): | $(OBJDIR)
$(addprefix $(OBJDIR)/, main.o): | $(OBJDIR)

# Create $(OBJDIR) and $(BINDIR)
$(OBJDIR) $(BINDIR):
	@mkdir -p $@

# Compile any file with a .cpp extension
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Compile any file with a .cc extension
$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	$(CXX) $(CXXFLAGS) $< -o $@

# Link object files into an executable
$(EXEFILE): $(addprefix $(OBJDIR)/, $(OBJFILES)) | $(BINDIR)
	$(CXX) $(addprefix $(OBJDIR)/, $(OBJFILES)) -o $@

# Link object files into an executable for testing
$(TESTEXEFILE): $(addprefix $(OBJDIR)/, $(TESTOBJFILES)) | $(BINDIR)
	$(CXX) $(TESTLDFLAGS) $(addprefix $(OBJDIR)/, $(TESTOBJFILES)) -o $@

# Remove all files generated during a build
clean:
	rm -rf $(BUILDDIR)
	rm -rf $(TESTINGDIR)/VotingSystem_AuditFile_*-*-*_*:*:*.*.txt
	rm -rf $(TESTINGDIR)/VotingSystem_MediaReport_*-*-*_*:*:*.*.txt
