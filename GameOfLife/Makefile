GTEST_DIR=googletest/googletest/
GTEST_CFLAGS=-I$(GTEST_DIR)/include -I$(GTEST_DIR) -pthread
GTEST_SRC=$(GTEST_DIR)/src/gtest-all.cc
GTEST_OBJECTS=$(GTEST_DIR)/src/gtest-all.o

OBJDIR:=obj
SRCDIR:=src
TSTDIR:=test

SOURCES:=$(shell find $(SRCDIR) -name \*.cc)
DEPENDS:=$(foreach file,$(SOURCES:.cc=.d),$(shell echo "$(OBJDIR)/$(file)"))
OBJECTS:=$(DEPENDS:.d=.o)

TEST_SOURCES:=$(shell find $(TSTDIR) -name \*.cc)
TEST_DEPENDS:=$(foreach file,$(TEST_SOURCES:.cc=.d),$(shell echo "$(OBJDIR)/$(file)"))
TEST_OBJECTS:=$(TEST_DEPENDS:.d=.o)

#WARNINGS = -Wall -Wextra -Wzero-as-null-pointer-constant -Wformat=2 -Wold-style-cast -Wmissing-include-dirs -Wlogical-op -Woverloaded-virtual -Wpointer-arith -Wredundant-decls
WARNINGS = -Wall -Wextra -Wformat=2 -Wold-style-cast -Wmissing-include-dirs -Wlogical-op -Woverloaded-virtual -Wpointer-arith -Wredundant-decls
CFLAGS=$(WARNINGS) -g -std=c++11 -Isrc

.PHONY: all superclean clean check_deps

all: unittest main

$(DEPENDS): $(OBJDIR)/%.d: %.cc
	@echo Computing dependencies for $<
	@mkdir -p `dirname $@`
	@$(CXX) -MM $(CFLAGS) $< | { sed 's#^[^:]*\.o[ :]*#$(OBJDIR)/$*.o $(OBJDIR)/$*.os $(OBJDIR)/$*.d : #g' ; echo "%.h:;" ; echo "" ; } > $@

$(OBJECTS): $(OBJDIR)/%.o: %.cc
	$(CXX) -c $(CFLAGS) -o $@ $<

$(TEST_DEPENDS): $(OBJDIR)/%.d: %.cc
	@echo Computing dependencies for $<
	@mkdir -p `dirname $@`
	@$(CXX) -MM $(CFLAGS) $(TEST_CFLAGS) $< | { sed 's#^[^:]*\.o[ :]*#$(OBJDIR)/$*.o $(OBJDIR)/$*.d : #g' ; echo "%.h:;" ; echo "" ; } > $@

$(TEST_OBJECTS): $(OBJDIR)/%.o: %.cc gtest
	$(CXX) -c $(CFLAGS) $(GTEST_CFLAGS) -o $@ $<

unittest: $(OBJECTS) $(TEST_OBJECTS) gtest
	g++ $(CFLAGS) $(GTEST_CFLAGS) $(GTEST_OBJECTS) $(OBJECTS) $(TEST_OBJECTS) test_main.cc -o unittest
	./unittest

main: $(OBJECTS)
	g++ $(CFLAGS) $(OBJECTS) main.cc -o main

gtest:
	[ -d googletest ] || git clone https://github.com/google/googletest.git
	g++ $(GTEST_CFLAGS) -c $(GTEST_SRC) -o $(GTEST_OBJECTS)

clean:
	rm -rf $(OBJDIR)

superclean: clean
	rm -rf googletest main unittest

-include $(DEPENDS) $(TEST_DEPENDS)
