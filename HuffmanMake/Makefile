# Name des ausfuehrbaren Programms
EXE = huffman

# Pfad zu den Quell-Dateien
SRC_PATH = .
SRC_FILES = $(SRC_PATH)/*.c $(SRC_PATH)/*.h

# Compiler-Optionen
GCC_OPTION = -O3

# Konfiguration fuer Doxygen
DOXYGEN      = doxygen ppr_doxygen.cfg
DOXYGEN_PATH = doxygen
DOXYGEN_FILE = $(DOXYGEN_PATH)/html/index.html

# Pfad fuer Test-Dateien
TEST_PATH = testfiles

# ----------------------------------------------------------------------------
# Das erste Ziel ist das Standardziel.
build : $(EXE)

# ----------------------------------------------------------------------------
# Regel zum Testen des aktuellen Programms
test : build test1 test2 test3

# ----------------------------------------------------------------------------
# Regeln zum Erzeugen des Projekts
clean_and_build : clean build
build_all : $(EXE) $(DOXYGEN_FILE)

# ----------------------------------------------------------------------------
# Erzeugung der exe-Datei aus .c- und .h-Dateien
$(EXE) : $(SRC_FILES)
	@echo ========================================================
	@echo Erzeuge $(EXE)
	@echo --------------------------------------------------------
	gcc $(GCC_OPTION) $(SRC_PATH)/*.c -o $(EXE)

# ----------------------------------------------------------------------------
# Erzeugung Doxygen Dokumentation
$(DOXYGEN_FILE) : $(SRC_FILES)
	$(DOXYGEN)

# ----------------------------------------------------------------------------
# Regel zum Loeschen aller erzeugten Dateien
clean :
	@echo ========================================================
	@echo Lösche alle abgeleiteten Dateien
	@echo --------------------------------------------------------
	rm -f $(EXE)
	rm -f -r $(DOXYGEN_PATH)
	rm -f $(ZIP_FILE)

# ----------------------------------------------------------------------------
# Regeln fuer Splint und Doxygen
# ----------------------------------------------------------------------------
# include ~/Makefile


# ----------------------------------------------------------------------------
# Regeln fuer die einzelnen Testfaelle

test1 :
	@echo .
	@echo ========================================================
	@echo "1. Testfall (alle Parameter, ausser -h)"
	@echo ========================================================
	-./$(EXE) -c -o $(TEST_PATH)/out.txt -l7 -v $(TEST_PATH)/in.txt

test2 :
	@echo .
	@echo ========================================================
	@echo "2. Testfall (Quelle und Ziel nach compress/decompress identisch)"
	@echo ========================================================
	rm -f $(TEST_PATH)/out.txt
	rm -f $(TEST_PATH)/outin.txt
	-./$(EXE) -c -o $(TEST_PATH)/out.txt $(TEST_PATH)/in.txt
	-./$(EXE) -d -o $(TEST_PATH)/outin.txt $(TEST_PATH)/out.txt
	-diff $(TEST_PATH)/outin.txt $(TEST_PATH)/in.txt

test3 :
	-diff $(TEST_PATH)/out.txt $(TEST_PATH)/in.txt
