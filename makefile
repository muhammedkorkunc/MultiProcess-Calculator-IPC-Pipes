# Derleyici tanımlaması
CC = gcc

# Çıktı programları
OUTPUTS = calculator addition subtraction multiplication division saver

# Varsayılan hedef
all: $(OUTPUTS)

# Ana hesaplayıcı programı
calculator: calculator.c
	$(CC) -o $@ $^

# Toplama işlemi
addition: addition.c
	$(CC) -o $@ $^

# Çıkarma işlemi
subtraction: subtraction.c
	$(CC) -o $@ $^

# Çarpma işlemi
multiplication: multiplication.c
	$(CC) -o $@ $^

# Bölme işlemi
division: division.c
	$(CC) -o $@ $^

# Sonuçları kaydetme işlemi
saver: saver.c
	$(CC) -o $@ $^

# Temizlik işlemi
clean:
	rm -f $(OUTPUTS) *.o
