# Name des ausfuehrbaren Programms
EXE = huffmanOUT

# Pfad zu den Quell-Dateien
SRC_PATH = .
SRC_FILES = $(SRC_PATH)/*.c $(SRC_PATH)/*.h

# Übergeordneter Ordner der zur Ausgabe dient
OUT_PATH = ..

# Compiler-Optionen
GCC_OPTION = -O3

# Konfiguration fuer Doxygen
DOXYGEN      = doxygen $(OUT_PATH)/ppr_doxygen.cfg
DOXYGEN_PATH = $(OUT_PATH)/doxygen
DOXYGEN_FILE = /html/index.html

# Pfad fuer Test-Dateien
TEST_PATH = $(OUT_PATH)/testfiles

# ----------------------------------------------------------------------------
# Das erste Ziel ist das Standardziel.
build : $(EXE)

# ----------------------------------------------------------------------------
# Regel zum Testen des aktuellen Programms
test : build test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12

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
	gcc $(GCC_OPTION) $(SRC_PATH)/*.c -o $(OUT_PATH)/$(EXE)

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
	@echo "1. Testfall (Quelle und Ziel nach compress/decompress identisch)"
	@echo ========================================================
	rm -f $(TEST_PATH)/out.txt
	rm -f $(TEST_PATH)/outin.txt
	-$(OUT_PATH)/$(EXE) -c -o $(TEST_PATH)/out.txt $(TEST_PATH)/01_in.txt
	-$(OUT_PATH)/$(EXE) -d -o $(TEST_PATH)/outin.txt $(TEST_PATH)/out.txt
	-diff $(TEST_PATH)/outin.txt $(TEST_PATH)/01_in.txt

test2 :
	@echo .
	@echo ========================================================
	@echo "2. Testfall (Quelle und Ziel nach compress/decompress identisch)"
	@echo ========================================================
	rm -f $(TEST_PATH)/out.txt
	rm -f $(TEST_PATH)/outin.txt
	-$(OUT_PATH)/$(EXE) -c -o $(TEST_PATH)/out.txt $(TEST_PATH)/02_ab.txt
	-$(OUT_PATH)/$(EXE) -d -o $(TEST_PATH)/outin.txt $(TEST_PATH)/out.txt
	-diff $(TEST_PATH)/outin.txt $(TEST_PATH)/02_ab.txt

test3 :
	@echo .
	@echo ========================================================
	@echo "3. Testfall (Quelle und Ziel nach compress/decompress identisch)"
	@echo ========================================================
	rm -f $(TEST_PATH)/out.txt
	rm -f $(TEST_PATH)/outin.txt
	-$(OUT_PATH)/$(EXE) -c -o $(TEST_PATH)/out.txt $(TEST_PATH)/03_leere.txt
	-$(OUT_PATH)/$(EXE) -d -o $(TEST_PATH)/outin.txt $(TEST_PATH)/out.txt
	-diff $(TEST_PATH)/outin.txt $(TEST_PATH)/03_leere.txt

test4 :
	@echo .
	@echo ========================================================
	@echo "4. Testfall (Quelle und Ziel nach compress/decompress identisch)"
	@echo ========================================================
	rm -f $(TEST_PATH)/out.txt
	rm -f $(TEST_PATH)/outin.txt
	-$(OUT_PATH)/$(EXE) -c -o $(TEST_PATH)/out.txt $(TEST_PATH)/04_1Byte.txt
	-$(OUT_PATH)/$(EXE) -d -o $(TEST_PATH)/outin.txt $(TEST_PATH)/out.txt
	-diff $(TEST_PATH)/outin.txt $(TEST_PATH)/04_1Byte.txt

test5 :
	@echo .
	@echo ========================================================
	@echo "5. Testfall (Quelle und Ziel nach compress/decompress identisch)"
	@echo ========================================================
	rm -f $(TEST_PATH)/out.txt
	rm -f $(TEST_PATH)/outin.txt
	-$(OUT_PATH)/$(EXE) -c -o $(TEST_PATH)/out.txt $(TEST_PATH)/05_0-255.txt
	-$(OUT_PATH)/$(EXE) -d -o $(TEST_PATH)/outin.txt $(TEST_PATH)/out.txt
	-diff $(TEST_PATH)/outin.txt $(TEST_PATH)/05_0-255.txt

test6 :
	@echo .
	@echo ========================================================
	@echo "6. Testfall (Quelle und Ziel nach compress/decompress identisch)"
	@echo ========================================================
	rm -f $(TEST_PATH)/out.txt
	rm -f $(TEST_PATH)/outin.txt
	-$(OUT_PATH)/$(EXE) -c -o $(TEST_PATH)/out.txt $(TEST_PATH)/06_8Nutzbits.txt
	-$(OUT_PATH)/$(EXE) -d -o $(TEST_PATH)/outin.txt $(TEST_PATH)/out.txt
	-diff $(TEST_PATH)/outin.txt $(TEST_PATH)/06_8Nutzbits.txt

test7 :
	@echo .
	@echo ========================================================
	@echo "7. Testfall (Quelle und Ziel nach compress/decompress identisch)"
	@echo ========================================================
	rm -f $(TEST_PATH)/out.txt
	rm -f $(TEST_PATH)/outin.txt
	-$(OUT_PATH)/$(EXE) -c -o $(TEST_PATH)/out.txt $(TEST_PATH)/07_in8Bits.txt
	-$(OUT_PATH)/$(EXE) -d -o $(TEST_PATH)/outin.txt $(TEST_PATH)/out.txt
	-diff $(TEST_PATH)/outin.txt $(TEST_PATH)/07_in8Bits.txt


test8 :
	@echo .
	@echo ========================================================
	@echo "8. Testfall (Quelle und Ziel nach compress/decompress identisch)"
	@echo ========================================================
	rm -f $(TEST_PATH)/out.txt
	rm -f $(TEST_PATH)/outin.txt
	-$(OUT_PATH)/$(EXE) -c -o $(TEST_PATH)/out.txt $(TEST_PATH)/08_splint.bin
	-$(OUT_PATH)/$(EXE) -d -o $(TEST_PATH)/outin.bin $(TEST_PATH)/out.txt
	-diff $(TEST_PATH)/outin.bin $(TEST_PATH)/08_splint.bin

test9 :
	@echo .
	@echo ========================================================
	@echo "9. Testfall (Quelle und Ziel nach compress/decompress identisch)"
	@echo ========================================================
	rm -f $(TEST_PATH)/out.txt
	rm -f $(TEST_PATH)/outin.txt
	-$(OUT_PATH)/$(EXE) -c -o $(TEST_PATH)/out.txt $(TEST_PATH)/09_LordOfTheRings.txt
	-$(OUT_PATH)/$(EXE) -d -o $(TEST_PATH)/outin.txt $(TEST_PATH)/out.txt
	-diff $(TEST_PATH)/outin.txt $(TEST_PATH)/09_LordOfTheRings.txt

test10 :
	@echo .
	@echo ========================================================
	@echo "10. Testfall (Quelle und Ziel nach compress/decompress identisch)"
	@echo ========================================================
	rm -f $(TEST_PATH)/out.txt
	rm -f $(TEST_PATH)/outin.txt
	-$(OUT_PATH)/$(EXE) -c -o $(TEST_PATH)/out.txt $(TEST_PATH)/10_in.txt
	-$(OUT_PATH)/$(EXE) -d -o $(TEST_PATH)/outin.txt $(TEST_PATH)/out.txt
	-diff $(TEST_PATH)/outin.txt $(TEST_PATH)/10_in.txt

test11 :
	@echo .
	@echo ========================================================
	@echo "11. Testfall (Quelle und Ziel nach compress/decompress identisch)"
	@echo ========================================================
	rm -f $(TEST_PATH)/out.txt
	rm -f $(TEST_PATH)/outin.txt
	-$(OUT_PATH)/$(EXE) -c -o $(TEST_PATH)/out.txt $(TEST_PATH)/PPR_P_Blatt09.pdf
	-$(OUT_PATH)/$(EXE) -d -o $(TEST_PATH)/outin.pdf $(TEST_PATH)/out.txt
	-diff $(TEST_PATH)/outin.pdf $(TEST_PATH)/PPR_P_Blatt09.pdf

test12 :
	@echo .
	@echo ========================================================
	@echo "12. Testfall (Quelle und Ziel nach compress/decompress identisch)"
	@echo ========================================================
	rm -f $(TEST_PATH)/out.txt
	rm -f $(TEST_PATH)/outin.txt
	-$(OUT_PATH)/$(EXE) -c -o $(TEST_PATH)/out.txt $(TEST_PATH)/Sonderzeichen.txt
	-$(OUT_PATH)/$(EXE) -d -o $(TEST_PATH)/outin.txt $(TEST_PATH)/out.txt
	-diff $(TEST_PATH)/outin.txt $(TEST_PATH)/Sonderzeichen.txt
