CXX = g++
CXXFLAGS = -Wall
DBGCXXFLAGS = -g -O0

#executable name
EXE = hw06

#declaration/definition of source
SRCDIR = src
SRCS = main.cpp ant.cpp critter.cpp doodlebug.cpp game_board.cpp
#turns the .cpp files into .o files -- puts the src in front of the .o files with a '/'
OBJS = $(SRCS:%.cpp=%.o)

#declaration of debug
DBGDIR = dbg
DBGOBJS = $(addprefix $(DBGDIR)/, $(OBJS))

#declaration of release
RELDIR = rel
RELOBJS = $(addprefix $(RELDIR)/, $(OBJS))

#'make all' makes all
all : release debug

#start of debug definition
$(DBGDIR)/$(EXE) : $(DBGOBJS)
	$(CXX) $(CXXFLAGS) $(DBGCXXFLAGS) -o $@ $^
$(DBGDIR)/%.o : $(SRCDIR)/%.cpp
	mkdir -p $(DBGDIR)
	$(CXX) $(CXXFLAGS) $(DBGCXXFLAGS) -c -o $@ $<
debug : $(DBGDIR)/$(EXE)

#start of release definition
$(RELDIR)/$(EXE) : $(RELOBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	# $^ is for all dependcies
$(RELDIR)/%.o : $(SRCDIR)/%.cpp
	mkdir -p $(RELDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
release : $(RELDIR)/$(EXE)

.PHONY : all clean debug release

clean :
	rm -rf $(DBGDIR) $(RELDIR)

	#tar tvf hw06.tar -- to check whats in .tar file
	#tar cvf hw06.tar src makefile -- to make tar file
