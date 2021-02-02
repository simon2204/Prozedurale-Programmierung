# Name des ausfuehrbaren Programms
EXE = heap

# Pfad zu den Quell-Dateien
SRC_PATH = .
SRC_FILES = $(SRC_PATH)/*.c $(SRC_PATH)/*.h

# Compiler-Optionen
GCC_OPTION = -Ofast

# Konfiguration fuer Doxygen
DOXYGEN      = doxygen ppr_doxygen.cfg
DOXYGEN_PATH = doxygen
DOXYGEN_FILE = $(DOXYGEN_PATH)/html/index.html
DOXYGEN_DOC = Documentation

# Pfad fuer Test-Dateien
TEST_PATH = testfiles

# ----------------------------------------------------------------------------
# Das erste Ziel ist das Standardziel.
build : $(EXE)

# ----------------------------------------------------------------------------
# Regel zum Testen des aktuellen Programms
test : build test1

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
	clang $(GCC_OPTION) $(SRC_PATH)/*.c -o $(EXE)

# ----------------------------------------------------------------------------
# Erzeugung Doxygen Dokumentation
$(DOXYGEN_FILE) : $(SRC_FILES)
	$(DOXYGEN)
	ln -s $(DOXYGEN_FILE) $(DOXYGEN_DOC)

# ----------------------------------------------------------------------------
# Regel zum Loeschen aller erzeugten Dateien
clean :
	@echo ========================================================
	@echo Lösche alle abgeleiteten Dateien
	@echo --------------------------------------------------------
	rm -f $(EXE)
	rm -f -r $(DOXYGEN_PATH)
	rm -f $(ZIP_FILE)
	rm -f $(DOXYGEN_DOC)

# ----------------------------------------------------------------------------
# Regeln fuer die einzelnen Testfaelle

test1 :
	@echo .
	@echo ========================================================
	@echo "1. Testfall"
	@echo ========================================================
	-./$(EXE)
